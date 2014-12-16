#include "entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "SDL.h"
#include "level.h"

/******
*	layers:
*	Effects:  0 -> BG; 1 -> arrows; 2 -> Special (Whitewash powerup)
*	Entities  0 -> spawn and powerup; 1 -> Enemies and Player; 1 -> walls; 2 -> bullets;
*
******/

Entity EntList[MAXENTITIES];
Effect EffList[MAXEFFECTS];
int numEnts;
int numEffs;
extern SDL_Surface *screen;
Entity *player;
Effect *back;

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
		EntList[i].sprite = NULL;
		EntList[i].think = NULL;
		EntList[i].used = 0;
	}
}
void UpdateParts(){
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
	DrawSprite(ent->sprite,screen,ent->x,ent->y,0);
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
void InitEnt(){
	int i;
	numEnts = 0;
	for(i = 0; i < MAXENTITIES; i++){
		EffList[i].sprite = NULL;
		EffList[i].think = NULL;
		EffList[i].used = 0;
	}
}
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
			if(EntList[i].used && EffList[i].z == j){
				DrawEnt(&EffList[i]);
			}
		}
	}
}
void DrawEff(Effect *eff){
	/*Frame set to 0 for testing purposes*/
	DrawSprite(eff->sprite,screen,eff->x,eff->y,0);
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
