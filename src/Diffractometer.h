/*
 * Diffractometer.h
 *
 *  Created on: May 4, 2012
 *      Author: samuelshaner
 */

#ifndef DIFFRACTOMETER_H_
#define DIFFRACTOMETER_H_

#include <stdlib.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include "log.h"
#include <math.h>
#include "Material.h"
#include "Binning.h"

class Diffractometer {
private:
	std::string _radiation;
	double _energy;
	double _lambda;
public:
	Diffractometer(std::string radiation, double energy);
	virtual ~Diffractometer();
	void run(Material* material, int numNeut, Binning* bins_cos, Binning* bins_sin, Binning* bins_total);
	double getLambda();
	double computeParticleSize(Binning* binsTotal, Binning* binsTwoTheta);
};


#endif /* DIFFRACTOMETER_H_ */
