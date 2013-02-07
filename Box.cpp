/*
 * Box.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "Box.h"
#include "aux.h"
#include "FloatingText.h"

Box::Box() {
	ItemNumber = -1;

}

Box::~Box() {
	// TODO Auto-generated destructor stub
}



void Box::Init(double X, double Y, double Xs, double Ys){
	XPos = X;
	YPos = Y;
	XSpeed = Xs;
	YSpeed = Ys;
	TimeLimit = 5000;
}

void Box::TimeTab(){
	int i;
	YSpeed = YSpeed + 0.3;
	XPos = XPos + XSpeed;
	YPos = YPos + YSpeed;
	if (FrmScreen.GetMapLine((XPos), YPos + 5, XSpeed, YSpeed) != 0) {
		YSpeed = -YSpeed / 2;
		YPos = YPos - 1;
	}
	i = FrmScreen.isPlayer((XPos), (YPos), 5, 5);
	if (i != 0) {
		FrmScreen.AddTextToBuffer( i - 1, "Plockade upp " + Item);
		if (Item == "kraft") {
			FrmScreen.getPlayer(i - 1)->CalcItem (0, Rnd() * 50);
		}
		else if (Item.find("item nr ") == 0) {
			FrmScreen.getPlayer(i - 1)->CalcItem( ItemNumber, 50 + Rnd() * 100);
		}
		else {
			FrmScreen.getPlayer(i - 1)->PickUp (Item);
		}
		PlaySound(dsReload);
		FrmScreen.RemoveObject(this);
		auto fText = new FloatingText;
		fText->Init(XPos, YPos - 10, 0, -1, Item, 50, i-1, .1);
		frmScreen.AddObject(fText);
	}
	if (TimeLimit < 0 ){
		FrmScreen.RemoveObject(this);
		FrmScreen.MakeSmoke(XPos, YPos, 0, -1, 0);
	}
	TimeLimit = TimeLimit - 1;
}

void Box::Render(){
	FrmScreen.DrawPlPic(ddItem, XPos - 5, YPos - 5, BoxType);
	if (GamePlay.ShowContent){
		FrmScreen.DrawText(XPos, YPos - 10, Item);
	}
}
