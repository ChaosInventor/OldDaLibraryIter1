#include <catch2/catch.hpp>

#include "../ASCIIString.hpp"
#include "../../../../Debugging/Debugging.hpp"

using namespace Library::DataStructures::Strings;
using namespace Debugging;

TEST_CASE("Create empty", "[ASCIIString][Creation]")
{

    ASCIIString l_string;
    
    l_string.m_Array.m_Buffer = (char*)0xdead;
    l_string.m_Array.m_Capacity = 4309567;
    l_string.m_Array.m_Size = 4242424242;

    SECTION("Copy c string null c string")
    {
        SECTION("Defaults")
        {
            CreateASCIIStringAtFromCopyOfCString(l_string, nullptr);
        }
        SECTION("Customs")
        {
            bool l_called = false;
            CreateASCIIStringAtFromCopyOfCStringUsingAllocator(
                l_string, nullptr,
                NullMalloc, &GeneralErrorCallback, &l_called
            );

            CHECK(l_called == false);
        }
    }
    SECTION("Copy c string only null charater")
    {
        SECTION("Defaults")
        {
            CreateASCIIStringAtFromCopyOfCString(l_string, "");
        }
        SECTION("Customs")
        {
            bool l_called = false;
            CreateASCIIStringAtFromCopyOfCStringUsingAllocator(
                l_string, "",
                NullMalloc, &GeneralErrorCallback, &l_called
            );

            CHECK(l_called == false);
        }
    }
    SECTION("Copy c string alloc error")
    {
    
        bool l_called = false;
        CreateASCIIStringAtFromCopyOfCStringUsingAllocator(
            l_string, "String",
            NullMalloc, &GeneralErrorCallback, &l_called
        );

        CHECK(l_called == true);
    
    }
    
    CHECK(l_string.m_Array.m_Buffer == nullptr);
    CHECK(l_string.m_Array.m_Capacity == 0);
    CHECK(l_string.m_Array.m_Size == 0);

}

TEST_CASE("Copy c string", "[ASCIIString][Creation]")
{

    ASCIIString l_string;

    const char* l_cString = GENERATE(
        "Hi",
        "String",
        "Hello, World!",
        "Pear",
        "Cloud",
        "Meow",
        "QwQ",
        "OmO"
    );

    Size l_cStringSize = FindSizeOfCString(l_cString);

    SECTION("Defaults")
    {
        CreateASCIIStringAtFromCopyOfCString(
            l_string, l_cString
        );
    }
    SECTION("Customs")
    {
        bool l_called = false;
        
        CreateASCIIStringAtFromCopyOfCStringUsingAllocator(
            l_string, l_cString,
            malloc, &GeneralErrorCallback, &l_called
        );
        
        CHECK(l_called == false);
    }

    REQUIRE(l_string != nullptr);
    REQUIRE(l_string.m_Array.m_Capacity >= l_cStringSize);
    REQUIRE(l_string.m_Array.m_Size == l_cStringSize);

    for(Size i = 0; i < l_cStringSize; ++i)
    {
        CHECK(l_string[i] == l_cString[i]);
    }

}
