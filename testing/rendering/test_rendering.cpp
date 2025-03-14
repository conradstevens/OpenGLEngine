//
// Created by Conrad Stevens  on 2025-03-14.
//

#include <gtest/gtest.h>

int getNum() {return 41;}

TEST(TestTopic, myTestName) {
    EXPECT_EQ(getNum(), 41);
}

TEST(TestTopic, myTestName_2) {
    EXPECT_EQ(getNum(), 99);
}