#ifndef PARTICLE_H
#define PARTICLE_H

#define PART_EMPTY 0
#define PART_FIRE 1





struct particle
{
	int type;
};

void renderParticles();
void clearParticleMap();
void updateParticleMap();
void createParticle(int x, int y, int type);
particle partAt(int x, int y);
particle npartAt(int x, int y);
static particle pmap[640][480]; // main particle map for the screen
static particle nmap[640][480]; // the new particle map
#endif