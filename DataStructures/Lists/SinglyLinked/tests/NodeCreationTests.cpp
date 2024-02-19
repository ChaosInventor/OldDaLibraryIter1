#include <catch2/catch.hpp>

#include "../Node.hpp"
#include "../../../../Debugging/Debugging.hpp"

using namespace Library;
using namespace Library::DataStructures::Lists::SinglyLinked;
using namespace Debugging;
using namespace Catch::Generators;

TEST_CASE("Node chain creation normal", "[Node][SinglyLinked][Creation]")
{

    Size l_requiredSizeOfChain = GENERATE(take<Size>(10, random<Size>(2, 1000)));

    Node<int>* l_firstNode = nullptr;
    Node<int>* l_lastNode = nullptr;

    Size l_returnValue;
    SECTION("Defaults")
    {
        l_returnValue =
        CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAt(
            l_requiredSizeOfChain,
            l_firstNode, l_lastNode
        );
    }
    SECTION("Customs")
    {
        bool l_called = false;
        l_returnValue =
        CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAtUsingAllocator(
            l_requiredSizeOfChain,
            l_firstNode, l_lastNode,
            malloc, GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    REQUIRE(l_returnValue == l_requiredSizeOfChain);
    
    REQUIRE(l_firstNode != nullptr);
    REQUIRE(l_lastNode != nullptr);
    REQUIRE(l_firstNode != l_lastNode);

    //This is done so that the loop bellow can function properly
    l_lastNode->m_NextNode = nullptr;

    Size l_numberOfNodes = 0;
    Node<int>* l_curNode = l_firstNode;
    while (l_curNode != nullptr)
    {
        ++l_numberOfNodes;

        l_curNode = l_curNode->m_NextNode;
    }

    CHECK(l_numberOfNodes == l_requiredSizeOfChain);    

    DestroyNodeChainWithFirstNodeAtAndLastNodeAt(*l_firstNode, *l_lastNode);

}

TEST_CASE("Node chain creation size 1", "[Node][SinglyLinked][Creation]")
{

    Node<int>* l_firstNode = nullptr;
    Node<int>* l_lastNode = nullptr;

    Size l_returnValue;
    SECTION("Defaults")
    {
        l_returnValue =
        CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAt(
            1,
            l_firstNode, l_lastNode
        );
    }
    SECTION("Customs")
    {
        bool l_called = false;

        SetCountOfNullMallocAfterCount(1);
        l_returnValue =
        CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAtUsingAllocator(
            1,
            l_firstNode, l_lastNode,
            NullMallocAfterCount, &GeneralErrorCallback, &l_called
        );
        
        CHECK(l_called == false);
    }

    CHECK(l_firstNode != nullptr);
    CHECK(l_lastNode != nullptr);

    CHECK(l_firstNode == l_lastNode);
    CHECK(l_returnValue == 1);

    DestroyNodeChainWithFirstNodeAtAndLastNodeAt(*l_firstNode, *l_lastNode);

}

TEST_CASE("Node chain creation size 0", "[Node][SinglyLinked][Creation]")
{

    Node<int>* l_firstNode = (Node<int>*)0xbeefdead;
    Node<int>* l_lastNode = (Node<int>*)0xdeadbeef;

    Size l_returnValue;
    SECTION("Defaults")
    {
        l_returnValue =
        CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAt(
            0,
            l_firstNode, l_lastNode
        );
    }
    SECTION("Customs")
    {
        bool l_called = false;
        l_returnValue =
        CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAtUsingAllocator(
            0,
            l_firstNode, l_lastNode,
            NullMalloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    CHECK(l_firstNode == nullptr);
    CHECK(l_lastNode == nullptr);
    CHECK(l_returnValue == 0);

}

TEST_CASE("Node chain creation allocation failure full", "[Node][SinglyLinked][Creation]")
{

    Size l_requiredSizeOfChain = GENERATE((Size)1, take<Size>(10, random<Size>(1, 1000)));

    Node<int>* l_firstNode = (Node<int>*)0xbeefdead;
    Node<int>* l_lastNode = (Node<int>*)0xdeadbeef;

    bool l_called = false;
    Size l_returnValue = 
    CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAtUsingAllocator(
        l_requiredSizeOfChain,
        l_firstNode, l_lastNode,
        NullMalloc, &GeneralErrorCallback, &l_called
    );
    REQUIRE(l_called == true);

    CHECK(l_firstNode == nullptr);
    CHECK(l_lastNode == nullptr);
    CHECK(l_returnValue == 0);

}

TEST_CASE("Node chain creation allocation failure partial", "[Node][SinglyLinked][Creation]")
{

    Size l_requiredSizeOfChain = GENERATE(take<Size>(10, random<Size>(10, 1000)));
    Size l_allocationFailureAfter = l_requiredSizeOfChain / 2;

    Node<int>* l_firstNode = nullptr;
    Node<int>* l_lastNode = nullptr;

    bool l_called = false;

    SetCountOfNullMallocAfterCount(l_allocationFailureAfter);
    Size l_returnValue = 
    CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAtUsingAllocator(
        l_requiredSizeOfChain,
        l_firstNode, l_lastNode,
        NullMallocAfterCount, &GeneralErrorCallback, &l_called
    );
    
    REQUIRE(l_called == true);

    REQUIRE(l_firstNode != nullptr);
    REQUIRE(l_lastNode != nullptr);
    REQUIRE(l_firstNode != l_lastNode);
    REQUIRE(l_returnValue == l_allocationFailureAfter);

    //This is required so that the bellow loop works.
    l_lastNode->m_NextNode = nullptr;

    Size l_numberOfNodes = 0;
    Node<int>* l_curNode = l_firstNode;
    while (l_curNode != nullptr)
    {
        ++l_numberOfNodes;

        l_curNode = l_curNode->m_NextNode;
    }

    CHECK(l_numberOfNodes == l_allocationFailureAfter);

    DestroyNodeChainWithFirstNodeAtAndLastNodeAt(*l_firstNode, *l_lastNode);

}
