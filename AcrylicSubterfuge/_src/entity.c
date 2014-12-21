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
Entity EnemList[MAXENEMIES];
Effect EffList[MAXEFFECTS];

int numEnem;

int chLvl;
int chLvlT;

int numEnts;
int numWalls;
int numBulls;
int numEnems;
int numEffs;

int killCount;

int powSpTimer;
int curPowStimer;

int dirSwitchT;
int curDirSwT;

int curPower;

int mEnem;

int ww;

Entity *playa;
Effect *back1;
Effect *back2;
Entity *spn;

//to be possibly externed
int direction; //direction as follows 0 = left, 1 = up, 2 = right, 3 = down (like gamemaker)
int level;

void InitParts(){
	int i;

	killCount = 10;
	direction = 0;
	dirSwitchT = 30;
	curDirSwT = 0;
	numWalls = 0;
	numBulls = 0;
	numEnts = 0;
	numEffs = 0;
	curPower = P_NORM;
	level = 0;
	mEnem = 2;
	ww = 1;
	chLvlT = 0;
	chLvl = 120;


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
	for(i = 0; i < MAXENEMIES; i ++){
		EnemList[i].sprite = NULL;
		EnemList[i].think = NULL;
		EnemList[i].used = 0;
	}
}
void UpdateParts(){
	//will also contain the spawning code
	int i;
	Effect *ef;
	Sprite *spr;

	printf("numEnems: %i, Max Enemies: %i\n",numEnems, mEnem);
	//curDirSwT += 1;
	if(curDirSwT >= dirSwitchT){
		direction += 1;
		if(direction > 3){
			direction = 0;
		}
		curDirSwT = 0;
	}

	if(level = 0){
		dirSwitchT = 90;
	}else if(level = 1){
		dirSwitchT = 80;
	}else if(level = 2){
		dirSwitchT = 70;
	}else if(level = 3){
		dirSwitchT = 60;
	}else if(level = 4){
		dirSwitchT = 50;
	}else if(level = 5){
		dirSwitchT = 40;
	} 
	if(curPower == P_WHITE && level < 5 && ww == 1){
		spr = LoadSprite("_img/spr_w.png",352,352,1);
		ef = CreateSpecial(0,0,spr,120,P_WHITE);
		ww = 0;
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
	for(i = 0; i < MAXENEMIES; i++){
		if(EnemList[i].used){
			if(EnemList[i].think != NULL){
				EnemList[i].think(&EnemList[i]);
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
Entity *NewEnem(){
	int i;
	if(numEnems + 1 >= MAXENEMIES){
		return NULL;
	}
	numEnems++;
	/*establish memory for new entity*/
	for(i = 0;i <= numEnems; i++){
		if(EnemList[i].used == 0)break;
	}
	EnemList[i].used = 1;
	return &EnemList[i];
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
	for(i = 0; i < MAXENEMIES;i++){
		if(EnemList[i].used){
			DrawEnt(&EnemList[i]);
		}
	}
	for(i = 0; i < MAXBULLETS;i++){
		if(BullList[i].used){
			DrawEnt(&BullList[i]);
		}
	}
	for(i = 0; i < MAXWALLS;i++){
		if(WallList[i].used){
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
void DestBull(Entity *ent){
	ent->used = 0;
	numBulls--;
	if(ent->sprite != NULL){
		FreeSprite(ent->sprite);
	}
	ent->sprite = NULL;
}
void DestWalls(Entity *ent){
	ent->used = 0;
	numWalls--;
	if(ent->sprite != NULL){
		FreeSprite(ent->sprite);
	}
	ent->sprite = NULL;
}
void DestEnems(Entity *ent){
	ent->used = 0;
	numEnems--;
	if(ent->sprite != NULL){
		FreeSprite(ent->sprite);
	}
	ent->sprite = NULL;
}
void ClearAll(){
	int i;
	for(i = 0;i < MAXENTITIES; i++){
		if(EntList[i].used != 0){
			DestEnt(&EntList[i]);
		}
	}
	for(i = 0;i < MAXWALLS; i++){
		if(WallList[i].used != 0){
			DestEnt(&WallList[i]);
		}
	}
	for(i = 0;i < MAXBULLETS; i++){
		if(BullList[i].used != 0){
			DestEnt(&BullList[i]);
		}
	}
	for(i = 0;i < MAXEFFECTS; i++){
		if(EffList[i].used != 0){
			DestEff(&EffList[i]);
		}
	}
	for(i = 0;i < MAXENEMIES; i++){
		if(EnemList[i].used != 0){
			DestEnt(&EnemList[i]);
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
	
	player->power = P_NORM;
	player->type = S_PLAYER;

	player->hp = 10;
	player->timer = 30;
	player->curTimer = 0;

	player->frame = 0;
	player->fTimer = 10;
	player->curFtimer = 0;
	player->numFrames = nF;
	//every subsequent powerup will have specified timers, I guess
	player->powLen = 0;
	player->think = PlayerThink;
	playa = player;
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
	return wall;
}
Entity *CreateBullet(int x, int y, Sprite *s, int vx, int vy, int timer, int type){
	Entity *bull;
	Sprite *spr;
	Entity *nB;

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
	if(bull->weapon == W_LASER){
		if(bull->vx > 0){
			nB = CreateBullet(bull->x+16,bull->y,bull->sprite,4,0,30,P_LASER);
		}else if(bull->vx < 0){
			nB = CreateBullet(bull->x-16,bull->y,bull->sprite,-4,0,30,P_LASER);
		}else if(bull->vy > 0){
			nB = CreateBullet(bull->x,bull->y+16,bull->sprite,0,4,30,P_LASER);
		}else if(bull->vy < 0){
			nB = CreateBullet(bull->x,bull->y-16,bull->sprite,0,-4,30,P_LASER);
		}
	}
	bull->think = BulletThink;
	bull->frame = 0;
	return bull;
}
Entity *CreatePowerup(int x, int y){
	Entity *pow;
	pow = NewEnt();
	if(pow == NULL) return pow;
	pow->x = x;
	pow->y = y;
	pow->w = 16;
	pow->h = 16;
	pow->z = 0;
	pow->timer = 120;
	pow->curTimer = 0;
	pow->type = S_POWER;
	pow->frame = 0;
	pow->think = PowerThink;
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
	spawn->timer = 120;
	spawn->curTimer = 0;
	spawn->think = SpawnThink;

	return spawn;
}
Entity *CreateEnemy(int x, int y, Sprite *s, int type, int nF,int hp){
	Entity *enemy;
	int dir; //this is that crazy randomization stuff this is going to implement
	enemy = NewEnem();
	if(enemy== NULL) return enemy;
	enemy->x = x;
	enemy->y = y;
	enemy->sprite = s;
	enemy->w = 32;
	enemy->h = 32;
	enemy->z = 1;
	enemy->hp = 5;
	enemy->enemy = type;
	//RANDOMNESS ENSUES at least for direction
	if(enemy->enemy == E_STRT || enemy->enemy == E_DIAGC || enemy->enemy == E_PHASE || enemy->enemy == E_SNAKE){
		dir = rand()%4;
		enemy->dir = dir;
		if(dir > 3 || dir < 0){ //because I'm a bit anal about rand for some reason
			enemy->dir = 0;
		}
	}else if(enemy->enemy == E_DISP){
		enemy->curTimer = 0;
		enemy->timer == 30;
	}else if(enemy->enemy == E_BOX){
		dir = rand()%2;
		enemy->dir = dir;
		if(dir > 1 || dir < 0){
			enemy->dir = 0;
		}
	}
	enemy->think = EnemyThink;
	enemy->frame = 0;
	enemy->fTimer = 30;
	enemy->curFtimer = 0;
	enemy->numFrames = nF;
	enemy->type = S_ENEMY;
	return enemy;
}
void EnemyThink(Entity *ent){
	int r;
	//Determining vx and vy for enemy types E_STRT, E_PHASE, E_SNAKE, and E_DISP
	ent->curFtimer+= 1;
	if(ent->curFtimer >= ent->fTimer){
		//So it hits every frame in the sequence
		if(ent->frame < ent->numFrames-1){
			ent->frame += 1;
		}else{
			ent->frame = 0;
		}
		ent->curFtimer = 0;
	}
	if(ent->hp == 0){
		killCount += 1;
		DestEnems(ent);
	}
	if(ent->enemy == E_STRT){
		if(ent->dir == 0){
			ent->vy = 0;
			if(placeFree(ent->x - 4,ent->y) && ent->x > 0){
				ent->x -= 4;
			}else{
				ent->dir = 1;
			}
		}else if(ent->dir == 1){
			ent->vy = 0;
			if(placeFree(ent->x + 4,ent->y) && ent->x < GAMEW - 32){
				ent->x += 4;
			}else{
				ent->dir = 0;
			}
		}else if(ent->dir == 2){
			ent->vx = 0;
			if(placeFree(ent->x,ent->y - 4) && ent->y > 0){
				ent->y -= 4;
			}else{
				ent->dir = 3;
			}
		}else{
			ent->vx = 0;
			if(placeFree(ent->x,ent->y+4) && ent->y < GAMEH - 32){
				ent->y += 4;
			}else{
				ent->dir = 2;
			}
		}
	}else if(ent->enemy == E_DIAGC){
		if(ent->dir == 0){
			if(placeFree(ent->x - 4 ,ent->y - 4) && ent->x < GAMEW - 32 && ent->y > 0){
				ent->x -= 2;
				ent->y -= 2;
			}else{
				r = rand()%3;
				if(r == 1){
					ent->dir = 1;
				}else if(r == 2){
					ent->dir = 2;
				}else{
					ent->dir = 3;
				}
			}
		}else if(ent->dir == 1){
			if(placeFree(ent->x+4,ent->y-4) && ent->x < GAMEW - 32 && ent->y > 0){
				ent->x += 2;
				ent->y -= 2;
			}else{
				r = rand()%3;
				if(r == 1){
					ent->dir = 0;
				}else if(r == 2){
					ent->dir = 2;
				}else{
					ent->dir = 3;
				}
			}
		}else if(ent->dir == 2){
			ent->vx = 0;
			if(placeFree(ent->x+4,ent->y+4) && ent->x < GAMEW - 32 && ent->y < GAMEH - 32){
				ent->y += 2;
				ent->x += 2;
			}else{
				r = rand()%3;
				if(r == 1){
					ent->dir = 1;
				}else if(r == 2){
					ent->dir = 0;
				}else{
					ent->dir = 3;
				}
			}
		}else{
			ent->vx = 0;
			if(placeFree(ent->x-4,ent->y+4) && ent->x > 0  && ent->y < GAMEH - 32){
				ent->y -= 2;
				ent->x += 2;
			}else{
				r = rand()%3;
				if(r == 1){
					ent->dir = 1;
				}else if(r == 2){
					ent->dir = 2;
				}else{
					ent->dir = 0;
				}
			}
		}
	}else if(ent->enemy == E_PHASE){
		if(ent->dir == 0){
			ent->vx = -4;
			ent->vy = 0;
			if(ent->x < -(ent->w)){
				ent->x = GAMEW;
			}
		}else if(ent->dir == 1){
			ent->vy = 4;
			ent->vy = 0;
			if(ent->x > GAMEW){
				ent->x = -(ent->w);
			}
		}else if(ent->dir == 2){
			ent->vx = 0;
			ent->vy = -4;
			if(ent->y < -(ent->h)){
				ent->y = GAMEH;
			}
		}else{
			ent->vx = 0;
			ent->vy = 4;
			if(ent->y > GAMEH){
				ent->y = -(ent->h);
			}
		}
		ent->x += ent->vx;
		ent->y += ent->vy;
	}else if(ent->enemy == E_SNAKE){
		if(ent->dir == 0){
			if(placeFree(ent->x - 4,ent->y) && ent->x > 0){
				ent->x -= 4;
				
			}else{
				r = rand()%2;
				if(r == 1){
					ent->dir = 2;
				}else{
					ent->dir = 3;
				}
			}
		}else if(ent->dir == 1){
			if(placeFree(ent->x + 4,ent->y) && ent->x < GAMEW-32){
				ent->x += 4;
			}else{
				r = rand()%2;
				if(r == 1){
					ent->dir = 2;
				}else{
					ent->dir = 3;
				}
			}
		}else if(ent->dir == 2){
			if(placeFree(ent->x,ent->y - 4) && ent->y > 0){
				ent->y -= 4;
			}else{
				r = rand()%2;
				if(r == 1){
					ent->dir = 0;
				}else{
					ent->dir = 1;
				}
			}
		}else{
			if(placeFree(ent->x,ent->y+4) && ent->y < GAMEH-32){
				ent->y += 4;
			}else{
				r = rand()%3;
				if(r == 1){
					ent->dir = 0;
				}else{
					ent->dir = 1;
				}
			}
		}
	}else if(ent->enemy == E_DISP){
		ent->curTimer += 1;
		if(ent->curTimer >= ent->timer+15){
			r = rand()%4;
			if(r == 0){
				if(ent->x-32 >= 0 && placeFree(ent->x - 32, ent->y)){
					ent->x -= 32;
				}
			}else if(r == 1){
				if(ent->x+32 <= GAMEW-32 && placeFree(ent->x + 32, ent->y)){
					ent->x += 32;
				}
			}else if(r == 2){
				if(ent->y-32 >= 0 && placeFree(ent->x, ent->y - 32)){
					ent->y -= 32;
				}
			}else{
				if(ent->y + 32 >= GAMEH-32 && placeFree(ent->x, ent->y + 32)){
					ent->y += 32;
				}
			}
			ent->curTimer = 0;
		}
	}
	if(playa->x < ent->x + ent->w && playa->x + playa->w > ent->x && playa->y < ent->y + ent->h && playa->y + playa->h > ent->y){
		playa->hp -= 1;
		DestEnems(ent);
	}
}
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
	if(self->power != curPower && level != 5){
		if(curPower != P_LVLU && curPower != P_LVLD){
			FreeSprite(self->sprite);
			if(curPower == P_NORM){
				self->sprite = LoadSprite("_img/spr_player.png",32,32,6);
			}else if(curPower == P_ROCK){
				self->sprite = LoadSprite("_img/spr_pRock.png",32,32,6);
			}else if(curPower == P_SHOT){
				self->sprite = LoadSprite("_img/spr_pShot.png",32,32,6);
			}else if(curPower == P_MINE){
				self->sprite = LoadSprite("_img/spr_pMine.png",32,32,6);
			}else if(curPower == P_LASER){
				self->sprite = LoadSprite("_img/spr_pLaser.png",32,32,6);
			}else if(curPower == P_KEEP){
				self->sprite = LoadSprite("_img/spr_pSame.png",32,32,6);
			}else if(curPower == P_WHITE){
				self->sprite = LoadSprite("_img/spr_pWhite.png",32,32,6);
			}
		}
		self->power = curPower;
	}
}
void BulletThink(Entity *ent){

	int i;
	Sprite *spr;
	Entity *e;

	if(ent->weapon == W_NORM){
		if(placeFree2(ent->x+ent->vx,ent->y+ent->vy,ent->w,ent->h) == 0 || ent->x > GAMEW || ent->y > GAMEH || ent->x < -16 || ent->y < -16){
			DestBull(ent);
		}
		for(i = 0; i< MAXENEMIES; i += 1){
			if(EnemList[i].used){
				if(EnemList[i].x < ent->x + ent->w && EnemList[i].x + EnemList[i].w > ent->x && EnemList[i].y < ent->y + ent->h && EnemList[i].y + EnemList[i].h > ent->y){
					EnemList[i].hp -= 1;
					DestBull(ent);
				}	
			}
		}
		ent->x += ent->vx;
		ent->y += ent->vy;
	}else if(ent->weapon == W_ROCK){
		if(placeFree2(ent->x+ent->vx,ent->y+ent->vy,ent->w,ent->h) == 0 || placeFree3(ent->x+ent->vx,ent->y+ent->vx,ent->w,ent->h) ||ent->x > GAMEW || ent->y > GAMEH || ent->x < -16 || ent->y < -16){
			spr = LoadSprite("_img/spr_bP.png",16,16,1);
			if(ent->vx > 0){
				e = CreateBullet(ent->x-16,ent->y,spr,0,4,40,W_NORM);
				e = CreateBullet(ent->x-16,ent->y,spr,2,2,40,W_NORM);
				e = CreateBullet(ent->x-16,ent->y,spr,0,-4,40,W_NORM);
				e = CreateBullet(ent->x-16,ent->y,spr,-2,-2,40,W_NORM);
				e = CreateBullet(ent->x-16,ent->y,spr,4,0,40,W_NORM);
				e = CreateBullet(ent->x-16,ent->y,spr,2,-2,40,W_NORM);
				e = CreateBullet(ent->x-16,ent->y,spr,-4,0,40,W_NORM);
				e = CreateBullet(ent->x-16,ent->y,spr,-2,2,40,W_NORM);
			}else if(ent->vx < 0){
				e = CreateBullet(ent->x+16,ent->y,spr,0,4,40,W_NORM);
				e = CreateBullet(ent->x+16,ent->y,spr,2,2,40,W_NORM);
				e = CreateBullet(ent->x+16,ent->y,spr,0,-4,40,W_NORM);
				e = CreateBullet(ent->x+16,ent->y,spr,-2,-2,40,W_NORM);
				e = CreateBullet(ent->x+16,ent->y,spr,4,0,40,W_NORM);
				e = CreateBullet(ent->x+16,ent->y,spr,2,-2,40,W_NORM);
				e = CreateBullet(ent->x+16,ent->y,spr,-4,0,40,W_NORM);
				e = CreateBullet(ent->x+16,ent->y,spr,-2,2,40,W_NORM);
			}else if(ent->vy > 0){
				e = CreateBullet(ent->x,ent->y-16,spr,0,4,40,W_NORM);
				e = CreateBullet(ent->x,ent->y-16,spr,2,2,40,W_NORM);
				e = CreateBullet(ent->x,ent->y-16,spr,0,-4,40,W_NORM);
				e = CreateBullet(ent->x,ent->y-16,spr,-2,-2,40,W_NORM);
				e = CreateBullet(ent->x,ent->y-16,spr,4,0,40,W_NORM);
				e = CreateBullet(ent->x,ent->y-16,spr,2,-2,40,W_NORM);
				e = CreateBullet(ent->x,ent->y-16,spr,-4,0,40,W_NORM);
				e = CreateBullet(ent->x,ent->y-16,spr,-2,2,40,W_NORM);
			}else{
				e = CreateBullet(ent->x,ent->y+16,spr,0,4,40,W_NORM);
				e = CreateBullet(ent->x,ent->y+16,spr,2,2,40,W_NORM);
				e = CreateBullet(ent->x,ent->y+16,spr,0,-4,40,W_NORM);
				e = CreateBullet(ent->x,ent->y+16,spr,-2,-2,40,W_NORM);
				e = CreateBullet(ent->x,ent->y+16,spr,4,0,40,W_NORM);
				e = CreateBullet(ent->x,ent->y+16,spr,2,-2,40,W_NORM);
				e = CreateBullet(ent->x,ent->y+16,spr,-4,0,40,W_NORM);
				e = CreateBullet(ent->x,ent->y+16,spr,-2,2,40,W_NORM);
			}
			DestBull(ent);
		}
		ent->x += ent->vx;
		ent->y += ent->vy;
	}else if(ent->weapon == W_LASER){
		ent->curTimer += 1;
		if(ent->curTimer >= ent->timer){
			printf("Making Lasers \n");
			DestBull(ent);	
		}
	}else if(ent->weapon == W_MINE){
		ent->curTimer += 1;
		if(ent->curTimer >= ent->timer){
			DestBull(ent);	
		}
	}
}
void PowerThink(Entity *e){
	int r;
	Sprite *spr;
	Effect *ef;

	e->curTimer += 1;
	if(e->sprite == NULL){
		if(e->curTimer >= e->timer){
			e->sprite = LoadSprite("_img/spr_pow.png",32,32,1);
		}
	}else{
		if(e->curTimer >= e->timer){
			if(playa->x < e->x + e->w && playa->x + playa->w > e->x && playa->y < e->y + e->h && playa->y + playa->h > e->y){
				r = rand()%100;
				if(r >= 0 && r <= 15){
					curPower = P_ROCK;
				}else if(r > 15 && r <= 55){
					curPower = P_SHOT;
				}else if(r > 55 && r <= 60){
					curPower = P_MINE;
				}else if(r > 60 && r <= 65){
					curPower = P_LASER;
				}else if(r > 65 && r <= 70){
					curPower = P_KEEP;
				}else if(r > 70 && r <= 75){
					curPower = P_LVLU;
					if(level < 5){
						level += 1;
					}else{
						level = 0; //to be nice
					}
				}else if(r > 75 && r <= 80){
					curPower = P_LVLD;
					if(level > 0){
						level -= 1;
					}
				}else{
					curPower = P_WHITE;
					ww = 1;
				}
				//FreeSprite(e->sprite);
			}
			e->curTimer = 0;
		}
	}
}
void SpawnThink(Entity *s){
	int r,t;
	Sprite *ss;
	Entity *en;

	s->curTimer += 1;
	if(s->curTimer > s->timer && numEnems < mEnem){
		r = rand()%100;
		ss = LoadSprite("_img/spr_enemy.png",32,32,9);
		if(r >= 0 && r < 20){
			t = E_STRT;
		}else if(r >= 20 && r < 40){
			t = E_PHASE;
		}else if(r >= 40 && r < 60){
			t = E_SNAKE;
		}else if(r >= 60 && r < 80){
			t = E_DIAGC;
		}else{
			t = E_DISP;
		}
		en = CreateEnemy(s->x,s->y,ss,t,9,5);
		s->curTimer = 0;
	}
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
Effect *CreateSpecial(int x, int y, Sprite *s, int t, int type){
	Effect *sp;
	sp = NewEff();
	if(sp == NULL){
		if(curPower == P_WHITE && level != 5)
			curPower = P_NORM;
		return sp;
	}
	sp->x  = x;
	sp->y = y;
	sp->w = 352;
	sp->h = 352;
	sp->sprite = s;
	sp->z = 2;
	sp->type = type;
	sp->curT = 0;
	sp->timer = t;
	sp->think = SpecThink;
	return sp;

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
void SpecThink(Effect *ef){
	if(ef->type == P_WHITE){
		ef->curT += 1;
		if(ef->curT >= ef->timer){
			curPower = P_NORM;
		}if(curPower != P_WHITE){
			DestEff(ef);
		}
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
int TouchSpawn(int x, int y){
	int cx,cy; 
	int cx2,cy2; //to check the full length

	cx = x / 32; //get the tile that is there
	cy = y / 32;
	cx2 = (x + 31)/32;
	cy2 = (y + 31)/32;

	if(lvl[cy][cx] == 2 || lvl[cy][cx2] == 2 || lvl[cy2][cx] == 2 || lvl[cy2][cx2] == 2){
		return 0;
	}
	return 1;
}
int placeFree2(int x, int y, int w, int h){
	//basically like placeFree but meant for collision between objects not stuck to the grid
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
	return 1;
}
int placeFree3(int x, int y, int w, int h){
	//This is between bullets and enemies
	int cx,cy,cx2,cy2;
	int bx,by,bw,bh;
	int i;

	for(i = 0; i< MAXENEMIES; i += 1){
		if(EnemList[i].used){
			if(EnemList[i].x < x + w && EnemList[i].x + EnemList[i].w > x && EnemList[i].y < y + h && EnemList[i].y + EnemList[i].h > y)
				return 0;
		}
	}
	return 1;
}