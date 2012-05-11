/*
 * Binning.h
 *
 *  Created on: May 4, 2012
 *      Author: samuelshaner
 */

#ifndef BINNING_H_
#define BINNING_H_

#include <stdlib.h>
#include <string>
#include "log.h"
#include <math.h>
#include <iostream>
#include <fstream>

class Binning {
private:
	double _min;
	double _max;
	double _spacing;
	double* _bins;
	int _num_bins;


public:
	Binning(double min, double max, double spacing);
	virtual ~Binning();
	void setMin(int min);
	void setMax(int max);
	void setSpacing(double spacing);
	void setTwoTheta();

	double getMin();
	double getMax();
	double getSpacing();
	double* getBins();
	double* getTwoThetaBins();
	double getValueToBin();
	int getNumBins();
	void generateSpectra(double* binsTwoTheta);
	double computeMin();
	double computeMax();
	void resetBins();
	void computeBatchStats();

};

#endif /* BINNING_H_ */
