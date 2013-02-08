/*
 * GasEel.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "GasEel.h"
#include "common.h"
#include "FireBomb.h"
static const long MaxAmmo = 20;

GasEel::GasEel() {
	KeyDown = 0;
	Ammo = 0;
	Delay = 0;

}

GasEel::~GasEel() {
}

void GasEel::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
	if (Ammo < MaxAmmo) {
//        Delay = Delay + 1;
//        if (Delay > 3) {
            Ammo = Ammo + 1./3.;
//            Delay = 0;
//        }
    }
    if (isFire) {
        if (Ammo > 2 && !KeyDown) {
            auto Shot = new FireBomb;
            Shot->Init(X + XAim / 3 * Turn, Y + YAim / 3, XAim / 5 * Turn, YAim / 5, Ammo);
            FrmScreen.AddObject(Shot);
            Ammo = Ammo - 15;
            if (Ammo < 0) { Ammo = 0;}
            PlaySound(dsLaunch);
        }
        KeyDown = 1;
    }else{
        KeyDown = 0;
    }
    FrmScreen.SetWeaponBar( MyPlayer->MyNumber,(double) Ammo / (double)MaxAmmo);
}
