/*
 * Options.cpp
 *
 *  Created on: Jan 21, 2012
 *      Author: Lulu Li
 *				MIT, Course 22
 *              lululi@mit.edu
 *
 *  Stores global program options
 *
 */

#include "Options.h"

#define LAST(str) (strcmp(argv[i-1], (str)) == 0)


/**
 * Options constructor
 * @param argc the number of command line arguments from console
 * @param argv a char array of command line arguments from console
 */
Options::Options(int argc, const char **argv) {

	_num_neut = 1000000;			/* default number of neutrons */
	_two_theta_min = 20;			/* default two theta minimum */
	_two_theta_max = 80;			/* default two theta maximum */
	_bin_spacing = .01;				/* default two theta bin spacing */
	_verbosity = "NORMAL";			/* default logging level */
	_crystal = "sc";				/* default crystal */
	_radius = .1;					/* default ionic radius (nm) */
	_crystal_size = 100;			/* default crystal size in (nm) */
	_radiation = "neutron";			/* default radiation is neutrons */
	_energy = .025;					/* default energy of radiation */
	_debye = .5;					/* default value for Debye-Waller factor */
	_batches = 1;					/* default number of batches */
	_scherrer = false;				/* default scherrer particle size calc */

	for (int i = 0; i < argc; i++) {
		if (i > 0) {
			if (LAST("--numneut") || LAST("-nn"))
				_num_neut = atoi(argv[i]);
			else if (LAST("--twothetamin") || LAST("-ttmin"))
				_two_theta_min = atof(argv[i]);
			else if (LAST("--twothetamax") || LAST("-ttmax"))
				_two_theta_max = atof(argv[i]);
			else if (LAST("--binspacing") || LAST("-bs"))
				_bin_spacing = atof(argv[i]);
			else if (LAST("--verbosity") || LAST("-v"))
				_verbosity = strdup(argv[i]);
			else if (LAST("--crystal") || LAST("-ctl"))
				_crystal = argv[i];
			else if (LAST("--radius") || LAST("-rd"))
				_radius = atof(argv[i]);
			else if (LAST("--crystalsize") || LAST("-cs"))
				_crystal_size = atof(argv[i]);
			else if (LAST("--radiation") || LAST("-rad"))
				_radiation = argv[i];
			else if (LAST("--energy") || LAST("-nrg"))
				_energy = atof(argv[i]);
			else if (LAST("--debye") || LAST("-dw"))
				_debye = atof(argv[i]);
			else if (LAST("--batches") || LAST("-bt"))
				_batches = atoi(argv[i]);
			else if (LAST("--scherrer") || LAST("-sc"))
				_scherrer = argv[i];

		}
	}
}

Options::~Options(void) { }

/**
 * Returns the number of neutrons being simulated
 */
int Options::getNumNeut() const{
	return _num_neut;
}

/**
 * Returns the minimum two theta
 */
double Options::getTwoThetaMin() const{
	return _two_theta_min;
}

/**
 * Returns the maximum two theta
 */
double Options::getTwoThetaMax() const{
	return _two_theta_max;
}

/**
 * Returns the bin spacing
 */
double Options::getBinSpacing() const{
	return _bin_spacing;
}

/**
 * Returns the verbosity logging level. By default this will return NORMAL if not set
 * at runtime from the console
 * @return the verbosity
 */
const char* Options::getVerbosity() const {
    return _verbosity.c_str();
}

/**
 * Returns the type of crystal structure
 */
std::string Options::getCrystal() const {
    return _crystal;
}

/**
 * Returns the unit cell side length
 */
double Options::getRadius() const{
	return _radius;
}

/**
 * Returns the unit cell side length
 */
double Options::getCrystalSize() const{
	return _crystal_size;
}

/**
 * Returns the diffractometer radiation
 */
std::string Options::getRadiation() const{
	return _radiation;
}

/**
 * Returns the diffractometer radiation
 */
double Options::getEnergy() const{
	return _energy;
}

/**
 * Returns the Debye-Waller factor
 */
double Options::getDebye() const{
	return _debye;
}

/**
 * Returns the number of batches
 */
int Options::getBatches() const{
	return _batches;
}

/**
 * Returns boolean for scherrer calculation
 */
bool Options::getScherrer() const{
	return _scherrer;
}

