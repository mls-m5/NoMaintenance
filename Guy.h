/*
 * Guy.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef GUY_H_
#define GUY_H_

#include "Player.h"
#include <string>
#include "WeaponCollection.h"

class Guy: public  Player {
public:
	Guy();
	virtual ~Guy();

	bool isGuy(){ return true; }

	void CalcItem(int , double ) ;


	void PickUp(std::string item) ;


	long getItem(long i) ;

	void setItem(int Index, long Val);

	double getXPos() ;


	double getYPos() ;


	void Damage(long damage) ;


	double getWidth() ;


	double getHeight() ;


	void TimeTab() ;

	void Render();

	bool EW(Player *player);

	void Init(double xPos, double yPos, double xSpeed, double ySpeed,
			int myNumber);


	void Die();

	void UpDateItems();

	long PictureNumber;
	long Items[8], ItemMax[8];
	long WheelY;
	long GuyStep; bool OnGround; int TurnIT; long Aim; long XAim;
	WeaponCollection Weapons;
	bool Dying;
	bool CrossVar;

};

#endif /* GUY_H_ */
