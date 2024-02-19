#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../Node.hpp"

using namespace Library::DataStructures::Lists::SinglyLinked;
using namespace Catch::Generators;

TEST_CASE("Default construction", "[Node][SinglyLinked][Member]")
{

    Node<int> l_node;

    CHECK(l_node.m_NextNode == nullptr);
    CHECK(l_node.m_Item == int());

}

TEST_CASE("Copying and moving", "[Node][SinglyLinked][Member]")
{

    Node<int> l_dummyNode;
    int l_dummyItem = GENERATE(take(10, random(0, INT32_MAX)));

    Node<int> l_node;
    Node<int> l_to;

    l_node.m_NextNode = &l_dummyNode;    
    l_node.m_Item = l_dummyItem;

    SECTION("Copying")
    {
        SECTION("Constructor")
        {
            l_to = Node<int>(l_node);
        }
        SECTION("Operator")
        {
            l_to = l_node;
        }
    }
    SECTION("Moving")
    {
        SECTION("Constructor")
        {
            l_to = Node<int>((Node<int>&&)l_node);
        }
        SECTION("Operator")
        {
            l_to = (Node<int>&&)l_node;
        }

        CHECK(l_node.m_NextNode == nullptr);
        CHECK(l_node.m_Item == int());
    }

    CHECK(l_to.m_NextNode == &l_dummyNode);
    CHECK(l_to.m_Item == l_dummyItem);

}

TEST_CASE("Member construction", "[Node][SinglyLinked][Member]")
{

    Node<int> l_dummyNode;
    int l_dummyItem = GENERATE(take(10, random(0, INT32_MAX)));

    Node<int>* l_expectedNode;
    int l_expectedItem;

    Node<int> l_node;

    SECTION("Item only")
    {
        l_node = Node<int>(l_dummyItem);

        l_expectedNode = nullptr;
        l_expectedItem = l_dummyItem;
    }
    SECTION("Next node only")
    {
        l_node = Node<int>(&l_dummyNode);

        l_expectedNode = &l_dummyNode;
        l_expectedItem = int();
    }
    SECTION("Next node and item")
    {
        l_node = Node<int>(&l_dummyNode, l_dummyItem);

        l_expectedNode = &l_dummyNode;
        l_expectedItem = l_dummyItem;
    }

    CHECK(l_node.m_NextNode == l_expectedNode);
    CHECK(l_node.m_Item == l_expectedItem);

}

TEST_CASE("Member conversion", "[Node][SinglyLinked][Member]")
{

    Node<int> l_dummyNode;
    int l_dummyItem = GENERATE(take(10, random(0, INT32_MAX)));

    Node<int> l_node(&l_dummyNode, l_dummyItem);

    Node<int>* l_resultNode = l_node;
    int l_resultItem = l_node;

    CHECK(l_resultNode == &l_dummyNode);
    CHECK(l_resultItem == l_dummyItem);

}

TEST_CASE("Comparison", "[Node][SinglyLinked][Member]")
{

    Node<int> l_dummyNode;
    int l_dummyItem = GENERATE(take(10, random(0, INT32_MAX)));

    Node<int> l_node(&l_dummyNode, l_dummyItem);
    Node<int> l_same(&l_dummyNode, l_dummyItem);
    Node<int> l_different(l_dummyItem * 13);

    CHECK(l_node == l_same);
    CHECK_FALSE(l_node == l_different);
    CHECK(l_node == l_node);

    CHECK_FALSE(l_node != l_same);
    CHECK(l_node != l_different);
    CHECK_FALSE(l_node != l_node);

}
