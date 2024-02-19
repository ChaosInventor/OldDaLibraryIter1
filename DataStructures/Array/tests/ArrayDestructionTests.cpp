#include <catch2/catch.hpp>

#include "../Array.hpp"
#include "../../../Debugging/Debugging.hpp"

using namespace Library;
using namespace Library::DataStructures::Array;
using namespace Debugging;

TEST_CASE("Destroy array test", "[Array][Destruction]")
{

    Size l_capacity = GENERATE(range(1, 100));

    Array<int> l_array;
    SECTION("Defaults")
    {
        CreateArrayAtOfCapacity(l_array, l_capacity);
        REQUIRE(l_array.m_Capacity == l_capacity);

        DestoryArray(l_array);
    }
    SECTION("Customs")
    {
        CreateArrayAtOfCapacityUsingAllocator(l_array, l_capacity, malloc, nullptr, nullptr);
    
        //Error check to make sure that allocation went well.
        REQUIRE(l_array.m_Capacity == l_capacity);


        DestroyArrayUsingDeallocator(l_array, free);
    }

    CHECK(l_array.m_Buffer == nullptr);
    CHECK(l_array.m_Size == 0);
    CHECK(l_array.m_Capacity == 0);

}
