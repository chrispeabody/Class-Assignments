// -*- mode: cpp -*-
// g++ main.cpp -lboost_unit_test_framework

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DecryptorTest
#include <boost/test/unit_test.hpp>
#include "rotor.h"
#include "funcs.h"

/**
 * Test that a Rotor will decrypt letters correctly when using disk 1
 */
BOOST_AUTO_TEST_CASE(test_disk1)
{
  Rotor test(1);
  BOOST_CHECK_EQUAL(test.decrypt('K'), 'A');
  BOOST_CHECK_EQUAL(test.decrypt('B'), 'B');
  BOOST_CHECK_EQUAL(test.decrypt('L'), 'C');
  BOOST_CHECK_EQUAL(test.decrypt('C'), 'D');
  BOOST_CHECK_EQUAL(test.decrypt('M'), 'E');
  BOOST_CHECK_EQUAL(test.decrypt('D'), 'F');
  BOOST_CHECK_EQUAL(test.decrypt('N'), 'G');
  BOOST_CHECK_EQUAL(test.decrypt('E'), 'H');
  BOOST_CHECK_EQUAL(test.decrypt('O'), 'I');
  BOOST_CHECK_EQUAL(test.decrypt('F'), 'J');
  BOOST_CHECK_EQUAL(test.decrypt('P'), 'K');
  BOOST_CHECK_EQUAL(test.decrypt('G'), 'L');
  BOOST_CHECK_EQUAL(test.decrypt('Q'), 'M');
  BOOST_CHECK_EQUAL(test.decrypt('H'), 'N');
  BOOST_CHECK_EQUAL(test.decrypt('R'), 'O');
  BOOST_CHECK_EQUAL(test.decrypt('I'), 'P');
  BOOST_CHECK_EQUAL(test.decrypt('S'), 'Q');
  BOOST_CHECK_EQUAL(test.decrypt('J'), 'R');
  BOOST_CHECK_EQUAL(test.decrypt('T'), 'S');
  BOOST_CHECK_EQUAL(test.decrypt('K'), 'T');
  BOOST_CHECK_EQUAL(test.decrypt('U'), 'U');
  BOOST_CHECK_EQUAL(test.decrypt('L'), 'V');
  BOOST_CHECK_EQUAL(test.decrypt('V'), 'W');
  BOOST_CHECK_EQUAL(test.decrypt('M'), 'X');
  BOOST_CHECK_EQUAL(test.decrypt('W'), 'Y');
  BOOST_CHECK_EQUAL(test.decrypt('N'), 'Z');
}

/**
 * Test that a Rotor will decrypt letters correctly when using disk 2
 */
BOOST_AUTO_TEST_CASE(test_disk2)
{
  Rotor test(2);
  BOOST_CHECK_EQUAL(test.decrypt('W'), 'A');
  BOOST_CHECK_EQUAL(test.decrypt('B'), 'B');
  BOOST_CHECK_EQUAL(test.decrypt('X'), 'C');
  BOOST_CHECK_EQUAL(test.decrypt('C'), 'D');
  BOOST_CHECK_EQUAL(test.decrypt('Y'), 'E');
  BOOST_CHECK_EQUAL(test.decrypt('D'), 'F');
  BOOST_CHECK_EQUAL(test.decrypt('Z'), 'G');
  BOOST_CHECK_EQUAL(test.decrypt('E'), 'H');
  BOOST_CHECK_EQUAL(test.decrypt('A'), 'I');
  BOOST_CHECK_EQUAL(test.decrypt('F'), 'J');
  BOOST_CHECK_EQUAL(test.decrypt('B'), 'K');
  BOOST_CHECK_EQUAL(test.decrypt('G'), 'L');
  BOOST_CHECK_EQUAL(test.decrypt('C'), 'M');
  BOOST_CHECK_EQUAL(test.decrypt('H'), 'N');
  BOOST_CHECK_EQUAL(test.decrypt('D'), 'O');
  BOOST_CHECK_EQUAL(test.decrypt('I'), 'P');
  BOOST_CHECK_EQUAL(test.decrypt('E'), 'Q');
  BOOST_CHECK_EQUAL(test.decrypt('J'), 'R');
  BOOST_CHECK_EQUAL(test.decrypt('F'), 'S');
  BOOST_CHECK_EQUAL(test.decrypt('K'), 'T');
  BOOST_CHECK_EQUAL(test.decrypt('G'), 'U');
  BOOST_CHECK_EQUAL(test.decrypt('L'), 'V');
  BOOST_CHECK_EQUAL(test.decrypt('H'), 'W');
  BOOST_CHECK_EQUAL(test.decrypt('M'), 'X');
  BOOST_CHECK_EQUAL(test.decrypt('I'), 'Y');
  BOOST_CHECK_EQUAL(test.decrypt('N'), 'Z');
}

