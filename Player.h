/*
 * Player.h
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Solid.h"
#include <string>


class Player: public Solid {

protected:
	int Items[8];
	int ItemMax[8]; int WheelY;
public:
	double XPos, YPos, XSpeed, YSpeed, Width, Height;
	virtual void Damage(long x){} ;
	virtual void Force(double x, double y){XSpeed += x; YSpeed += y;}

	Player(){} ;
	virtual ~Player(){} ;

	virtual void Init(double X, double Y, double XSpeed2, double YSpeed2, int Number){};

	virtual bool isGuy() {return false;}

	virtual void Die(){} ;

	virtual void setItem(int Index, int Val);

	virtual long getItem(int Index){return Items[Index];};

	virtual void CalcItem(int Index, long Val);

	virtual void DropGuy(){} ;

	virtual void PickUp(std::string Item){} ;

	virtual void UpDateItems(){} ;

	virtual void DoNinjarope(){} ;

	double getXPos() {return XPos;};

	double getYPos() {return YPos;};




	double getWidth(){return Width;};


	double getHeight(){return Height;} ;



	int MyNumber;
};

#endif /* PLAYER_H_ */
