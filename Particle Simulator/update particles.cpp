#include "particle.h"
#include "update particles.h"
#include "screen.h"
#include <iostream>
#include <cstdlib>

void createParticleSquareFill(int x1, int y1, int x2, int y2, int partType)
{
	if(x1 < x2 && y1 < y2)
	{
		for(int xx = 0; xx < (x2-x1); xx++)
		{
			for( int yy = 0; yy < (y2-y1);yy++)
			{
				createParticle(xx,yy,partType,100);
			}
		}
	}
}
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
void particleLine(int x1,int y1,int x2,int y2,int partType)
{

  int dx,dy,sdx,sdy,px,py,dxabs,dyabs,i;
  float slope;

  dx=x2-x1;      /* the horizontal distance of the line */
  dy=y2-y1;      /* the vertical distance of the line */
  dxabs=abs(dx);
  dyabs=abs(dy);
  sdx=sgn(dx);
  sdy=sgn(dy);
  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
  {
    slope=(float)dy / (float)dx;
    for(i=0;i!=dx;i+=sdx)
    {
      px=i+x1;
      py=slope*i+y1;
	  
	  

	  createParticle(px,py,partType,100);

    }
  }
  else /* the line is more vertical than horizontal */
  {
    slope=(float)dx / (float)dy;
    for(i=0;i!=dy;i+=sdy)
    {
      px=slope*i+x1;
      py=i+y1;
   
	  createParticle(px,py,partType,100);
    }
  }
}

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

void explodeTrail(int x, int y, int radius, int intensity)
{
	for(int i = 0; i < intensity; i++)
	{
		int xx = (rand()%radius)-rand()%radius;
		int yy = (rand()%radius)-rand()%radius;
		if(x-xx > 0 && x-xx < screen_width && y-yy > 0 && y-yy < screen_height)
			particleLine(x,y,x-xx,y-yy,PART_FIRE);
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
	//if(frame%2==0)
	
	//else
	
	{
	

	if(partAt(x,y+1).type == PART_EMPTY  && y+2 < screen_height)
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
	}
		done:
		int dn = 0;
	}
	
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
		if(rand()%9 == 1)
		{
		explode(x,y,5,2);
		createParticle(x,y,PART_EMPTY,10);
		createParticle(x,y+1,PART_FIRE,200);
		}
		else
		{
			createParticle(x,y-rand()%10,PART_FIRE,200);
			createParticle(x,y,PART_FIRE,200);
			createParticle(x,y+rand()%10,PART_FIRE,200);
		}
	}
}

void simWater(int x, int y)
{
	float h = heatAt(x,y);

	if(h>100)
	{
		createParticle(x,y+1,PART_STEAM,100);
		setHeat(x,y,h-4); 
	}
	else
	{
		if(isInContactWith(x, y, PART_FIRE)==1)
		{
		createParticle(x,y,PART_STEAM,100);
		setHeat(x,y,h-4); 
		}
		else
		{
			simLiquid(x,y);
		}
	}
	
}
void simNitro(int x, int y)
{
	simLiquid(x,y);
	if(isInContactWith(x, y, PART_FIRE)==1)
	{
		explode(x,y,10,10);
		explodeTrail(x,y,35,5);
	}
}
void simSand(int x, int y)
{
	simPowder(x,y);
}



void simGunPowder(int x, int y)
{
	simPowder(x,y);
	if(canIgnite(x,y) == 1 && rand()%10 == 0)
	{
		createParticle(x,y,0,100);
		explode(x,y,2,4);
		explodeTrail(x,y,20,20);
		//particleLine(x,y,0,0,PART_FIRE);

	}
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
		if(heatAt(x,y) < 1400)
			setHeat(x,y,heatAt(x,y)+50);

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

void simGas(int x, int y)
{

	int thisType = partAt(x,y).type;

	int movY = rand()%3;
	int movX = rand()%3;
	
	int nx = x+(movX-1);
	int ny = y+(movY-1);

	int life = partAt(x,y).life;

	
	
	if(partAt(nx,ny).type == PART_EMPTY && npartAt(nx,ny).type == PART_EMPTY)
	{

		if(nx > 0 && nx < screen_width-1 && ny > 0 && ny < screen_height-1)
		{
		createParticle(nx,ny,thisType,life);
		createParticle(x,y,PART_EMPTY,life);
		}
	}
}



void simSteam(int x, int y)
{
	float h = heatAt(x,y);
	if(h < 20)
	{
		createParticle(x,y,PART_WATER,100);
		setHeat(x,y,h-4);
	}
	else
	{
	simGas(x,y);
	}
}
void simPropane(int x, int y)
{
	simGas(x,y);
	if(canIgnite(x,y) == 1)
	{
		explode(x,y,8,10);
	}
}