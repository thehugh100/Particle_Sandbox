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

	if(partAt(nx,ny).type == PART_EMPTY && npartAt(nx,ny).type == PART_EMPTY)
	{

		if(nx > 0 && nx < screen_width-1 && ny > 0 && ny < screen_height-1)
		{
		createParticle(nx,ny,PART_FIRE);
		createParticle(x,y,PART_EMPTY);
		}
	}

}