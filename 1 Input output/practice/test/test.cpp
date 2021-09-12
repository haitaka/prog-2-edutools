// Indicates that the `main` function is need to be set.
// Add this directive only in a one test file!
#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "../../../utils/checkio.hpp"

// Headers of objects that student should implement:
int test();

// Tests:
TEST_CASE("zero elements", "[SumTest]") {
    chio::checkIO(test, "0\n", "0");
}

TEST_CASE("single element", "[SumTest]") {
    chio::checkIO(test, "1\n 42\n", "42");
}

TEST_CASE("negative elements", "[SumTest]") {
    chio::checkIO(test, "3\n 23 -23 42\n", "42");
}

TEST_CASE("lost numbers", "[SumTest]") {
    chio::checkIO(test, "6\n 4 8 15 16 23 42\n", "108");
}
