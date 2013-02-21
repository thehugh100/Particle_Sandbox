#ifndef PARTICLE_H
#define PARTICLE_H

#define PART_EMPTY 0
#define PART_FIRE 1

void renderParticles();
void clearParticleMap();

struct particle
{
	int type;
};

static particle pmap[640][480]; // main particle map for the screen
static particle nmap[640][480]; // the new particle map
#endif