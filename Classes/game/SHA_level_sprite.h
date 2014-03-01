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
	uniform int SY_LightCount;
	uniform sampler2D SY_Lights[8];
	uniform vec4 SY_Colors[8];

	void main() {
		float threshold = 0.2;
		float wallSample = texture2D(CC_Texture0, v_texCoord).r;

		vec4 color = vec4(0.);
		for(int i=0; i<SY_LightCount; ++i) {
			vec4 lightColor = texture2D(SY_Lights[i], v_texCoord).r * SY_Colors[i];
			lightColor.a = lightColor.a / 3.;
			color +=  lightColor;
		}

		if(!(color.r > threshold && color.g > threshold && color.b > threshold) && wallSample < threshold) {
			color = vec4(0., 0., 0., 1.);
		}

		gl_FragColor = vec4(color);
	}

	//end
);

#endif //GAME_SHA_LEVEL_SPRITE_H