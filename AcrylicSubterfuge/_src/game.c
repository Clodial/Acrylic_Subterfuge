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

void Init_All();

SDL_Event Event;

int main(int argc, char *argv[]){
	SDL_Surface *temp;
	SDL_Surface *bg;
	Sprite *spr; //for creating player weapons
	int done;
	int keyn;
	Uint8 *keys;
	time_t t;

	srand((unsigned) time(&t));
	Init_Graphics();
	done = 0;
	Init_All();
	do{
		UpdateParts();
		SDL_PumpEvents();
		keys = SDL_GetKeyState(&keyn);
		
		if(keys[SDLK_a]){
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
		}else if(keys[SDLK_d]){
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
		}else if(keys[SDLK_w]){
			if(direction == 0){
				if(placeFree(playa->x,playa->y - 2) && playa->y-2 > 0)
				playa->y -= 2;
			}else if(direction == 1){
				if(placeFree(playa->x + 2,playa->y) && playa->x+2 < GAMEW)
				playa->x += 2;
			}else if(direction == 2){
				if(placeFree(playa->x,playa->y + 2) && playa->y+2 < GAMEH)
				playa->y += 2;
			}else{
				if(placeFree(playa->x - 2,playa->y) && playa->x-2 > 0)
				playa->x -= 2;
			}
		}else if(keys[SDLK_s]){
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
		}

		if(keys[SDLK_LEFT]){
			if(playa->curTimer >= playa->timer){
				spr = LoadSprite("_img/spr_bP.png",16,16,1);
				if(direction == 0){
					CreateBullet(playa->x+8,playa->y+8,spr,-4,0,10,W_NORM);
				}else if(direction == 1){
					CreateBullet(playa->x+8,playa->y+8,spr,0,-4,10,W_NORM);
				}else if(direction == 2){
					CreateBullet(playa->x+8,playa->y+8,spr,4,0,10,W_NORM);
				}else{
					CreateBullet(playa->x+8,playa->y+8,spr,0,4,10,W_NORM);
				}
				playa->curTimer = 0;
			}
		}else if(keys[SDLK_UP]){
			if(playa->curTimer >= playa->timer){
				spr = LoadSprite("_img/spr_bP.png",16,16,1);
				if(direction == 0){
					CreateBullet(playa->x+8,playa->y+8,spr,0,-4,10,W_NORM);
				}else if(direction == 1){
					CreateBullet(playa->x+8,playa->y+8,spr,4,0,10,W_NORM);
				}else if(direction == 2){
					CreateBullet(playa->x+8,playa->y+8,spr,0,4,10,W_NORM);
				}else{
					CreateBullet(playa->x+8,playa->y+8,spr,-4,0,10,W_NORM);
				}
				playa->curTimer = 0;
			}
		}else if(keys[SDLK_RIGHT]){
			if(playa->curTimer >= playa->timer){
				spr = LoadSprite("_img/spr_bP.png",16,16,1);
				if(direction == 0){
					CreateBullet(playa->x+8,playa->y+8,spr,4,0,10,W_NORM);
				}else if(direction == 1){
					CreateBullet(playa->x+8,playa->y+8,spr,0,4,10,W_NORM);
				}else if(direction == 2){
					CreateBullet(playa->x+8,playa->y+8,spr,-4,0,10,W_NORM);
				}else{
					CreateBullet(playa->x+8,playa->y+8,spr,0,-4,10,W_NORM);
				}
				playa->curTimer = 0;
			}
		}else if(keys[SDLK_DOWN]){
			if(playa->curTimer >= playa->timer){
				spr = LoadSprite("_img/spr_bP.png",16,16,1);
				if(direction == 0){
					CreateBullet(playa->x+8,playa->y+8,spr,0,4,10,W_NORM);
				}else if(direction == 1){
					CreateBullet(playa->x+8,playa->y+8,spr,-4,0,10,W_NORM);
				}else if(direction == 2){
					CreateBullet(playa->x+8,playa->y+8,spr,0,-4,10,W_NORM);
				}else{
					CreateBullet(playa->x+8,playa->y+8,spr,4,0,10,W_NORM);
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
	CloseSprites();
}

void Init_All(){
	InitParts();
	InitLvl();
	atexit(CleanUpAll);
}