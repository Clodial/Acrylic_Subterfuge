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

void Init_All();

SDL_Event Event;

int main(int argc, char *argv[]){
	SDL_Surface *temp;
	SDL_Surface *bg;
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
		
		if(keys[SDLK_LEFT]){
			playa->x -= 2;
		}else if(keys[SDLK_RIGHT]){
			playa->x += 2;	
		}else if(keys[SDLK_UP]){
			playa->y -= 2;
		}else if(keys[SDLK_DOWN]){
			playa->y += 2;
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