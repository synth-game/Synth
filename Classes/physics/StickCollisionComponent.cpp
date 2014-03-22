#include <cmath>
#include <string>
#include <vector>
#include "StickCollisionComponent.h"
#include "CollisionComponent.h"
#include "core/SynthActor.h"
#include "events/ChangePositionEvent.h"
#include "events/ChangeStateEvent.h"
#include "events/InterruptMoveEvent.h"
#include "events/CollisionEvent.h"

namespace physics
{

    StickCollisionComponent::StickCollisionComponent()
	: CollisionComponent(),
	_bIsSticked(false) {
        
    }
    
    StickCollisionComponent::~StickCollisionComponent() {
        if (_pPhysicCollision != nullptr) { delete _pPhysicCollision; }
        EventDispatcher::getInstance()->removeEventListener(_pTestCollisionEventListener);
        EventDispatcher::getInstance()->removeEventListener(_pChangeStateCollision);
    }
    
    void StickCollisionComponent::onEnter() {
        CCLOG("StickCollisionComponent::onEnter STICK COLLISION COMPONENT ON ENTER");
    }
    
    void StickCollisionComponent::initListeners() {
        EventDispatcher::getInstance()->addEventListenerWithFixedPriority(EventListenerCustom::create(events::TestCollisionEvent::EVENT_NAME, CC_CALLBACK_1(StickCollisionComponent::onTestCollision, this)), 1);
        EventDispatcher::getInstance()->addEventListenerWithFixedPriority(EventListenerCustom::create(events::ChangeStateEvent::EVENT_NAME, CC_CALLBACK_1(CollisionComponent::onChangeState, this)), 1);
    }
    
    StickCollisionComponent* StickCollisionComponent::create() {
        StickCollisionComponent* pStickCollisionComponent = new StickCollisionComponent();
        if (pStickCollisionComponent != nullptr && pStickCollisionComponent->init()) {
            pStickCollisionComponent->autorelease();
            pStickCollisionComponent->_pPhysicCollision = nullptr;
            pStickCollisionComponent->_eMovingState = core::ActorState::NOT_ON_FLOOR_STATE;
            pStickCollisionComponent->_pTestCollisionEventListener = nullptr;
            pStickCollisionComponent->_pChangeStateCollision = nullptr;
        } else {
            CC_SAFE_DELETE(pStickCollisionComponent);
        }
        return pStickCollisionComponent;
    }
    
    bool StickCollisionComponent::init() {
        SynthComponent::init(CollisionComponent::COMPONENT_TYPE);
        return true;
    }
    
    void StickCollisionComponent::onTestCollision(EventCustom* pEvent) {
        events::TestCollisionEvent* pTestColEvent = static_cast<events::TestCollisionEvent*>(pEvent);
        core::SynthActor* pOwner = static_cast<core::SynthActor*>(_owner);
        core::SynthActor* pEventSource = static_cast<core::SynthActor*>(pTestColEvent->getSource());
        if (pOwner->getActorID() == pEventSource->getActorID()) {
            // initialize the computing position
            Point computingPos = pTestColEvent->getTargetPosition();
            
            // check if the component have a PhysicCollision
            if (_pPhysicCollision != nullptr) {
                ECollisionType eCollision = NO_COLLISION;
                //CCLOG("StickCollisionComponent::onTestCollision STATE = %d", _eMovingState);
                if (_eMovingState == core::ActorState::ON_FLOOR_STATE) {
                    eCollision = slopeTest(pTestColEvent, computingPos);
                } else {
                    eCollision = boundingTest(pTestColEvent, computingPos);
                }
                
                events::InterruptMoveEvent* pInterruptMovementEvent = nullptr;
                if (eCollision == VERTICAL) {
                    pInterruptMovementEvent = new events::InterruptMoveEvent(_owner, false, true, true);
                    EventDispatcher::getInstance()->dispatchEvent(pInterruptMovementEvent);
                } else if (eCollision == HORIZONTAL) {
                    pInterruptMovementEvent = new events::InterruptMoveEvent(_owner, true, false, true);
                    EventDispatcher::getInstance()->dispatchEvent(pInterruptMovementEvent);
                } else if (eCollision == BOTH) {
                    pInterruptMovementEvent = new events::InterruptMoveEvent(_owner, true, true, true);
                    EventDispatcher::getInstance()->dispatchEvent(pInterruptMovementEvent);
                }
                
                if (eCollision != NO_COLLISION) {
                    _bIsSticked = true;
                    //CCLOG("CollisionComponent::onTestCollision SEND COLLISION EVENT, ACTOR IS STICKED !");
                    events::CollisionEvent* pCollisionEvent = new events::CollisionEvent(_owner, eCollision);
                    EventDispatcher::getInstance()->dispatchEvent(pCollisionEvent);
                }
                else {
                    _bIsSticked = false;
                }
            }
            
            //check if the PhysicCollision have a LightCollision
            LightCollision* pLightCollision = _pPhysicCollision->getLightCollision();
            if (pLightCollision != nullptr) {
                Color4B aL = pLightCollision->getCurrentColor(computingPos);
            }
            
            // Change position
            if (!pTestColEvent->getCurrentPosition().equals(computingPos)) {
                //CCLOG("CollisionComponent::onTestCollision SEND CHANGE POSITION EVENT current pos %.2f, %.2f | computing pos %.2f %.2f", pTestColEvent->getCurrentPosition().x,pTestColEvent->getCurrentPosition().y, computingPos.x, computingPos.y);
                events::ChangePositionEvent* pChangePositionEvent = new events::ChangePositionEvent(_owner, computingPos);
                EventDispatcher::getInstance()->dispatchEvent(pChangePositionEvent);
            }
            
        }
    }
    
