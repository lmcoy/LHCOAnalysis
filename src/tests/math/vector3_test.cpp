#include "gtest/gtest.h"
#include "src/math/Vector3.h"

TEST(Vector3, DotProduct) {
	Vector3 a(2.3,1.7,4.3);
	Vector3 b(-4.5,2.3,1.0);

	EXPECT_EQ(a.Dot(b),-2.3*4.5+1.7*2.3+4.3);

}

TEST(Vector3,DeltaPhi) {
	Vector3 a(2.3, 1.7, 4.3);
	Vector3 b(-4.5, 2.3, 1.0);
	EXPECT_EQ(Vector3::DeltaPhi(a,b), -2.03258750228477814e+00);

	Vector3 c(1.0,0.0,0.0);
	EXPECT_EQ(Vector3::DeltaPhi(c,c), 0.0);

	Vector3 d(0.0,1.0,0.0);
	EXPECT_EQ(Vector3::DeltaPhi(c,d), -PI/2.0 );
}

TEST(Vector3,DeltaR) {
	Vector3 a(1.0,0.0,0.0);
	EXPECT_EQ(Vector3::DeltaR(a,a), 0.0);

	Vector3 b(0.0,1.0,0.0);
	EXPECT_EQ(Vector3::DeltaR(a,b), PI/2.0 );
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
