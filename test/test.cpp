
#define BOOST_TEST_MODULE A429_test_module
#include <boost/test/included/unit_test.hpp>

#include <a429/a429base.hpp>
#include <a429/a429dis.hpp>
#include <a429/a429bcd.hpp>
#include <a429/a429bnr.hpp>
#include <a429/a429hyb.hpp>

BOOST_AUTO_TEST_SUITE( a429base_suite )

BOOST_AUTO_TEST_CASE( construct_default )
{
    // Default construction, explicit cast
    a429::a429base testword;
    BOOST_TEST((a429::UINT)testword == 0);
}

BOOST_AUTO_TEST_CASE(construct_value_copy)
{
    // Construct by value, implicit cast
    a429::a429base testword(0xdeadbeef);
    BOOST_TEST(testword == 0xdeadbeef);

    // Construct by copy
    a429::a429base testword2(testword);
    BOOST_TEST(testword2 == 0xdeadbeef);
}

BOOST_AUTO_TEST_CASE(assign_operator)
{
    a429::a429base testword(0xdeadbeef);
    a429::a429base testword2;

    testword2 = testword;
    BOOST_TEST(testword2 == 0xdeadbeef);

    testword2 = 0xa5a5a5a5;
    BOOST_TEST(testword2 == 0xa5a5a5a5);
}

BOOST_AUTO_TEST_CASE(construct_ref)
{
    // Construct by reference, GetWord
    unsigned int reference = 0xdeadbeef;
    a429::a429base testword(&reference);
    BOOST_TEST(testword.GetWord() == 0xdeadbeef);

    reference = 0xa5a5a5a5;
    BOOST_TEST(testword.GetRevLbl() == 0xa5);
}

BOOST_AUTO_TEST_CASE(set_params)
{
    a429::a429base testword;
    testword.SetLbl(0271).SetSDI(01).SetSSM(3);
    BOOST_TEST (testword.GetWord() == 0x6000019d);
}

BOOST_AUTO_TEST_CASE(get_params)
{
    const a429::a429base testword(0x69a53cf0);
    BOOST_TEST (testword.GetLbl() == 017);
    BOOST_TEST (testword.GetRevLbl() == 0xf0);
    BOOST_TEST (testword.GetSDI() == 0);
    BOOST_TEST (testword.GetSSM() == 3);
    BOOST_TEST (testword.GetWord() == 0x69a53cf0);
    BOOST_TEST (testword.GetPar() == 0);
}

BOOST_AUTO_TEST_CASE(get_parity)
{
    a429::a429base testword(0x600001ad);

    BOOST_TEST (testword.GetPar() == 0);
    BOOST_TEST (testword.CalcPar() == 1);
    BOOST_TEST (testword.GetPar() == 0);
    BOOST_TEST (testword.SetPar().GetPar() == 1);
    BOOST_TEST (testword.SetPar(0).GetPar() == 0);
}

BOOST_AUTO_TEST_SUITE_END() // End a429base_suite


BOOST_AUTO_TEST_SUITE( a429dis_suite )

BOOST_AUTO_TEST_CASE( dis_copy_ctor )
{
    a429::a429dis word1 = 0xa5a5a5a5;
    a429::a429dis word2(word1);

    BOOST_TEST (word2 == 0xa5a5a5a5);

    a429::a429base word3 = 0xdeadbeef;
    a429::a429dis word4(word3);

    BOOST_TEST (word4 == 0xdeadbeef);
}

BOOST_AUTO_TEST_CASE(dis_bit)
{
    a429::a429dis testword(0x00000200);
    testword.SetBit(1, 9);
    BOOST_TEST(testword.GetWord() == 0x00000300);
    BOOST_TEST(testword.GetBit(9) == 1);
}

BOOST_AUTO_TEST_CASE(dis_bits)
{
    a429::a429dis testword;
    testword.SetBits(0xa, 16, 13);
    BOOST_TEST(testword.GetWord() == 0x0000a000);
    BOOST_TEST(testword.GetBits(16, 13) == 0xa);
}

BOOST_AUTO_TEST_CASE(dis_ssm)
{
    a429::a429dis testword;
    testword.SetSDI(a429::DIS_NCD);
    BOOST_TEST(testword.GetSDI() == a429::DIS_NCD);
}

BOOST_AUTO_TEST_SUITE_END() // End a429dis_suite

BOOST_AUTO_TEST_SUITE( a429bcd_suite )

BOOST_AUTO_TEST_CASE( bcd_copy_ctor )
{
    a429::a429bcd word1 = 0xa5a5a5a5;
    a429::a429bcd word2(word1);

    BOOST_TEST (word2 == 0xa5a5a5a5);

    a429::a429base word3 = 0xdeadbeef;
    a429::a429bcd word4(word3);

    BOOST_TEST (word4 == 0xdeadbeef);
}

BOOST_AUTO_TEST_CASE(bcd_set_digit)
{
    a429::a429bcd testword;
    testword.SetDigit(0x7, 9, 11);
    BOOST_TEST(testword.GetWord() == 0x00000700);

    testword.SetDigit(0x0, 9, 10);
    BOOST_TEST(testword.GetWord() == 0x00000400);

    BOOST_TEST(testword.GetDigit(5, 12) == 0x40);
}

