#include "particle.h"
#include "update particles.h"
#include "screen.h"
#include <iostream>
#include <cstdlib>

void explode(int x, int y, int radius, int intensity)
{
	for(int i = 0; i < intensity; i++)
	{
		int xx = (rand()%radius)-rand()%radius;
		int yy = (rand()%radius)-rand()%radius;
		if(x-xx > 0 && x-xx < screen_width && y-yy > 0 && y-yy < screen_height)
		createParticle(x-xx,y-yy,PART_FIRE,40);
	}
}

bool canIgnite(int x, int y)
{
	// are we touching a fire particle
	if(x > 0 && x < screen_width && y> 0 && y < screen_height)
	{
	if(partAt(x+1,y).type == PART_FIRE)
		return 1;
	if(partAt(x-1,y).type == PART_FIRE)
		return 1;

	if(partAt(x,y+1).type == PART_FIRE)
		return 1;
	if(partAt(x,y-1).type == PART_FIRE)
		return 1;
	// diagonal test
	if(partAt(x+1,y+1).type == PART_FIRE)
		return 1;
	if(partAt(x-1,y+1).type == PART_FIRE)
		return 1;

	if(partAt(x+1,y+1).type == PART_FIRE)
		return 1;
	if(partAt(x-1,y-1).type == PART_FIRE)
		return 1;
	}
	return 0;
}

void simWall(int x, int y)
{
	createParticle(x,y,PART_WALL,100);
}

void simFire(int x, int y)
{
	int movY = rand()%2;
	int movX = rand()%3;
	
	int nx = x+(movX-1);
	int ny = y-movY;

	int life = partAt(x,y).life;
	life -=1;
	if(life > 0)
	{
	if(partAt(nx,ny).type == PART_EMPTY && npartAt(nx,ny).type == PART_EMPTY)
	{

		if(nx > 0 && nx < screen_width-1 && ny > 0 && ny < screen_height-1)
		{
		createParticle(nx,ny,PART_FIRE,life);
		createParticle(x,y,PART_EMPTY,life);
		}
		else
		{
			if(ny<= 0)
			{
				life = 0;
				createParticle(x,y,PART_EMPTY,100);
			}
		}
	}
	}
	else
	{
		createParticle(x,y,PART_EMPTY,0);
	}

}
void simPropane(int x, int y)
{
	int movY = rand()%3;
	int movX = rand()%3;
	
	int nx = x+(movX-1);
	int ny = y+(movY-1);

	int life = partAt(x,y).life;

	if(canIgnite(x,y) != 1)
	{
	if(life > 0)
	{
	if(partAt(nx,ny).type == PART_EMPTY && npartAt(nx,ny).type == PART_EMPTY)
	{

		if(nx > 0 && nx < screen_width-1 && ny > 0 && ny < screen_height-1)
		{
		createParticle(nx,ny,PART_PROPANE,life);
		createParticle(x,y,PART_EMPTY,life);
		}
	}
	}
	else
	{
		createParticle(x,y,PART_EMPTY,0);
	}
	}
	else
	{
		//we can ignite.
		createParticle(x,y,PART_FIRE,100);
		createParticle(x+1,y,PART_FIRE,100);
		createParticle(x-1,y,PART_FIRE,100);
		createParticle(x,y+1,PART_FIRE,100);
		createParticle(x,y-1,PART_FIRE,100);

		explode(x,y,8,10);
	}
}