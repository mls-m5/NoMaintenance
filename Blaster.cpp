/*
 * Blaster.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Blaster.h"
#include "Blast.h"
#include "aux.h"

Blaster::Blaster() {
	KeyDown = 0;

}

Blaster::~Blaster() {
	// TODO Auto-generated destructor stub
}

void Blaster::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {


	if (! isFire && KeyDown) {
		auto nBomb = new Blast;
		nBomb->Init(X + XAim / 3 * Turn, Y + YAim / 3, XAim / 5 * Turn, YAim / 5, Charge / 5 + 2);
		FrmScreen.AddObject(nBomb);

		if (XAim || YAim) {
			PlaySound(dsFire5);
		}
		else{
			PlaySound(dsLaunch);
		}
		KeyDown = 0;
	}
	else if (isFire && !KeyDown) {
		Charge = 1;
		KeyDown = 1;
	}
	else if (isFire && KeyDown) {
		if (Charge <500){
			Charge = Charge + 1;
		}
		FrmScreen.SetWeaponBar(MyPlayer->MyNumber, (double) Charge / 500.);
	}

}


