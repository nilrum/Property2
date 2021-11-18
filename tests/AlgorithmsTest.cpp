//
// Created by user on 17.11.2021.
//

#include "gtest/gtest.h"
#include "Base/Algorithms.h"

TEST(TestAlgo, TestDoubleCheckEqual)
{
    EXPECT_EQ(TDoubleCheck::Equal(1., 1.), true);
    EXPECT_EQ(TDoubleCheck::Equal(-1., -1.), true);
    EXPECT_EQ(TDoubleCheck::Equal(0., 0.), true);
    EXPECT_EQ(TDoubleCheck::Equal(-0., -0.), true);
    EXPECT_EQ(TDoubleCheck::Equal(-0., 0.), true);
    EXPECT_EQ(TDoubleCheck::Equal(0., -0.), true);

    EXPECT_EQ(TDoubleCheck::Equal(1., 1. + TDoubleCheck::HalfDelta()), true);
    EXPECT_EQ(TDoubleCheck::Equal(1. + TDoubleCheck::HalfDelta(), 1), true);

    EXPECT_EQ(TDoubleCheck::Equal(-1., -1. + TDoubleCheck::HalfDelta()), true);
    EXPECT_EQ(TDoubleCheck::Equal(-1. + TDoubleCheck::HalfDelta(), -1), true);
    EXPECT_EQ(TDoubleCheck::Equal(TDoubleCheck::HalfDelta(), -TDoubleCheck::HalfDelta()), true);

    EXPECT_EQ(TDoubleCheck::Equal(1., 1. + TDoubleCheck::Delta()), false);
    EXPECT_EQ(TDoubleCheck::Equal(1. + TDoubleCheck::Delta(), 1.), false);
}


TEST(TestAlgo, TestDoubleCheckLess)
{
    EXPECT_EQ(TDoubleCheck::Less(1., 1. + TDoubleCheck::HalfDelta()), false);//они равны
    EXPECT_EQ(TDoubleCheck::Less(1., 1. + TDoubleCheck::Delta()), true);
    EXPECT_EQ(TDoubleCheck::Less(1., 2), true);

    EXPECT_EQ(TDoubleCheck::Less(-1. - TDoubleCheck::HalfDelta(), -1), false);//они равны
    EXPECT_EQ(TDoubleCheck::Less(-1. - TDoubleCheck::Delta(), -1), true);
    EXPECT_EQ(TDoubleCheck::Less(-2., -1), true);

    EXPECT_EQ(TDoubleCheck::Less(-1., 1.), true);
    EXPECT_EQ(TDoubleCheck::Less(1., -1.), false);
}
