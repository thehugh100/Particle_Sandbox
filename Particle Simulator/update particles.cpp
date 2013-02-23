#include "particle.h"
#include "update particles.h"
#include "screen.h"
#include <iostream>
#include <cstdlib>
void simFire(int x, int y)
{
	int movY = rand()%2;
	int movX = rand()%3;
	
	int nx = x+(movX-1);
	int ny = y-movY;

	int life = partAt(x,y).life;

	if(life > 0)
	{
	if(partAt(nx,ny).type == PART_EMPTY && npartAt(nx,ny).type == PART_EMPTY)
	{

		if(nx > 0 && nx < screen_width-1 && ny > 0 && ny < screen_height-1)
		{
		createParticle(nx,ny,PART_FIRE,life-1);
		createParticle(x,y,PART_EMPTY,life-1);
		}
	}
	}
	else
	{
		createParticle(x,y,PART_EMPTY,0);
	}

}