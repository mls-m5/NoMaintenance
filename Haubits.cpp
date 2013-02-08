/*
 * Haubits.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Haubits.h"
#include "common.h"
#include "Spark.h"

struct Position{
	double X,Y;
};
Haubits::Haubits() {
	// TODO Auto-generated constructor stub

}

Haubits::~Haubits() {
	// TODO Auto-generated destructor stub
}

void Haubits::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
	if (!isFire) { return;;}
	    if (MyPlayer->getItem(1) < 100 || MyPlayer->getItem(6) < 2 || MyPlayer->getItem(2) < 20) { return;;}
	    MyPlayer->setItem( 1, 0);
	    MyPlayer->CalcItem(6, -2);
	    MyPlayer->CalcItem(2, -30);
	    long i; Position Speed; Position Pos;
	    Speed.X = XAim / 10 * Turn;
	    Speed.Y = YAim / 10;
	    Pos.X = X + XAim / 3 * Turn;
	    Pos.Y = Y + YAim / 3;
	    FrmScreen.DrawPlPic(ddbExp, X - 15 + XAim / 4 * Turn, Y - 15 + YAim / 4, 0);
	    for(i = 0; i <= 100; ++i){
	        Pos.X = Pos.X + Speed.X;
	        Pos.Y = Pos.Y + Speed.Y;
	        if (FrmScreen.GetMap((Pos.X), (Pos.Y)) || FrmScreen.isPlayer((Pos.X), (Pos.Y))) { break;}
	    }
	    PlaySound(dsFire6);
	    if (i == 101) { return;;}
	    Pos.X = Pos.X - Speed.X;
	    Pos.Y = Pos.Y - Speed.Y;
	    FrmScreen.Explosion((Pos.X), (Pos.Y), 1, 5, 5);
	    for(i = 0; i <= 10; ++i){
	        auto nSpark = new Spark;
	        nSpark->Init((Pos.X), (Pos.Y), Rnd() * 10 - 5, Rnd() * 10 - 5);
	        FrmScreen.AddObject(nSpark);
	    }
	    for(i = 0; i <= 3; ++i){
	        FrmScreen.MakeSmoke((Pos.X), (Pos.Y), -Speed.X + Rnd() * 4 - 2, -Speed.Y + Rnd() * 4 - 2);
	    }
}


