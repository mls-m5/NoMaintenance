/*
 * Phykoser.h
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#ifndef PHYKOSER_H_
#define PHYKOSER_H_

#include "Player.h"
#include "WeaponCollection.h"

class Phykoser: public Player {
	int WheelY;
	int CWheelY[2];
	double WheelRotate; bool OnGround; int TurnIT; long Aim; long XAim;

	bool Dying; bool JetsOn; bool SwitchJet; long SwitchDelay; long JetRotation;
	bool CrossVar;
	WeaponCollection Weapons;
public:
	Phykoser();
	virtual ~Phykoser();

	void TimeTab();

	void Init(double X, double Y, double XSpeed2, double YSpeed2, int Number);

	void WheelCalculate(double Val);


	void Damage(long Val);

	void Die();

	void DropGuy();

	void PickUp(std::string Item);

	void Render();
};

#endif /* PHYKOSER_H_ */
