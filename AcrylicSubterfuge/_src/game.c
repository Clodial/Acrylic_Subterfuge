#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include "level.h"
#include "entity.h"

/******
/
/	Explaining the 5 visual effects
/
******/
/*****
/
/	Explaining the 5 powerup types
/
*****/

/*****
/
/	Explaining the player controls
/
*****/

/*****
/
/	Explaining the Entity Types
/
*****/
extern SDL_Surface *screen;
extern SDL_Surface *buffer;
extern SDL_Rect Camera;

void Init_All();

SDL_Event Event;

int main(int argc, char *argv[]){
	int done;
	int keyn;
	int tCol;
	int i;
	int ci;
	Uint8 *keys;
	Init_Graphics();
	done = 0;
	Init_All();
	do{
		SDL_PumpEvents();
		keys = SDL_GetKeyState(&keyn);
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