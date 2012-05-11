/*
 * Binning.cpp
 *
 *  Created on: May 4, 2012
 *      Author: samuelshaner
 */

#include "Binning.h"

/* Constructor */
Binning::Binning(double min, double max, double spacing) {

	_min = min;
	_max = max;
	_spacing = spacing;
	_num_bins = ceil((max - min) / spacing);
	_bins = new double[_num_bins];

}

/* Default destructor */
Binning::~Binning() {
	delete [] _bins;
}

void Binning::setTwoTheta(){
	for (int i = 0; i < _num_bins; i++){
		_bins[i] = _min + (i + .5) * _spacing;
	}

}

/* set min */
void Binning::setMin(int min){
	_min = min;
}

/* set max */
void Binning::setMax(int max){
	_max = max;
}

/* set bin spacing */
void Binning::setSpacing(double spacing){
	_spacing = spacing;
}

/* get min */
double Binning::getMin(){
	return _min;
}

/* get max */
double Binning::getMax(){
	return _max;
}

/* get bin spacing */
double Binning::getSpacing(){
	return _spacing;
}

/* get pointer to bins */
double* Binning::getBins(){
	return _bins;
}

/* get number of bins */
int Binning::getNumBins(){
	return _num_bins;
}

/* write spectra data to file */
void Binning::generateSpectra(double* binsTwoTheta){
	std::ofstream myfile;
	myfile.open("spectra.txt");

	for (int i = 0; i < _num_bins; i++){
		myfile << binsTwoTheta[i] << "    " << _bins[i] << "\n";
	}

	myfile.close();

}

/* compute min value in bin */
double Binning::computeMin(){
	double min = _bins[0];
	for (int i = 0; i < _num_bins; i++){
		if (_bins[i] < min){
			min = _bins[i];
		}
	}

	return min;
}

/* compute max value in bin */
double Binning::computeMax(){
	double max = _bins[0];
	for (int i = 0; i < _num_bins; i++){
		if (_bins[i] > max){
			max = _bins[i];
		}
	}

	return max;
}

/* reset bins to zero */
void Binning::resetBins(){
	for (int i = 0; i < _num_bins; i++){
		_bins[i] = 0;
	}
}

/* compute the mean and std dev for all bins */
void Binning::computeBatchStats(){

	double mean = 0;
	double std_dev_sum = 0;
	double std_dev = 0;

	// compute mean
	for (int i = 0; i < _num_bins; i++){
		mean = mean + _bins[i];
	}

	mean = mean / _num_bins;

	// compute std dev
	for (int i = 0; i < _num_bins; i++){
		std_dev_sum = std_dev_sum + pow(_bins[i] - mean, 2);
	}

	std_dev = sqrt(1.0 / _num_bins * std_dev_sum);

	// print
	log_printf(NORMAL, "batch statistics: %f +/- %f", mean, 2*std_dev);

}




