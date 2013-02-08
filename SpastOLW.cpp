/*
 * SpastOLW.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "SpastOLW.h"
#include "MiniShot.h"
#include "common.h"

SpastOLW::SpastOLW() {

}

SpastOLW::~SpastOLW() {
}


void SpastOLW::Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire){
    if (!isFire) { return;}
    if (MyPlayer->getItem(1) < 200) { return;;}
    MyPlayer->CalcItem(1, -200);
    for(int i = 0; i <= 4; ++i){
        auto nShot = new MiniShot;
        nShot->Init(X + XAim / 3 * Turn, Y + YAim / 3, XAim / 3 * Turn + Rnd() * 4 - 2, YAim / 3 + Rnd() * 4 - 2);
        FrmScreen.AddObject(nShot);
    }
    PlaySound(dsShotgun);

}
