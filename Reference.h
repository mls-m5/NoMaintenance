/*
 * Reference.h
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#ifndef REFERENCE_H_
#define REFERENCE_H_

#include "Player.h"
#include "WeaponCollection.h"

class Reference: public Player {

	int CWheelY[2]; double WheelRotate;
	bool OnGround;
	int TurnIT; long Aim; long XAim;
	WeaponCollection Weapons;
	bool Dying; long SmokeTrace; long JumpLeft;
	bool CrossVar;

public:
	Reference();
	virtual ~Reference();

	void Init(double X, double Y, double XSpeed2, double YSpeed2, int Number);

	void TimeTab();

	void Render();

	bool isGuy() {return false;}

	void Die() ;

	void DropGuy() ;

	void PickUp(std::string Item) ;

	void UpDateItems() ;

	void Damage(long x);

	void MakeWarp();

	void WheelCalculate(float val);

};

#endif /* REFERENCE_H_ */
