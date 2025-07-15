#include <gtest/gtest.h>
#include "Rational.hpp"
#include <sstream>

//quick functions to test combinatorics using basic arithmetic operations.
Integer fact(int a) {
    Integer result(1);
    for (int i=1; i<=a; i++) {
        result *= i;
    }
    return result;
}


Integer binom(int n, int k) {
    return fact(n)/(fact(k) * fact(n-k));
}


TEST(CombinatoricsTest, RegularInteger) {
    EXPECT_EQ(binom(4, 2), Integer(6));
    EXPECT_EQ(binom(5,3), Integer(10));
    EXPECT_EQ(binom(10, 5), Integer(252));
    EXPECT_EQ(binom(20, 10), Integer(184756));
}

TEST(CombinatoricsTest, LargeInteger) {
    Integer expected("24506254412642342501091642025419005736848368002709819291175537925074331126818028255524941459053852607200");
    EXPECT_EQ(binom(348,174).toString(),expected.toString());

    Integer expected2(1);
    for (int i=2287; i<=4573; i++) {
        expected2 *= i;
    }
    Rational r(expected2, fact(4573-2286));

    expected2 /= fact(4573-2286);
    EXPECT_EQ(binom(4573, 2286).toString(), expected2.toString());
    EXPECT_EQ(expected2.toString().size(), 1375); //integer has 1375 digits (number of atoms in the universe has less than 100 digits)
    EXPECT_EQ(r.getNumerator().toString(), expected2.toString());
    EXPECT_EQ(r.getDenominator().toString(), Integer(1).toString());
    EXPECT_EQ(r.isInteger(), true);
}