/**
 * Test that a Rotor will decrypt letters correctly when using disk 3
 */
BOOST_AUTO_TEST_CASE(test_disk3)
{
  /*
   * TODO: Fill this in! Until it's filled in, we'll just fail right
   * away.
   */
  Rotor test(3);
  BOOST_CHECK_EQUAL(test.decrypt('W'), 'A');
  BOOST_CHECK_EQUAL(test.decrypt('T'), 'B');
  BOOST_CHECK_EQUAL(test.decrypt('N'), 'C');
  BOOST_CHECK_EQUAL(test.decrypt('F'), 'D');
  BOOST_CHECK_EQUAL(test.decrypt('D'), 'E');
  BOOST_CHECK_EQUAL(test.decrypt('R'), 'F');
  BOOST_CHECK_EQUAL(test.decrypt('G'), 'G');
  BOOST_CHECK_EQUAL(test.decrypt('U'), 'H');
  BOOST_CHECK_EQUAL(test.decrypt('I'), 'I');
  BOOST_CHECK_EQUAL(test.decrypt('J'), 'J');
  BOOST_CHECK_EQUAL(test.decrypt('Y'), 'K');
  BOOST_CHECK_EQUAL(test.decrypt('S'), 'L');
  BOOST_CHECK_EQUAL(test.decrypt('H'), 'M');
  BOOST_CHECK_EQUAL(test.decrypt('X'), 'N');
  BOOST_CHECK_EQUAL(test.decrypt('P'), 'O');
  BOOST_CHECK_EQUAL(test.decrypt('O'), 'P'); //Here was the error thrown
  BOOST_CHECK_EQUAL(test.decrypt('W'), 'Q');
  BOOST_CHECK_EQUAL(test.decrypt('Z'), 'R');
  BOOST_CHECK_EQUAL(test.decrypt('P'), 'S');
  BOOST_CHECK_EQUAL(test.decrypt('J'), 'T');
  BOOST_CHECK_EQUAL(test.decrypt('S'), 'U');
  BOOST_CHECK_EQUAL(test.decrypt('V'), 'V');
  BOOST_CHECK_EQUAL(test.decrypt('K'), 'W');
  BOOST_CHECK_EQUAL(test.decrypt('Z'), 'X');
  BOOST_CHECK_EQUAL(test.decrypt('U'), 'Y');
  BOOST_CHECK_EQUAL(test.decrypt('R'), 'Z');
}

/**
 * Test that a Rotor will decrypt letters correctly when using disk 4
 */
