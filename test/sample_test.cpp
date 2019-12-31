#include "catch/catch.hpp"

SCENARIO("Simple addition test")
{
    int result = 1 + 2;
    REQUIRE(result == 3);
}
