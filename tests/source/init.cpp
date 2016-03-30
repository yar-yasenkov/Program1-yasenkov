#include <Matrix.hpp>
#include <catch.hpp>

SCENARIO("Matrix init", "[init]") {

	GIVEN("The number of rows and columns") {

		auto rows = 3;
		auto columns = 3;

		WHEN("Create instansce of Matrix") {

			Matrix matrix(rows, columns);

			THEN("The number of rows and columns must be preserved") {

				REQUIRE(matrix.kolstrok() == rows);
				REQUIRE(matrix.kolstolb() == columns);
			}
		}
	}
}

SCENARIO("Matrix >>", "[fill]") {
	Matrix A = Matrix(2, 2);
	REQUIRE( A.Zapoln("A2x2.txt") );
}

SCENARIO("Matrix +", "[addition]") {
	Matrix A = Matrix(2, 2);
	A.Zapoln("A2x2.txt");
	Matrix B = Matrix(2, 2);
	B.Zapoln("B2x2.txt");
	Matrix expected = Matrix(2, 2);
	expected.Zapoln("A+B2x2.txt");

	Matrix result = A + B;
	REQUIRE(result == expected);
}
