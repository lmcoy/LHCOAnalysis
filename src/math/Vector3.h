#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>

static const double PI = 3.14159265358979323846264338327950288419716939937510582097494459;

// Vector3 represents a vector with 3 real components.
class Vector3 {
	public:
		Vector3(double x, double y, double z);

		// Index operators
		double & operator[](int index);
		const double & operator[](int index) const;

		// Dot returns the dot product of this vector and v.
		double Dot(const Vector3 & v) const;

		// PseudoRapidity calculates the pseudorapidity of this vector.
		double PseudoRapidity() const;

		static double DeltaPhi( const Vector3 & a, const Vector3 & b );
		static double DeltaR( const Vector3 & a, const Vector3 & b );
	private:
		double data[3];
};




#endif
