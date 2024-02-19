#include <catch2/catch.hpp>

#include <limits.h>
#include "../ASCIIString.hpp"

using namespace Library::DataStructures::Strings;
using namespace Library::DataStructures::Array;
using namespace Catch::Generators;

TEST_CASE("Remove all whitespaces")
{

    
    const char* l_cString = GENERATE(
        "Hi",
        "String and string",
        "Th  is s t r i n   g h a a s   a  lo   t ",
        " of    w h i te sp a ce s"
        "        ",
        "String",
        "",
        "Hello, world"
    );
    ASCIIString l_string(l_cString);

    char* l_oldBuffer = l_string;
    Size l_oldSize = l_string.m_Array.m_Size;
    Size l_oldCapacity = l_string.m_Array.m_Capacity;

    RemoveAllWhitespacesFromASCIIString(l_string);

    REQUIRE(l_string.m_Array.m_Buffer == l_oldBuffer);
    REQUIRE(l_string.m_Array.m_Size <= l_oldSize);
    REQUIRE(l_string.m_Array.m_Capacity == l_oldCapacity);

    Size l_expectedSize = 0;
    for(Size i = 0, n = 0; i < FindSizeOfCString(l_cString); ++i)
    {
        if(l_cString[i] != ' ')
        {
            ++l_expectedSize;
            INFO(l_cString << " i = " << i << " n = " << n);
            CHECK(l_string[n] == l_cString[i]);
            ++n;
        }
    }

    CHECK(l_string.m_Array.m_Size == l_expectedSize);

    DestoryArray<char>(l_string);

}

TEST_CASE("Remove trailing whitespaces")
{

    //In order to add a string here the string must not contain any whitespaces
    //besides the ones at the end or the test case will give false positives.
    const char* l_cString = GENERATE(
        "String   ",
        "Apple   ",
        ">w<",
        "1236   ",
        "                                                             ",
        "",
        "Byeeee    "
    );
    ASCIIString l_string(l_cString);

    char* l_oldBuffer = l_string;
    Size l_oldSize = l_string.m_Array.m_Size;
    Size l_oldCapacity = l_string.m_Array.m_Capacity;

    RemoveAllWhitespacesFromASCIIString(l_string);    

    REQUIRE(l_string.m_Array.m_Buffer == l_oldBuffer);
    REQUIRE(l_string.m_Array.m_Size <= l_oldSize);
    REQUIRE(l_string.m_Array.m_Capacity == l_oldCapacity);

    Size l_expectedSize = 0;
    for(Size i = 0; i < FindSizeOfCString(l_cString); ++i)
    {
        if(l_cString[i] != ' ')
        {
            CHECK(l_string[i] == l_cString[i]);
            ++l_expectedSize;
        }
        else
        {
            break;
        }
    }

    CHECK(l_string.m_Array.m_Size == l_expectedSize);

    DestoryArray<char>(l_string);

}

TEST_CASE("Upper and lower case")
{

    char l_upperChars[26];
    char l_lowerChars[26];

    Size i = 0;
    for(char n = 'A'; n <= 'Z'; ++n, ++i)
    {
        l_upperChars[i] = n;
    }
    i = 0;
    for(char n = 'a'; n <= 'z'; ++n, ++i)
    {
        l_lowerChars[i] = n;
    }

    SECTION("To upper")
    {
        for(Size i = 0; i < sizeof(l_lowerChars); ++i)
        {
            ASCIILetterAtToUpper(l_lowerChars[i]);
            CHECK(l_lowerChars[i] == l_upperChars[i]);
        }
    }
    SECTION("To lower")
    {
        for(Size i = 0; i < sizeof(l_upperChars); ++i)
        {
            ASCIILetterAtToLower(l_upperChars[i]);
            CHECK(l_upperChars[i] == l_lowerChars[i]);
        }
    }
    SECTION("Invalid chars")
    {
        for(char l_char = CHAR_MIN; l_char++ < CHAR_MAX;)
        {
            if
            (
                (l_char >= 'A' && l_char <= 'Z')
                ||
                (l_char >= 'a' && l_char <= 'z')
            )
            {
                continue;
            }

            char l_old = l_char;
            ASCIILetterAtToLower(l_char);
            REQUIRE(l_char == l_old);
            ASCIILetterAtToUpper(l_char);
            REQUIRE(l_char == l_old);
        }
    }

}

TEST_CASE("String to upper and lower")
{

    //Note: this test depends on the other test: "Upper and lower case" to
    //function properly.

    const char* l_cString = GENERATE(
        "String",
        "",
        "Goodbye, cruel world",
        "hElOO",
        "I am trained in gorilla warfare and I’m the top sniper in the entire US armed forces. You are nothing to me but just another target. I will wipe you the f*^# out with precision the likes of which has never been seen before on this Earth, mark my f#@!$&* words...",
        "OwOwOwO"
    );
    ASCIIString l_string1(l_cString);
    ASCIIString l_string2(l_cString);

    ASCIIStringAtToLower(l_string1);
    ASCIIStringAtToUpper(l_string2);

    if(FindSizeOfCString(l_cString) > 0)
    {
        REQUIRE(l_string1 != nullptr);
        REQUIRE(l_string1.m_Array.m_Capacity == FindSizeOfCString(l_cString));
        REQUIRE(l_string1.m_Array.m_Size == FindSizeOfCString(l_cString));

        REQUIRE(l_string2 != nullptr);
        REQUIRE(l_string2.m_Array.m_Capacity == FindSizeOfCString(l_cString));
        REQUIRE(l_string2.m_Array.m_Size == FindSizeOfCString(l_cString));
    }
    else
    {
        REQUIRE(l_string1 == nullptr);
        REQUIRE(l_string1.m_Array.m_Capacity == FindSizeOfCString(l_cString));
        REQUIRE(l_string1.m_Array.m_Size == FindSizeOfCString(l_cString));

        REQUIRE(l_string2 == nullptr);
        REQUIRE(l_string2.m_Array.m_Capacity == FindSizeOfCString(l_cString));
        REQUIRE(l_string2.m_Array.m_Size == FindSizeOfCString(l_cString));
    }
    
    for(Size i = 0; i < FindSizeOfCString(l_cString); ++i)
    {
        if(l_cString[i] >= 'A' || l_cString[i] <= 'Z')
        {
            char l_charButLower = l_cString[i];
            ASCIILetterAtToLower(l_charButLower);
            CHECK(l_string1[i] == l_charButLower);
        }
        else
        {
            CHECK(l_cString[i] == l_string1[i]);
        }
    }
    for(Size i = 0; i < FindSizeOfCString(l_cString); ++i)
    {
        if(l_cString[i] >= 'a' || l_cString[i] <= 'z')
        {
            char l_charButUpper = l_cString[i];
            ASCIILetterAtToUpper(l_charButUpper);
            CHECK(l_string2[i] == l_charButUpper);
        }
        else
        {
            CHECK(l_cString[i] == l_string2[i]);
        }
    }

    DestoryArray<char>(l_string1);
    DestoryArray<char>(l_string2);

}
