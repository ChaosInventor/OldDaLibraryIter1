#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../DoublyLinkedListNode.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked;
using namespace Catch::Generators;

TEST_CASE("Default constructor", "[Member][DoublyLinkedListNode]")
{

    Node<int> l_node;

    CHECK(l_node.m_PreviousNode == nullptr);
    CHECK(l_node.m_NextNode == nullptr);
    CHECK(l_node.m_Item == int());

}

TEST_CASE("Construction from pointers", "[Member][DoublyLinkedListNode]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;

    Node<int> l_node;

    SECTION("Just pointers")
    {
        l_node = Node<int>(&l_dummy1, &l_dummy2);

        CHECK(l_node.m_Item == int());
    }
    SECTION("Pointers and item")
    {
        l_node = Node<int>(&l_dummy1, &l_dummy2, 0xBeef);

        CHECK(l_node.m_Item == 0xBeef);
    }

    CHECK(l_node.m_PreviousNode == &l_dummy1);
    CHECK(l_node.m_NextNode == &l_dummy2);

}

TEST_CASE("Construction from item", "[Member][DoublyLinkedListNode]")
{

    int l_int = GENERATE(range(10, 50));

    Node<int>l_node(l_int);

    CHECK(l_node.m_PreviousNode == nullptr);
    CHECK(l_node.m_NextNode == nullptr);
    CHECK(l_node.m_Item == l_int);

}

TEST_CASE("Copy and move", "[Member][DoublyLinkedListNode]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;

    Node<int> l_from(&l_dummy1, &l_dummy2, 0x42069);

    Node<int> l_to;

    SECTION("Copy constructor")
    {
        l_to = Node<int>(l_from);
    }
    SECTION("Move constructor")
    {
        l_to = Node<int>((Node<int>&&)l_from);

        CHECK(l_from.m_PreviousNode == nullptr);
        CHECK(l_from.m_NextNode == nullptr);
        CHECK(l_from.m_Item == int());
    }

    SECTION("Copy operator")
    {
        Node<int>& l_returnValue = (l_to = l_from);

        CHECK(&l_returnValue == &l_to);
    }
    SECTION("Move operator")
    {
        Node<int>& l_returnValue = (l_to = (Node<int>&&)l_from);

        CHECK(&l_returnValue == &l_to);

        CHECK(l_from.m_PreviousNode == nullptr);
        CHECK(l_from.m_NextNode == nullptr);
        CHECK(l_from.m_Item == int());
    }


    CHECK(l_to.m_PreviousNode == &l_dummy1);
    CHECK(l_to.m_NextNode == &l_dummy2);
    CHECK(l_to.m_Item == 0x42069);

}

TEST_CASE("Convertsion to item", "[Member][DoublyLinkedListNode]")
{

    int l_int = GENERATE(range(10, 50));

    Node<int>l_node(l_int);

    int l_result = l_node;

    CHECK(l_result == l_int);

}

TEST_CASE("Comparison", "[Member][DoublyLinkedListNode]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;

    Node<int> l_node(&l_dummy1, &l_dummy2, 889429582);
    Node<int> l_same(&l_dummy1, &l_dummy2, 889429582);
    Node<int> l_different(&l_dummy2, &l_dummy1, 666);

    CHECK((l_node == l_same));
    CHECK_FALSE((l_node == l_different));
    CHECK((l_node == l_node));

    CHECK_FALSE((l_node != l_same));
    CHECK((l_node != l_different));
    CHECK_FALSE((l_node != l_node));

}

