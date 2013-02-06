/*
 * Player.cpp
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#include "Player.h"
#include "aux.h"


void Player::setItem(int Index, int Val) {
	Items[Index] = Val;
	if (Items[Index] < 0) { Items[Index] = 0;}
	if (Items[Index] > ItemMax[Index]) { Items[Index] = ItemMax[Index];}
	if (MyNumber < 2) { FrmScreen.SetStatus((MyNumber), Index, (double)Items[Index] / (double)ItemMax[Index]);}
}

void Player::CalcItem(int Index, long Val) {
	if (ItemMax[Index] == 0) Items[Index] = 0;
	Items[Index] = Items[Index] + Val;
	if (Items[Index] < 0) { Items[Index] = 0;}
	if (Items[Index] > ItemMax[Index]) { Items[Index] = ItemMax[Index];}
	if (MyNumber < 2) { FrmScreen.SetStatus((MyNumber), Index, (double)Items[Index] / (double)ItemMax[Index]);}
}


