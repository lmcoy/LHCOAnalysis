/*
 * FourVector.cpp
 *
 *  Created on: 11.09.2012
 *      Author: lo
 */

#include "FourVector.h"

FourVector::FourVector() {
	data[0] = 0.0;
	data[1] = 0.0;
	data[2] = 0.0;
	data[3] = 0.0;
}

FourVector::~FourVector() {

}

double& FourVector::operator [](int index) {
	return data[index];
}

const double& FourVector::operator [](int index) const {
	return data[index];
}

void FourVector::SetFromMomentumAndMass(double m, double p1, double p2, double p3) {
	data[0] = sqrt(p1 * p1 + p2 * p2 + p3 * p3 + m * m);
	data[1] = p1;
	data[2] = p2;
	data[3] = p3;
}

void FourVector::SetFromMassPtEtaPhi(double m, double pT, double eta, double phi) {
	SetFromMomentumAndMass(m, pT * cos(phi), pT * sin(phi), pT * sinh(eta));
}

void FourVector::SetFromEnergyPtEtaPhi(double e, double pT, double eta, double phi) {
	data[0] = e;
	data[1] = pT * cos(phi);
	data[2] = pT * sin(phi);
	data[3] = pT * sinh(eta);
}

double FourVector::Phi() const {
	return atan2(data[2],data[1]);
}

double FourVector::Eta() const {
	return -log(tan(Theta()/2.0));
}

double FourVector::MomentumAbs() const {
	return sqrt(data[1]*data[1]+data[2]*data[2]+data[3]*data[3]);
}

double FourVector::E() const {
	return data[0];
}

Vector3 FourVector::Momentum() const {
	return Vector3(data[1],data[2],data[3]);
}

double FourVector::PT() const {
	return sqrt(data[1]*data[1]+data[2]*data[2]);
}

double FourVector::ET() const {
	return E()*PT()/MomentumAbs();
}

double FourVector::Dot(const FourVector& fv) const {
	return data[0]*fv.data[0] - data[1]*fv.data[1] - data[2]*fv.data[2] - data[3]*fv.data[3];
}

FourVector FourVector::Plus(const FourVector& fv) const {
	return FourVector(data[0]+fv.data[0], data[1]+fv.data[1], data[2]+fv.data[2], data[3]+fv.data[3]);
}

double FourVector::Theta() const {
	double tmp = sqrt(data[1]*data[1] + data[2]*data[2]);
	return atan2(tmp,data[3]);
}

FourVector::FourVector(double p0, double p1, double p2, double p3) {
	data[0] = p0;
	data[1] = p1;
	data[2] = p2;
	data[3] = p3;
}

FourVector FourVector::Minus(const FourVector& fv) const {
	return FourVector(data[0]-fv.data[0], data[1]-fv.data[1], data[2]-fv.data[2], data[3]-fv.data[3]);
}
