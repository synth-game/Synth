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
	uniform sampler2D SY_Lights[16];

	void main() {
		vec3 texSample = texture2D(CC_Texture0, v_texCoord).rgb;

		vec3 color = vec3(0., 0., texSample.r);
		if(texSample.r > 0.5) {
			color += texture2D(SY_Lights[0], v_texCoord).rgb /3.;
			color += texture2D(SY_Lights[1], v_texCoord).rgb /3.;
			color += texture2D(SY_Lights[2], v_texCoord).rgb /3.;
		}
		//vec3 color = texture2D(SY_Lights[2], v_texCoord).rgb;

		gl_FragColor = vec4(color, 1.);
	}

	//end
);

#endif //GAME_SHA_LEVEL_SPRITE_H