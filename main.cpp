//
//  main.cpp
//  Bilgisayar Proje II - Real-Time Computer Graphics
//  Project #IV - ###
//
//  Merter TURAN - turanmerter@gmail.com
//  040080204
//
#include <iostream>
#include <windows.h>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include "Scene.h"
#include "TextureNode.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define WINDOW_TITLE_PREFIX "Proje 4"

void IdleFunction(void);
void ResizeFunction(int Width, int Height);
void setupScene();

unsigned FrameCount = 0;

int CurrentWidth = 800,
CurrentHeight = 600;

Light* light;
Camera *camera;
Scene* scene;
TextureNode *temp;

static void Draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    scene->draw();
    
    glutSwapBuffers();
}

static void Key(unsigned char key, int x, int y)
{
    switch (key) {
		case 32: // Space
			if (temp->rampIsOn  > 0.5)
				temp->rampIsOn = 0.0;
			else if (temp->rampIsOn < 0.5)
				temp->rampIsOn = 1.0;
            break;
		case 27: // ESC
			exit(0);
            break;
	}
}

void SpecialKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT:
			if (temp->screenProportionHorizontal > 0.0){
				temp->screenProportionHorizontal -= 0.05;
				printf("Proportion is decreased horizantally.\n");
			}
			break;
		case GLUT_KEY_RIGHT:
			if (temp->screenProportionHorizontal < 0.5){
				temp->screenProportionHorizontal += 0.05;
				printf("Proportion is increased horizantally.\n");
			}
			break;
		case GLUT_KEY_DOWN:
			if (temp->screenProportionVertical > 0.0){
				temp->screenProportionVertical -= 0.05;
				printf("Proportion is decreased vertically.\n");
			}
			break;
		case GLUT_KEY_UP:
			if (temp->screenProportionVertical < 0.5){
				temp->screenProportionVertical += 0.05;
				printf("Proportion is increased vertically.\n");
			}
			break;
	}
}

static void Mouse(int x, int y)
{
	temp->xCoordinate = float(x);
	temp->yCoordinate = 600.0 - float(y);

    glutPostRedisplay();
}

void ResizeFunction(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
    scene->resize();
}

static void timerCallback (int value)
{
    if (0 != value) {
		char* TempString = (char*)
        malloc(512 + strlen(WINDOW_TITLE_PREFIX));
        
		sprintf(
                TempString,
                "%s: %d Frames Per Second @ %d x %d",
                WINDOW_TITLE_PREFIX,
                FrameCount * 4,
                CurrentWidth,
                CurrentHeight
                );
        
		glutSetWindowTitle(TempString);
		free(TempString);
	}
	FrameCount = 0;
	glutTimerFunc(250, timerCallback, 1);
}

void IdleFunction(void)
{
	glutPostRedisplay();
}

void setupScene(){
    scene = new Scene();
    camera = new Camera();
    
    camera->translate(0.f, 0.f, 20.f);
    scene->setCamera(camera);
    
    scene->addEffect( temp = new TextureNode(&CurrentWidth,&CurrentHeight));
    
}

int main (int argc, char ** argv)
{
    
    GLenum type;
    
	glutInit(&argc, argv);
	glutInitWindowSize(CurrentWidth,CurrentHeight);
	type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
    type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	glutCreateWindow("");
#ifdef _WIN32
    GLenum err = glewInit();
	if (GLEW_OK != err)
	{
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    
    printf("GLSL Version: %s\n",glslVersion);
    
    const GLubyte* glVersion = glGetString(GL_VERSION);
    
    printf("GL Version: %s\n",glVersion);
    
    glClearColor(0.0, 1.0, 0.0, 1.0);
    // Z-Buffer i aciyoruz
    glEnable(GL_DEPTH_TEST);
    
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE); 
    
       
    setupScene();
    
    timerCallback(0);
    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(Draw);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);
    glutIdleFunc(IdleFunction);
    glutPassiveMotionFunc(Mouse);

	printf("\nBilgisayar Proje II - Real-Time Computer Graphics\n");
	printf("Project #IV\n\n");
	printf("Commands:\n");
	printf("---------\n");
	printf("	Space:      On/Off the ramp texture.\n");
	printf("	Arrow keys: Resize ramp texture area.\n");
	printf("	Mouse:      Move ramp texture area.\n");
	printf("	ESC:        Exit the application.\n");

    glutMainLoop();
    
    return 0;
}