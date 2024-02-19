#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../DoublyLinkedCountedCachedList.hpp"
#include "../../../DoublyLinkedListNode.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked::Counted::Cached;
using namespace Library::DataStructures::Lists::DoublyLinked;
using namespace Catch::Generators;

TEST_CASE("Default constructor", "[List][DoublyLinked][Counted][Cached][Member]")
{

    ListCache<int> l_cache;

    CHECK(l_cache.m_Node == nullptr);
    CHECK(l_cache.m_NodeIndex == 0);

}

TEST_CASE("Index and node pointer constructor", "[List][DoublyLinked][Counted][Cached][Member]")
{

    Node<int> l_dummy1;
    Size l_index = GENERATE(range(0, 100));

    ListCache<int> l_cache(&l_dummy1, l_index);

    CHECK(l_cache.m_Node == &l_dummy1);
    CHECK(l_cache.m_NodeIndex == l_index);

}

TEST_CASE("Copying and moving", "[List][DoublyLinked][Counted][Cached][Member]")
{

    Node<int> l_dummy1;
    Size l_dummyIndex = 100;

    ListCache<int> l_from(&l_dummy1, l_dummyIndex);
    ListCache<int> l_to;

    SECTION("Copy constructor")
    {
        l_to = ListCache<int>(l_from);
    }
    SECTION("Copy operator")
    {
        l_to = l_from;
    }
    SECTION("Move constructor")
    {
        l_to = ListCache<int>((ListCache<int>&&)l_from);

        CHECK(l_from.m_Node == nullptr);
        CHECK(l_from.m_NodeIndex == 0);
    }
    SECTION("Move operator")
    {
        l_to = (ListCache<int>&&)l_from;

        CHECK(l_from.m_Node == nullptr);
        CHECK(l_from.m_NodeIndex == 0);
    }


    CHECK(l_to.m_Node == &l_dummy1);
    CHECK(l_to.m_NodeIndex == l_dummyIndex);

}

TEST_CASE("Comparison", "[List][DoublyLinked][Counted][Cached][Member]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;
    Size l_dummyIndex = GENERATE(range(1, 100));

    ListCache<int> l_cache(&l_dummy1, l_dummyIndex);
    ListCache<int> l_same(&l_dummy1, l_dummyIndex);
    ListCache<int> l_different1(&l_dummy2, l_dummyIndex * 2);
    ListCache<int> l_different2(&l_dummy1, l_dummyIndex * 2);
    ListCache<int> l_different3(&l_dummy2, l_dummyIndex);

    CHECK((l_cache == l_same));
    CHECK_FALSE((l_cache == l_different1));
    CHECK_FALSE((l_cache == l_different2));
    CHECK_FALSE((l_cache == l_different3));
    CHECK((l_cache == l_cache));

    CHECK_FALSE((l_cache != l_same));
    CHECK((l_cache != l_different1));
    CHECK((l_cache != l_different2));
    CHECK((l_cache != l_different3));
    CHECK_FALSE((l_cache != l_cache));

}
