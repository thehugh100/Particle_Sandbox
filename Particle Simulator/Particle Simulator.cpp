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
#include <conio.h>
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

void changeSize2(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,200, 480,0);
    glEnable(GL_BLEND);
      //glEnable(GL_POLYGON_SMOOTH);
}

int x = 0;
POINT m;
POINT p;
void drawSelection()
{

	particle pt = selection;
	int ptt = pt.type;

	createParticle(mousex/2,mousey/2,ptt,10);

	createParticle((mousex/2)-1,(mousey/2),ptt,10);
	createParticle((mousex/2)+1,(mousey/2),ptt,10);
	createParticle((mousex/2),(mousey/2)-1,ptt,10);
	createParticle((mousex/2),(mousey/2)+1,ptt,10);


}
void handleGUI()
{
	if(mousePressed == 1 )
	{
		if(mousex > 0 && mousex < 640 && mousey > 0 && mousey < 480)
		drawSelection();
	}

	if(GetAsyncKeyState('F') != 0)
		selection.type = PART_FIRE;
	if(GetAsyncKeyState('G') != 0)
		selection.type = PART_PROPANE;
	if(GetAsyncKeyState('W') != 0)
		selection.type = PART_WALL;


}

void renderScene()
{
	glutReshapeWindow(640,480); // prevent window reshaping
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 
	//mouse pos
	GetCursorPos(&m);
	int xx = glutGet(GLUT_WINDOW_X);
	int yy = glutGet(GLUT_WINDOW_Y);
	mousex = m.x-xx;
	mousey = m.y-yy;


	
	//createParticle(100,100,PART_FIRE,50);
	//createParticle(150,100,PART_PROPANE,100);

	
	renderParticles();
	updateParticleMap();

	glutSwapBuffers();
	glutPostRedisplay();

	handleGUI();

}

static void sen(char *string)
{

    int len,i;
    len=(int)strlen(string);
    for(i=0; i<len; i++)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,string[i]);
}
static void senL(char *string)
{

    int len,i;
    len=(int)strlen(string);
    for(i=0; i<len; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
}
void drawButton(int x, int y, int w, int h, char *string,int type)
{
	glBegin(GL_QUADS);
	
	glColor3f(0.9,0.9,0.9);

	if((pmousex >= x && pmousex <= x+w) && (pmousey >= y && pmousey <= y+h))
	{
		glColor3f(1,0.9,0.9);
		if(mousePressed == 1)
		{
			glColor3f(0.5,1,0.5);
			if(type >=0 )
			{
			selection.type = type;
			}
			else
			{
				if(type == -4)
				{
					clearParticleMap();
				}
			}
		}
	}
	glVertex2f(x,y);
	glVertex2f(x+w,y);
	glVertex2f(x+w,y+h);
	glVertex2f(x,y+h);
	glEnd();
	glColor3f(0.2,0.2,0.2);
	glRasterPos2f(x+5,y+22);
	sen(string);

	if(selection.type == type)
	{
		glBegin(GL_QUADS);
		
		glColor3f(1,0,0);

		glVertex2f(x,y);
		glVertex2f(x+6,y);
		glVertex2f(x+6,y+6);
		glVertex2f(x,y+6);

		glEnd();
	}

}

void renderPallete()
{
	glutReshapeWindow(200,480);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GetCursorPos(&p);
	int xx = glutGet(GLUT_WINDOW_X);
	int yy = glutGet(GLUT_WINDOW_Y);
	pmousex = m.x-xx;
	pmousey = m.y-yy;

	glBegin(GL_QUADS);
	glColor3f(1,1,1);

	glVertex2f(0,0);
	glVertex2f(200,0);
	glVertex2f(200,480);
	glVertex2f(0,480);
	glEnd();

	glColor3f(0.3,0.3,0.3);
	glRasterPos2f(30,32);
	senL("Particle Box");

	drawButton(0,50,66,30,"Fire",PART_FIRE);
	drawButton(66,50,66,30,"Wall",PART_WALL);
	drawButton(66*2,50,66,30,"Propane",PART_PROPANE);

	drawButton(0,80,66,30,"Napalm",PART_NAPALM);
	drawButton(66,80,66,30,"Water",PART_WATER);
	drawButton(66*2,80,66,30,"Sand",PART_SAND);

	drawButton(0,480-30,66,30,"Clear",-4);

	glutSwapBuffers();
	glutPostRedisplay();
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

	glutInitWindowPosition(760,100);
	glutInitWindowSize(200,480);
	int pallete = glutCreateWindow("Pallete");
	glutDisplayFunc(renderPallete);
	glutReshapeFunc(changeSize2);
	glutMouseFunc(mouse);

	clearParticleMap();
	
	selection.life = 100;
	selection.type = 1;

	FreeConsole();

	// enter GLUT event processing loop
	glutMainLoop();
	return 1;
}