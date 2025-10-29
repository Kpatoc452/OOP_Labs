#include "replace.hpp"

#include <gtest/gtest.h>


TEST(ReplaceTest, BasicCases) {
    std::string s1 = "acb";
    Replace(s1);
    EXPECT_EQ(s1, "bca");

    std::string s2 = "aabacbaa";
    Replace(s2);
    EXPECT_EQ(s2, "bbabcabb");

    std::string s4 = "";
    Replace(s4);
    EXPECT_EQ(s4, "");
}

TEST(ReplaceTest, OnlyAorBorC) {
    std::string s = "aaaa";
    Replace(s);
    EXPECT_EQ(s, "bbbb");

    s = "bbbb";
    Replace(s);
    EXPECT_EQ(s, "aaaa");

    s = "ccccc";
    Replace(s);
    EXPECT_EQ(s, "ccccc");
}

