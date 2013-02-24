#include "particle.h"
#include "screen.h"
#include <iostream>
#include "GL/glut.h"
#include "update particles.h"


void updateParticleMap()
{

	for(int x = 0; x < screen_width; x++)
	{
		for(int y = 0; y < screen_height; y++)
		{
			pmap[x][y].type = nmap[x][y].type; // CAlled at the end of the frame, this is to replace the current particle map with the next
			pmap[x][y].life = nmap[x][y].life;
		}
	}

}

particle partAt(int x, int y)
{
	return pmap[x][y];
}
particle npartAt(int x, int y)
{
	return nmap[x][y];
}
void clearParticleMap()
{
	for(int i = 0; i < screen_width; i++)
	{
		for( int ii = 0; ii < screen_height; ii++)
		{
			pmap[i][ii].type = PART_EMPTY;
			nmap[i][ii].type = PART_EMPTY;
			pmap[i][ii].life = 0;
			nmap[i][ii].life = 0;
		}
	}
}

void createParticle(int x, int y, int type, int life)
{
	nmap[x][y].type = type;
	nmap[x][y].life = life;
}

void renderParticles() // main render function
{
	
	int currentParticleType = PART_EMPTY;
	float tx = 640.0/screen_width;
	float ty = 480.0/screen_height;
	glBegin(GL_QUADS);
	for(int y = 0; y < screen_height; y++)
	{
		for(int x = 0; x < screen_width; x++)
		{
			float cx = tx*x;
			float cy = ty*y;

			currentParticleType = partAt(x,y).type;

			
			if(currentParticleType != PART_EMPTY )
			{

			switch(currentParticleType)
			{
			case PART_EMPTY:
				break;
			case PART_FIRE:
				simFire(x,y);
				glColor3ub(255,32,32);
				
				break;
			case PART_PROPANE:
				simPropane(x,y);
				glColor3ub(255,255,255);
				break;
			case PART_WALL:
				simWall(x,y);
				glColor3ub(128,128,128);
				break;

			case PART_NAPALM:
				simNapalm(x,y);
				glColor3ub(128,128,0);
				break;
			case PART_WATER:
				simWater(x,y);
				glColor3ub(64,64,255);
				break;
			case PART_SAND:
				simSand(x,y);
				glColor3ub(255,255,130);
				break;
			}
					
			}
			else
			{
				glColor3f(0,0,0);
			}

			glVertex2f(cx,cy);
			glVertex2f(cx+tx,cy);
			glVertex2f(cx+tx,cy+ty);
			glVertex2f(cx,cy+ty);
		}
	}
	glEnd();

}
