/*
 * Miligun.cpp
 *
 *  Created on: 6 feb 2013
 *      Author: mattias
 */

#include "Miligun.h"
#include "common.h"
#include "SoundFunctions.h"
#include "MiniShot.h"

Miligun::~Miligun() {
}

void Miligun::Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire){
    if (!isFire) { return;;}
    if (MyPlayer->getItem(1) < 30) { return;;}
    MyPlayer->CalcItem(1, -30);
    auto nShot = new MiniShot;
    nShot->Init(X + XAim / 3 * Turn, Y + YAim / 3, XAim / 3 * Turn + Rnd() * 4 - 2, YAim / 3 + Rnd() * 4 - 2);
    FrmScreen.AddObject(nShot);
    PlaySound(dsFire8);
}


