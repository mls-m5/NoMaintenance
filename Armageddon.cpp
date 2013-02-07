/*
 * Armageddon.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Armageddon.h"
#include "aux.h"
#include "Meteor.h"

Armageddon::Armageddon() {
	NextAttack = 0;
}

Armageddon::~Armageddon() {
	// TODO Auto-generated destructor stub
}

long NextAttack;

void Armageddon::Fire(double X, double Y, double XAim, double YAim, int Turn, bool isFire){
    NextAttack = NextAttack - 1;
    if (NextAttack < 0) {
        long MapWidth;
        MapWidth = FrmScreen.GetMapWidth();
        NextAttack = 10;
        auto nMet = new Meteor;
        nMet->Init(MapWidth * Rnd(), -100., Rnd() * 10. - 5., Rnd() * 10. + 10.);
        FrmScreen.AddObject(nMet);
    }
}
