/*
 * EldFunkarProj.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "EldFunkarProj.h"
#include "common.h"
#include <math.h>
#include "Spark.h"

EldFunkarProj::EldFunkarProj() {
	// TODO Auto-generated constructor stub

}

EldFunkarProj::~EldFunkarProj() {
	// TODO Auto-generated destructor stub
}



void EldFunkarProj::Init(double X, double Y, double Xs, double Ys){
	XPos = X;
	YPos = Y;
	XSpeed = Xs;
	YSpeed = Ys;
}

void EldFunkarProj::TimeTab(){
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	XSpeed = XSpeed / 1.2;
	YSpeed = YSpeed / 1.05;
	FrmScreen.MakeSmoke(XPos - XSpeed, YPos - YSpeed, -XSpeed / 1.5 + Rnd() * 2 - 1, -YSpeed / 1.5 + Rnd() * 2 - 1, 0);

	if (FrmScreen.GetMapLine((XPos), (YPos), XSpeed, YSpeed) != 0) {
		FrmScreen.RemoveObject(this);
		FrmScreen.HugeExplosion((XPos), (YPos), 30, 10);
		PlaySound(dsExplosion);
	}
	if (FrmScreen.isPlayer((XPos), (YPos)) != 0) {
		FrmScreen.RemoveObject(this);
		FrmScreen.HugeExplosion((XPos), (YPos), 30, 10);
		PlaySound(dsExplosion);
	}
	if (sqrt(XSpeed * XSpeed + YSpeed * YSpeed) < 2) {
		double i;
		for(i = 0; i <= PI * 2; i += .1){
			auto nCluster = new Spark();
			nCluster->Init((XPos), (YPos), sin(i) * 10, cos(i) * 10);
			FrmScreen.AddObject(nCluster);
			if (i > PI * 2) { break;}
		}
		FrmScreen.RemoveObject(this);
	}
}

void EldFunkarProj::Render(){
	FrmScreen.DrawPlPic(ddMissile, XPos - 3, YPos - 3, 0);
	FrmScreen.DrawPlPic(ddMissile, XPos - 3 - XSpeed / 2, YPos - 3 - YSpeed / 2, 1);
	FrmScreen.DrawPlPic(ddMissile, XPos - 3 - XSpeed, YPos - 3 - YSpeed, 1);
}
