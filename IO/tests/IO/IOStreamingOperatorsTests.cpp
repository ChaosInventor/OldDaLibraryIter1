#include <catch2/catch.hpp>

#include "../../include/IO.hpp"

using namespace Library;
using namespace Library::IO;

TEMPLATE_TEST_CASE(
    "Reading and writing using the streaming operators", "[IO][Stream][Streaming]",
    char, short, int, long, long long,
    unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long
)
{

    TestType l_thing;

    Byte* l_thingAsBytes = (Byte*)&l_thing;
    for(Size i = 0; i < sizeof(TestType); ++i)
    {
        l_thingAsBytes[i] = (Byte)rand();
    }

    g_NullStream >> l_thing;
    for(Size i = 0; i < sizeof(TestType); ++i)
    {
        CHECK(l_thingAsBytes[i] == 0);
    }
    
    //This really just needs to NOT crash and log something.
    g_NullStream << l_thing;

}
