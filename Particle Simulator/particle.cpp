#include "particle.h"
#include "screen.h"
#include <iostream>
#include "GL/glut.h"
#include "update particles.h"

float hm = 0.999;
void updateParticleMap()
{

	for(int x = 0; x < screen_width; x++)
	{
		for(int y = 0; y < screen_height; y++)
		{
			pmap[x][y].type = nmap[x][y].type; // CAlled at the end of the frame, this is to replace the current particle map with the next
			pmap[x][y].life = nmap[x][y].life;
			heatMap[x][y] = newHeatMap[x][y];

			float h = heatAt(x,y);

			float hl = heatAt(x+1,y);
			float hr = heatAt(x-1,y);
			float hu = heatAt(x,y+1);
			float hd = heatAt(x,y-1);
			
			float hlu = heatAt(x+1,y-1);
			float hru = heatAt(x-1,y-1);
			float hld = heatAt(x+1,y+1);
			float hrd = heatAt(x-1,y+1);
			

			
			
			newHeatMap[x][y] = ((hl + hr + hu + hd + hlu + hru + hld +hrd)/8.0f)*hm;
			

			//newHeatMap[x][y] -=0.5;
			
		}
	}

}

void updatePresureMap()
{
	float mp;
	float lp;
	float rp;
	float up;
	float dp;
	for(int x = 0; x < screen_width; x++)
	{
		for(int y = 0; y < screen_height; y++)
		{
			mp = pressureMap[x][y];
			
			lp = pressureMap[x-1][y];
			rp = pressureMap[x+1][y];
			up = pressureMap[x][y-1];
			dp = pressureMap[x][y+1];

			if(lp>mp)
			{
				newPressureMap[x][y]+=0.1;
				newPressureMap[x-1][y]-=0.1;
			}
			if(rp>mp)
			{
				newPressureMap[x][y]+=0.1;
				newPressureMap[x+1][y]-=0.1;
			}
			if(up>mp)
			{
				newPressureMap[x][y]+=0.1;
				newPressureMap[x][y-1]-=0.1;
			}
			if(dp>mp)
			{
				newPressureMap[x][y]+=0.1;
				newPressureMap[x][y+1]-=0.1;
			}
			pressureMap[x][y] = newPressureMap[x][y];
			//std::cout << pressureMap[x][y];
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
void setHeat(int x, int y, float heat)
{
	newHeatMap[x][y] = heat;
}
float heatAt(int x, int y)
{
	return heatMap[x][y];
}
float newHeatAt(int x, int y)
{
	return newHeatMap[x][y];
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
			heatMap[i][ii] = 0;
			newHeatMap[i][ii] = 0;
		}
	}
}

void createParticle(int x, int y, int type, int life)
{
	if(x>=0 && x <= 640)
		if(y>0 && y < 490)
		{
	nmap[x][y].type = type;
	nmap[x][y].life = life;
	newPressureMap[x][y] = 0;
		}
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
			case PART_GUNPOWDER:
				simGunPowder(x,y);
				glColor3ub(200,200,200);
				break;
			case PART_NITRO:
				simNitro(x,y);
				glColor3ub(25,230,25);
				break;
			case PART_STEAM:
				simSteam(x,y);
				glColor3ub(200,200,250);
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
