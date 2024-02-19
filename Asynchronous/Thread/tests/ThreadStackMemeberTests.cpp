#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../include/Thread.hpp"

using namespace Library::Asynchronous;

TEST_CASE("Default constructor", "[Asynchronous][Thread][Stack][Member]")
{

    Stack l_stack;

    CHECK(l_stack.m_Address == nullptr);
    CHECK(l_stack.m_Size == 0);

}

TEST_CASE("Copying and moving", "[Asynchronous][Thread][Stack][Member]")
{

    void* l_dummyPointer = (void*)0xdeadbeef;
    Size l_dummySize = 0x1234567890;

    Stack l_from;
    Stack l_to;

    l_from.m_Address = l_dummyPointer;
    l_from.m_Size = l_dummySize;

    SECTION("Copying")
    {
        SECTION("Constructor")
        {
            l_to = Stack(l_from);
        }
        SECTION("Operator")
        {
            l_to = l_from;
        }
    }
    SECTION("Moving")
    {
        SECTION("Constructor")
        {
            l_to = Stack((Stack&&)l_from);
        }
        SECTION("Operator")
        {
            l_to = (Stack&&)l_from;
        }

        CHECK(l_from.m_Address == nullptr);
        CHECK(l_from.m_Size == 0);
    }

    CHECK(l_to.m_Address == l_dummyPointer);
    CHECK(l_to.m_Size == l_dummySize);

}

TEST_CASE("Paramater to member constructor", "[Asynchronous][Thread][Stack][Member]")
{

    void* l_dummyPointer = (void*)0xdeadbeef;
    Size l_dummySize = 0x1234567890;

    Stack l_stack(l_dummyPointer, l_dummySize);

    CHECK(l_stack.m_Address == l_dummyPointer);
    CHECK(l_stack.m_Size == l_dummySize);

}
