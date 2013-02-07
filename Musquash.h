/*
 * Musquash.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef MUSQUASH_H_
#define MUSQUASH_H_

#include "Solid.h"
#include "Player.h"
#include "WeaponCollection.h"

class Musquash: public Player {

	static const int inAir = 0;
	static const int inDirt = 1;
	static const int inRock = 2;
	static const int inEnemy = 3;

public:

	int CWheelY[2]; int WheelY;
	double WheelRotate;
	bool OnGround;
	int TurnIT; double Aim; double XAim; double CAim;
	WeaponCollection Weapons;
	bool Dying; long SpecialLeft; long DTurnOn; int Target;
	bool CrossVar;
	////////////////NinjaRep////////////////////////;
	double NinjaPosX, NinjaPosY; double nXS; double nYS;
	bool NinjaOut; int NinjaMode; long NinjaPic; Player *TheEnemy; double NinjaLength;
	////////////////////////////////////////////////;

	Musquash();
	virtual ~Musquash();


	void TimeTab();

	void Init(double X, double Y, double XSpeed2, double YSpeed2, int Number);

	void WheelCalculate(double Val);


	void Damage(long Val);

	void Die();

	void DropGuy();

	void PickUp(std::string Item);

	void DoNinjarope();

	void Render();
};

#endif /* MUSQUASH_H_ */
