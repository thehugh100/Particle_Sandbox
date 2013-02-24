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
		createParticle(x-xx,y-yy,PART_FIRE,200);
	}
}
bool isInContactWith(int x, int y, int type)
{
	if(x > 0 && x < screen_width && y> 0 && y < screen_height)
	{
	if(partAt(x+1,y).type == type)
		return 1;
	if(partAt(x-1,y).type == type)
		return 1;

	if(partAt(x,y+1).type == type)
		return 1;
	if(partAt(x,y-1).type == type)
		return 1;
	// diagonal test
	if(partAt(x+1,y+1).type == type)
		return 1;
	if(partAt(x-1,y+1).type == type)
		return 1;

	if(partAt(x+1,y+1).type == type)
		return 1;
	if(partAt(x-1,y-1).type == type)
		return 1;
	}
	return 0;
}

bool isSurrounded(int x,int y)
{
	if(partAt(x+1,y).type != 0 && partAt(x-1,y).type != 0 && partAt(x,y+1).type != 0 && partAt(x,y-1).type != 0  )
	return 1;
	return 0;
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
	//createParticle(x,y,PART_WALL,100);
}


void simPowder(int x, int y)
{
	int thisSolid = partAt(x,y).type;

	if(partAt(x,y+1).type == PART_EMPTY /*&& npartAt(x,y+1).type == PART_EMPTY*/ && y+2 < screen_height)
	{
		createParticle(x,y,PART_EMPTY,100);
		createParticle(x,y+1,thisSolid,100);

	}
	else
	{
	

	int rr = 1;
	int ll = 1;

	if(partAt(x-1,y).type == 0 && npartAt(x-1,y).type == 0)
		ll = 0;
	if(partAt(x+1,y).type == 0 && npartAt(x+1,y).type == 0)
		rr = 0;
	if(partAt(x,y+1).type != 0)
	{
		if(ll == 1 && rr == 0)
		{
			if(partAt(x+1,y).type == 0 && partAt(x+1,y+1).type == 0)
			{
				if(rand()%2 == 0)
				{
					createParticle(x,y,PART_EMPTY,100);
					createParticle(x+1,y,thisSolid,100);
				}
			}
		}
		if(ll == 0 && rr == 1)
		{
			if(partAt(x-1,y).type == 0 && partAt(x-1,y+1).type == 0)
			{
				if(rand()%2 == 0)
				{
					createParticle(x,y,PART_EMPTY,100);
					createParticle(x-1,y,thisSolid,100);
				}
			}
		}

		if(ll == 0 && rr == 0)
		{
			int r = rand()%2;
			if(r==0)
			{
				createParticle(x,y,PART_EMPTY,100);
				createParticle(x-1,y,thisSolid,100);
			}
			else
			{
				createParticle(x,y,PART_EMPTY,100);
				createParticle(x+1,y,thisSolid,100);
			}
		}
	}
	/*
	if(ll == 0 && rr == 0)
	{
		int r = rand()%3;
		if(r == 0)
		{
			createParticle(x,y,PART_EMPTY,100);
			createParticle(x-1,y,thisSolid,100);
		}
		if(r == 1)
		{
			createParticle(x,y,PART_EMPTY,100);
			createParticle(x+1,y,thisSolid,100);
		}
	}
	*/
	}
	done:
	int dn = 0;
}

void simLiquid(int x, int y)
{

	int thisLiquid = partAt(x,y).type;

	if(partAt(x,y+1).type == PART_EMPTY /*&& npartAt(x,y+1).type == PART_EMPTY*/ && y+2 < screen_height)
	{
		createParticle(x,y,PART_EMPTY,100);
		createParticle(x,y+1,thisLiquid,100);

	}
	else
	{
	

	int rr = 1;
	int ll = 1;

	if(partAt(x-1,y).type == 0 && npartAt(x-1,y).type == 0)
		ll = 0;
	if(partAt(x+1,y).type == 0 && npartAt(x+1,y).type == 0)
		rr = 0;

	if(ll == 1 && rr == 0)
	{
		if(npartAt(x+1,y).type == 0)
		{
			if(rand()%2 == 0)
			{
		createParticle(x,y,PART_EMPTY,100);
		createParticle(x+1,y,thisLiquid,100);
			}
		}
	}
	if(ll == 0 && rr == 1)
	{
		if(npartAt(x-1,y).type == 0)
		{
			if(rand()%2 == 0)
			{
		createParticle(x,y,PART_EMPTY,100);
		createParticle(x-1,y,thisLiquid,100);
			}
		}
	}

	if(ll == 0 && rr == 0)
	{
		int r = rand()%3;
		if(r == 0)
		{
			createParticle(x,y,PART_EMPTY,100);
			createParticle(x-1,y,thisLiquid,100);
		}
		if(r == 1)
		{
			createParticle(x,y,PART_EMPTY,100);
			createParticle(x+1,y,thisLiquid,100);
		}
	}

	}
	done:
	int dn = 0;
}

void simNapalm(int x, int y)
{
	simLiquid(x,y);
	if(canIgnite(x,y) == 1)
	{
		if(rand()%10 == 1)
		{
		explode(x,y,5,2);
		createParticle(x,y,PART_EMPTY,10);
		createParticle(x,y+1,PART_FIRE,200);
		}
		else
		{
			createParticle(x,y-2,PART_FIRE,200);
			createParticle(x,y+2,PART_FIRE,200);
		}
	}
}

void simWater(int x, int y)
{
	simLiquid(x,y);
	if(isInContactWith(x, y, PART_FIRE)==1)
	{
		createParticle(x,y,PART_EMPTY,100);
	}
}
void simSand(int x, int y)
{
	simPowder(x,y);
}

void simFire(int x, int y)
{
	int movY = rand()%2;
	int movX = rand()%3;
	
	int nx = x+(movX-1);
	int ny = y-movY;

	int life = partAt(x,y).life;
	//life --;
	if(life > 0)
	{
	if(isInContactWith(x,y,PART_WATER)==1)
	{
		createParticle(x,y,0,1);
	}
	if(isSurrounded(x,y) == 1)
	{
		//life -=2;
	}
		//if(life > 100)
			//life = 100;

	
		if(partAt(nx,ny).type == PART_EMPTY && npartAt(nx,ny).type == PART_EMPTY)
		{

			if(nx > 0 && nx < screen_width-1 && ny > 0 && ny < screen_height-1)
			{
			createParticle(nx,ny,PART_FIRE,life-1);
			createParticle(x,y,PART_EMPTY,life-1);
			}
			else
			{
				if(ny<= 0)
				{
					life = 0;
					createParticle(x,y,PART_EMPTY,0);
				}
			}
		}
		else
		{
			if(rand()%5== 1)
			createParticle(x,y,PART_EMPTY,0);
			//createParticle(nx,ny,PART_EMPTY,0);
		}
	}
	else
	{
		createParticle(x,y,PART_EMPTY,0);
		createParticle(nx,ny,PART_EMPTY,0);
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

		explode(x,y,8,10);
	}
}