#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../Queue.hpp"

using namespace Library::DataStructures::Queue;
using namespace Library::DataStructures::Array;

TEST_CASE("Default constructor", "[Queue][Member]")
{

    Queue<int> l_queue;

    CHECK(l_queue.m_Buffer == Array<int>());
    CHECK(l_queue.m_LastItem == 0);

}

TEST_CASE("Copying and moving", "[Queue][Member]")
{

    int l_dummy;
    Queue<int> l_from({&l_dummy, 10, 32});
    
    Queue<int> l_to;

    SECTION("Copy constructor")
    {
        l_to = Queue<int>(l_from);
    }
    SECTION("Copy operator")
    {
        l_to = l_from;
    }

    SECTION("Move constructor")
    {
        l_to = Queue<int>((Queue<int>&&)l_from);

        CHECK(l_from.m_Buffer == Array<int>());
        CHECK(l_from.m_LastItem == 0);
    }
    SECTION("Move operator")
    {
        l_to = (Queue<int>&&)l_from;

        CHECK(l_from.m_Buffer == Array<int>());
        CHECK(l_from.m_LastItem == 0);
    }

    CHECK(l_to.m_Buffer.m_Buffer == &l_dummy);
    CHECK(l_to.m_Buffer.m_Size == 10);
    CHECK(l_to.m_Buffer.m_Capacity == 32);

}
