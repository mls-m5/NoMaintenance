/*
 * aux.h
 *
 *  Created on: 23 jan 2013
 *      Author: mattias
 */

#ifndef AUX_H_
#define AUX_H_


const double PI = 3.14159265359;

//enum{ //De olika bildnummrerna
//	ddChassi = 0,
//	ddWheel = 1,
//	ddLevel = 2,
//	ddEagle = 3,
//	ddSmoke = 4,
//	ddbExp = 5,
//	ddSpark = 6,
//	ddBomb = 7,
//	ddRLevel = 8,
//	ddCrossHair = 9,
//	ddGuy = 10,
//	ddAirokurtz = 11,
//	ddItem = 12,
//	ddDisk = 13,
//	ddTurret = 14,
//	ddMissile = 15,
//	ddShell = 16,
//	ddNuke = 17,
//	ddhExp = 18,
//	ddJetWheel = 19,
//	ddNinjaRope = 20,
//	ddMech = 21,
//	ddFlag = 22,
//	ddFlashbang = 23,
//
//	ddLast //Håller reda på räkningen
//};
//
//enum { //De olika ljudnummrerna
//	dsFire1,
//	dsFire2,
//	dsFire3,
//	dsFire4,
//	dsFire5,
//	dsFire6,
//	dsFire7,
//	dsFire8,
//	dsFire9,
//	dsShotgun,
//	dsExplosion,
//	dsReload,
//	dsReload2,
//	dsOpen,
//	dsLaser,
//	dsLaunch,
//	dsOusch,
//	dsDie,
//
//	dslast //Håller reda på räkningen
//};
//
//
//enum{// MapElement //Olika kart-element
//	mAir = 0, //Luft
//	mWater = 1, //Vatten (Används inte)
//	mRock = 2, //Sten\oförstörbar mark
//	mOut = 3, //Utanför kartan (Används inte)
//	mDirt = 4, //Jord
//};

const int ddChassi = 0;
const int ddWheel2 = 1;
const int ddLevel = 2;
const int ddEagle = 3;
const int ddSmoke = 4;
const int ddbExp2 = 5;
const int ddSpark = 6;
const int ddBomb = 7;
const int ddRLevel = 8;
const int ddCrossHair2 = 9;
const int ddGuy = 10;
const int ddAirokurtz = 11;
const int ddItem = 12;
const int ddDisk = 13;
const int ddTurret = 14;
const int ddMissile = 15;
const int ddShell = 16;
const int ddNuke = 17;
const int ddhExp = 18;
const int ddJetWheel = 19;
const int ddNinjaRope = 20;
const int ddMech = 21;
const int ddFlag = 22;
const int ddFlashbang = 23;
const int ddWheel = 24;
const int ddCrossHair = 25;
const int ddbExp = 26;

const int ddLast = 27;// Håller reda på räkningen



const int dsFire1 = 0;
const int dsFire2 = 1;
const int dsFire3 = 2;
const int dsFire4 = 3;
const int dsFire5 = 4;
const int dsFire6 = 4;
const int dsFire7 = 6;
const int dsFire8 = 7;
const int dsFire9 = 8;
const int dsShotgun = 9;
const int dsExplosion = 10;
const int dsReload = 11;
const int dsReload2 = 12;
const int dsOpen = 13;
const int dsLaser = 14;
const int dsLaunch = 15;
const int dsOusch = 16;
const int dsDie =  17;

const int dslast = 18; //'Håller reda på räkningen


const int mAir = 0; //Luft
const int mWater = 1; //Vatten (Används inte)
const int mRock = 2; //Sten\oförstörbar mark
const int mOut = 3; //Utanför kartan (Används inte)
const int mDirt = 4; //Jord

class Color{
public:
	unsigned int color;
	double r, g, b;

	Color(): color(0), r(0), g(0), b(0){};
	Color(double r, double g, double b);
	Color(unsigned int c);
};

#include "Screen.h"
#include "SoundFunctions.h"

double Rnd();
extern class Screen frmScreen;
#define FrmScreen frmScreen

inline int GetRot(double x, double y, int TotalRotate) {
	double Total;

	if (x > 0){
		if (y > 0){
			Total = x + y;
		}
		else{
			Total = x - y;
		}
	}
	else{
		if (y > 0){
			Total = -x +y;
		}
		else{
			Total = -x -y;
		}
	}
	if (x > 0){
		return (int) ((y/Total) * TotalRotate / 4 + TotalRotate / 4 * 3);
	}
	else if(x != 0){
		return (int) (-(y/Total) * TotalRotate / 4 + TotalRotate / 4);
	}
	else{
		return TotalRotate / 2;
	}
	//int a = (int) (((Math.atan2(x	, y) / Math.PI / 2. + 1) * TotalRotate));
	//return a;
}

double Rnd();

struct GameplayStruct{

    long Armor;
    long Ammo;
    long Blood;
    long Veihles;
    long StartV;
    long SoldierType[1];

};


extern GameplayStruct GamePlay;

#include <iostream>

using std::cout;
using std::endl;

#endif /* AUX_H_ */
