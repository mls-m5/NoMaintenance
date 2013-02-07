/*
 * Blast.cpp
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#include "Blast.h"
#include "aux.h"

Blast::Blast() {
	// TODO Auto-generated constructor stub

}

Blast::~Blast() {
	// TODO Auto-generated destructor stub
}



void Blast::Init(double x, double y, double xs, double ys, long charged){
	xpos = x;
	ypos = y;
	xspeed = xs;
	yspeed = ys;
	charge = charged;
}

void Blast::TimeTab() {
	yspeed = yspeed + 0.3;
	xpos = xpos + xspeed;
	ypos = ypos + yspeed;
	if(FrmScreen.GetMapLine((xpos), (ypos), xspeed, yspeed) != 0){
		FrmScreen.RemoveObject(this);
		FrmScreen.CustomExplosion (xpos - xspeed / 2., ypos - yspeed / 2., charge + 1, (int) charge + 5, charge);
		PlaySound (dsExplosion);
		FrmScreen.MakeQuake (charge);
	}
	if(FrmScreen.isPlayer((xpos), (ypos)) != 0 ){
		FrmScreen.RemoveObject(this);
		FrmScreen.CustomExplosion( xpos - xspeed / 2., ypos - yspeed / 2., charge + 1, (int) charge + 5, charge);
		PlaySound( dsExplosion);
		FrmScreen.MakeQuake (charge);
	}
}

void Blast::Render() {

	FrmScreen.DrawPlLine (xpos, ypos, xpos - xspeed, ypos - yspeed, (int) (charge + 1), Color(1,1,0), true);
}
