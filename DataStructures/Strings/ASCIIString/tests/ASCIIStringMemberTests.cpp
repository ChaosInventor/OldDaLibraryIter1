#include <catch2/catch.hpp>

#include "../ASCIIString.hpp"

using namespace Library::DataStructures::Strings;
using namespace Library::DataStructures::Array;
using namespace Catch::Generators;

TEST_CASE("Default constructor", "[ASCIIString][Member][Creation]")
{

    ASCIIString l_string;

    CHECK(l_string.m_Array.m_Buffer == nullptr);
    CHECK(l_string.m_Array.m_Capacity == 0);
    CHECK(l_string.m_Array.m_Size == 0);

}

TEST_CASE("Copying", "[ASCIIString][Member]")
{

    ASCIIString l_from;
    ASCIIString l_to;

    l_from.m_Array.m_Buffer = (char*)GENERATE(range<intptr_t>(1, 10));
    l_from.m_Array.m_Capacity = GENERATE(range(1, 10));
    l_from.m_Array.m_Size = GENERATE(range(1, 10));

    SECTION("Constructor")
    {
        l_to = ASCIIString(l_from);
    }
    SECTION("Operator")
    {
        l_to = l_from;
    }

    CHECK(l_to.m_Array.m_Buffer == l_from.m_Array.m_Buffer);
    CHECK(l_to.m_Array.m_Capacity == l_from.m_Array.m_Capacity);
    CHECK(l_to.m_Array.m_Size == l_from.m_Array.m_Size);

}
TEST_CASE("Moving", "[ASCIIString][Member]")
{

    ASCIIString l_from;
    ASCIIString l_to;

    char* l_buffer = (char*)GENERATE(range<intptr_t>(1, 10));
    Size l_capacity = GENERATE(range(1, 10));
    Size l_size = GENERATE(range(1, 10));

    l_from.m_Array.m_Buffer = l_buffer;
    l_from.m_Array.m_Capacity = l_capacity;
    l_from.m_Array.m_Size = l_size;

    SECTION("Constructor")
    {
        l_to = ASCIIString((ASCIIString&&)l_from);
    }
    SECTION("Operator")
    {
        l_to = (ASCIIString&&)l_from;
    }

    CHECK(l_to.m_Array.m_Buffer == l_buffer);
    CHECK(l_to.m_Array.m_Capacity == l_capacity);
    CHECK(l_to.m_Array.m_Size == l_size);

    CHECK(l_from.m_Array.m_Buffer == nullptr);
    CHECK(l_from.m_Array.m_Capacity == 0);
    CHECK(l_from.m_Array.m_Size == 0);

}

TEST_CASE("Construction from array", "[ASCIIString][Member]")
{

    Array<char> l_array;

    l_array.m_Buffer = (char*)GENERATE(range<intptr_t>(1, 10));
    l_array.m_Capacity = GENERATE(range(1, 10));
    l_array.m_Size = GENERATE(range(1, 10));

    ASCIIString l_string(l_array);

    CHECK(l_string.m_Array.m_Buffer == l_array.m_Buffer);
    CHECK(l_string.m_Array.m_Capacity == l_array.m_Capacity);
    CHECK(l_string.m_Array.m_Size == l_array.m_Size);


}

TEST_CASE("Construction from c string", "[ASCIIString][Member][Creation]")
{

    const char* l_cString = GENERATE("Hi", "Hello", "C string lol", "9996");
    const char* l_empty = "";

    ASCIIString l_string(l_cString);
    ASCIIString l_emptyString(l_empty);
    ASCIIString l_null(nullptr);

    CHECK(l_emptyString.m_Array.m_Buffer == nullptr);
    CHECK(l_emptyString.m_Array.m_Capacity == 0);
    CHECK(l_emptyString.m_Array.m_Size == 0);

    CHECK(l_null.m_Array.m_Buffer == nullptr);
    CHECK(l_null.m_Array.m_Capacity == 0);
    CHECK(l_null.m_Array.m_Size == 0);

    REQUIRE(l_string.m_Array.m_Buffer != nullptr);
    REQUIRE(l_string.m_Array.m_Size == FindSizeOfCString(l_cString));
    REQUIRE(l_string.m_Array.m_Capacity == l_string.m_Array.m_Size);

    for(Size i = 0; i < l_string.m_Array.m_Size; ++i)
    {
        CHECK(l_string[i] == l_cString[i]);
    }

    DestoryArray(l_string.m_Array);

}

TEST_CASE("Conversion to array and pointer", "[ASCIIString][Member][Conversion]")
{

    ASCIIString l_string;

    l_string.m_Array.m_Buffer = (char*)GENERATE(range<intptr_t>(1, 10));
    l_string.m_Array.m_Capacity = GENERATE(range(1, 10));
    l_string.m_Array.m_Size = GENERATE(range(1, 10));

    Array<char>& l_array = l_string;
    char* l_buffer = l_string;

    CHECK(&l_array == &l_string.m_Array);
    CHECK(l_buffer == l_string.m_Array.m_Buffer);

}

