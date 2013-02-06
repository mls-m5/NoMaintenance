/*
 * WeaponCollection.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef WEAPONCOLLECTION_H_
#define WEAPONCOLLECTION_H_

#include <vector>
#include "Player.h"
#include "Weapon.h"

class WeaponCollection{
	std::vector<Weapon *> wlist;

	int Index;

	Player *myPlayer;

	Weapon w;
public:
	WeaponCollection();
	virtual ~WeaponCollection();


	Weapon* GetCurrentWeapon() ;

	Weapon* SetNextWeapon() ;

	void SetWeapon(int i) ;

	void AddWeapon(std::string item) ;

	void Init(Player *p) ;

};

#endif /* WEAPONCOLLECTION_H_ */
