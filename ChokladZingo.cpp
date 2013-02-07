/*
 * ChokladZingo.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "ChokladZingo.h"
#include "NukeGrenade.h"
#include "aux.h"

ChokladZingo::ChokladZingo() {
	// TODO Auto-generated constructor stub

}

ChokladZingo::~ChokladZingo() {
	// TODO Auto-generated destructor stub
}

void ChokladZingo::Fire(double X, double Y, double XAim, double YAim, int Turn,
		bool isFire) {
    if (! isFire) { return;;}
    if (MyPlayer->getItem(1) < 200 || MyPlayer->getItem(2) < 10) { return;;}
    MyPlayer->CalcItem(1, -200);
    MyPlayer->CalcItem(2, -30);
    auto nGren = new NukeGrenade;
    nGren->Init(X + XAim / 4 * Turn, Y + YAim / 4, XAim / 8 * Turn, YAim / 8);
    FrmScreen.AddObject(nGren);
    PlaySound(dsLaunch);

}


