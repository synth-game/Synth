/*!
 * \file level_sprite_shaders.h
 * \brief shaders for render the LevelSprite
 * \author Jijidici
 * \date 26/02/2014
 */
#ifndef GAME_SHA_LEVEL_SPRITE_H
#define GAME_SHA_LEVEL_SPRITE_H

#include "cocos2d.h"

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

	uniform int SY_LightCount;
	uniform sampler2D SY_Lights_0;
	uniform sampler2D SY_Lights_1;
	uniform sampler2D SY_Lights_2;
	uniform sampler2D SY_Lights_3;
	uniform sampler2D SY_Lights_4;
	uniform sampler2D SY_Lights_5;
	uniform sampler2D SY_Lights_6;
	uniform sampler2D SY_Lights_7;
	uniform sampler2D SY_Lights_8;
	uniform vec4 SY_Colors[9];
	
	vec3 getLightTexel(sampler2D lightTex, int lightId) {
		vec3 texelColor = vec3(0.);
		if(lightId < SY_LightCount) {
			texelColor = texture2D(lightTex, v_texCoord).rgb;
		}

		return texelColor;
	}

	void main() {
		float threshold = 0.2;
		float wallSample = texture2D(CC_Texture0, v_texCoord).r;
		float fRayStep = (SY_LevelPixelSize.x + SY_LevelPixelSize.y) /2.;

		//construct lights samples
		vec3 ligthTexels[9] = vec3[](
			getLightTexel(SY_Lights_0, 0),
			getLightTexel(SY_Lights_1, 1),
			getLightTexel(SY_Lights_2, 2),
			getLightTexel(SY_Lights_3, 3),
			getLightTexel(SY_Lights_4, 4),
			getLightTexel(SY_Lights_5, 5),
			getLightTexel(SY_Lights_6, 6),
			getLightTexel(SY_Lights_7, 7),
			getLightTexel(SY_Lights_8, 8));

		//apply precomute lighting
		vec4 color = vec4(0.);
		vec4 NoOccultedcolor = vec4(0.);
		vec4 OccultedColor = vec4(0.);
		for(int i=0; i<SY_LightCount; ++i) {
			vec3 lightTexel = ligthTexels[i];

			vec4 lightColor = SY_Colors[i];
			if (lightColor.a > 0.) {
				lightColor.a = lightColor.a/3. + lightTexel.b;
				NoOccultedcolor +=  lightTexel.r * lightColor;
				OccultedColor += lightTexel.g * lightColor;
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

		gl_FragColor = vec4(color);
	}

	//end
);

#endif //GAME_SHA_LEVEL_SPRITE_H