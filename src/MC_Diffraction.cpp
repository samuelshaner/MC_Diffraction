//============================================================================
// Name        : MC_Diffraction.cpp
// Author      : Sam Shaner
// Version     :
// Copyright   : MIT DNSE
// Description : Monte Carlo Neutron Diffractometer
//============================================================================

#include <iostream>
#include "log.h"
#include "Timer.h"
#include "Options.h"
#include "Material.h"
#include "Binning.h"
#include "Diffractometer.h"
#include "gnuplot.h"
#include <fstream>

using namespace std;

int main(int argc, const char **argv) {
	log_printf(NORMAL, "Starting MC_Diffraction...");

	Timer timer;

	/* Create an options class to parse command line options */
	Options opts(argc, argv);

	/* set the verbosity */
	log_setlevel(opts.getVerbosity());

	/* make bins */
	log_printf(NORMAL, "Creating bins...");
	Binning bins_cos(opts.getTwoThetaMin(), opts.getTwoThetaMax(), opts.getBinSpacing());
	Binning bins_sin(opts.getTwoThetaMin(), opts.getTwoThetaMax(), opts.getBinSpacing());
	Binning bins_total(opts.getTwoThetaMin(), opts.getTwoThetaMax(), opts.getBinSpacing());
	Binning bins_two_theta(opts.getTwoThetaMin(), opts.getTwoThetaMax(), opts.getBinSpacing());
	bins_two_theta.setTwoTheta();
	Binning bins_particle_size(0,opts.getBatches(), 1);

	/* make material */
	log_printf(NORMAL, "Creating material...");
	Material material(opts.getCrystal(), opts.getRadius(), opts.getCrystalSize(), opts.getDebye());

	/* Make diffractometer object */
	Diffractometer diffractometer(opts.getRadiation(), opts.getEnergy());

	/* run diffraction simulation */
	for (int i = 0; i  < opts.getBatches(); i++){
		log_printf(NORMAL, "Starting diffractometer batch %i...", i + 1);
		diffractometer.run(&material, opts.getNumNeut(), &bins_cos, &bins_sin, &bins_total);

		/* compute particle size */
		if (opts.getScherrer() == true){
			bins_particle_size.getBins()[i] = diffractometer.computeParticleSize(&bins_total, &bins_two_theta);
			log_printf(NORMAL, "Mean particle size: %f", bins_particle_size.getBins()[i]);
		}

		bins_sin.resetBins();
		bins_cos.resetBins();
	}

	/* particle size statistics */
	bins_particle_size.computeBatchStats();

	/* output data to file */
	bins_total.generateSpectra(bins_two_theta.getBins());

	log_printf(NORMAL, "Ending MC_Diffraction...");
}