//Note: index operator is not tested as it's a wrapper for array.

TEST_CASE("Comparison with c string", "[ASCIIString][Member]")
{

    ASCIIString l_string("String");
    ASCIIString l_nullString;
    ASCIIString l_emptyString;
    CreateArrayAtOfCapacity((Array<char>&)l_emptyString, 10);

    const char* l_same = "String";
    const char* l_diffrent1 = "Stirng";
    const char* l_diffrent2 = "Stringing";
    const char* l_diffrent3 = "Str";
    const char* l_empty = "";

    CHECK(l_string == l_same);
    CHECK_FALSE(l_string == l_diffrent1);
    CHECK_FALSE(l_string == l_diffrent2);
    CHECK_FALSE(l_string == l_diffrent3);
    CHECK_FALSE(l_string == l_empty);
    CHECK_FALSE(l_string == nullptr);

    CHECK_FALSE(l_string != l_same);
    CHECK(l_string != l_diffrent1);
    CHECK(l_string != l_diffrent2);
    CHECK(l_string != l_diffrent3);
    CHECK(l_string != l_empty);
    CHECK(l_string != nullptr);

    CHECK_FALSE(l_nullString == l_same);
    CHECK_FALSE(l_nullString == l_diffrent1);
    CHECK_FALSE(l_nullString == l_diffrent2);
    CHECK_FALSE(l_nullString == l_diffrent3);
    CHECK_FALSE(l_nullString == l_empty);
    CHECK(l_nullString == nullptr);

    CHECK(l_nullString != l_same);
    CHECK(l_nullString != l_diffrent1);
    CHECK(l_nullString != l_diffrent2);
    CHECK(l_nullString != l_diffrent3);
    CHECK(l_nullString != l_empty);
    CHECK_FALSE(l_nullString != nullptr);

    CHECK_FALSE(l_emptyString == l_same);
    CHECK_FALSE(l_emptyString == l_diffrent1);
    CHECK_FALSE(l_emptyString == l_diffrent2);
    CHECK_FALSE(l_emptyString == l_diffrent3);
    CHECK(l_emptyString == l_empty);
    CHECK_FALSE(l_emptyString == nullptr);

    CHECK(l_emptyString != l_same);
    CHECK(l_emptyString != l_diffrent1);
    CHECK(l_emptyString != l_diffrent2);
    CHECK(l_emptyString != l_diffrent3);
    CHECK_FALSE(l_emptyString != l_empty);
    CHECK(l_emptyString != nullptr);

    DestoryArray(l_string.m_Array);
    DestoryArray<char>(l_emptyString);

}

//Note: Comparison between 2 strings is not tested as it is a wrapper for
//array comparison.

