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

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 
	
	createParticle(100,100,PART_FIRE);
	createParticle(101,100,PART_FIRE);

	renderParticles();
	updateParticleMap();

	glutSwapBuffers();
	glutPostRedisplay();

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
	//glutMouseFunc(m);
	
	clearParticleMap();
	

	// enter GLUT event processing loop
	glutMainLoop();

	return 1;
}