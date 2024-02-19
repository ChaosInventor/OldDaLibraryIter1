#include <catch2/catch.hpp>

#include "../DoublyLinkedListNode.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked;

TEST_CASE("Insertion of nodes", "[DoublyLinkedListNode][Mutable]")
{

    Node<int> l_node1;
    Node<int> l_node2;

    Node<int>* l_originalPrev = l_node1.m_PreviousNode;
    Node<int>* l_originalNext = l_node1.m_NextNode;


    //The insertsions need to happen in the section as to not cause problems
    //with the second test where l_dummy1 will be destroyed before it is checked
    //and used.
    SECTION("No next node")
    {
        InsertNodeAfterNode(l_node2, l_node1);
    }
    SECTION("With next node")
    {
        Node<int> l_dummy1;

        l_node1.m_NextNode = &l_dummy1;
        l_originalNext = l_node1.m_NextNode;

        InsertNodeAfterNode(l_node2, l_node1);

        CHECK(l_dummy1.m_PreviousNode == &l_node2);
        CHECK(l_dummy1.m_NextNode == nullptr);
    }

    CHECK(l_node1.m_NextNode == &l_node2);
    CHECK(l_node1.m_PreviousNode == l_originalPrev);

    CHECK(l_node2.m_NextNode == l_originalNext);
    CHECK(l_node2.m_PreviousNode == &l_node1);

}

TEST_CASE("Poping of nodes", "[DoublyLinkedListNode][Mutable]")
{

    Node<int> l_node;

    SECTION("Null next node")
    {
        //The default constructor makes the next node null.
        Node<int>* l_returnValue = PopNodesNextNode(l_node);

        CHECK(l_returnValue == nullptr);
    }

    SECTION("With next node")
    {
        Node<int> l_dummy1;

        l_node.m_NextNode = &l_dummy1;
        l_dummy1.m_PreviousNode = &l_node;
    
        SECTION("Null next next node")
        {
            Node<int>* l_returnValue = PopNodesNextNode(l_node);

            CHECK(l_returnValue == &l_dummy1);
            CHECK(l_dummy1.m_NextNode == nullptr);
            CHECK(l_dummy1.m_PreviousNode == &l_node);

            CHECK(l_node.m_NextNode == nullptr);
            CHECK(l_node.m_PreviousNode == nullptr);
        }
        SECTION("With next next node")
        {
            Node<int> l_dummy2;

            l_dummy1.m_NextNode = &l_dummy2;
            l_dummy2.m_PreviousNode = &l_dummy1;

            Node<int>* l_returnValue = PopNodesNextNode(l_node);

            CHECK(l_returnValue == &l_dummy1);
            CHECK(l_dummy1.m_NextNode == &l_dummy2);
            CHECK(l_dummy1.m_PreviousNode == &l_node);

            CHECK(l_node.m_NextNode == &l_dummy2);
            CHECK(l_node.m_PreviousNode == nullptr);

            CHECK(l_dummy2.m_NextNode == nullptr);
            CHECK(l_dummy2.m_PreviousNode == &l_node);
        }
    }

}