TEST_CASE("Concatenating strings", "[ASCIIString][Member]")
{

    ASCIIString l_string = (ASCIIString)GENERATE(
        "String",
        "Hi",
        "",
        "World",
        "UwU",
        "  O  "
    );
    ASCIIString l_string2 = (ASCIIString)GENERATE(
        "Pear",
        "Bye",
        "",
        "Universe",
        "OwO",
        "  A  "
    );
    const char* l_cString = GENERATE(
        "Cat",
        "",
        "What the f(@! did you just f#*$!6g say about me, you little b$&^@? I’ll have you know I graduated top of my class in the Navy Seals, and I’ve been involved in numerous secret raids on Al-Quaeda, and I have over 300...",
        "asdasdasda",
        "7w7",
        "  U  "
    );
    Size l_cStringSize = FindSizeOfCString(l_cString);

    ASCIIString l_result;

    SECTION("First example")
    {
        Size l_collectiveSize = l_string.m_Array.m_Size + l_string2.m_Array.m_Size;

        l_result = l_string + l_string2;

        if(ArrayIsEmpty<char>(l_string) && ArrayIsEmpty<char>(l_string2))
        {
            CHECK(ArrayIsEmpty<char>(l_result));
            CHECK(l_result.m_Array.m_Capacity == 0);

            return;
        }

        REQUIRE(l_result.m_Array.m_Buffer != nullptr);
        REQUIRE(l_result.m_Array.m_Capacity >= l_collectiveSize);
        REQUIRE(l_result.m_Array.m_Size == l_collectiveSize);

        //Checks for l_result
        Size i;
        for(i = 0; i < l_string.m_Array.m_Size; ++i)
        {
            CHECK(l_result[i] == l_string[i]);
        }
        for(Size n = 0; n < l_string2.m_Array.m_Size; ++n, ++i)
        {
            CHECK(l_result[i] == l_string2[n]);
        }
    }
    SECTION("Second example")
    {
        Size l_collectiveSize = l_string2.m_Array.m_Size + l_string.m_Array.m_Size;
        l_result = l_string2 + l_string;

        if(ArrayIsEmpty<char>(l_string) && ArrayIsEmpty<char>(l_string2))
        {
            CHECK(ArrayIsEmpty<char>(l_result));
            CHECK(l_result.m_Array.m_Capacity == 0);

            return;
        } 

        REQUIRE(l_result.m_Array.m_Buffer != nullptr);
        REQUIRE(l_result.m_Array.m_Capacity >= l_collectiveSize);
        REQUIRE(l_result.m_Array.m_Size == l_collectiveSize);

        //Checks for l_result
        Size i;
        for(i = 0; i < l_string2.m_Array.m_Size; ++i)
        {
            CHECK(l_result[i] == l_string2[i]);
        }
        for(Size n = 0; n < l_string.m_Array.m_Size; ++n, ++i)
        {
            CHECK(l_result[i] == l_string[n]);
        }
    }
    SECTION("Third example")
    {
        Size l_collectiveSize = l_cStringSize + l_string.m_Array.m_Size;
        l_result = l_cString + l_string;

        if(ArrayIsEmpty<char>(l_string) && l_cStringSize == 0)
        {
            CHECK(ArrayIsEmpty<char>(l_result));
            CHECK(l_result.m_Array.m_Capacity == 0);

            return;
        }

        REQUIRE(l_result.m_Array.m_Buffer != nullptr);
        REQUIRE(l_result.m_Array.m_Capacity >= l_collectiveSize);
        REQUIRE(l_result.m_Array.m_Size == l_collectiveSize);

        //Checks for l_result
        Size i;
        for(i = 0; i < l_cStringSize; ++i)
        {
            CHECK(l_result[i] == l_cString[i]);
        }
        for(Size n = 0; n < l_string.m_Array.m_Size; ++n, ++i)
        {
            CHECK(l_result[i] == l_string[n]);
        }
    }
    SECTION("Fourth example")
    {
        Size l_collectiveSize = l_string.m_Array.m_Size + l_string2.m_Array.m_Size + l_cStringSize;

        l_result = (l_string + l_string2) += l_cString;

        if(ArrayIsEmpty<char>(l_string) && ArrayIsEmpty<char>(l_string2) && l_cStringSize == 0)
        {
            CHECK(ArrayIsEmpty<char>(l_result));
            CHECK(l_result.m_Array.m_Capacity == 0);

            return;
        }

        REQUIRE(l_result.m_Array.m_Buffer != nullptr);
        REQUIRE(l_result.m_Array.m_Capacity >= l_collectiveSize);
        REQUIRE(l_result.m_Array.m_Size == l_collectiveSize);

        //Checks for l_result
        Size i;
        for(i = 0; i < l_string.m_Array.m_Size; ++i)
        {
            CHECK(l_result[i] == l_string[i]);
        }
        for(Size n = 0; n < l_string2.m_Array.m_Size; ++n, ++i)
        {
            CHECK(l_result[i] == l_string2[n]);
        }
        for(Size n = 0; n < l_cStringSize; ++n, ++i)
        {
            CHECK(l_result[i] == l_cString[n]);
        }
    }
    SECTION("Fifth example")
    {
        Size l_collectiveSize = l_string.m_Array.m_Size + l_string2.m_Array.m_Size + l_cStringSize;

        l_result = (l_string + l_cString) += l_string2;

        if(ArrayIsEmpty<char>(l_string) && ArrayIsEmpty<char>(l_string2) && l_cStringSize == 0)
        {
            CHECK(ArrayIsEmpty<char>(l_result));
            CHECK(l_result.m_Array.m_Capacity == 0);

            return;
        }

        REQUIRE(l_result.m_Array.m_Buffer != nullptr);
        REQUIRE(l_result.m_Array.m_Capacity >= l_collectiveSize);
        REQUIRE(l_result.m_Array.m_Size == l_collectiveSize);

        //Checks for l_result
        Size i;
        for(i = 0; i < l_string.m_Array.m_Size; ++i)
        {
            CHECK(l_result[i] == l_string[i]);
        }
        for(Size n = 0; n < l_cStringSize; ++n, ++i)
        {
            CHECK(l_result[i] == l_cString[n]);
        }
        for(Size n = 0; n < l_string2.m_Array.m_Size; ++n, ++i)
        {
            CHECK(l_result[i] == l_string2[n]);
        }
    }

    DestoryArray<char>(l_string);
    DestoryArray<char>(l_string2);
    DestoryArray<char>(l_result);

}
