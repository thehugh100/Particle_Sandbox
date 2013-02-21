#include "particle.h"
#include "screen.h"
#include <iostream>
#include "GL/glut.h"

void clearParticleMap()
{
	for(int i = 0; i < screen_width; i++)
	{
		for( int ii = 0; ii < screen_height; ii++)
		{
			pmap[i][ii].type = PART_EMPTY;
			nmap[i][ii].type = PART_EMPTY;
		}
	}
}

void renderParticles() // main render function
{
	
	int currentParticleType = PART_EMPTY;
	
	glBegin(GL_QUADS);
	for(int x = 0; x < screen_width; x++)
	{
		for(int y = 0; y < screen_height; y++)
		{

			if( pmap[x][y].type != PART_EMPTY )
			{

			}
			
			glColor3f(1,1,1);
			glVertex2f(x,y);
			glVertex2f(x+1,y);
			glVertex2f(x+1,y+1);
			glVertex2f(x,y+1);

		}
	}
	glEnd();

}