BOOST_AUTO_TEST_CASE(bcd_6_digit)
{
    a429::a429bcd testword;
    testword.SetBCDProperties(0.001, 6);
    testword.SetBCD(123.456);
    BOOST_TEST(testword.GetWord() == 0x12345600);
    BOOST_TEST(testword.GetBCD() == 123.456); // Todo: add tolerance
}

BOOST_AUTO_TEST_CASE(bcd_5_digit)
{
    a429::a429bcd testword;
    testword.SetBCDProperties(1.0, 5);
    testword.SetBCD(76543);
    BOOST_TEST (testword.GetWord() == 0x1d950c00);
    BOOST_TEST (testword.GetBCD() == 76543);
}

BOOST_AUTO_TEST_CASE(bcd_5_digit_inv)
{
    a429::a429bcd testword(0xffffffff); // testing that we can also remove 1s
    testword.SetBCDProperties(0.1, 5);
    testword.SetBCD(32.1); // testing that leading zeros are cleared
    BOOST_TEST (testword.GetWord() == 0x700c87ff);
    BOOST_TEST (testword.GetBCD() == 32.1); // Todo: add tolerance
}

BOOST_AUTO_TEST_CASE(bcd_4_digit)
{
    a429::a429bcd testword;
    testword.SetBCDProperties(0.1, 4);
    testword.SetBCD(432.1);
    BOOST_TEST (testword.GetWord() == 0x10c84000);
    BOOST_TEST (testword.GetBCD() == 432.1); // Todo: add tolerance
}

BOOST_AUTO_TEST_CASE(bcd_ssm)
{
    a429::a429bcd testword;
    testword.SetSDI(a429::BCD_NCD);
    BOOST_TEST(testword.GetSDI() == a429::BCD_NCD);
}

BOOST_AUTO_TEST_SUITE_END() // End a429bcd_suite

BOOST_AUTO_TEST_SUITE( a429bnr_suite )

BOOST_AUTO_TEST_CASE( bnr_copy_ctor )
{
    a429::a429bnr word1 = 0xa5a5a5a5;
    a429::a429bnr word2(word1);

    BOOST_TEST (word2 == 0xa5a5a5a5);

    a429::a429base word3 = 0xdeadbeef;
    a429::a429bnr word4(word3);

    BOOST_TEST (word4 == 0xdeadbeef);
}

BOOST_AUTO_TEST_CASE( bnr_pack )
{
    a429::a429bnr testword;
    testword.SetBNR(34.0, 1.0, 8);

    BOOST_TEST (testword.GetWord() == 0x04400000);

    testword.SetBNRPropertiesA(2.0, 12);
    testword.SetBNR(-5108.0);

    BOOST_TEST (testword.GetWord() == 0x19fa0000);
}

BOOST_AUTO_TEST_CASE( bnr_unpack )
{
    a429::a429bnr testword(0x04400000);
    testword.SetBNRPropertiesA(1.0, 8);

    BOOST_TEST(testword.GetBNR() == 34.0); // Todo: add tolerance

    testword = 0x19fa0000;
    BOOST_TEST (testword.GetBNR(2.0, 12) == -5108.0); // Todo: add tolerance
}

BOOST_AUTO_TEST_CASE(bnr_ssm)
{
    a429::a429bnr testword;
    testword.SetSDI(a429::BNR_NCD);
    BOOST_TEST(testword.GetSDI() == a429::BNR_NCD);
}

BOOST_AUTO_TEST_SUITE_END() // End a429bnr_suite

BOOST_AUTO_TEST_SUITE( a429hyb_suite )

BOOST_AUTO_TEST_CASE( hyb_copy_ctor )
{
    a429::a429hyb word1 = 0xa5a5a5a5;
    a429::a429hyb word2(word1);

    BOOST_TEST (word2 == 0xa5a5a5a5);

    a429::a429base word3 = 0xdeadbeef;
    a429::a429hyb word4(word3);

    BOOST_TEST (word4 == 0xdeadbeef);
}

BOOST_AUTO_TEST_CASE( hyb_bnr )
{
    a429::a429hyb testword;
    testword.SetBNR(34.0, 1.0, 8);

    BOOST_TEST (testword.GetWord() == 0x04400000);

    testword.SetBNRPropertiesA(2.0, 12);
    testword.SetBNR(-5108.0);

    BOOST_TEST (testword.GetWord() == 0x19fa0000);

    BOOST_TEST(testword.GetBNR() == 34.0); // Todo: add tolerance

    testword = 0x19fa0000;
    BOOST_TEST (testword.GetBNR(2.0, 12) == -5108.0); // Todo: add tolerance
}

BOOST_AUTO_TEST_CASE( hyb_bcd )
{
    a429::a429hyb testword;
    testword.SetBCDProperties(0.001, 6);
    testword.SetBCD(123.456);
    BOOST_TEST(testword.GetWord() == 0x12345600);
    BOOST_TEST(testword.GetBCD() == 123.456); // Todo: add tolerance
}

BOOST_AUTO_TEST_CASE( hyb_dis )
{
    a429::a429hyb testword(0x00000200);
    testword.SetBit(1, 9);
    BOOST_TEST(testword.GetWord() == 0x00000300);
    BOOST_TEST(testword.GetBit(9) == 1);

    testword.SetBits(0xa, 16, 13);
    BOOST_TEST(testword.GetWord() == 0x0000a300);
    BOOST_TEST(testword.GetBits(16, 13) == 0xa);
}

BOOST_AUTO_TEST_SUITE_END()
