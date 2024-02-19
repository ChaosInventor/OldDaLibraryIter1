#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <limits.h>

#include "../ASCIIString.hpp"
using namespace Library::DataStructures::Strings;

TEST_CASE("Get size of c string", "[ASCIIString][Helper]")
{

    CHECK(FindSizeOfCString("123") == 3);
    CHECK(FindSizeOfCString("Hi") == 2);
    CHECK(FindSizeOfCString("") == 0);
    CHECK(FindSizeOfCString("the quick brown fox jumped over the lazy dog") == 44);

}

TEST_CASE("Upper lower case check")
{

    for(char l_char = CHAR_MIN; l_char++ < CHAR_MAX;)
    {
        if(l_char >= 'a' && l_char <= 'z')
        {
            CHECK(ASCIICharacterIsLowercaseLetter(l_char) == true);
            CHECK(ASCIICharacterIsUppercaseLetter(l_char) == false);
        }
        else if(l_char >= 'A' && l_char <= 'Z')
        {
            CHECK(ASCIICharacterIsLowercaseLetter(l_char) == false);
            CHECK(ASCIICharacterIsUppercaseLetter(l_char) == true);
        }
        else
        {
            CHECK(ASCIICharacterIsLowercaseLetter(l_char) == false);
            CHECK(ASCIICharacterIsUppercaseLetter(l_char) == false);
        }
        
    }

}

TEST_CASE("Printable not printable check")
{

    for(char l_char = CHAR_MIN; l_char++ < CHAR_MAX;)
    {
        if(l_char >= 0x20 && l_char < 0x7F)
        {
            CHECK(ASCIICharacterIsPrintable(l_char) == true);
            CHECK(ASCIICharacterIsNotPrintable(l_char) == false);
        }
        else if((l_char >= 0x0 && l_char <= 0x20) || l_char == 0x7F)
        {
            CHECK(ASCIICharacterIsPrintable(l_char) == false);
            CHECK(ASCIICharacterIsNotPrintable(l_char) == true);
        }
        else
        {
            CHECK(ASCIICharacterIsPrintable(l_char) == false);
            CHECK(ASCIICharacterIsNotPrintable(l_char) == true);
        }
    }

}
