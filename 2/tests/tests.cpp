#include <gtest/gtest.h>
#include "decimal.hpp"
#include "exceptions.hpp"

class DecimalTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(DecimalTest, ConstructorWithSizeAndValue) {
    Decimal::Decimal num(4, 7);
    EXPECT_EQ(num.String(), "7777");
}

TEST_F(DecimalTest, EmptyConstructor) {
    Decimal::Decimal num;
    EXPECT_EQ(num.String(), "0");
}

TEST_F(DecimalTest, ConstructorFromString) {
    Decimal::Decimal num1("98765");
    EXPECT_EQ(num1.String(), "98765");
    
    Decimal::Decimal num2("000456");
    EXPECT_EQ(num2.String(), "456");
}

TEST_F(DecimalTest, ListInitialization) {
    Decimal::Decimal num{5, 6, 7};
    EXPECT_EQ(num.String(), "567");
    
    Decimal::Decimal num2{0, 0, 8, 9, 0};
    EXPECT_EQ(num2.String(), "890");
}

TEST_F(DecimalTest, InvalidStringInput) {
    EXPECT_THROW(Decimal::Decimal num("45x89"), exception::NaNException);
    EXPECT_THROW(Decimal::Decimal num("78.23"), exception::NaNException);
}

TEST_F(DecimalTest, CopyConstruction) {
    Decimal::Decimal original("67890");
    Decimal::Decimal copy(original);
    EXPECT_EQ(copy.String(), "67890");
}

TEST_F(DecimalTest, MoveConstruction) {
    Decimal::Decimal original("54321");
    Decimal::Decimal moved(std::move(original));
    EXPECT_EQ(moved.String(), "54321");
}

TEST_F(DecimalTest, SubtractionOperation) {
    Decimal::Decimal n1("789");
    Decimal::Decimal n2("234");
    Decimal::Decimal diff = Decimal::Decimal::Sub(n1, n2);
    EXPECT_EQ(diff.String(), "555");

    Decimal::Decimal n3("5000");
    Decimal::Decimal n4("1");
    Decimal::Decimal diff2 = Decimal::Decimal::Sub(n3, n4);
    EXPECT_EQ(diff2.String(), "4999");

    Decimal::Decimal n5("888");
    Decimal::Decimal diff3 = Decimal::Decimal::Sub(n5, n5);
    EXPECT_EQ(diff3.String(), "0");
}

TEST_F(DecimalTest, AdditionOperation) {
    Decimal::Decimal n1("234");
    Decimal::Decimal n2("567");
    Decimal::Decimal sum1 = Decimal::Decimal::Add(n1, n2);
    EXPECT_EQ(sum1.String(), "801");

    Decimal::Decimal n3("888");
    Decimal::Decimal n4("112");
    Decimal::Decimal sum2 = Decimal::Decimal::Add(n3, n4);
    EXPECT_EQ(sum2.String(), "1000");

    Decimal::Decimal n5("0");
    Decimal::Decimal sum3 = Decimal::Decimal::Add(n2, n5);
    EXPECT_EQ(sum3.String(), "567");

    Decimal::Decimal n6("987654321");
    Decimal::Decimal n7("123456789");
    Decimal::Decimal sum4 = Decimal::Decimal::Add(n6, n7);
    EXPECT_EQ(sum4.String(), "1111111110");
}

TEST_F(DecimalTest, ComparisonTests) {
    Decimal::Decimal n1("789");
    Decimal::Decimal n2("234");
    Decimal::Decimal n3("789");
    Decimal::Decimal n4("7890");
    Decimal::Decimal n5("78");
    
    EXPECT_TRUE(n2.Less(n1));
    EXPECT_FALSE(n1.Less(n2));
    EXPECT_TRUE(n1.Equals(n3));
    EXPECT_FALSE(n1.Equals(n2));
    EXPECT_TRUE(n1.Greater(n5));
    EXPECT_FALSE(n5.Greater(n1));

    EXPECT_TRUE(n1.Less(n4));
    EXPECT_TRUE(n4.Greater(n1));
}

TEST_F(DecimalTest, NegativeSubtractionError) {
    Decimal::Decimal n1("100");
    Decimal::Decimal n2("500");
    
    EXPECT_THROW(Decimal::Decimal::Sub(n1, n2), exception::NegativeException);
}

TEST_F(DecimalTest, MultiplicationOperation) {
    Decimal::Decimal n1("25");
    Decimal::Decimal n2("40");
    Decimal::Decimal multi1 = Decimal::Decimal::Multi(n1, n2);
    EXPECT_EQ(multi1.String(), "1000");

    Decimal::Decimal n3("0");
    Decimal::Decimal multi2 = Decimal::Decimal::Multi(n1, n3);
    EXPECT_EQ(multi2.String(), "0");

    Decimal::Decimal n4("1");
    Decimal::Decimal multi3 = Decimal::Decimal::Multi(n1, n4);
    EXPECT_EQ(multi3.String(), "25");

    Decimal::Decimal n5("54321");
    Decimal::Decimal n6("98765");
    Decimal::Decimal multi4 = Decimal::Decimal::Multi(n5, n6);
    EXPECT_EQ(multi4.String(), "5365013565");

    Decimal::Decimal n7("88");
    Decimal::Decimal n8("88");
    Decimal::Decimal multi5 = Decimal::Decimal::Multi(n7, n8);
    EXPECT_EQ(multi5.String(), "7744");
}

TEST_F(DecimalTest, BoundaryConditions) {
    Decimal::Decimal zero1("0");
    Decimal::Decimal zero2("00000");
    EXPECT_EQ(zero1.String(), "0");
    EXPECT_EQ(zero2.String(), "0");
    EXPECT_TRUE(zero1.Equals(zero2));

    Decimal::Decimal big("987654321098765432109876543210");
    EXPECT_EQ(big.String(), "987654321098765432109876543210");

    Decimal::Decimal trimmed("00000000456");
    EXPECT_EQ(trimmed.String(), "456");
}

TEST_F(DecimalTest, CopyMethodTest) {
    Decimal::Decimal n1("11111");
    Decimal::Decimal n2("99999");
    
    n1.Copy(n2);
    EXPECT_EQ(n1.String(), "99999");
    EXPECT_TRUE(n1.Equals(n2));
}

TEST_F(DecimalTest, StringConversion) {
    Decimal::Decimal n1("54321");
    Decimal::Decimal n2(0, 0);
    Decimal::Decimal n3{9, 8, 7};
    
    EXPECT_EQ(n1.String(), "54321");
    EXPECT_EQ(n2.String(), "0");
    EXPECT_EQ(n3.String(), "987");
}

TEST_F(DecimalTest, CombinedArithmeticOperations) {
    Decimal::Decimal a("2000");
    Decimal::Decimal b("750");
    Decimal::Decimal c("450");
    
    Decimal::Decimal total = Decimal::Decimal::Add(a, b);
    Decimal::Decimal final = Decimal::Decimal::Sub(total, c);
    EXPECT_EQ(final.String(), "2300");

    Decimal::Decimal x("15");
    Decimal::Decimal y("30");
    Decimal::Decimal z("50");
    
    Decimal::Decimal multiuct = Decimal::Decimal::Multi(x, y);
    Decimal::Decimal result = Decimal::Decimal::Add(multiuct, z);
    EXPECT_EQ(result.String(), "500");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}