// Spring.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <stdlib.h>
#include "GL\glut.h"
#include <iostream>
#include <windows.h>
#include <WinUser.h>
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <time.h>
#include <fstream>
#include "particle.h"
#include "interface.h"
using namespace std;


void changeSize(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640, 480,0);
    glEnable(GL_BLEND);
      //glEnable(GL_POLYGON_SMOOTH);
}
int x = 0;
POINT m;

void drawSelection()
{
	createParticle(mousex/2,mousey/2,PART_PROPANE,10);

	createParticle(1-mousex/2,mousey/2,PART_PROPANE,10);
	createParticle(1+mousex/2,mousey/2,PART_PROPANE,10);
	createParticle(mousex/2,1-mousey/2,PART_PROPANE,10);
	createParticle(mousex/2,1+mousey/2,PART_PROPANE,10);
}
void handleGUI()
{
	if(mousePressed == 1 )
	{
		if(mousex > 0 && mousex < 640 && mousey > 0 && mousey < 480);
		drawSelection();
	}
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 
	//mouse pos
	GetCursorPos(&m);
	int xx = glutGet(GLUT_WINDOW_X);
	int yy = glutGet(GLUT_WINDOW_Y);
	mousex = m.x-xx;
	mousey = m.y-yy;


	
	createParticle(100,100,PART_FIRE,50);
	createParticle(150,100,PART_PROPANE,100);

	
	renderParticles();
	updateParticleMap();

	glutSwapBuffers();
	glutPostRedisplay();

	handleGUI();

}
void mouse(int button, int state, int x, int y)
{
	if(state == GLUT_UP && button == GLUT_LEFT_BUTTON)
	{
        mousePressed = 0;
	}
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
       mousePressed = 1;
	}
	/*if(state == GLUT_UP && button == GLUT_RIGHT_BUTTON)
    {
        rightm = 0;
    }
    if(state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
    {
        rightm = 1;
    }*/
}
int main(int argc, char **argv) {
	srand(time(0));
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	int window1 = glutCreateWindow("Partical Simulator");
    //glEnable(GL_BLEND); //Enable alpha blending
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutMouseFunc(mouse);
	//glutMouseFunc(m);
	
	clearParticleMap();
	
	selection.life = 100;
	selection.type = 1;

	// enter GLUT event processing loop
	glutMainLoop();

	return 1;
}