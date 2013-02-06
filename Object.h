/*
 * Object.h
 *
 *  Created on: 23 jan 2013
 *      Author: mattias
 */

#ifndef OBJECT_H_
#define OBJECT_H_

class Object {
public:
	Object();
	virtual ~Object();

	virtual void Init(double X, double Y, double Xs, double Ys){};
	virtual void TimeTab(){};
};

#endif /* OBJECT_H_ */
