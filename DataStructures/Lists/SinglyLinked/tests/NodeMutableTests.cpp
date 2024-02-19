#include <catch2/catch.hpp>

#include "../Node.hpp"
#include "../../../../Debugging/Debugging.hpp"

using namespace Library;
using namespace Library::DataStructures::Lists::SinglyLinked;
using namespace Catch::Generators;
using namespace Debugging;

TEST_CASE("Insert node", "[Node][SinglyLinked][Mutable]")
{

    Node<int> l_node1;
    Node<int> l_node2;
    
    Node<int>* l_dummyPointer = (Node<int>*)GENERATE(take(10, random<intptr_t>(INTPTR_MIN, INTPTR_MAX)));

    l_node1.m_NextNode = l_dummyPointer;

    InsertNodeAfterNode(l_node2, l_node1);

    CHECK(l_node1.m_NextNode == &l_node2);
    CHECK(l_node2.m_NextNode == l_dummyPointer);

}

TEST_CASE("Add item, normal", "[Node][SinglyLinked][Mutable]")
{

    int l_item = GENERATE(take(10, random(INT_MIN, INT_MAX)));

    Node<int> l_node;
    
    Node<int>* l_dummyPointer = (Node<int>*)GENERATE(take(10, random<intptr_t>(INTPTR_MIN, INTPTR_MAX)));

    l_node.m_NextNode = l_dummyPointer;

    SECTION("Defaults")
    {
        AddItemAfterNode(l_item, l_node);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        AddItemAfterNodeUsingAllocator(
            l_item,
            l_node,
            malloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }
    REQUIRE(l_node.m_NextNode != nullptr);

    REQUIRE(l_node.m_NextNode->m_NextNode == l_dummyPointer);
    REQUIRE(l_node.m_NextNode->m_Item == l_item);

    free(l_node.m_NextNode);

}

TEST_CASE("Add item, alloc error", "[Node][SinglyLinked][Mutable]")
{

    Node<int> l_node;
    
    Node<int>* l_dummyPointer = (Node<int>*)GENERATE(take(10, random<intptr_t>(INTPTR_MIN, INTPTR_MAX)));

    l_node.m_NextNode = l_dummyPointer;    

    bool l_called = false;
    AddItemAfterNodeUsingAllocator(
        0, l_node,
        NullMalloc, GeneralErrorCallback, &l_called
    );
    CHECK(l_called == true);

    CHECK(l_node.m_NextNode == l_dummyPointer);

}

TEST_CASE("Extract node", "[Node][SinglyLinked][Mutable]")
{

    Node<int> l_node1;
    Node<int> l_node2;
    
    Node<int>* l_dummyPointer = (Node<int>*)GENERATE(take(10, random<intptr_t>(INTPTR_MIN, INTPTR_MAX)));

    l_node1.m_NextNode = &l_node2;
    l_node2.m_NextNode = l_dummyPointer;

    Node<int>* l_returnValue = ExtractNodeAfterNode(l_node1);

    CHECK(l_returnValue == &l_node2);

    CHECK(l_node1.m_NextNode == l_dummyPointer);

}

TEST_CASE("Remove node", "[Node][SinglyLinked][Mutable]")
{

    Node<int> l_node1;
    Node<int>* l_node2 = (Node<int>*)malloc(sizeof(Node<int>));
    REQUIRE(l_node2 != nullptr);

    Node<int>* l_dummyPointer = (Node<int>*)GENERATE(take(10, random<intptr_t>(INTPTR_MIN, INTPTR_MAX)));

    l_node1.m_NextNode = l_node2;
    l_node2->m_NextNode = l_dummyPointer;

    SECTION("Defaults")
    {
        RemoveNodeAfterNode(l_node1);
    }
    SECTION("Customs")
    {
        RemoveNodeAfterNodeUsingDeallocator(l_node1, free);
    }

    CHECK(l_node1.m_NextNode == l_dummyPointer);

}
