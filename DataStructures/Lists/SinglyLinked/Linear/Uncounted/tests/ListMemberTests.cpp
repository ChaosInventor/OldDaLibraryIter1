#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../List.hpp"

using namespace Library::DataStructures::Lists::SinglyLinked::Linear::Uncounted;
using namespace Library::DataStructures::Lists::SinglyLinked;
using namespace Library;
using namespace Catch::Generators;

TEST_CASE("Default constructor", "[LinkedList][SinglyLinked][Uncounted][Linear][Member]")
{

    List<int> l_list;

    CHECK(l_list.m_FirstNode == nullptr);
    CHECK(l_list.m_LastNode == nullptr);

}

TEST_CASE("Copying and moving", "[LinkedList][SinglyLinked][Uncounted][Linear][Member]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;

    List<int> l_to;
    List<int> l_from;

    l_from.m_FirstNode = &l_dummy1;
    l_from.m_LastNode = &l_dummy2;

    SECTION("Copying")
    {
        SECTION("Constructor")
        {
            l_to = List<int>(l_from);
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
            l_to = List<int>((List<int>&&)l_from);
        }
        SECTION("Operator")
        {
            l_to = (List<int>&&)l_from;
        }

        CHECK(l_from.m_FirstNode == nullptr);
        CHECK(l_from.m_LastNode == nullptr);
    }

    CHECK(l_to.m_FirstNode == &l_dummy1);
    CHECK(l_to.m_LastNode == &l_dummy2);

}

TEST_CASE("First and last node constructor", "[LinkedList][SinglyLinked][Uncounted][Linear][Member]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;

    List<int> l_list(&l_dummy1, &l_dummy2);    

    CHECK(l_list.m_FirstNode == &l_dummy1);
    CHECK(l_list.m_LastNode == &l_dummy2);

}

TEST_CASE("Comparison", "[LinkedList][SinglyLinked][Uncounted][Linear][Member]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;

    List<int> l_list(&l_dummy1, &l_dummy2);
    List<int> l_same(&l_dummy1, &l_dummy2);
    List<int> l_different(&l_dummy2, &l_dummy1);
    List<int> l_null;

    CHECK((l_list == l_same));
    CHECK_FALSE((l_list == l_different));
    CHECK_FALSE((l_list == l_null));
    CHECK((l_list == l_list));

    CHECK_FALSE((l_list != l_same));
    CHECK((l_list != l_different));
    CHECK((l_list != l_null));
    CHECK_FALSE((l_list != l_list));

}

TEST_CASE("Indexing", "[LinkedList][SinglyLinked][Uncounted][Linear][Member]")
{

    Size l_sizeOfList = GENERATE(take(10, random(1, 100)));
    Size l_index = GENERATE_COPY(range<Size>(0, l_sizeOfList));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Node<int>* l_result = l_list[l_index];

    CHECK(l_result == FindNodeAtIndexNoErrorCheckFromList(l_index, l_list));

    DestroyList(l_list);

}
