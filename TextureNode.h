#ifndef TextureNode_h
#define TextureNode_h
#include "Effect.h"
#include "SOIL\SOIL.h"

class TextureNode: public Effect{
public:

	float rampIsOn;
	float xCoordinate, yCoordinate;
	float screenProportionHorizontal;
	float screenProportionVertical;

    TextureNode(int* screen_width, int* screen_height):Effect("texture_node.frag",screen_width, screen_height){

		rampIsOn = 1.0;
		xCoordinate = 400.0;
		yCoordinate = 300.0;
		screenProportionHorizontal = 0.5;
		screenProportionVertical = 0.5;

		texture1 = glGetUniformLocation(programID, "texture1");
        if (texture1 == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "texture1");
        }

        texture2 = glGetUniformLocation(programID, "texture2");
        if (texture2 == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "texture2");
        }

		rampOn = glGetUniformLocation(programID, "rampOn");
        if (rampOn == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "rampOn");
        }

		xCoord = glGetUniformLocation(programID, "xCoord");
        if (xCoord == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "xCoord");
        }

		yCoord = glGetUniformLocation(programID, "yCoord");
        if (yCoord == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "yCoord");
        }

		screenPropHorizontal = glGetUniformLocation(programID, "screenPropHorizontal");
        if (screenPropHorizontal == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "screenPropHorizontal");
        }

		screenPropVertical = glGetUniformLocation(programID, "screenPropVertical");
        if (screenPropVertical == -1) {
            fprintf(stderr, "Could not bind attribute %s\n", "screenPropVertical");
        }

    }
    virtual void draw(){
        glUseProgram(programID);

		glUniform1f(rampOn, rampIsOn);
		glUniform1f(xCoord, xCoordinate);
		glUniform1f(yCoord, yCoordinate);
		glUniform1f(screenPropHorizontal, screenProportionHorizontal);
		glUniform1f(screenPropVertical, screenProportionVertical);

		glActiveTexture(GL_TEXTURE1);
		LoadGLTexture("fb.jpg", 640, 640);
        glUniform1i(texture1, 1);

		glActiveTexture(GL_TEXTURE2);
		LoadGLTexture("fb2.png", 640, 1);
        glUniform1i(texture2, 2);

		glActiveTexture(GL_TEXTURE0);

        Effect::draw();
    }
private:
    GLuint texture1, texture2, rampOn, 
		xCoord, yCoord, screenPropHorizontal,screenPropVertical;

	GLint LoadGLTexture(const char *filename, int width, int height) {
		GLuint _texture;
    
		_texture = SOIL_load_OGL_texture
		(
		 filename,
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT 
		 );
    
		if(_texture == 0) {
			printf( "[ERROR] SOIL loading error: '%s'\n", SOIL_last_result() );
		}

		glBindTexture(GL_TEXTURE_2D, _texture);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  
  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    
		return _texture;
	}

};

#endif
