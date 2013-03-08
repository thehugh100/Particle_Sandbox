#ifndef UPDATE_PARTICLES_H
#define UPDATE_PARTICLES_H

void simFire(int x, int y);
void simPropane(int x, int y);
void simWall(int x, int y);
void simNapalm(int x, int y);
void simWater(int x, int y);
void simSand(int x, int y);
void simGunPowder(int x, int y);
void simNitro(int x, int y);

void simLiquid(int x, int y);
void simPowder(int x, int y);

bool isInContactWith(int x, int y, int type);

bool canIgnite(int x, int y);
void explode(int x, int y, int radius, int intensity);
#endif