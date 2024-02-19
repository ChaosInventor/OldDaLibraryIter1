#include <catch2/catch.hpp>

#include "../ASCIIString.hpp"

using namespace Library::DataStructures::Strings;
using namespace Catch::Generators;
using namespace Library::DataStructures::Array;

TEMPLATE_TEST_CASE("Number to character", "[ASCIIString][Conversion][Num to char]",
    char, short, int, long,
    unsigned char, unsigned short, unsigned int, unsigned long
)
{

    for(TestType i = 0; i <= 9; ++i)
    {
        char l_char;
        ConvertNumberToASCIICharacterAtAssumingProperNumber<TestType>(i, l_char);

        switch(i)
        {
            case 0:
            {
                CHECK(l_char == '0');
                break;
            }
            case 1:
            {
                CHECK(l_char == '1');
                break;
            }
            case 2:
            {
                CHECK(l_char == '2');
                break;
            }
            case 3:
            {
                CHECK(l_char == '3');
                break;
            }
            case 4:
            {
                CHECK(l_char == '4');
                break;
            }
            case 5:
            {
                CHECK(l_char == '5');
                break;
            }
            case 6:
            {
                CHECK(l_char == '6');
                break;
            }
            case 7:
            {
                CHECK(l_char == '7');
                break;
            }
            case 8:
            {
                CHECK(l_char == '8');
                break;
            }
            case 9:
            {
                CHECK(l_char == '9');
                break;
            }

            default:
            {
                FAIL("Error in test case, i = " << i);
                break;
            }
        }
    }

    for(TestType i = 10; i <= 35; ++i)
    {
        char l_char;
        ConvertNumberToASCIICharacterAtAssumingProperNumber<TestType>(i, l_char);
        
        switch(i)
        {
            case 10:
            {
                CHECK(l_char == 'A');
                break;
            }
            case 11:
            {
                CHECK(l_char == 'B');
                break;
            }
            case 12:
            {
                CHECK(l_char == 'C');
                break;
            }
            case 13:
            {
                CHECK(l_char == 'D');
                break;
            }
            case 14:
            {
                CHECK(l_char == 'E');
                break;
            }
            case 15:
            {
                CHECK(l_char == 'F');
                break;
            }
            case 16:
            {
                CHECK(l_char == 'G');
                break;
            }
            case 17:
            {
                CHECK(l_char == 'H');
                break;
            }
            case 18:
            {
                CHECK(l_char == 'I');
                break;
            }
            case 19:
            {
                CHECK(l_char == 'J');
                break;
            }
            case 20:
            {
                CHECK(l_char == 'K');
                break;
            }
            case 21:
            {
                CHECK(l_char == 'L');
                break;
            }
            case 22:
            {
                CHECK(l_char == 'M');
                break;
            }
            case 23:
            {
                CHECK(l_char == 'N');
                break;
            }
            case 24:
            {
                CHECK(l_char == 'O');
                break;
            }
            case 25:
            {
                CHECK(l_char == 'P');
                break;
            }
            case 26:
            {
                CHECK(l_char == 'Q');
                break;
            }
            case 27:
            {
                CHECK(l_char == 'R');
                break;
            }
            case 28:
            {
                CHECK(l_char == 'S');
                break;
            }
            case 29:
            {
                CHECK(l_char == 'T');
                break;
            }
            case 30:
            {
                CHECK(l_char == 'U');
                break;
            }
            case 31:
            {
                CHECK(l_char == 'V');
                break;
            }
            case 32:
            {
                CHECK(l_char == 'W');
                break;
            }
            case 33:
            {
                CHECK(l_char == 'X');
                break;
            }
            case 34:
            {
                CHECK(l_char == 'Y');
                break;
            }
            case 35:
            {
                CHECK(l_char == 'Z');
                break;
            }

            default:
            {
                FAIL("Error in test case, i = " << i);
                break;
            }
        
        }
    }

}

TEMPLATE_TEST_CASE("Character to number", "[ASCIIString][Conversion][Char to num]",
    char, short, int, long,
    unsigned char, unsigned short, unsigned int, unsigned long
)
{


    SECTION("Number chars")
    {
        TestType l_result = -1;
        TestType l_expectedResult = 0;
        for(char l_char = '0'; l_char <= '9'; ++l_char, ++l_expectedResult)
        {
            ConvertASCIICharacterToNumberAtAssummingProperCharacter<TestType>(
                l_char,
                l_result
            );

            CHECK(l_result == l_expectedResult);
        }
    }
    SECTION("Letters")
    {
        TestType l_resultUpper = -1;
        TestType l_resultLower = -1;

        TestType l_expectedResult = 10;
        for(char l_upper = 'A', l_lower = 'a'; l_upper <= 'Z';++l_expectedResult, ++l_upper, ++l_lower)
        {
            ConvertASCIICharacterToNumberAtAssummingProperCharacter<TestType>(
                l_upper,
                l_resultUpper
            );
            ConvertASCIICharacterToNumberAtAssummingProperCharacter<TestType>(
                l_lower,
                l_resultLower
            );

            CHECK(l_resultUpper == l_expectedResult);
            CHECK(l_resultLower == l_expectedResult);
        }
    }

}

TEST_CASE("Number to string", "[ASCIIString][Conversion][Num to string]")
{

    ASCIIString l_string;

    //The way this test works is by first picking an index ranging from 0 to
    //l_numberOfConversions. This number is converted to a string at
    //l_string. The base is l_base[i], where i is the same index that was used
    //in l_num. After the conversion the result is compared to l_expected[i]
    //where i is the same index that was used in l_num and l_base.

    Size l_numberOfConversions = 6;
    int l_num[] = 
    {
        3,
        255,
        67890,
        1222,
        -667,
        -5
    };
    int l_base[] = 
    {
        2,
        16,
        10,
        36,
        3,
        2
    };
    const char* l_expected[] = 
    {
        "11",
        "FF",
        "67890",
        "XY",
        "-220201",
        "-101"
    };

    Size i = GENERATE_COPY(range<Size>(0, l_numberOfConversions));

    ConvertNumberToASCIIStringInBaseUsingAllocator(l_num[i], l_string, l_base[i]);

    INFO("i = " << i);
    CHECK(l_string == l_expected[i]);

    DestoryArray<char>(l_string);

}

TEST_CASE("String to number", "[ASCIIString][Conversion][String to num]")
{

    int l_result;

    Size l_numberOfConversions = 6;
    ASCIIString l_string[] = 
    {
        ASCIIString("11"),
        ASCIIString("fF"),
        ASCIIString("67890"),
        ASCIIString("Xy"),
        ASCIIString("-220201"),
        ASCIIString("-101")
    };
    int l_base[] = 
    {
        2,
        16,
        10,
        36,
        3,
        2
    };
    int l_expected[] = 
    {
        3,
        255,
        67890,
        1222,
        -667,
        -5
    };

    Size i = GENERATE_COPY(range<Size>(0, l_numberOfConversions));

    ConvertASCIIStringToNumberAtInBase(l_string[i], l_result, l_base[i]);

    INFO("i = " << i);
    CHECK(l_result == l_expected[i]);

    DestoryArray<char>(l_string[i]);

}
