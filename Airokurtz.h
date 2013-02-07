/*
 * Airokurtz.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef AIROKURTZ_H_
#define AIROKURTZ_H_

#include "Player.h"
#include "WeaponCollection.h"

class Airokurtz: public Player {

	int WheelY;
	bool OnGround; int TurnIT; long Aim; long XAim;
	WeaponCollection Weapons;
	bool Dying;
public:
	int MyNumber;
	Airokurtz();
	~Airokurtz();

	void Damage(long x) ;

	void Init(double X, double Y, double XSpeed2, double YSpeed2, int Number);

	void TimeTab();
	void Render();

	bool isGuy() {return false;}

	void Die() ;

	void DropGuy() ;

	void PickUp(std::string Item) ;

	void UpDateItems() ;
};

#endif /* AIROKURTZ_H_ */
