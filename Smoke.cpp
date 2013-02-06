/*
 * Smoke.cpp
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#include "Smoke.h"
#include "aux.h"
#include <GL/glew.h>
#include "ImageFunctions.h"

Smoke::Smoke() {
	// TODO Auto-generated constructor stub

}

Smoke::~Smoke() {
	// TODO Auto-generated destructor stub
}


void Smoke::Init(double X, double Y, double Xs, double Ys, long SmokeType){
	CurrentRotate = 15;
	XPos = X;
	YPos = Y;
	XSpeed = Xs;
	YSpeed = Ys;
	mSmokeType = SmokeType;
}

void Smoke::TimeTab(){
	CurrentRotate = CurrentRotate - 1;
	if (CurrentRotate < 0) {
		frmScreen.RemoveObject(this);
	}
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	if (frmScreen.GetMap((XPos), (YPos))!= 0) {
		frmScreen.RemoveObject(this);
	}
}

void Smoke::Render(){
	FrmScreen.DrawPlPic(ddSmoke, XPos - 7, YPos - 7, 5 + 6 * mSmokeType - CurrentRotate / 3);
//	FrmScreen.DrawPlPic(ddSmoke, XPos - 7+ 15, YPos - 7, 5 + 6 * mSmokeType - CurrentRotate / 3);
}
