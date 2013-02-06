/*
 * Spark.h
 *
 *  Created on: 30 jan 2013
 *      Author: mattias
 */

#ifndef SPARK_H_
#define SPARK_H_

#include "Solid.h"

class Spark: public Solid {
public:
	Spark();
	~Spark();

	double XPos; double YPos; double XSpeed; double YSpeed;

	void Init(double X, double Y, double Xs, double Ys);
	void TimeTab();
	void Render();
};

#endif /* SPARK_H_ */
