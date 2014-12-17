#ifndef _ENTITY_
#define _ENTITY_

#include "SDL.h"
#include "SDL_keyboard.h"
#include "SDL_keysym.h"
#include "graphics.h"

#define MAXENTITIES 511
#define MAXEFFECTS 255
#define SP 4
#define MAXSPEED 16
#define LAYERS 3
#define MAXWALLS 13
#define MAXBULLETS 128
#define MAXENEMIES 20

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

//Though, let's be real, if I'm randomizing what enemies can come out, this is problematic
enum ENTYPE{
	E_STRT, E_DIAG, E_WEP, E_PHASE, E_SNAKE, E_BOX, E_CPY, E_DISP
};

//Entity types (SC represents Scene)
enum SCTYPE{
	S_WALL, S_PLAYER, S_SPAWN, S_BULLET, S_EFFECT, S_POWER, S_ENEMY
};

//affects state of the game, as well
enum POWUP{
	//powerups can only be rockets, shotguns, mines, lasers, lvlds, whitewashes, and lvlus
	P_NORM, P_ROCK, P_SHOT, P_MINE, P_LASER, P_KEEP, P_LVLU, P_LVLD, P_WHITE 
};
enum DIR{
	D_RIGHT, D_LEFT, D_UP, D_DOWN
};
enum WEAP{
	W_NORM, W_ROCK, W_MINE, W_LASER
};
typedef struct Ent{

	Sprite			*sprite;
	int				x,y,z;	//z represents depth (sigh)
	int				cX,cY; //current x and current y
	int				w,h;
	int				vx, vy;	//speed, duh
	int				pos;	//this is for one of the crazy powerups (haven't figured it out yet)
	
	int				dir;	//different from pos -> meant to determine what direction enemies will start out in (meant for 

	int				lx,ly,rx,ry,ux,uy,dx,dy; //oh boy oh boy, this is for that one powerup
					//This might be for a version of this game that's a little easier than what is currently available here... cuz...
	int				type;	
	int 			hp;

	int				solid;

	int				power;	//current powerup
	int				weapon; //weapon
	int				powLen; //powerup length

	int 			timer; //weapon power
	int				curTimer;

	int				fTimer;
	int				curFtimer;
	
	int				spTimer;
	int				curSpT;

	int				pWeapon; //I mean, if there is only two kinds of moving entitities besides bullets that can 'own' ammo
	int				enemy;	//only used if SCTYPE = S_ENEMY
	int 			frame;
	int				numFrames;
	int				used;	//	I'M NOT GONNA BLOW SHIT UP, AGAIN
	void			(*think)(struct Ent *self); //do on update
	void			(*touch)(struct Ent *self, struct Ent *other); //when enemies touch player and when bullets hit 

}Entity;
//This is only for the instances that directly can tell the player in what position 
//they are playing the game in.
typedef struct Eff{
	Sprite 			*sprite;
	int 			x,y,z;
	int				ix, iy; //the original positions of the lines for directional changes
	int 			w,h;
	int 			v;
	int 			used;
	int 			pos;
	int				curDir; //meant to change around directions and stuff

	int				type;

	int				curT;
	int				timer;

	void 			(*think)(struct Eff *self);
}Effect;

void InitParts();
void UpdateParts();
void ClearAll();

Entity *NewEnt();
Entity *NewWall();
Entity *NewBullet();
Entity *NewEnem();
void DestEnt(Entity *ent);
void DrawEnt(Entity *ent);
void DrawEnts();

Effect *NewEff();
void DrawEffs();
void DrawEff(Effect *eff);
void DestEff(Effect *eff);

Entity *CreatePlayer(int x, int y, Sprite *sprite, int nF);
void 	PlayerThink(Entity *self);
void 	PlayerTouch(Entity *self, Entity *other);

Entity *CreateBlock(int x, int y, Sprite *sprite);
Entity *NewWall();
void BlockThink(Entity *self);

Entity *CreateBullet(int x, int y, Sprite *sprite, int vx, int vy, int timer, int type);
Entity *NewBull();
void	BulletThink(Entity *self);
void 	BulletTouch(Entity *self, Entity *other);

Entity *CreatePowerup(int x, int y);
void	PowerThink(Entity *self);
void 	PowerTouch(Entity *self, Entity *other);
void 	PowerSpawn();

Entity *CreateSpawn(int x, int y, Sprite *sprite);

Entity *CreateEnemy(int x, int y, Sprite *sprite, int type, int nF, int hp);
void	EnemyThink(Entity *self);
void	EnemyTouch(Entity *self, Entity *other);
//Effect Code
Effect *CreateBGEff(int x, int y, Sprite *sprite);
void 	BGThink(Effect *self);

Effect *CreateLine(int x, int y, Sprite *sprite, int vx);
void	LineEfThink(Effect *self);

Effect *CreateSpecial(int x, int y, Sprite *sprite, int timer, int type); //for level 6 and whitewashes
void	SpecThink(Effect *self);
//extra functions
int placeFree(int x, int y);//GAMEMAKER, no seriously... GAMEMAKER
int placeFree2(int x, int y, int w, int h);
#endif