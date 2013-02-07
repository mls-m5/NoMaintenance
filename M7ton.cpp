/*
 * M7ton.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "M7ton.h"
#include "aux.h"
#include "Grenade.h"

M7ton::M7ton() {
	// TODO Auto-generated constructor stub

}

M7ton::~M7ton() {
	// TODO Auto-generated destructor stub
}

void M7ton::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
    if (!isFire) { return;;}
    if (MyPlayer->getItem(1) < 200 || MyPlayer->getItem(2) < 10) { return;;}
    MyPlayer->CalcItem(1, -200);
    MyPlayer->CalcItem(2, -10);
    auto nGren = new Grenade;
    nGren->Init(X + XAim / 4 * Turn, Y + YAim / 4, XAim / 8 * Turn, YAim / 8);
    FrmScreen.AddObject(nGren);
    if (XAim || YAim) {
    	PlaySound(dsFire5);
    }
    else{
    	PlaySound(dsLaunch);
    }

}


