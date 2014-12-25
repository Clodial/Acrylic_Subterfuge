#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "level.h"
#include "entity.h"

extern SDL_Surface *screen;
extern SDL_Surface *buffer;
extern SDL_Rect Camera;

extern Entity *playa;
extern int direction;
extern int curPower;
extern int level;
extern int ww;
extern int killCount;

void Init_All();

SDL_Event Event;

int main(int argc, char *argv[]){
	Sprite *spr; //for creating player weapons
	int done;
	int keyn;
	Uint8 *keys;
	time_t t;
	int r1,r2,r3,r4;
	Entity *e1,*e2,*e3,*e4;

	srand((unsigned) time(&t));
	Init_Graphics();
	done = 0;
	Init_All();
	do{
		UpdateParts();
		SDL_PumpEvents();
		keys = SDL_GetKeyState(&keyn);
		if(keys[SDLK_1]){
			curPower = P_NORM;
		}else if(keys[SDLK_2]){
			curPower = P_ROCK;
		}else if(keys[SDLK_3]){
			curPower = P_SHOT;
		}else if(keys[SDLK_4]){
			curPower = P_MINE;
		}else if(keys[SDLK_5]){
			curPower = P_PHASER;
		}

		if(keys[SDLK_a]){
			playa->dir = 0;
		}else if(keys[SDLK_d]){
			playa->dir = 2;
		}else if(keys[SDLK_w]){
			playa->dir = 1;
		}else if(keys[SDLK_s]){
			playa->dir = 3;
		}

		if(keys[SDLK_e]){
			spr = LoadSprite("_img/spr_enemy.png",32,32,1);
			e1 = CreateEnemy(160,160,spr,E_STRT,9,5);
		}else if(keys[SDLK_r]){
			spr = LoadSprite("_img/spr_enemy.png",32,32,1);
			e1 = CreateEnemy(160,160,spr,E_PHASE,9,5);
		}else if(keys[SDLK_t]){
			spr = LoadSprite("_img/spr_enemy.png",32,32,1);
			e1 = CreateEnemy(160,160,spr,E_DIAGC,9,5);
		}else if(keys[SDLK_y]){
			spr = LoadSprite("_img/spr_enemy.png",32,32,1);
			e1 = CreateEnemy(160,160,spr,E_SNAKE,9,5);
		}else if(keys[SDLK_u]){
			spr = LoadSprite("_img/spr_enemy.png",32,32,1);
			e1 = CreateEnemy(160,160,spr,E_DISP,9,5);
		}

		if(keys[SDLK_LEFT]){
			if(playa->curTimer >= playa->timer){
				if(playa->power != P_KEEP){
					if(playa->power == P_NORM){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,10,W_NORM);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,10,W_NORM);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,10,W_NORM);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,10,W_NORM);
						}
					}else if(playa->power == P_PHASER){
						spr = LoadSprite("_img/spr_bPL.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,60,W_PHASE);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,60,W_PHASE);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,60,W_PHASE);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,60,W_PHASE);
						}
					}else if(playa->power == P_SHOT){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						r1 = rand()%8-4;
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r1,10,W_NORM);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,-8,10,W_NORM);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,r1,10,W_NORM);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,8,10,W_NORM);
						}
					}else if(playa->power == P_ROCK){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,10,W_ROCK);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,10,W_ROCK);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,10,W_ROCK);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,10,W_ROCK);
						}
					}
				}
				playa->curTimer = 0;
			}
		}else if(keys[SDLK_UP]){
			if(playa->curTimer >= playa->timer){
				if(playa->power != P_KEEP){
					if(playa->power == P_NORM){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,10,W_NORM);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,10,W_NORM);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,10,W_NORM);	
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,10,W_NORM);
						}
					}else if(playa->power == P_PHASER){
						spr = LoadSprite("_img/spr_bPL.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,60,W_PHASE);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,60,W_PHASE);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,60,W_PHASE);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,60,W_PHASE);
						}
					}else if(playa->power == P_SHOT){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						r1 = rand()%8-4;						
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,-8,10,W_NORM);							
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,r1,10,W_NORM);							
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,8,10,W_NORM);							
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r1,10,W_NORM);							
						}
					}else if(playa->power == P_ROCK){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,10,W_ROCK);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,10,W_ROCK);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,10,W_ROCK);	
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,10,W_ROCK);
						}
					}
				}
				playa->curTimer = 0;
			}
		}else if(keys[SDLK_RIGHT]){
			if(playa->curTimer >= playa->timer){
				if(playa->power != P_KEEP){
					if(playa->power == P_NORM){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,10,W_NORM);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,10,W_NORM);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,10,W_NORM);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,10,W_NORM);
						}
					}else if(playa->power == P_PHASER){
						spr = LoadSprite("_img/spr_bPL.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,60,W_PHASE);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,60,W_PHASE);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,60,W_PHASE);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,60,W_PHASE);
						}
					}else if(playa->power == P_SHOT){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						r1 = rand()%8-4;						
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,r1,10,W_NORM);					
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,8,10,W_NORM);					
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r1,10,W_NORM);			
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,-8,10,W_NORM);							
						}
					}if(playa->power == P_ROCK){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,10,W_ROCK);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,10,W_ROCK);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,10,W_ROCK);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,10,W_ROCK);
						}
					}
				}
				//printf("number of uses: %i\n", );
				playa->curTimer = 0;
			}
		}else if(keys[SDLK_DOWN]){
			if(playa->curTimer >= playa->timer){
				if(playa->power != P_KEEP){
					if(playa->power == P_NORM){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,10,W_NORM);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,10,W_NORM);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,10,W_NORM);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,10,W_NORM);
						}
					}else if(playa->power == P_PHASER){
						spr = LoadSprite("_img/spr_bPL.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,60,W_PHASE);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,60,W_PHASE);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,60,W_PHASE);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,60,W_PHASE);
						}
					}else if(playa->power == P_SHOT){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						r1 = rand()%8-4;
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,8,10,W_NORM);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r1,10,W_NORM);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,-8,10,W_NORM);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r1,10,W_NORM);							
						}
					}else if(playa->power == P_ROCK){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,10,W_ROCK);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,10,W_ROCK);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,10,W_ROCK);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,10,W_ROCK);
						}
					}
				}
				playa->curTimer = 0;
			}
		}

		ResetBuffer();
		DrawEffs();
		DrawEnts();
		NextFrame();
		if(keys[SDLK_ESCAPE]) done = 1;
	}while(!done);
	exit(0);
	return 0;

}
void CleanUpAll(){
	ClearAll();
	CloseSprites();
}

void Init_All(){
	InitParts();
	InitLvl();
	atexit(CleanUpAll);
}