#include "entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "SDL.h"
#include "level.h"
#include "graphics.h"

/******
*	layers:
*	Effects:  0 -> BG; 1 -> arrows; 2 -> Special (Whitewash powerup)
*	Entities  0 -> spawn and powerup; 1 -> Enemies and Player; 2 -> walls; 3 -> bullets;
*
******/

Entity EntList[MAXENTITIES];
Effect EffList[MAXEFFECTS];
int numEnts;
int numEffs;
extern SDL_Surface *screen;
Entity *playa;
Effect *back1;
Effect *back2;

void InitParts(){
	int i;
	numEnts = 0;
	for(i = 0; i < MAXENTITIES; i++){
		EntList[i].sprite = NULL;
		EntList[i].think = NULL;
		EntList[i].used = 0;
	}
	numEffs = 0;
	for(i = 0; i < MAXEFFECTS; i++){
		EffList[i].sprite = NULL;
		EffList[i].think = NULL;
		EffList[i].used = 0;
	}
}
void UpdateParts(){
	//will also contain the spawning code
	int i;
	for(i = 0; i < MAXENTITIES; i++){
		if(EntList[i].used){
			if(EntList[i].think != NULL){
				EntList[i].think(&EntList[i]);
			}
		}
	}
	for(i = 0; i < MAXEFFECTS; i++){
		if(EffList[i].used){
			if(EffList[i].think != NULL){
				EffList[i].think(&EffList[i]);
			}
		}
	}
}
/****
*	Entity main parts
****/
Entity *NewEnt(){
	int i;
	if(numEnts + 1 >= MAXENTITIES){
		return NULL;
	}
	numEnts++;
	/*establish memory for new entity*/
	for(i = 0;i <= numEnts; i++){
		if(EntList[i].used == 0)break;
	}
	EntList[i].used = 1;
	return &EntList[i];
}
void DrawEnts(){
	int i,j;
	for(j = 0; j < LAYERS; j++){
		for(i = 0; i < MAXENTITIES;i++){
			if(EntList[i].used && EntList[i].z == j){
				DrawEnt(&EntList[i]);
			}
		}
	}
}
void DrawEnt(Entity *ent){
	/*Frame set to 0 for testing purposes*/
	DrawSprite(ent->sprite,screen,32,32,ent->x,ent->y,ent->frame);
}
void DestEnt(Entity *ent){
	ent->used = 0;
	numEnts--;
	if(ent->sprite != NULL){
		FreeSprite(ent->sprite);
	}
	ent->sprite = NULL;
}
void ClearAllEnt(){
	int i;
	for(i = 0;i < MAXENTITIES; i++){
		if(EntList[i].used != 0){
			DestEnt(&EntList[i]);
		}
	}
}

/******
*	Effects
******/
Effect *NewEff(){
	int i;
	if(numEffs + 1 >= MAXEFFECTS){
		return NULL;
	}
	numEffs++;
	/*establish memory for new entity*/
	for(i = 0;i <= numEffs; i++){
		if(EffList[i].used == 0)break;
	}
	EffList[i].used = 1;
	return &EffList[i];
}
void DrawEffs(){
	int i,j;
	for(j = 0; j < LAYERS; j++){
		for(i = 0; i < MAXEFFECTS;i++){
			if(EffList[i].used && EffList[i].z == j){
				DrawEff(&EffList[i]);
			}
		}
	}
}
void DrawEff(Effect *eff){
	/*Frame set to 0 for testing purposes*/
	DrawSprite(eff->sprite,screen,eff->w,eff->h,eff->x,eff->y,0);
}
void DestEff(Effect *eff){
	eff->used = 0;
	numEnts--;
	if(eff->sprite != NULL){
		FreeSprite(eff->sprite);
	}
	eff->sprite = NULL;
}
void ClearAllEff(){
	int i;
	for(i = 0;i < MAXEFFECTS; i++){
		if(EffList[i].used != 0){
			DestEff(&EffList[i]);
		}
	}
}

