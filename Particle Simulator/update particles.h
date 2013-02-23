#ifndef UPDATE_PARTICLES_H
#define UPDATE_PARTICLES_H

void simFire(int x, int y);
void simPropane(int x, int y);
bool canIgnite(int x, int y);
void explode(int x, int y, int radius, int intensity);
#endif