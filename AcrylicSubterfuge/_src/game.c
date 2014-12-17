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

	temp = IMG_Load("_img/lvl1_horz.png");
	if(temp != NULL){
		bg = SDL_DisplayFormat(temp);
	}
	SDL_FreeSurface(temp);
	if(bg != NULL){
		SDL_BlitSurface(bg,NULL,buffer,NULL);
	}
	done = 0;
	Init_All();
	do{
		UpdateParts();
		SDL_PumpEvents();
		keys = SDL_GetKeyState(&keyn);
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
	//InitEnt();
	//InitEff();
	InitLvl();
	atexit(CleanUpAll);
}