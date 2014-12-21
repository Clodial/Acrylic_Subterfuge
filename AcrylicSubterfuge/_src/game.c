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
			curPower = P_LASER;
		}else if(keys[SDLK_6]){
			curPower = P_WHITE;
			if(ww != 1)
				ww = 1;
		}else if(keys[SDLK_7]){
			curPower = P_KEEP;
		}else if(keys[SDLK_8]){
			if(level == 0){
				level = 1;
			}if(level == 1){
				level = 2;	
			}if(level == 2){
				level = 3;	
			}if(level == 3){
				level = 4;	
			}if(level == 4){
				level = 5;	
			}else{
				killCount = 0;	
			}
		}
		if(keys[SDLK_a]){
			if(playa->power != P_KEEP){
				if(direction == 0){
					if(placeFree(playa->x - 2,playa->y) && playa->x - 2 > 0)
					playa->x -= 2;
				}else if(direction == 1){
					if(placeFree(playa->x,playa->y-2) && playa->y - 2 >0)
					playa->y -= 2;
				}else if(direction == 2){
					if(placeFree(playa->x + 2,playa->y) && playa->x + 2 < GAMEW)
					playa->x += 2;
				}else{
					if(placeFree(playa->x,playa->y+2) && playa->y +2 <GAMEH)
					playa->y += 2;
				}
			}else{
				if(placeFree(playa->x - 2,playa->y) && playa->x - 2 > 0)
					playa->x -= 2;
			}
		}else if(keys[SDLK_d]){
			if(playa->power != P_KEEP){
				if(direction == 0){
					if(placeFree(playa->x + 2,playa->y) && playa->y - 2 < GAMEW)
					playa->x += 2;
				}else if(direction == 1){
					if(placeFree(playa->x,playa->y+2) && playa->y + 2 < GAMEH)
					playa->y += 2;
				}else if(direction == 2){
					if(placeFree(playa->x - 2,playa->y) && playa->x-2 > 0)
					playa->x -= 2;
				}else{
					if(placeFree(playa->x,playa->y-2) && playa->y-2 > 0)
					playa->y -= 2;
				}
			}else{
				if(placeFree(playa->x + 2,playa->y) && playa->y - 2 < GAMEW)
					playa->x += 2;
			}
		}else if(keys[SDLK_w]){
			if(playa->power != P_KEEP){
				if(direction == 0){
					if(placeFree(playa->x,playa->y - 2) && playa->y-2 > 0)
					playa->y -= 2;
				}else if(direction == 1){
					if(placeFree(playa->x + 2,playa->y) && playa->x+34 < GAMEW)
					playa->x += 2;
				}else if(direction == 2){
					if(placeFree(playa->x,playa->y + 2) && playa->y+34 < GAMEH)
					playa->y += 2;
				}else{
					if(placeFree(playa->x - 2,playa->y) && playa->x-2 > 0)
					playa->x -= 2;
				}
			}else{
				if(placeFree(playa->x,playa->y - 2) && playa->y-2 > 0)
					playa->y -= 2;
			}
		}else if(keys[SDLK_s]){
			if(playa->power != P_KEEP){
				if(direction == 0){
					if(placeFree(playa->x,playa->y + 2) && playa->y+2 < GAMEH)
					playa->y += 2;
				}else if(direction == 1){
					if(placeFree(playa->x - 2,playa->y) && playa->x-2 > 0)
					playa->x -= 2;
				}else if(direction == 2){
					if(placeFree(playa->x,playa->y - 2) && playa->y-2 > 0)
					playa->y -= 2;
				}else{
					if(placeFree(playa->x + 2,playa->y) && playa->x+2 < GAMEW)
					playa->x += 2;
				}
			}else{
				if(placeFree(playa->x,playa->y + 2) && playa->y+2 < GAMEH)
					playa->y += 2;
			}
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
					}else if(playa->power == P_LASER){
						spr = LoadSprite("_img/spr_bPL.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,60,W_LASER);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,60,W_LASER);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,60,W_LASER);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,60,W_LASER);
						}
					}else if(playa->power == P_SHOT){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						r1 = rand()%4-2;
						r2 = rand()%4-2;
						r3 = rand()%4-2;
						r4 = rand()%4-2;
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r1,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r2,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r3,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r4,10,W_NORM);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,-8,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,r2,-8,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,r3,-8,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,r4,-8,10,W_NORM);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,r1,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,8,r2,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,8,r3,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,8,r4,10,W_NORM);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,8,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,r2,8,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,r3,8,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,r4,8,10,W_NORM);
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
					}else if(playa->power == P_LASER){
						spr = LoadSprite("_img/spr_bPL.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,60,W_LASER);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,60,W_LASER);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,60,W_LASER);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,60,W_LASER);
						}
					}else if(playa->power == P_SHOT){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						r1 = rand()%4-2;
						r2 = rand()%4-2;
						r3 = rand()%4-2;
						r4 = rand()%4-2;
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,-8,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,r2,-8,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,r3,-8,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,r4,-8,10,W_NORM);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,r1,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,8,r2,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,8,r3,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,8,r4,10,W_NORM);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,8,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,r2,8,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,r3,8,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,r4,8,10,W_NORM);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r1,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r2,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r3,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r4,10,W_NORM);
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
					}else if(playa->power == P_LASER){
						spr = LoadSprite("_img/spr_bPL.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,60,W_LASER);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,60,W_LASER);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,60,W_LASER);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,60,W_LASER);
						}
					}else if(playa->power == P_SHOT){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						r1 = rand()%4-2;
						r2 = rand()%4-2;
						r3 = rand()%4-2;
						r4 = rand()%4-2;
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,r1,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,8,r2,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,8,r3,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,8,r4,10,W_NORM);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,8,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,r2,8,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,r3,8,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,r4,8,10,W_NORM);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r1,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r2,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r3,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r4,10,W_NORM);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,-8,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,r2,-8,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,r3,-8,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,r4,-8,10,W_NORM);
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
					}else if(playa->power == P_LASER){
						spr = LoadSprite("_img/spr_bPL.png",16,16,1);
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,8,60,W_LASER);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,0,60,W_LASER);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,0,-8,60,W_LASER);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,8,0,60,W_LASER);
						}
					}else if(playa->power == P_SHOT){
						spr = LoadSprite("_img/spr_bP.png",16,16,1);
						r1 = rand()%4-2;
						r2 = rand()%4-2;
						r3 = rand()%4-2;
						r4 = rand()%4-2;
						if(direction == 0){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,8,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,r2,8,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,r3,8,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,r4,8,10,W_NORM);
						}else if(direction == 1){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r1,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r2,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r3,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r4,10,W_NORM);
						}else if(direction == 2){
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,r1,-8,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,r2,-8,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,r3,-8,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,r4,-8,10,W_NORM);
						}else{
							e1 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r1,10,W_NORM);
							e2 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r2,10,W_NORM);
							e3 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r3,10,W_NORM);
							e4 = CreateBullet(playa->x+8,playa->y+8,spr,-8,r4,10,W_NORM);
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