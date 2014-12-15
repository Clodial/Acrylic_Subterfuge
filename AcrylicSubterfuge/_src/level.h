#ifndef _LEVEL_
#define _LEVEL_

#define TILEH 32
#define TILEW 32
#define TILEX 11
#define TILEY 11

#include "SDL.h"

//At the start of every game, the level is randomly chosen from constructed versions

void CreateLevelList();
void CreateLevel(int *lvl[TILEY][TILEX]);
void InitLvl();
int ChooseLvl();
void LoadLvl(int c);

#endif