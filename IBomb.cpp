/*
 * IBomb.cpp
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#include "IBomb.h"
#include "common.h"

IBomb::IBomb() {
	// TODO Auto-generated constructor stub

}

IBomb::~IBomb() {
	// TODO Auto-generated destructor stub
}



void IBomb::Init(double X, double Y, long Limit){
	XPos = X;
	YPos = Y;
	TimeLimit = Limit + 1;
}

void IBomb::TimeTab(){
	TimeLimit = TimeLimit - 1;
	if (TimeLimit == 0) {
		FrmScreen.HugeExplosion(XPos + 15, YPos + 20, 80, 40);
		PlaySound(dsExplosion2);
	}
	if (TimeLimit == -5) {
		FrmScreen.HugeExplosion(XPos - 15, YPos + 10, 80, 40);
		PlaySound(dsExplosion2);
	}
	if (TimeLimit == -10) {
		FrmScreen.HugeExplosion(XPos + 15, YPos + 0, 80, 40);
		PlaySound(dsExplosion2);
	}
	if (TimeLimit == -15) {
		FrmScreen.HugeExplosion(XPos - 15, YPos - 10, 80, 40);
		PlaySound(dsExplosion2);
	}
	if (TimeLimit == -20) {
		FrmScreen.HugeExplosion(XPos + 15, YPos - 20, 80, 40);
		PlaySound(dsExplosion2);
	}
	if (TimeLimit < -20) { FrmScreen.RemoveObject(this);}
}
