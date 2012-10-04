#include "gtest/gtest.h"
#include "src/math/FourVector.h"

TEST(FourVector, Phi) {
	FourVector a(1.0, 1.0, 1.0, 1.0);
	EXPECT_EQ(a.Phi(), 7.85398163397448279e-01);

	FourVector b(1.0, -1.0, -1.0, 1.0);
	EXPECT_EQ(b.Phi(), -2.35619449019234484e+00);

	FourVector c(1.0, 0.0, 0.0, 1.0);
	EXPECT_EQ(c.Phi(), 0.0 );

	FourVector d(0.0, 0.0, 0.0, 0.0);
	EXPECT_EQ(d.Phi(), 0.0);
}

TEST(FourVector, Theta) {
	FourVector a(1.0, 1.0, 1.0, 1.0);
	EXPECT_EQ(a.Theta(), 9.55316618124509298e-01);

	FourVector b(1.0, -1.0, -1.0, 1.0);
	EXPECT_EQ(b.Theta(), 9.55316618124509298e-01);

	FourVector c(1.0, 1.0, 0.0, 0.0);
	EXPECT_EQ(c.Theta(), PI/2.0 );

	FourVector d(0.0, 0.0, 0.0, 0.0);
	EXPECT_EQ(d.Theta(), 0.0);
}

TEST(FourVector, Eta) {
	FourVector a(1.0, 1.0, 1.0, 1.0);
	EXPECT_NEAR(a.Eta(), 6.58478948462408509e-01, 1e-9);

	FourVector c(1.0, 1.0, 0.0, 1.0);
	EXPECT_NEAR(c.Eta(), 8.81373587019542826e-01, 1e-9);
}

TEST(FourVector, Dot) {
	FourVector a(1.0, 1.0, 1.0, 1.0);
	EXPECT_EQ( a.Dot(a), -2.0 );

	FourVector c(1.0, 1.0, 0.0, 1.0);
	EXPECT_EQ( a.Dot(c), -1.0 );

	FourVector n( 0.0, 0.0, 0.0, 0.0 );
	EXPECT_EQ( n.Dot(a), 0.0 );
}

TEST(FourVector, SetFromMomentumAndMass) {
	FourVector a;
	a.SetFromMomentumAndMass(200.0, 123.0, 345.0, -34.0);
	EXPECT_EQ( a[0], 4.18700370193292258e+02 );
	EXPECT_EQ( a[1], 123.0 );
	EXPECT_EQ( a[2], 345.0 );
	EXPECT_EQ( a[3], -34.0 );
}

TEST(FourVector, SetFromMassPtEtaPhi) {
	FourVector a;
	a.SetFromMassPtEtaPhi( 2.0, 23.0, 0.5, 0.0 );

	EXPECT_EQ( a[1], 23.0 );
	EXPECT_EQ( a[2], 0.0 );
	EXPECT_EQ( a[3], 1.19851920263561897e+01 );
	EXPECT_EQ( a[0], 2.60123975809349801e+01 );

	FourVector b;
	b.SetFromMassPtEtaPhi( 4.0, 12.0, 1.0, 0.5*PI );
	EXPECT_EQ( b[1], 7.34788079488411875e-16 );
	EXPECT_EQ( b[2], 12.0 );
	EXPECT_EQ( b[3], 1.41024143237256165e+01 );
	EXPECT_EQ( b[0], 1.89440779600914198e+01 );


}


int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
