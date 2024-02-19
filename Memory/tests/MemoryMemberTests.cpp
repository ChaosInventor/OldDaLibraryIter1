#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../Memory.hpp"

using namespace Library;
using namespace Catch::Generators;

TEST_CASE("Default constructor", "[Memory][Member]")
{

    Memory l_mem;

    CHECK(l_mem.m_Location == nullptr);
    CHECK(l_mem.m_Size == 0);
    CHECK(l_mem.m_Permissions == 0);

}

TEST_CASE("Field constructor", "[Memory][Member]")
{

    Byte* l_dummyLocation = (Byte*)GENERATE(take(10, random(INTPTR_MIN, INTPTR_MAX)));
    Size l_dummySize = GENERATE(take(10, random<Size>(0, SIZE_MAX)));;
    Byte l_dummyPremissions = GENERATE(take(10, random(0, 7)));;

    Memory l_mem(l_dummyLocation, l_dummySize, l_dummyPremissions);

    CHECK(l_mem.m_Location == l_dummyLocation);
    CHECK(l_mem.m_Size == l_dummySize);
    CHECK(l_mem.m_Permissions == l_dummyPremissions);

}

TEST_CASE("Copying and moving", "[Memory][Member]")
{

    Byte* l_dummyLocation = (Byte*)GENERATE(take(10, random(INTPTR_MIN, INTPTR_MAX)));
    Size l_dummySize = GENERATE(take(10, random<Size>(0, SIZE_MAX)));;
    Byte l_dummyPremissions = GENERATE(take(10, random(0, 7)));;

    Memory l_source(l_dummyLocation, l_dummySize, l_dummyPremissions);
    Memory l_destination;

    SECTION("Copying")
    {
        SECTION("Constructor")
        {
            l_destination = Memory(l_source);
        }
        SECTION("Operator")
        {
            l_destination = l_source;
        }
    }
    SECTION("Moving")
    {
        SECTION("Constructor")
        {
            l_destination = Memory((Memory&&)l_source);
        }
        SECTION("Operator")
        {
            l_destination = (Memory&&)l_source;
        }

        CHECK(l_source.m_Location == nullptr);
        CHECK(l_source.m_Size == 0);
        CHECK(l_source.m_Permissions == 0);
    }

    CHECK(l_destination.m_Location == l_dummyLocation);
    CHECK(l_destination.m_Size == l_dummySize);
    CHECK(l_destination.m_Permissions == l_dummyPremissions);


}

TEST_CASE("Comparison", "[Memory][Member]")
{

    Byte* l_dummyLocation = (Byte*)GENERATE(take(10, random(INTPTR_MIN, INTPTR_MAX)));
    Size l_dummySize = GENERATE(take(10, random<Size>(0, SIZE_MAX)));;
    Byte l_dummyPremissions = GENERATE(take(10, random(0, 7)));;

    Memory l_mem(l_dummyLocation, l_dummySize, l_dummyPremissions);
    Memory l_same(l_dummyLocation, l_dummySize, l_dummyPremissions);
    Memory l_different(l_dummyLocation + 2, l_dummySize - 2, l_dummyPremissions & 1);

    CHECK((l_mem == l_same));
    CHECK_FALSE((l_mem == l_different));
    CHECK((l_mem == l_mem));

    CHECK_FALSE((l_mem != l_same));
    CHECK((l_mem != l_different));
    CHECK_FALSE((l_mem != l_mem));

}