    ECollisionType StickCollisionComponent::boundingTest(events::TestCollisionEvent* pInitiatorEvent, Point& resPosition) {
        //CCLOG("StickCollisionComponent::boundingTest");
        
        if (_bIsSticked) {
            //CCLOG("StickCollisionComponent::boundingTest : STICKED SO BYPASS BOUNDING TEST COLLISION");
            _eMovingState = core::ActorState::NOT_ON_FLOOR_STATE;
            events::ChangeStateEvent* pChangeStateEvent = new events::ChangeStateEvent(_owner, _eMovingState);
            EventDispatcher::getInstance()->dispatchEvent(pChangeStateEvent);
            return NO_COLLISION;
        }
        
        ECollisionType eRet = NO_COLLISION;
        core::ActorState nextState = core::ActorState::NOT_ON_FLOOR_STATE;
        
        // build position-target vector
        Point currentPosition = Point(floor(pInitiatorEvent->getCurrentPosition().x), floor(pInitiatorEvent->getCurrentPosition().y));
        Point targetPosition = Point(floor(pInitiatorEvent->getTargetPosition().x), floor(pInitiatorEvent->getTargetPosition().y));
        Point movementDir = targetPosition - currentPosition;
        Size halfSize = pInitiatorEvent->getSize()/2.f;
        Size quarterSize = pInitiatorEvent->getSize()/4.f;
        float fMovementLength;
        float fBigMovementLength;
        Point movementStep;
        bool bIsOnGround = false;
        
        bool bCollideOnTop = false;
        
        Point centerPos = currentPosition;
        
        // Test horizontal, then vertical displacement
        for (int i=0; i<2; ++i) {
            if (i==0) {
                // first loop - horizontal displacement
                fMovementLength = abs(movementDir.x);
                fBigMovementLength = pInitiatorEvent->getSize().width;
                movementStep = Point(movementDir.x, 0).normalize();
            } else {
                // second loop - vertical displacement
                fMovementLength = abs(movementDir.y);
                fBigMovementLength = pInitiatorEvent->getSize().height;
                movementStep = Point(0, movementDir.y).normalize();
            }
            
            float fStepCountToExecute = 100000.f; // default big value to initialize
            
            // corner points
            Point blPos = Point(centerPos.x-halfSize.width, centerPos.y-halfSize.height);
            Point brPos = Point(centerPos.x+halfSize.width, centerPos.y-halfSize.height);
            Point trPos = Point(centerPos.x+halfSize.width, centerPos.y+halfSize.height);
            Point tlPos = Point(centerPos.x-halfSize.width, centerPos.y+halfSize.height);
            
            // middle points
            Point bcPos = Point(centerPos.x, centerPos.y-halfSize.height);
            Point lcPos = Point(centerPos.x-halfSize.width, centerPos.y);
            Point tcPos = Point(centerPos.x, centerPos.y+halfSize.height);
            Point rcPos = Point(centerPos.x+halfSize.width, centerPos.y);
            
            // quarter laeral points
            Point l1Pos = Point(centerPos.x-halfSize.width, centerPos.y-quarterSize.height);
            Point l2Pos = Point(centerPos.x-halfSize.width, centerPos.y+quarterSize.height);
            Point r1Pos = Point(centerPos.x+halfSize.width, centerPos.y-quarterSize.height);
            Point r2Pos = Point(centerPos.x+halfSize.width, centerPos.y+quarterSize.height);
            
            // first, test if the actor land on the ground
            float fBCSampleCount = _pPhysicCollision->countStepToNextPixel(bcPos, movementStep, false, fMovementLength);
            float fBigBCSampleCount = _pPhysicCollision->countStepToNextPixel(bcPos, movementStep, false, fBigMovementLength);
            float fBLSampleCount = _pPhysicCollision->countStepToNextPixel(blPos, movementStep, false, fMovementLength);
            float fBRSampleCount = _pPhysicCollision->countStepToNextPixel(brPos, movementStep, false, fMovementLength);
            if ((!_pPhysicCollision->collide(bcPos)) && fBCSampleCount >= 0.f // bottom center point collide a wall
                && _pPhysicCollision->collide(bcPos + movementStep*fBCSampleCount + Point(0., -1)) ) { // test if there is void below the moved bc pixel
                fStepCountToExecute = fBCSampleCount;
                bIsOnGround = true;
            } else {
                std::vector<Point> pointToTest;
                
                // test bottom point first, if ONLY one of them collide, stick the actor on the ground (XOR operator)
                if ((!_pPhysicCollision->collide(blPos) && fBLSampleCount >= 0.f) != (!_pPhysicCollision->collide(brPos) && fBRSampleCount >= 0.f)
                    && _pPhysicCollision->collide(bcPos + movementStep*fBigBCSampleCount + Point(0., -1)) ) { // test if there is void below the moved bc pixel) {
                    /*Point newBCPos = bcPos + movementStep*fBigBCSampleCount;
                     if((!_pPhysicCollision->collide(blPos) && fBLSampleCount >= 0.f)) {
                     newBCPos.x -= 1.f;
                     } else {
                     newBCPos.x += 1.f;
                     }
                     // test the slope coeff to see if we stick or if we repulse
                     if(_pPhysicCollision->computeSurfaceSlope(newBCPos) > SLOPE_THRESHOLD) {
                     centerPos = centerPos + _pPhysicCollision->getBelowSurfacePixel(newBCPos, movementDir.y) - bcPos + movementStep*fBigBCSampleCount;
                     break;
                     } else {*/
                    fStepCountToExecute = fBigBCSampleCount;
                    bIsOnGround = true;
					//}
                } else {
                    
                    // test other point
                    if (!_pPhysicCollision->collide(blPos)) { pointToTest.push_back(blPos); }
                    if (!_pPhysicCollision->collide(brPos)) { pointToTest.push_back(brPos); }
                    if (!_pPhysicCollision->collide(trPos)) { pointToTest.push_back(trPos); }
                    if (!_pPhysicCollision->collide(tlPos)) { pointToTest.push_back(tlPos); }
                    if (!_pPhysicCollision->collide(lcPos)) { pointToTest.push_back(lcPos); }
                    if (!_pPhysicCollision->collide(tcPos)) { pointToTest.push_back(tcPos); }
                    if (!_pPhysicCollision->collide(rcPos)) { pointToTest.push_back(rcPos); }
                    if (!_pPhysicCollision->collide(l1Pos)) { pointToTest.push_back(l1Pos); }
                    if (!_pPhysicCollision->collide(l2Pos)) { pointToTest.push_back(l2Pos); }
                    if (!_pPhysicCollision->collide(r1Pos)) { pointToTest.push_back(r1Pos); }
                    if (!_pPhysicCollision->collide(r2Pos)) { pointToTest.push_back(r2Pos); }
                    
                    std::vector<float> stepsVector;
                    for (std::vector<Point>::iterator itPoint=pointToTest.begin(); itPoint!=pointToTest.end(); ++itPoint) {
                        float fPossibleStepCount = _pPhysicCollision->countStepToNextPixel(*itPoint, movementStep, false, fMovementLength);
                        if ((itPoint->equals(tcPos) || itPoint->equals(trPos) || itPoint->equals(tlPos)) && int(fPossibleStepCount) == 1) {
                            bCollideOnTop = true;
                        }

                        stepsVector.push_back(fPossibleStepCount);
                    }
                    
                    for (std::vector<float>::iterator itStep=stepsVector.begin(); itStep!=stepsVector.end(); ++itStep) {
                        if (*itStep < fStepCountToExecute && *itStep >= 0) {
                            fStepCountToExecute = *itStep;
                        }
                    }
                }
                
                // if step count is again the default value, there is no collision => set the max movement length
                if (fStepCountToExecute == 100000.f) {
                    fStepCountToExecute = fMovementLength; 
                } else {
                    if (i==0) {
                        eRet = VERTICAL;
                    } else {
                        if (eRet == VERTICAL) {
                            eRet = BOTH;
                        } else {
                            eRet = HORIZONTAL;
                        }
                        
                    }
                }
            }
            
            centerPos = centerPos + (movementStep*fStepCountToExecute);
            
            if(bIsOnGround) { // in this case, we break. Either we've already done the 2 loops, or the actor land on the ground and we don't compute vertical displacement
                if (eRet == VERTICAL) {
                    eRet = BOTH;
                } else {
                    eRet = HORIZONTAL;
                }
                nextState = core::ActorState::STUCK_BOTTOM_STATE;
                break;
            }
            
            if (bCollideOnTop) {
                CCLOG("StickCollisionComponent::boundingTest COLLIDE TOP STUCK TOP STATE");
                nextState = core::ActorState::STUCK_TOP_STATE;
            }
        }
        
        //update position
        resPosition = centerPos;
        
        //update state of Collision and Movement components
        if(nextState != _eMovingState) {
            _eMovingState = nextState;
            events::ChangeStateEvent* pChangeStateEvent = new events::ChangeStateEvent(_owner, _eMovingState);
            EventDispatcher::getInstance()->dispatchEvent(pChangeStateEvent);
        }
        
        return eRet;
    }


    
    void StickCollisionComponent::update(float fDt) {
        CollisionComponent::update(fDt);
    }
}  // namespace physics
