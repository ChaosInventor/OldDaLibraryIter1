#include <catch2/catch.hpp>

#include "../Node.hpp"

using namespace Library;
using namespace Library::DataStructures::Lists::SinglyLinked;
using namespace Catch::Generators;

TEST_CASE("Find node number of links after node, 0 links", "[Node][SinglyLinked][Immutable]")
{

    Node<int> l_node;

    Node<int>* l_result = FindNodeNumberOfLinksAfterNode(0, l_node);

    CHECK(l_result == &l_node);

}

TEST_CASE("Find node number of links after node, n links", "[Node][SinglyLinked][Immutable]")
{

    Size l_size = GENERATE(take(10, random(2, 100)));
    Size l_numOfLinks = GENERATE_COPY(range<Size>(1, l_size));

    Node<int>* l_firstNode;
    Node<int>* l_lastNode;

    CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAt(
        l_size,
        l_firstNode, l_lastNode
    );

    REQUIRE(l_firstNode != nullptr);
    REQUIRE(l_lastNode != nullptr);

    Node<int>* l_result = FindNodeNumberOfLinksAfterNode(l_numOfLinks, *l_firstNode);

    Node<int>* l_expected = l_firstNode;
    for(Size i = 0; i < l_numOfLinks; ++i)
    {
        l_expected = l_expected->m_NextNode;
    }
    CHECK(l_result == l_expected);

    DestroyNodeChainWithFirstNodeAtAndLastNodeAt(*l_firstNode, *l_lastNode);

}
