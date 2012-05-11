/*
 * Options.h
 *
 *  Created on: Jan 21, 2012
 *      Author: Lulu Li
 *				MIT, Course 22
 *              lululi@mit.edu
 *
 *  Stores global program options
 *
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <string.h>
#include <stdlib.h>
#include "log.h"

class Options {
private:

	int _num_neut;
	double _two_theta_min;
	double _two_theta_max;
	double _bin_spacing;
	std::string _verbosity;
	std::string _crystal;
	double _radius;
	double _crystal_size;
	std::string _radiation;
	double _energy;
	double _debye;
	int _batches;
	bool _scherrer;

public:
    Options(int argc, const char **argv);
    ~Options(void);
    int getNumNeut() const;
    double getTwoThetaMin() const;
    double getTwoThetaMax() const;
    double getBinSpacing() const;
    std::string getCrystal() const;
    const char* getVerbosity() const;
    double getRadius() const;
    double getCrystalSize() const;
    std::string getRadiation() const;
    double getEnergy() const;
    double getDebye() const;
    int getBatches() const;
    bool getScherrer() const;
};

#endif
