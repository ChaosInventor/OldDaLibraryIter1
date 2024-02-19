#include <catch2/catch.hpp>

#include "../Memory.hpp"

using namespace Library;
using namespace Catch::Generators;

TEST_CASE("Memory permission checking", "[Memory][Immutable]")
{

    Byte* l_dummyLocation = (Byte*)0xdeadbeef;
    Size l_dummySize = 2693420;
    Byte l_permissions = GENERATE(range(0, 7));

    Memory l_mem(l_dummyLocation, l_dummySize, l_permissions);

    CHECK(MemoryIsReadable(l_mem) == (bool)((l_permissions & 1) == 1));
    CHECK(MemoryIsWritable(l_mem) == (bool)((l_permissions & 0b010) == 0b010));
    CHECK(MemoryIsExecutable(l_mem) == (bool)((l_permissions & 0b100) == 0b100));

}
