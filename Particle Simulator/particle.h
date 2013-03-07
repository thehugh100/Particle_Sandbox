#ifndef PARTICLE_H
#define PARTICLE_H

#define PART_EMPTY 0
#define PART_FIRE 1
#define PART_PROPANE 2
#define PART_WALL 3
#define PART_NAPALM 4
#define PART_WATER 5
#define PART_SAND 6
#define PART_GUNPOWDER 7

struct particle
{
	int type;
	int life;
};

void renderParticles();
void clearParticleMap();
void updateParticleMap();

void updatePresureMap();

void createParticle(int x, int y, int type, int life);
particle partAt(int x, int y);
particle npartAt(int x, int y);

float pressureAt(int x, int y);
float newPressureAt(int x, int y);
static particle pmap[640][480]; // main particle map for the screen
static particle nmap[640][480]; // the new particle map

static int frame;

static float pressureMap[640][480];
static float newPressureMap[640][480];
#endif