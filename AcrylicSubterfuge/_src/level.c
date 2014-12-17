#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "level.h"
#include "entity.h"
/******
*	Levels are chosen randomly from the start
******/

/******
*
*	Level Value Denominators
*	1 = Wall
*	2 = Player
*	8 = Spawn
*
******/
//extern int menu;
int lvlMode;
int *lvl[11][11];
int *eBack[11][11];
int numSpawns;

int *c1[11][11] ={
	//The Box
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,8,0,0,0,0,0,0,0,8,0},
	{0,0,1,1,0,0,0,1,1,0,0},
	{0,0,1,8,0,0,0,8,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,2,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,8,0,0,0,8,1,0,0},
	{0,0,1,1,0,0,0,1,1,0,0},
	{0,8,0,0,0,0,0,0,0,8,0},
	{0,0,0,0,0,0,0,0,0,0,0},
};
int *c2[11][11] ={
	//The Cyclone
	{8,0,0,0,0,0,0,0,0,0,0},
	{0,8,0,0,0,0,0,0,0,8,0},
	{1,1,1,1,0,0,0,0,1,0,0},
	{0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,2,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,1,1,1,1},
	{0,0,8,0,0,0,0,0,0,8,0},
	{0,0,0,0,0,0,0,0,0,0,8}
};
int *c3[11][11] ={
	//Trolls under the Bridge
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,8,0,0,0,8,0,0,0},
	{0,0,0,0,0,8,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{8,0,0,0,0,2,0,0,0,0,8},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,8,0,0,0,0,0},
	{0,0,8,0,0,0,0,0,8,0,0},
	{0,0,0,0,0,0,0,0,0,0,0}
};
int *c4[11][11] ={
	//The field
	{0,0,0,0,0,0,0,0,0,0,8},
	{0,8,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,2,1,0,0,0,0},
	{0,0,1,1,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,8,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,8}
};

/******
*
*	Effect Board
*	Regular status: moves to the left
*	1 -> 4px
*	2 -> 8px
*	3 -> 16px
*	4 -> 2px
*
******/

int *e1[11][11] ={
	{1,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,3,0,0,0,0,0,1,0,0},
	{0,1,0,0,0,0,0,0,0,2,0},
	{0,0,0,0,3,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,3,0,0,0,0},
	{0,2,0,0,0,0,0,0,0,1,0},
	{0,0,1,0,0,0,0,0,4,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,1}
};
int *e2[11][11] ={
	{0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,3,0,0,0,0,0},
	{0,0,0,1,0,0,0,1,0,0,0},
	{0,0,0,0,0,4,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,2,0,0,1,0,0,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,0,0,2,0,0,0},
	{0,0,0,0,0,3,0,0,0,0,0},
	{0,0,2,0,0,0,0,0,0,0,0}
};
int *e3[11][11] ={
	{0,0,0,1,0,0,0,3,0,0,0},
	{1,0,0,0,0,0,2,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,0,0,0},
	{0,0,0,0,0,4,0,0,0,0,0},
	{0,0,0,2,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,1},
	{0,0,1,0,0,0,0,0,2,0,0}
};

void InitLvl(){

	int ilvl,ieff;
	int i,j;
	Sprite *sprite;
	Entity *ent;
	Effect *eff;
	Effect *bg1,*bg2;

	numSpawns = 0;
	ilvl = (rand()%4);
	ieff = (rand()%3);
	printf("ilvl: %i ieff: %i\n",ilvl,ieff);
	if(ilvl == 0){
		memcpy(lvl, *c1,sizeof(c1));
	}else if(ilvl == 1){
		memcpy(lvl, *c2,sizeof(c2));
	}else if(ilvl == 2){
		memcpy(lvl, *c3,sizeof(c3));
	}else if(ilvl == 3){
		memcpy(lvl, *c4,sizeof(c4));
	}else{
		memcpy(lvl, *c1,sizeof(c1));
	}

	if(ieff == 0){
		memcpy(eBack, *e1,sizeof(e1));
	}else if(ieff == 1){
		memcpy(eBack, *e2,sizeof(e2));
	}else if(ieff == 2){
		memcpy(eBack, *e3,sizeof(e3));
	}else{
		memcpy(eBack, *e1,sizeof(e1));
	}

	//creating the entities on the map
	for(i = 0; i < TILEY; i++){
		for(j = 0; j < TILEX; j++){
			if(lvl[i][j] == 1){
				sprite = LoadSprite("_img/spr_wall.png",32,32,1);
				ent = CreateBlock(j*32,i*32, sprite);
			}else if(lvl[i][j] == 8){
				numSpawns += 1;
				sprite = LoadSprite("_img/spr_spawn.png",32,32,1);
				ent = CreateSpawn(j*32,i*32,sprite);
			}else if(lvl[i][j] == 2){
				sprite = LoadSprite("_img/spr_player.png",32,32,6);
				ent = CreatePlayer(j*32,i*32,sprite,6);
			}
		}
	}
	//creating the back images on the map
	sprite = LoadSprite("_img/lvl1_horz.png",2112,352,1);
	bg1 = CreateBGEff(0,0,sprite);
	bg2 = CreateBGEff(-2112,0,sprite);

	for(i = 0; i < TILEY; i++){
		for(j = 0; j <TILEX; j++){
			if(eBack[i][j] == 1){
				sprite = LoadSprite("_img/spr_horz.png",64,16,1);
				eff = CreateLine(j*32,i*32+8,sprite, 4);
			}else if(eBack[i][j] == 2){
				sprite = LoadSprite("_img/spr_horz.png",64,16,1);
				eff = CreateLine(j*32,i*32+8,sprite, 8);
			} if(eBack[i][j] == 3){
				sprite = LoadSprite("_img/spr_horz.png",64,16,1);
				eff = CreateLine(j*32,i*32+8,sprite, 16);
			} if(eBack[i][j] == 4){
				sprite = LoadSprite("_img/spr_horz.png",64,16,1);
				eff = CreateLine(j*32,i*32+8,sprite, 2);
			}
		}
	}
}