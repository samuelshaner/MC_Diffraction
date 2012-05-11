/*
 * Material.h
 *
 *  Created on: May 4, 2012
 *      Author: samuelshaner
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <stdlib.h>
#include <string>
#include "log.h"
#include <math.h>

class Material {
private:
	std::string _crystal;
	double _unit_length;
	double _size;
	int _num_planes;
	double* _planes_cdf;
	double* _planes_spacing;
	double _debye;

public:
	Material(std::string crystal, double radius, double size, double debye);
	virtual ~Material();
	void setCrystal(std::string crystal);
	void setUnitLength(double unitLength);
	void setSize(double size);

	std::string getCrystal();
	double getUnitLength();
	double getSize();
	void buildCDF();
	double computeSpacing(int h, int k, int l, double spacing);
	double getNumPlanes();
	double* getPlanesSpacing();
	double* getPlanesCDF();
	double getDebye();

};


#endif /* MATERIAL_H_ */
