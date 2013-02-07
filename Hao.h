/*
 * Hao.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef HAO_H_
#define HAO_H_

#include "Player.h"
#include "WeaponCollection.h"

class Hao: public Player {
//	int MyNumber;
	bool OnGround; int TurnIT;
	long Aim; long XAim; float CAim;
	bool Dying;
	WeaponCollection Weapons;
public:
	Hao();
	virtual ~Hao();

	void Init(double X, double Y, double XSpeed2, double YSpeed2, int Number);

	void TimeTab();
	void Render();

	bool isGuy() {return false;}

	void Damage(long val);

	void Die() ;

	void DropGuy() ;

	void PickUp(std::string Item) ;

	void UpDateItems() ;

	void Terminate();
};

#endif /* HAO_H_ */
