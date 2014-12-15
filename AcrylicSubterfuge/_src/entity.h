#ifndef _ENTITY_
#define _ENTITY_

#include "SDL.h"
#include "SDL_keyboard.h"
#include "SDL_keysym.h"
#include "graphics.h"

#define MAXENTITIES 1024
#define MAXSPEED 4.0f
#define ACCEL 0.5f

//For Crazy Powerup effect 1 -> SPIN DA WORLD
enum POS{
	P_RIGHT, P_LEFT, P_UP, P_DOWN
};

//Decide which enemy will spawn for specific thing... whatever... blagh
//E_STRT -> Back and forth movement
//E_DIAG -> Bounces across stage diagonally
//E_FOL -> Move toward direction of player
//	Think of this as moving in specific degrees based on the player location
//	As in, it won't be perfect, this is more for simpler box collisions
//E_SNAKE -> Hits a wall, goes in the next verticy
enum ENTYPE{
	E_STRT, E_DIAG, E_FOL, E_PHASE,  E_SNAKE
};

//Entity types (SC represents Scene)
enum SCTYPE{
	S_WALL, S_PLAYER, S_SPAWN, S_BULLET, S_EFFECT, S_POWER
};

enum DIR{
	D_RIGHT, D_LEFT, D_UP, D_DOWN
};

//this is for an added game feature I wanted to add
enum WALLSTATE{
	W_START, W_EMPTY, W_WALL
};

typedef struct Ent{

	Sprite			*sprite;
	int				x,y,z;	//z represents depth (sigh)
	int				w,h;
	int				vx, vy;	//speed, duh
	int				pos;	//this is for one of the crazy powerups (haven't figured it out yet)
	int				type;	
	int 			hp;

	int				power;	//current powerup/weapon
	int				powLen; //powerup length			
	int				curA;	//ammo value
	int				maxA;

	int 			timer;

	int 			solid;

	Entity 			*owner;
	int				enemy;	//only used if SCTYPE = S_ENEMY
	
	int				used;	//	I'M NOT GONNA BLOW SHIT UP, AGAIN
	void			(*think)(struct Ent *self); //do on update
	void			(*touch)(struct Ent *self, struct Ent *other); //when enemies touch player and when bullets hit 

}Entity;
//This is only for the instances that directly can tell the player in what position 
//they are playing the game in.
typedef struct Eff{
	Sprite 			*sprite;
	int 			x,y;
	int 			w,h;
	int 			vx,vy;
	int 			used;
	void 			(*think)(struct Ent *self);
}Effect;

void InitEnt();
Entity *NewEnt();
void DestEnt(Entity *ent);
void ClearAllEnt();
void DrawEnt(Entity *ent);
void DrawEnts();
void UpdateEnt();

Entity *CreatePlayer(int x, int y, Sprite *sprite, );
void 	PlayerThink(Entity *self);
void 	PlayerTouch(Entity *self, Entity *other);

Entity *CreateBlock(int x, int y, Sprite *sprite));
void BlockThink(Entity *self);

Entity *CreateBullet(int x, int y, Sprite *sprite, int vx, int vy, Entity *owner, int timer);
void	BulletThink(Entity *self);
void 	BulletTouch(Entity *self, Entity *other);

Entity *CreatePowerup(int x, int y, Sprite *sprite, int timer);
void	PowerThink(Entity *self);
void 	PowerTouch(Entity *self, Entity *other);