BOOST_AUTO_TEST_CASE(test_disk4)
{
  Rotor test(4);
  BOOST_CHECK_EQUAL(test.decrypt('B'), 'A');
  BOOST_CHECK_EQUAL(test.decrypt('Z'), 'B');
  BOOST_CHECK_EQUAL(test.decrypt('E'), 'C');
  BOOST_CHECK_EQUAL(test.decrypt('Y'), 'D');
  BOOST_CHECK_EQUAL(test.decrypt('H'), 'E');
  BOOST_CHECK_EQUAL(test.decrypt('X'), 'F');
  BOOST_CHECK_EQUAL(test.decrypt('K'), 'G');
  BOOST_CHECK_EQUAL(test.decrypt('W'), 'H');
  BOOST_CHECK_EQUAL(test.decrypt('N'), 'I');
  BOOST_CHECK_EQUAL(test.decrypt('V'), 'J');
  BOOST_CHECK_EQUAL(test.decrypt('Q'), 'K');
  BOOST_CHECK_EQUAL(test.decrypt('U'), 'L');
  BOOST_CHECK_EQUAL(test.decrypt('T'), 'M');
  BOOST_CHECK_EQUAL(test.decrypt('T'), 'N');
  BOOST_CHECK_EQUAL(test.decrypt('W'), 'O');
  BOOST_CHECK_EQUAL(test.decrypt('S'), 'P');
  BOOST_CHECK_EQUAL(test.decrypt('Z'), 'Q');
  BOOST_CHECK_EQUAL(test.decrypt('R'), 'R');
  BOOST_CHECK_EQUAL(test.decrypt('C'), 'S');
  BOOST_CHECK_EQUAL(test.decrypt('Q'), 'T');
  BOOST_CHECK_EQUAL(test.decrypt('F'), 'U');
  BOOST_CHECK_EQUAL(test.decrypt('P'), 'V');
  BOOST_CHECK_EQUAL(test.decrypt('I'), 'W');
  BOOST_CHECK_EQUAL(test.decrypt('O'), 'X');
  BOOST_CHECK_EQUAL(test.decrypt('L'), 'Y');
  BOOST_CHECK_EQUAL(test.decrypt('N'), 'Z');
}

/**
 * Test that a Rotor will decrypt letters correctly when using disk 5
 */
BOOST_AUTO_TEST_CASE(test_disk5)
{
  /*
   * TODO: Fill this in! Until it's filled in, we'll just fail right
   * away.
   */
  Rotor test(5);
  BOOST_CHECK_EQUAL(test.decrypt('A'), 'A');
  BOOST_CHECK_EQUAL(test.decrypt('Z'), 'B');
  BOOST_CHECK_EQUAL(test.decrypt('E'), 'C');
  BOOST_CHECK_EQUAL(test.decrypt('Y'), 'D');
  BOOST_CHECK_EQUAL(test.decrypt('D'), 'E');
  BOOST_CHECK_EQUAL(test.decrypt('D'), 'F');
  BOOST_CHECK_EQUAL(test.decrypt('C'), 'G');
  BOOST_CHECK_EQUAL(test.decrypt('C'), 'H');
  BOOST_CHECK_EQUAL(test.decrypt('H'), 'I');
  BOOST_CHECK_EQUAL(test.decrypt('B'), 'J');
  BOOST_CHECK_EQUAL(test.decrypt('G'), 'K');
  BOOST_CHECK_EQUAL(test.decrypt('G'), 'L');
  BOOST_CHECK_EQUAL(test.decrypt('F'), 'M');
  BOOST_CHECK_EQUAL(test.decrypt('F'), 'N');
  BOOST_CHECK_EQUAL(test.decrypt('K'), 'O');
  BOOST_CHECK_EQUAL(test.decrypt('E'), 'P');
  BOOST_CHECK_EQUAL(test.decrypt('J'), 'Q');
  BOOST_CHECK_EQUAL(test.decrypt('J'), 'R');
  BOOST_CHECK_EQUAL(test.decrypt('I'), 'S');
  BOOST_CHECK_EQUAL(test.decrypt('I'), 'T');
  BOOST_CHECK_EQUAL(test.decrypt('N'), 'U');
  BOOST_CHECK_EQUAL(test.decrypt('H'), 'V');
  BOOST_CHECK_EQUAL(test.decrypt('M'), 'W');
  BOOST_CHECK_EQUAL(test.decrypt('M'), 'X');
  BOOST_CHECK_EQUAL(test.decrypt('L'), 'Y');
  BOOST_CHECK_EQUAL(test.decrypt('L'), 'Z');
}

BOOST_AUTO_TEST_CASE(test_decrypt_message)
{
  BOOST_CHECK_EQUAL(decrypt_message(1, 2, 3, "EKY_ONHQJ_RLDEE_ZFZ_MVLFD_JEYM_WKK_SMVM_ROC"), "THE_QUICK_BROWN_FOX_JUMPS_OVER_THE_LAZY_DOG");
  BOOST_CHECK_EQUAL(decrypt_message(3, 4, 5, "VYO_QKSFZ_ZWQGV_POJ_IBBRB_WEWR_EHS_DZWE_JFR"), "THE_QUICK_BROWN_FOX_JUMPS_OVER_THE_LAZY_DOG");
}
