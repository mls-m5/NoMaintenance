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
#include "Tropelet.h"
#include "Armageddon.h"
#include "Klachnikow.h"
#include "ChokladZingo.h"
#include "Haubits.h"
#include "EldFunkar.h"
#include "Jolt.h"
#include "Weapon.h"


Weapon *CreateWeaponFromString(std::string w){
	if (w == "kanonare"){
		return new Canoner();
	}
	else if (w == "armageddon"){
		return new Armageddon();
	}
	else if (w == "haubits"){
		return new Haubits();
	}
	else if (w == "jolt"){
		return new Jolt;
	}
	else if (w == "eldfunkar"){
		return new EldFunkar;
	}
	else if (w == "tropelet"){
		return new Tropelet;
	}
	else if (w == "miligun"){
		return new Miligun;
	}
	else if (w == "carlgustaf"){
		return new CarlGustaf;
	}
	else if (w == "chokladzingo"){
		return new ChokladZingo;
	}
	return new Klachnikow;
}

WeaponCollection::WeaponCollection() {
	// TODO Auto-generated constructor stub
	Index = 0;
}

WeaponCollection::~WeaponCollection() {
	for (auto w: wlist){
		delete w;
	}
	wlist.clear();
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
	{
		auto w = CreateWeaponFromString(item);
		w->MyPlayer = myPlayer;
		wlist.push_back(w);
	}

	{
		auto p = new Jolt();
		p->MyPlayer = myPlayer;
		wlist.push_back(p);
	}
	{
		auto e = new EldFunkar();
		e->MyPlayer = myPlayer;
		wlist.push_back(e);
	}
	auto h = new Haubits();
	h->MyPlayer = myPlayer;
	wlist.push_back(h);
	auto z = new ChokladZingo();
	z->MyPlayer = myPlayer;
	wlist.push_back(z);
	auto k = new Klachnikow();
	k->MyPlayer = myPlayer;
	wlist.push_back(k);
	auto a = new Armageddon();
	a->MyPlayer = myPlayer;
	wlist.push_back(a);
	auto t = new Tropelet();
	t->MyPlayer = myPlayer;
	wlist.push_back(t);
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
