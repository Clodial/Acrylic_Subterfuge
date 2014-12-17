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

//externed variables
extern SDL_Surface *screen;
extern int numSpawns; //necessary for where enemies will be spawning
extern Effect *bg1,*bg2;
extern int *lvl[11][11];

Entity EntList[MAXENTITIES];
Entity WallList[MAXWALLS];
Entity BullList[MAXBULLETS];
Effect EffList[MAXEFFECTS];
int numEnts;
int numWalls;
int numBulls;
int numEffs;

int killCount;

int powSpTimer;
int curPowStimer;

int dirSwitchT;
int curDirSwT;

Entity *playa;
Effect *back1;
Effect *back2;

//to be possibly externed
int direction; //direction as follows 0 = left, 1 = up, 2 = right, 3 = down (like gamemaker)
int level;

void InitParts(){
	int i;

	killCount = 0;
	direction = 0;
	dirSwitchT = 240;
	curDirSwT = 0;
	numWalls = 0;
	numBulls = 0;
	numEnts = 0;
	numEffs = 0;
	level = 0;

	for(i = 0; i < MAXENTITIES; i++){
		EntList[i].sprite = NULL;
		EntList[i].think = NULL;
		EntList[i].used = 0;
	}
	for(i = 0; i < MAXWALLS; i++){
		WallList[i].sprite = NULL;
		WallList[i].think = NULL;
		WallList[i].used = 0;
	}
	for(i = 0; i < MAXBULLETS; i++){
		BullList[i].sprite = NULL;
		BullList[i].think = NULL;
		BullList[i].used = 0;
	}
	for(i = 0; i < MAXEFFECTS; i++){
		EffList[i].sprite = NULL;
		EffList[i].think = NULL;
		EffList[i].used = 0;
	}
}
void UpdateParts(){
	//will also contain the spawning code
	int i;

	//curDirSwT += 1;
	if(curDirSwT >= dirSwitchT){
		direction += 1;
		if(direction > 3){
			direction = 0;
		}
		curDirSwT = 0;
	}

	for(i = 0; i < MAXENTITIES; i++){
		if(EntList[i].used){
			if(EntList[i].think != NULL){
				EntList[i].think(&EntList[i]);
			}
		}
	}
	for(i = 0; i < MAXBULLETS;i++){
		if(BullList[i].used){
			if(BullList[i].think != NULL){
				BullList[i].think(&BullList[i]);
			}
		}
	}
	for(i = 0; i < MAXWALLS;i++){
		if(WallList[i].used){
			if(WallList[i].think != NULL){
				WallList[i].think(&WallList[i]);
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
Entity *NewWall(){
	int i;
	if(numWalls + 1 >= MAXWALLS){
		return NULL;
	}
	numWalls++;
	/*establish memory for new entity*/
	for(i = 0;i <= numWalls; i++){
		if(WallList[i].used == 0)break;
	}
	WallList[i].used = 1;
	return &WallList[i];
}
Entity *NewBull(){
	int i;
	if(numBulls + 1 >= MAXBULLETS){
		return NULL;
	}
	numBulls++;
	/*establish memory for new entity*/
	for(i = 0;i <= numBulls; i++){
		if(BullList[i].used == 0)break;
	}
	BullList[i].used = 1;
	return &BullList[i];
}
void DrawEnts(){
	int i,j;
	for(j = 0; j < 2; j++){
		for(i = 0; i < MAXENTITIES;i++){
			if(EntList[i].used && EntList[i].z == j){
				DrawEnt(&EntList[i]);
			}
		}
	}
	for(i = 0; i < MAXBULLETS;i++){
		if(BullList[i].used && BullList[i].z == j){
			DrawEnt(&BullList[i]);
		}
	}
	for(i = 0; i < MAXWALLS;i++){
		if(WallList[i].used && WallList[i].z == j){
			DrawEnt(&WallList[i]);
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
	player->timer = 20;
	player->curTimer = 0;

	player->frame = 0;
	player->fTimer = 10;
	player->curFtimer = 0;
	player->numFrames = nF;
	//every subsequent powerup will have specified timers, I guess
	player->powLen = 0;
	player->think = PlayerThink;
	playa = player;
	printf("created player \n");
	return player;
}
Entity *CreateBlock(int x, int y, Sprite *s){
	Entity *wall;
	wall = NewWall();
	if(wall == NULL) return wall;
	wall->sprite = s;
	wall->x = x;
	wall->y = y;
	wall->w = 32;
	wall->h = 32;
	wall->z = 2;
	wall->frame = 0;
	wall->type = S_WALL;
	wall->solid = 1;
	printf("created block \n");
	return wall;
}
Entity *CreateBullet(int x, int y, Sprite *s, int vx, int vy, int timer, int type){
	Entity *bull;
	bull = NewBull();
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
	bull->think = BulletThink;
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
	spawn->spTimer = 120;
	spawn->curSpT = 0;
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

	self->curTimer += 1;
	self->curFtimer+= 1;
	if(self->curFtimer >= self->fTimer){
		//So it hits every frame in the sequence
		if(self->frame < self->numFrames-1){
			self->frame += 1;
		}else{
			self->frame = 0;
		}
		self->curFtimer = 0;
	}
}
void BulletThink(Entity *ent){
	if(placeFree2(ent->x+ent->vx,ent->y+ent->vy,ent->w,ent->h) == 0 || ent->x > GAMEW || ent->y > GAMEH || ent->x < -16 || ent->y < -16){
		DestEnt(ent);
	}
	ent->x += ent->vx;
	ent->y += ent->vy;
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
	bg->curDir = 0;
	bg->sprite = s;
	bg->think = BGThink;
	return bg;
}
Effect *CreateLine(int x, int y,Sprite *s, int v){
	Effect *line;
	line = NewEff();
	if(line == NULL) return line;
	line->x = x;
	line->y = y;
	line->w = 64;
	line->h = 16;
	line->z = 1;
	line->curDir = 0;
	line->v = v;
	line->ix = x;
	line->iy = y;
	line->sprite = s;
	line->think = LineEfThink;
	return line;
}
//Effect Think functions
void BGThink(Effect *eff){

	//left -> up -> right -> down (like gamemaker)
	if(direction == eff->curDir){
		if(direction == 0){
			if(eff->x >= eff->w){
				eff->x = -(eff->w);
			}
			eff->x += 8;
		}else if(direction == 1){
			if(eff->y >= eff->h){
				eff->y = -(eff->h);
			}
			eff->y += 8;
		}else if(direction == 2){
			if(eff->x <= -(eff->w)){
				eff->x = (eff->w);
			}
			eff->x -= 8;
		}else{
			if(eff->y <= -(eff->h)){
				eff->y = (eff->h);
			}
			eff->y -= 8;
		}
	}else{
		FreeSprite(eff->sprite);
		if(direction == 0 || direction == 2){
			eff->w = 2112;
			eff->h = 352;
			bg1->x = 0;
			bg2->x = -2112;
			bg1->y = 0;
			bg2->y = 0;
			if(level == 0){
				eff->sprite = LoadSprite("_img/lvl1_horz.png",2112,352,1);
			}else if(level == 1){
				eff->sprite = LoadSprite("_img/lvl2_horz.png",2112,352,1);
			}else if(level == 2){
				eff->sprite = LoadSprite("_img/lvl3_horz.png",2112,352,1);
			}else if(level == 3){
				eff->sprite = LoadSprite("_img/lvl4_horz.png",2112,352,1);
			}else {
				eff->sprite = LoadSprite("_img/lvl5_horz.png",2112,352,1);
			}
		}else if(direction == 1 || direction == 3){
			eff->w = 352;
			eff->h = 2112;
			bg1->x = 0;
			bg2->x = 0;
			bg1->y = 0;
			bg2->y = -2112;
			if(level == 0){
				eff->sprite = LoadSprite("_img/lvl1_vert.png",352,2112,1);
			}else if(level == 1){
				eff->sprite = LoadSprite("_img/lvl2_vert.png",352,2112,1);
			}else if(level == 2){
				eff->sprite = LoadSprite("_img/lvl3_vert.png",352,2112,1);
			}else if(level == 3){
				eff->sprite = LoadSprite("_img/lvl4_vert.png",352,2112,1);
			}else {
				eff->sprite = LoadSprite("_img/lvl5_vert.png",352,2112,1);
			}
		}

		eff->curDir = direction;
	}
}
void LineEfThink(Effect *eff){

	if(direction == eff->curDir){
		if(direction == 0){
			if(eff->x <= -(eff->w)){
				eff->x = GAMEW;
			}
			eff->x -= eff->v;
		}else if(direction == 1){
			if(eff->y <= -(eff->h)){
				eff->y = GAMEH;
			}
			eff->y -= eff->v;
		}else if(direction == 2){
			if(eff->x >= GAMEW){
				eff->x = -(eff->w);
			}
			eff->x += eff->v;
		}else{
			if(eff->y >= GAMEH){
				eff->y = -(eff->h);
			}
			eff->y += eff->v;
		}
	}else{
		FreeSprite(eff->sprite);
		if(direction == 0 || direction == 2){
			eff->w = 64;
			eff->h = 16;
			eff->x = eff->ix;
			eff->y = eff->iy;
			eff->sprite = LoadSprite("_img/spr_horz.png",64,16,1);
		}else{
			eff->w = 16;
			eff->h = 64;
			eff->x = eff->ix;
			eff->y = eff->iy;
			eff->sprite = LoadSprite("_img/spr_vert.png",16,64,1);
		}
		eff->curDir = direction;
	}
}
int placeFree(int x, int y){
	int cx,cy; 
	int cx2,cy2; //to check the full length

	cx = x / 32; //get the tile that is there
	cy = y / 32;
	cx2 = (x + 31)/32;
	cy2 = (y + 31)/32;

	if(lvl[cy][cx] == 1 || lvl[cy][cx2] == 1 || lvl[cy2][cx] == 1 || lvl[cy2][cx2] == 1){
		return 0;
	}
	return 1;
}
int placeFree2(int x, int y, int w, int h){
	int cx,cy,cx2,cy2;
	int bx,by,bw,bh;
	int i;

	cx = x / 32;
	cy = y / 32;
	cx2 = (x + 32)/32;
	cy2 = (y + 32)/32;
	
	bx = x - (x%32);
	by = y - (y%32);
	bw = 32;
	bh = 32;

	for(i = 0; i< MAXWALLS; i += 1){
		if(WallList[i].used){
			if(WallList[i].x < x + w && WallList[i].x + WallList[i].w > x && WallList[i].y < y + h && WallList[i].y + WallList[i].h > y)
			return 0;
		}
	}

	/*if(lvl[cy][cx] == 1 || lvl[cy][cx2] == 1 || lvl[cy2][cx] == 1 || lvl[cy2][cx2] == 1){
		if(bx < x + w && bx + bw > x && by < y + h && by + bh > y)
		return 0;
	}*/

	return 1;
}