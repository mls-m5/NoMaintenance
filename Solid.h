/*
 * Solid.h
 *
 *  Created on: 29 jan 2013
 *      Author: mattias
 */

#ifndef SOLID_H_
class Solid {
public:
	Solid(){};
	virtual ~Solid(){};

	virtual void TimeTab(){};
	virtual void Render(){};
};

#define SOLID_H_

#endif /* SOLID_H_ */
