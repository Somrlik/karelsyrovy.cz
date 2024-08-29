#include <gtest/gtest.h>
#include <random.h>
#include <vector>

TEST(Random, SmokeTest) {
    randomIntReset();
    EXPECT_EQ(randomInt(), 8);
    EXPECT_EQ(randomInt(), 109);
    EXPECT_EQ(randomInt(), 220);
    EXPECT_EQ(randomInt(), 222);
    EXPECT_EQ(randomInt(), 241);

    randomIntReset();
    EXPECT_EQ(randomInt(), 8);
    EXPECT_EQ(randomInt(), 109);
    EXPECT_EQ(randomInt(), 220);
    EXPECT_EQ(randomInt(), 222);
    EXPECT_EQ(randomInt(), 241);
}

TEST(Random, UnexpectedValues) {
    randomIntReset();

    EXPECT_EQ(randomIntBetween(0, 0), 0);
    EXPECT_EQ(randomIntBetween(-1, 1), 0);
    EXPECT_EQ(randomIntBetween(1, -1), 1);
    EXPECT_EQ(randomIntBetween(-1, -1), -1);
    EXPECT_EQ(randomIntBetween(0, -100), -241);
    EXPECT_EQ(randomIntBetween(-100, 0), -51);
    // just no.
    // EXPECT_EQ(randomIntBetween(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()), 0);
}

TEST(Random, InBetween) {
    randomIntReset();
    EXPECT_EQ(randomIntBetween(0, 100), 2);
    EXPECT_EQ(randomIntBetween(0, 100), 36);
    EXPECT_EQ(randomIntBetween(0, 100), 73);
    EXPECT_EQ(randomIntBetween(0, 100), 74);

    randomIntReset();
    EXPECT_EQ(randomIntBetween(0, 100), 2);
    EXPECT_EQ(randomIntBetween(0, 100), 36);
    EXPECT_EQ(randomIntBetween(0, 100), 73);
    EXPECT_EQ(randomIntBetween(0, 100), 74);
}

TEST(Random, RepeatsAfter256) {
    randomIntReset();

    auto ints1 = std::vector<int>(256);
    for (int i = 0; i < 256; i++) {
        ints1.push_back(randomInt());
    }

    auto ints2 = std::vector<int>(256);
    for (int i = 0; i < 256; i++) {
        ints2.push_back(randomInt());
    }

    for (int i = 0; i < 256; i++) {
        SCOPED_TRACE(i);
        EXPECT_EQ(ints1.at(i), ints2.at(i));
    }
}
