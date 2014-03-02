/*!
 * \file level_sprite_shaders.h
 * \brief shaders for render the LevelSprite
 * \author Jijidici
 * \date 26/02/2014
 */
#ifndef GAME_SHA_LEVEL_SPRITE_H
#define GAME_SHA_LEVEL_SPRITE_H

#include <GL\glew.h>

#ifndef GL_STRINGIFY
#define GL_STRINGIFY(s) #s
#endif

#define SHA_LIGHT_MAX_COUNT 16

const GLchar* levelSprite_vert =
GL_STRINGIFY(
	//begin

	attribute vec4 a_position;
	attribute vec2 a_texCoord;

	varying vec2 v_texCoord;

	void main()
	{
		gl_Position = CC_MVPMatrix * a_position;
		v_texCoord = a_texCoord;
	}

	//end
);

const GLchar* levelSprite_frag =
GL_STRINGIFY(
	//begin

	varying vec2 v_texCoord;

	uniform sampler2D CC_Texture0;

	uniform vec2 SY_LevelPixelSize;
	uniform vec2 SY_HeroPixelSize;
	uniform vec2 SY_HeroPos;

	uniform sampler2D SY_HeroTex;
	uniform vec2 SY_HeroTexPos;
	uniform vec2 SY_HeroTexSize;
	uniform int SY_HeroIsRotated;
	uniform int SY_HeroIsFlippedX;

	uniform int SY_LightCount;
	uniform sampler2D SY_Lights[8];
	uniform vec2 SY_LightPos[8];
	uniform vec4 SY_Colors[8];

	vec2 getHeroUV(vec2 uv) {
		vec2 texSize = SY_HeroTexSize;
		if(SY_HeroIsRotated == 1) {
			float fTmp = uv.x;
			uv.x = 1.-uv.y;
			uv.y = fTmp;

			fTmp = texSize.x;
			texSize.x = texSize.y;
			texSize.y = fTmp;
		}

		if(SY_HeroIsFlippedX == 1) {
			if(SY_HeroIsRotated == 1) {
				uv.y = 1.-uv.y;
			} else {
				uv.x = 1.-uv.x;
			}
		}

		return vec2(SY_HeroTexPos.x + uv.x*texSize.x, SY_HeroTexPos.y + uv.y*texSize.y);
	}

	vec4 getHeroTexel(vec2 levelSpaceUV) {
		vec2 levelUV = vec2(levelSpaceUV.x - SY_HeroPos.x*SY_LevelPixelSize.x, levelSpaceUV.y - SY_HeroPos.y*SY_LevelPixelSize.y);
		vec2 heroUV = vec2(levelUV.x*SY_HeroPixelSize.x/SY_LevelPixelSize.x, levelUV.y*SY_HeroPixelSize.y/SY_LevelPixelSize.y);
		//return texture2D(SY_HeroTex, getHeroUV(heroUV));

		if(heroUV.x > 0. && heroUV.x < 1. && heroUV.y > 0. && heroUV.y < 1.) {
			return vec4(1., 0., 1., texture2D(SY_HeroTex, getHeroUV(heroUV)).a);
		}

		return vec4(0.);
	}

	bool isInHeroShadow(vec2 position, vec2 lightPos, float fStep, float threshold) {
		vec2 l = normalize(lightPos - position);
		vec2 samplePos = position;

		float fDotTest = 1.;
		while(fDotTest > 0.) {
			samplePos = samplePos + vec2(l.x*fStep, l.y*fStep);
			fDotTest = dot(lightPos-samplePos, lightPos-position);

			float fAlphaTest = getHeroTexel(samplePos).a;
			if(fAlphaTest > threshold && fDotTest > 0.) {
				return true;
				break;
			}
		}

		return false;
	}

	void main() {
		float threshold = 0.2;
		float wallSample = texture2D(CC_Texture0, v_texCoord).r;
		float fRayStep = (SY_LevelPixelSize.x + SY_LevelPixelSize.y) /2.;

		//apply precomute lighting
		vec4 color = vec4(0.);
		vec4 NoOccultedcolor = vec4(0.);
		vec4 OccultedColor = vec4(0.);
		for(int i=0; i<SY_LightCount; ++i) {
			vec3 lightTexel = texture2D(SY_Lights[i], v_texCoord).rgb;

			vec4 lightColor = SY_Colors[i];
			lightColor.a = lightColor.a / 3.;

			NoOccultedcolor +=  lightTexel.r * lightColor;

			//compute shadows
			if(lightTexel.g > threshold) {
				if(!isInHeroShadow(v_texCoord, vec2(SY_LightPos[i].x*SY_LevelPixelSize.x, SY_LightPos[i].y*SY_LevelPixelSize.y), fRayStep, threshold)){
					OccultedColor += lightTexel.g * lightColor;
				}
			}

		}

		if(NoOccultedcolor.r > threshold && NoOccultedcolor.g > threshold && NoOccultedcolor.b > threshold) {
			color = NoOccultedcolor;
		} else {
			if(wallSample < threshold) {
				color = vec4(0., 0., 0., 1.);
			} else {
				color = OccultedColor;
			}
		}

		color = getHeroTexel(v_texCoord);

		gl_FragColor = vec4(color);
	}

	//end
);

#endif //GAME_SHA_LEVEL_SPRITE_H