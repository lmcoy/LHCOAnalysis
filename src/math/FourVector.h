/*
 * FourVector.h
 *
 *  Created on: 11.09.2012
 *      Author: lo
 */

#ifndef FOURVECTOR_H_
#define FOURVECTOR_H_

#include <cmath>

#include "Vector3.h"

// FourVector represents a fourvector.
class FourVector {
public:
	FourVector();
	FourVector(double p0, double p1, double p2, double p3);
	virtual ~FourVector();

	double & operator[](int index);
	const double & operator[](int index) const;

	// SetFromMomentumAndMass constructs a fourvector from mass m and momentum p.
	void SetFromMomentumAndMass(double m, double p1, double p2, double p3);

	// SetFromMassPtEtaPhi constructs a fourvector from mass m and transverse momentum pT,
	// pseudo rapidity eta and azimuthal angle phi.
	void SetFromMassPtEtaPhi(double m, double pT, double eta, double phi);

	// SetFromEnergyPtEtaPhi constructs a fourvector from energy e and transverse momentum pT,
	// pseudo rapidity eta and azimuthal angle phi.
	void SetFromEnergyPtEtaPhi(double e, double pT, double eta, double phi);

	// Phi returns the azimuthal angle in the range [-pi,pi].
	//
	// For an angle in [0,2*pi] add 2*pi to the negative values.
	double Phi() const;

	// Theta returns the polar angle in the range [0,pi].
	double Theta() const;

	// Eta returns the pseudorapidity.
	double Eta() const;

	// MomentumAbs returns the euclidean length of the momentum.
	double MomentumAbs() const;

	// E returns the energy.
	double E() const;

	// Momentum returns the momentum.
	Vector3 Momentum() const;

	// PT returns the transverse momentum.
	//
	//     PT = Sqrt(px*px + py*py)
	double PT() const;

	// ET returns the transverse energy.
	//
	//     ET = E*sin(theta) = E*PT/|P|
	double ET() const;

	// Dot calculates the fourvector dot product of this vector and fv.
	double Dot(const FourVector & fv ) const;

	// Plus returns a new FourVector this + fv.
	FourVector Plus(const FourVector & fv) const;

	// Minus returns a new FourVector this - fv.
	FourVector Minus(const FourVector & fv) const;

private:
	double data[4];
};

#endif /* FOURVECTOR_H_ */
