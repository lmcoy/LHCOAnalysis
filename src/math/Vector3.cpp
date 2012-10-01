#include "Vector3.h"

Vector3::Vector3(double x, double y, double z) {
	data[0] = x;
	data[1] = y;
	data[2] = z;
}

const double & Vector3::operator[](int index) const {
	return data[index];
}

double & Vector3::operator[](int index) {
	return data[index];
}

double Vector3::Dot(const Vector3 & v) const {
	return data[0]*v.data[0] + data[1]*v.data[1] + data[2]*v.data[2];
}

double Vector3::PseudoRapidity() const {
	double tmp = sqrt( data[0]*data[0] + data[1]*data[1] );
	double theta = atan2(tmp,data[2]);
	return log(tan(theta/2.0));
}

double Vector3::DeltaPhi( const Vector3 & a, const Vector3 & b ) {
	double phi1 = atan2(a[1],a[0]);
	double phi2 = atan2(b[1],b[0]);
	double dphi = phi1 - phi2;

	while( dphi >= PI ) {
		dphi -= 2.0 * PI;
	}
	while( dphi < -PI ) {
		dphi += 2.0 * PI;
	}
	return dphi;
}
double Vector3::DeltaR( const Vector3 & a, const Vector3 & b ) {
	double eta1 = a.PseudoRapidity();
	double eta2 = b.PseudoRapidity();
	double deta = eta1 - eta2;
	double dphi = Vector3::DeltaPhi(a,b);
	return sqrt(deta*deta + dphi*dphi );
}

