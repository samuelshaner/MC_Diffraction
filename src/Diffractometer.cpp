/*
 * Diffractometer.cpp
 *
 *  Created on: May 4, 2012
 *      Author: samuelshaner
 */


#include "Diffractometer.h"

#define PI 3.1415926536

/* Constructor */
Diffractometer::Diffractometer(std::string radiation, double energy) {

	_radiation = radiation;
	_energy = energy;

	double planck = 4.135667517 * 1e-15;				// planck's constant (eV s)
	double c = 299792458;			  					// speed of light (m/s)

	if (radiation == "neutron"){
		double mass = 939.565378 * 1e6 / pow(c,2);		// mass of neutron (eV s2 m-2)
		double velocity = sqrt((2 * energy) / mass);	// velocity of neturon (m/s)
		_lambda = planck / (mass * velocity) * 1e9; 	// neutron wavelength (nm)
	}
	else if (radiation == "xray"){
		_lambda = c * planck / energy * 1e9;			// wavelength of neturon (nm)
	}
	else if (radiation == "electron"){
		double mass = 0.510998928 * 1e6 / pow(c,2);		// mass of electron (eV s2 m-2)
		double velocity = sqrt((2 * energy) / mass);	// velocity of electron (m/s)
		_lambda = planck / (mass * velocity) * 1e9; 	// electron wavelength (nm)
	}

	const char* rad = radiation.c_str();
	log_printf(NORMAL, "Radiation: %s", rad);
	log_printf(NORMAL, "Radiation wavelength: %f nm", _lambda);

}

/* Default destructor */
Diffractometer::~Diffractometer() {}

/* simulate diffraction experiment */
void Diffractometer::run(Material* material, int numNeut, Binning* binsCos, Binning* binsSin, Binning* binsTotal){

	/* intialize variables */
	double twoTheta;
	int planeNumber;
	int numPlanes = 1;
	double planeSpacing = 1;
	double coherence_cos;
	double coherence_sin;
	double randPlane;
	double Qr;
	double debyeExp;
	int bin;

	/* seed random number generator */
	srand ( time(NULL) );

	/* loop over number of neutrons */
	for (int i = 0; i < numNeut; i++){

		/* generate random two theta in range */
		twoTheta = (rand() % int(binsSin->getMax() - binsSin->getMin())) + binsSin->getMin() + (rand() % int(1e5)) * 1e-5;

		/* choose scattering plane */
		randPlane = ((rand() % 100) + (rand() % int(1e5)) * 1e-5) / 100.0;
		log_printf(DEBUG, "random plane: %f", randPlane);
		for (int j = 0; j < material->getNumPlanes(); j++){
			if (randPlane < material->getPlanesCDF()[j]){
				planeSpacing = material->getPlanesSpacing()[j];
				numPlanes = material->getSize() / planeSpacing;
				break;
			}
		}

		log_printf(DEBUG, "number of planes: %i", numPlanes);
		log_printf(DEBUG, "plane spacing: %f", planeSpacing);

		/* generate random lattice plane to diffract neutron */
		planeNumber = rand() % numPlanes;
		log_printf(DEBUG, "plane: %i", planeNumber);

		/* compute coherence */
		Qr = 4 * PI * sin(twoTheta / 2 / 180 * PI) * planeNumber * planeSpacing / _lambda;
		debyeExp =  exp(-2 * material->getDebye() * pow(sin(twoTheta / 2 / 180 * PI) / (_lambda * 10),2));
		coherence_cos = cos(Qr) * debyeExp;
		coherence_sin = sin(Qr) * debyeExp;

		/* bin coherence */
		bin = floor((twoTheta - binsSin->getMin()) / (binsSin->getMax() - binsSin->getMin()) * binsSin->getNumBins());
		binsSin->getBins()[bin] = binsSin->getBins()[bin] + coherence_sin;
		binsCos->getBins()[bin] = binsCos->getBins()[bin] + coherence_cos;

	}

	for (int k = 0; k < binsTotal->getNumBins(); k++){
		binsTotal->getBins()[k] = pow(binsSin->getBins()[k],2) + pow(binsCos->getBins()[k],2);
	}

}

double Diffractometer::getLambda(){
	return _lambda;
}

/* use the scherrer equation to compute the mean particle size */
double Diffractometer::computeParticleSize(Binning* binsTotal, Binning* binsTwoTheta){

	double K = 0.9;
	double max = binsTotal->computeMax();
	double min = binsTotal->computeMin();
	double beta_left = 1;
	double beta_right = 2;
	double theta = 1;
	double tau;

	// compute beta
	bool left = false;
	bool mid = false;
	for (int i = 0; i < binsTotal->getNumBins(); i++){
		double intensity = binsTotal->getBins()[i];
		// find left mid
		if (left == false && intensity  > (max - min) / 2){
			beta_left = binsTwoTheta->getBins()[i];
			left = true;
		}
		// find if max reached
		if (intensity == max){
			mid = true;
			theta = binsTwoTheta->getBins()[i] / 2;
		}
		// find right mid
		if (mid == true && intensity < (max - min) / 2){
			beta_right = binsTwoTheta->getBins()[i];
			break;
		}
	}

	log_printf(INFO, "beta_left: %f", beta_left);
	log_printf(INFO, "beta_right: %f", beta_right);
	log_printf(INFO, "theta: %f", theta);
	log_printf(INFO, "min: %f", min);
	log_printf(INFO, "max: %f", max);


	// compute mean particle size
	tau = K * _lambda / ((beta_right - beta_left) / 180 * PI * cos(theta / 180 * PI));

	return tau;
}







