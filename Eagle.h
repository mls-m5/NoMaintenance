/*
 * Eagle.h
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#ifndef EAGLE_H_
#define EAGLE_H_

#include "Player.h"
#include "Canoner.h"
#include <string>
#include "CarlGustaf.h"

class Eagle: public Player {
	int WheelY;
	int CWheelY; float WheelRotate; bool OnGround; int TurnIT;
	Canoner Weapon1; CarlGustaf Weapon2;
	bool Dying;
public:
	int MyNumber;
	Eagle();
	virtual ~Eagle();



	void TimeTab();
	void Render();

	void Init(double X, double Y, double XSpeed2, double YSpeed2, int Number);

	void WheelCalculate(float Val);

	void Damage(long Val);

	void Die();

	void Terminate();

	void DropGuy();

	void PickUp(std::string Item);

	void UpDateItems();
};

#endif /* EAGLE_H_ */
