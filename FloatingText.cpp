/*
 * FloatingText.cpp
 *
 *  Created on: 7 feb 2013
 *      Author: mattias
 */

#include "FloatingText.h"
#include "aux.h"

FloatingText::FloatingText() {
	// TODO Auto-generated constructor stub

}

FloatingText::~FloatingText() {
	// TODO Auto-generated destructor stub
}

void FloatingText::Init(double X, double Y, double Xs, double Ys,
		std::string t, int duration , int playerNum, double friction) {
	XPos = X;
	YPos = Y;
	XSpeed = Xs;
	YSpeed = Ys;
	text = t;
	Friction = friction;
	PlayerNum = playerNum;
	left = duration;
}

void FloatingText::TimeTab() {
	XPos += XSpeed;
	YPos += YSpeed;
	XSpeed /= (1.+Friction);
	YSpeed /= (1.+Friction);
	left --;
	if (left <= 0) frmScreen.RemoveObject(this);
}

void FloatingText::Render() {
	if (PlayerNum == 0 || PlayerNum == 1){
		FrmScreen.DrawOneText(XPos, YPos, text, PlayerNum);
	}
	else{
		FrmScreen.DrawText(XPos, YPos, text);
	}
}



