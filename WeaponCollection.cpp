/*
 * WeaponCollection.cpp
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#include "WeaponCollection.h"
#include <string>
#include "Canoner.h"
#include "Miligun.h"
#include "CarlGustaf.h"



WeaponCollection::WeaponCollection() {
	// TODO Auto-generated constructor stub
	Index = 0;
}

WeaponCollection::~WeaponCollection() {
	// TODO Auto-generated destructor stub
}


Weapon* WeaponCollection::GetCurrentWeapon() {
	if ((int)wlist.size() < Index){
		return &w;
	}
	return wlist[Index];
}

Weapon* WeaponCollection::SetNextWeapon() {
	Index = Index + 1;
	if (Index >= (int)wlist.size()){
		Index = 0;
	}
	return wlist[Index];

}

void WeaponCollection::SetWeapon(int i) {
	Index = i;
	if (Index >= (int)wlist.size()){
		Index = 0;
	}

}

void WeaponCollection::AddWeapon(std::string item) {
//	auto w = new Canoner();
	Weapon * w = new Miligun();
	w->MyPlayer = (myPlayer);
	wlist.push_back(w);
	w = new Canoner();
	w->MyPlayer = myPlayer;
	wlist.push_back(w);
	w = new CarlGustaf();
	w->MyPlayer = myPlayer;
	wlist.push_back(w);
}

void WeaponCollection::Init(Player *p) {
	myPlayer = p;
}
