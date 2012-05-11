/*
 * Material.cpp
 *
 *  Created on: May 4, 2012
 *      Author: samuelshaner
 */


#include "Material.h"

/* Constructor */
Material::Material(std::string crystal, double radius, double size, double debye) {

	_crystal = crystal;
	_size = size;
	_debye = debye;

	if (crystal == "fcc"){
		_num_planes = 4;
		_unit_length = 4 * radius / sqrt(2);
	}
	else if (crystal == "bcc"){
		_num_planes = 3;
		_unit_length = 4 * radius / sqrt(3);
	}
	else if (crystal == "sc"){
		_num_planes = 3;
		_unit_length = 2 * radius;
	}

	_planes_cdf 	= new double[_num_planes];
	_planes_spacing = new double[_num_planes];
	buildCDF();
}

/* Default destructor */
Material::~Material() {
	delete [] _planes_cdf;
	delete [] _planes_spacing;

}

/* set crystal type */
void Material::setCrystal(std::string crystal){
	_crystal = crystal;
}

/* set unit length of crystal (nm) */
void Material::setUnitLength(double unitLength){
	_unit_length = unitLength;
}

/* set the size of the crystal (nm) */
void Material::setSize(double size){
	_size = size;
}

/* return the type of crystal */
std::string Material::getCrystal(){
	return _crystal;
}

/* return the unit cell side length (nm) */
double Material::getUnitLength(){
	return _unit_length;
}

/* get the size of the crystal (nm) */
double Material::getSize(){
	return _size;
}

/* get the number of reflection planes */
double Material::getNumPlanes(){
	return _num_planes;
}

/* get pointer to planes spacing array */
double* Material::getPlanesSpacing(){
	return _planes_spacing;
}

/* get pointer to planes pdf */
double* Material::getPlanesCDF(){
	return _planes_cdf;
}

/* get Debye-Waller factor */
double Material::getDebye(){
	return _debye;
}


/* build a probability density function base
 * on the type of crystal
 */
void Material::buildCDF(){

	if (_crystal == "fcc"){
		/* compute the number of planes in the particle for each plane */
		_planes_spacing[0] = computeSpacing(1,1,1, _unit_length);
		_planes_spacing[1] = computeSpacing(2,0,0, _unit_length);
		_planes_spacing[2] = computeSpacing(2,2,0, _unit_length);
		_planes_spacing[3] = computeSpacing(3,1,1, _unit_length);

		/* compute the plane_number weighted planar density of each plane */
		double density1 = int(_size / _planes_spacing[0]) * 8 / (sqrt(3) * pow(_unit_length,2));
		double density2 = int(_size / _planes_spacing[1]) * 2 / pow(_unit_length,2);
		double density3 = int(_size / _planes_spacing[2]) * sqrt(2) / pow(_unit_length,2);
		double density4 = int(_size / _planes_spacing[3]) * .5977 / pow(_unit_length,2);
		double densitySum = density1 + density2 + density3 + density4;

		/* normalize densities and save in array of cdf values */
		_planes_cdf[0] = density1 / densitySum;							// (111) plane
		_planes_cdf[1] = _planes_cdf[0] + density2 / densitySum;		// (200) plane
		_planes_cdf[2] = _planes_cdf[1] + density3 / densitySum;		// (220) plane
		_planes_cdf[3] = _planes_cdf[2] + density4 / densitySum;		// (311) plane

	}
	else if (_crystal == "bcc"){
		/* compute the number of planes in the particle for each plane */
		_planes_spacing[0] = computeSpacing(2,0,0, _unit_length);
		_planes_spacing[1] = computeSpacing(1,1,0, _unit_length);
		_planes_spacing[2] = computeSpacing(2,1,1, _unit_length);

		/* compute the plane_number weighted planar density of each plane */
		double density1 = int(_size / _planes_spacing[0]) / pow(_unit_length,2);
		double density2 = int(_size / _planes_spacing[1]) * sqrt(2) / pow(_unit_length,2);
		double density3 = int(_size / _planes_spacing[2]) * 4 / (3 * pow(_unit_length,2));
		double densitySum = density1 + density2 + density3;

		/* normalize densities and save in array of cdf values */
		_planes_cdf[0] = density1 / densitySum;							// (200) plane
		_planes_cdf[1] = _planes_cdf[0] + density2 / densitySum;		// (110) plane
		_planes_cdf[2] = _planes_cdf[1] + density3 / densitySum;		// (211) plane

	}
	else if (_crystal == "sc"){
		/* compute the number of planes in the particle for each plane */
		_planes_spacing[0] = computeSpacing(1,0,0, _unit_length);
		_planes_spacing[1] = computeSpacing(1,1,0, _unit_length);
		_planes_spacing[2] = computeSpacing(1,1,1, _unit_length);

		/* compute the plane_number weighted planar density of each plane */
		double density1 = int(_size / _planes_spacing[0]) / pow(_unit_length,2);
		double density2 = int(_size / _planes_spacing[1]) * 1 / (sqrt(2) * pow(_unit_length,2));
		double density3 = int(_size / _planes_spacing[2]) * 2 / (sqrt(3) * pow(_unit_length,2));
		double densitySum = density1 + density2 + density3;

		/* normalize densities and save in array of cdf values */
		_planes_cdf[0] = density1 / densitySum;							// (100) plane
		_planes_cdf[1] = _planes_cdf[0] + density2 / densitySum;		// (110) plane
		_planes_cdf[2] = _planes_cdf[1] + density3 / densitySum;		// (111) plane

	}

}

double Material::computeSpacing(int h, int k, int l, double spacing){
	return spacing / pow((pow(h,2) + pow(k,2) + pow(l,2)),.5);
}