//Create Entity functions
Entity *CreatePlayer(int x, int y, Sprite *s, int nF){
	Entity *player;
	player = NewEnt();
	if(player == NULL) return player;
	player->sprite = s;
	player->x = x;
	player->y = y;
	player->w = 32;
	player->h = 32;
	player->z = 1;
	player->type = S_PLAYER;

	player->hp = 10;
	player->frame = 2;
	player->fTimer = 1;
	player->curFtimer = 0;
	player->numFrames = nF;
	//every subsequent powerup will have specified timers, I guess
	player->powLen = 0;
	playa = player;
	printf("created player \n");
	return player;
}
Entity *CreateBlock(int x, int y, Sprite *s){
	Entity *wall;
	wall = NewEnt();
	if(wall == NULL) return wall;
	wall->sprite = s;
	wall->x = x;
	wall->y = y;
	wall->w = 32;
	wall->h = 32;
	wall->z = 2;
	wall->frame = 0;
	wall->type = S_WALL;
	printf("created block \n");
	return wall;
}
Entity *CreateBullet(int x, int y, Sprite *s, int vx, int vy, int timer, int type){
	Entity *bull;
	bull = NewEnt();
	if(bull == NULL) return bull;
	bull->sprite = s;
	bull->x = x;
	bull->y = y;
	bull->w = 16;
	bull->h = 16;
	bull->vx = vx;
	bull->vy = vy;
	bull->z = 2;
	bull->curTimer = 0;
	bull->timer = timer;
	bull->weapon = type;
	bull->type = S_BULLET;
	bull->frame = 0;
	return bull;
}
Entity *CreatePowerup(int x, int y, Sprite *s, int timer, int type){
	Entity *pow;
	pow = NewEnt();
	if(pow == NULL) return pow;
	pow->x = x;
	pow->y = y;
	pow->sprite = s;
	pow->w = 16;
	pow->h = 16;
	pow->z = 0;
	pow->timer = timer;
	pow->power = type;
	pow->type = S_POWER;
	pow->frame = 0;
	return pow;
}
Entity *CreateSpawn(int x, int y, Sprite *s){
	Entity *spawn;
	spawn = NewEnt();
	if(spawn == NULL) return spawn;
	spawn->x = x;
	spawn->y = y;
	spawn->sprite = s;
	spawn->z = 0;
	spawn->w = 32;
	spawn->h = 32;
	spawn->frame = 0;
	printf("created spawn \n");
	return spawn;
}
Entity *CreateEnemy(int x, int y, Sprite *s, int type, int nF,int hp){
	Entity *enemy;
	int dir; //this is that crazy randomization stuff this is going to implement
	enemy = NewEnt();
	if(enemy== NULL) return enemy;
	enemy->x = x;
	enemy->y = y;
	enemy->sprite = s;
	enemy->w = 32;
	enemy->h = 32;
	enemy->z = 1;
	enemy->hp = hp;
	enemy->enemy = type;
	//RANDOMNESS ENSUES at least for direction
	if(enemy->enemy == E_STRT || enemy->enemy == E_DIAG || enemy->enemy == E_PHASE || enemy->enemy == E_SNAKE){
		dir = rand()%4;
		enemy->dir = dir;
		if(dir > 3 || dir < 0){ //because I'm a bit anal about rand for some reason
			enemy->dir = 0;
		}
	}else if(enemy->enemy == E_BOX){
		dir = rand()%2;
		enemy->dir = dir;
		if(dir > 1 || dir < 0){
			enemy->dir = 0;
		}
	}
	//enemy->think = EnemyThink;
	enemy->frame = 0;
	enemy->numFrames = nF;
	enemy->type = S_ENEMY;
	return enemy;
}
//void EnemyThink(Entity *ent){
//	//Determining vx and vy for enemy types E_STRT, E_DIAG, E_PHASE, E_BOX, and E_PHASE
//	if(ent->enemy == 
//}
void PlayerThink(Entity *self){
	
}
//Effect Create functions
Effect *CreateBGEff(int x, int y, Sprite *s){
	Effect *bg;
	bg = NewEff();
	if(bg == NULL) return bg;
	bg->x = x;
	bg->y = y;
	bg->w = 2112;
	bg->h = 352;
	bg->z = 0;
	bg->sprite = s;
	bg->think = BGThink;
	return bg;
}
Effect *CreateLine(int x, int y,Sprite *s, int vx){
	Effect *line;
	line = NewEff();
	if(line == NULL) return line;
	line->x = x;
	line->y = y;
	line->w = 64;
	line->h = 16;
	line->z = 1;
	line->vx = vx;
	line->sprite = s;
	line->think = LineEfThink;
	return line;
}
void BGThink(Effect *eff){
	if(eff->x >= eff->w){
		eff->x = -(eff->w);
	}
	eff->x += 8;
}
void LineEfThink(Effect *eff){
	if(eff->x <= -(eff->w)){
		eff->x = GAMEW;
	}
	eff->x -= eff->vx;
}