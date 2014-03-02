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
	uniform sampler2D SY_HeroTex;
	uniform vec2 SY_HeroTexPos;
	uniform vec2 SY_HeroTexSize;
	uniform int SY_HeroIsRotated;
	uniform int SY_HeroIsFlippedX;
	uniform int SY_LightCount;
	uniform sampler2D SY_Lights[8];
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

	void main() {
		float threshold = 0.2;
		float wallSample = texture2D(CC_Texture0, v_texCoord).r;

		vec4 color = vec4(0.);
		vec4 NoOccultedcolor = vec4(0.);
		vec4 OccultedColor = vec4(0.);
		for(int i=0; i<SY_LightCount; ++i) {
			vec3 lightTexel = texture2D(SY_Lights[i], v_texCoord).rgb;

			vec4 lightColor = SY_Colors[i];
			lightColor.a = lightColor.a / 3.;

			NoOccultedcolor +=  lightTexel.r * lightColor;
			OccultedColor += lightTexel.g * lightColor;

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

		vec4 heroSample = texture2D(SY_HeroTex, getHeroUV(v_texCoord));
		if(heroSample.a > 0.5) {
			color = vec4(0., 0., 0., 1.);
		} else {
			color = vec4(1.);
		}
		
		color = color/2. + texture2D(CC_Texture0, v_texCoord)/2.;

		gl_FragColor = vec4(color);
	}

	//end
);

#endif //GAME_SHA_LEVEL_SPRITE_H