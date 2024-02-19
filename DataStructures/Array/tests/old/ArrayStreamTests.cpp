#include <catch2/catch.hpp>

#include "../Array.hpp"

using namespace Library;
using namespace Library::DataStructures::Array;
using namespace Library::IO;


TEST_CASE("Array stream tests", "[Array][IO]")
{

    Size l_capacity = GENERATE(Catch::Generators::range<Size>(0, 10));
    Size l_size = GENERATE_COPY(Catch::Generators::range<Size>(0, 10));
    if(l_size > l_capacity)
    {
        l_size = l_capacity;
    }

    Array<int> l_array;

    CAPTURE(l_capacity, l_size);
    CreateArrayAtOfCapacity(l_array, l_capacity);
    REQUIRE(l_array.m_Capacity == l_capacity);

    for(Size i = 0; i < l_size; ++i)
    {
        l_array[i] = (int)i;
    }
    l_array.m_Size = l_size;

    CAPTURE(l_array);

    void* l_oldBuffer = l_array.m_Buffer;
    g_NullStream << l_array;

    REQUIRE(l_array.m_Buffer == l_oldBuffer);
    REQUIRE(l_array.m_Capacity == l_capacity);
    REQUIRE(l_array.m_Size == 0);

    CAPTURE(l_array);
    g_NullStream >> l_array;
    REQUIRE(l_array.m_Buffer == l_oldBuffer);
    REQUIRE(l_array.m_Capacity == l_capacity);
    REQUIRE(l_array.m_Size == l_capacity);

    CAPTURE(l_array);
    for(Size i = 0; i < l_capacity; ++i)
    {
        CHECK(l_array[i] == 0);
    }

    DestoryArray(l_array);

}
