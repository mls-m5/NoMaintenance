/*
 * Meteor.cpp
 *
 *  Created on: 23 jan 2013
 *      Author: mattias
 */

#include "Meteor.h"
#include "aux.h"
#include "Screen.h"


Meteor::Meteor() {
	// TODO Auto-generated constructor stub

}

void Meteor::Init(double X, double Y, double Xs, double Ys) {
	XPos = X;
	YPos = Y;
	XSpeed = Xs;
	YSpeed = Ys;
}

void Meteor::TimeTab() {
	frmScreen.MakeSmoke (XPos, YPos, Rnd() * 2 - 1, Rnd() * 2 - 1, 1);
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	if (frmScreen.GetMapLine(XPos, YPos, XSpeed, YSpeed)){
		frmScreen.HugeExplosion (XPos, YPos, 100, 150);
		frmScreen.RemoveObject (this);
		frmScreen.MakeQuake (15);
		PlaySound (dsExplosion);
	}

}

void Meteor::Render() {
	frmScreen.DrawPlPic(ddbExp, XPos - 15, YPos - 15, 0);
}

Meteor::~Meteor() {
	// TODO Auto-generated destructor stub
}

