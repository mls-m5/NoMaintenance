/*
 * Weapon.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef WEAPON_H_
#define WEAPON_H_
#include "Player.h"

class Weapon {
public:
	Weapon(){};
	Weapon(Player *p): MyPlayer(p){}
	virtual ~Weapon(){};
	virtual void Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire){};
	virtual void setPlayer(Player *p){MyPlayer = p;} ;

	Player *MyPlayer;
};

#endif /* WEAPON_H_ */
