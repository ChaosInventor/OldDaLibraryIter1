#include <catch2/catch.hpp>

#include "../DoublyLinkedListNode.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked;

TEST_CASE("Null chain and cyclic chain", "[Immutable][DoublyLinkedListNode]")
{

    Node<int> l_nullChain1;
    Node<int> l_nullChain2;
    Node<int> l_nullChain3;
    Node<int> l_nullChain4;
    Node<int> l_nullChain5;

    l_nullChain1.m_PreviousNode = nullptr;

    l_nullChain1.m_NextNode = &l_nullChain2;
    l_nullChain2.m_PreviousNode = &l_nullChain1;

    l_nullChain2.m_NextNode = &l_nullChain3;
    l_nullChain3.m_PreviousNode = &l_nullChain2;

    l_nullChain3.m_Item = 0xdad;

    l_nullChain3.m_NextNode = &l_nullChain4;
    l_nullChain4.m_PreviousNode = &l_nullChain3;

    l_nullChain4.m_NextNode = &l_nullChain5;
    l_nullChain5.m_PreviousNode = &l_nullChain4;

    l_nullChain5.m_NextNode = nullptr;


    Node<int> l_cyclicChain1;
    Node<int> l_cyclicChain2;
    Node<int> l_cyclicChain3;
    Node<int> l_cyclicChain4;
    Node<int> l_cyclicChain5;

    l_cyclicChain1.m_PreviousNode = &l_cyclicChain5;

    l_cyclicChain1.m_NextNode = &l_cyclicChain2;
    l_cyclicChain2.m_PreviousNode = &l_cyclicChain1;

    l_cyclicChain2.m_NextNode = &l_cyclicChain3;
    l_cyclicChain3.m_PreviousNode = &l_cyclicChain2;

    l_cyclicChain3.m_Item = 0xdad;

    l_cyclicChain3.m_NextNode = &l_cyclicChain4;
    l_cyclicChain4.m_PreviousNode = &l_cyclicChain3;

    l_cyclicChain4.m_NextNode = &l_cyclicChain5;
    l_cyclicChain5.m_PreviousNode = &l_cyclicChain4;

    l_cyclicChain5.m_NextNode = &l_cyclicChain1;

    SECTION("Distance")
    {
        CHECK(CountDistanceFromNodeToNode<int>(l_nullChain1, nullptr) == 5);
        CHECK(CountDistanceFromNodeToNode<int>(l_nullChain1, &l_nullChain2) == 1);
        CHECK(CountDistanceFromNodeToNode<int>(l_nullChain1, &l_nullChain3) == 2);
        CHECK(CountDistanceFromNodeToNode<int>(l_nullChain1, &l_nullChain4) == 3);
        CHECK(CountDistanceFromNodeToNode<int>(l_nullChain1, &l_nullChain5) == 4);

        CHECK(CountDistanceFromNodeToNode<int>(l_cyclicChain1, &l_cyclicChain1) == 5);
        CHECK(CountDistanceFromNodeToNode<int>(l_cyclicChain1, &l_cyclicChain2) == 1);
        CHECK(CountDistanceFromNodeToNode<int>(l_cyclicChain1, &l_cyclicChain3) == 2);
        CHECK(CountDistanceFromNodeToNode<int>(l_cyclicChain1, &l_cyclicChain4) == 3);
        CHECK(CountDistanceFromNodeToNode<int>(l_cyclicChain1, &l_cyclicChain5) == 4);


        CHECK(CountDistanceFromNodeToNodeBackwards<int>(l_nullChain5, nullptr) == 5);
        CHECK(CountDistanceFromNodeToNodeBackwards<int>(l_nullChain2, &l_nullChain1) == 1);
        CHECK(CountDistanceFromNodeToNodeBackwards<int>(l_nullChain3, &l_nullChain1) == 2);
        CHECK(CountDistanceFromNodeToNodeBackwards<int>(l_nullChain4, &l_nullChain1) == 3);
        CHECK(CountDistanceFromNodeToNodeBackwards<int>(l_nullChain5, &l_nullChain1) == 4);

        CHECK(CountDistanceFromNodeToNodeBackwards<int>(l_cyclicChain1, &l_cyclicChain1) == 5);
        CHECK(CountDistanceFromNodeToNodeBackwards<int>(l_cyclicChain2, &l_cyclicChain1) == 1);
        CHECK(CountDistanceFromNodeToNodeBackwards<int>(l_cyclicChain3, &l_cyclicChain1) == 2);
        CHECK(CountDistanceFromNodeToNodeBackwards<int>(l_cyclicChain4, &l_cyclicChain1) == 3);
        CHECK(CountDistanceFromNodeToNodeBackwards<int>(l_cyclicChain5, &l_cyclicChain1) == 4);
    }
    SECTION("Find first with item")
    {
        CHECK(FindFirstNodeWithItemBetweenNodeAndNode<int>(0xdad, l_nullChain1, nullptr) == &l_nullChain3);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNode<int>(0xdad, l_nullChain1, &l_nullChain2) == nullptr);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNode<int>(0xdad, l_nullChain1, &l_nullChain3) == nullptr);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNode<int>(0xdad, l_nullChain1, &l_nullChain4) == &l_nullChain3);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNode<int>(0xdad, l_nullChain1, &l_nullChain5) == &l_nullChain3);

        CHECK(FindFirstNodeWithItemBetweenNodeAndNode<int>(0xdad, l_cyclicChain1, &l_cyclicChain1) == &l_cyclicChain3);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNode<int>(0xdad, l_cyclicChain1, &l_cyclicChain2) == nullptr);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNode<int>(0xdad, l_cyclicChain1, &l_cyclicChain3) == nullptr);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNode<int>(0xdad, l_cyclicChain1, &l_cyclicChain4) == &l_cyclicChain3);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNode<int>(0xdad, l_cyclicChain1, &l_cyclicChain5) == &l_cyclicChain3);


        CHECK(FindFirstNodeWithItemBetweenNodeAndNodeBackwards<int>(0xdad, l_nullChain5, nullptr) == &l_nullChain3);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNodeBackwards<int>(0xdad, l_nullChain2, &l_nullChain1) == nullptr);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNodeBackwards<int>(0xdad, l_nullChain3, &l_nullChain1) == nullptr);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNodeBackwards<int>(0xdad, l_nullChain4, &l_nullChain1) == &l_nullChain3);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNodeBackwards<int>(0xdad, l_nullChain5, &l_nullChain1) == &l_nullChain3);

        CHECK(FindFirstNodeWithItemBetweenNodeAndNodeBackwards<int>(0xdad, l_cyclicChain1, &l_cyclicChain1) == &l_cyclicChain3);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNodeBackwards<int>(0xdad, l_cyclicChain2, &l_cyclicChain1) == nullptr);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNodeBackwards<int>(0xdad, l_cyclicChain3, &l_cyclicChain1) == nullptr);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNodeBackwards<int>(0xdad, l_cyclicChain4, &l_cyclicChain1) == &l_cyclicChain3);
        CHECK(FindFirstNodeWithItemBetweenNodeAndNodeBackwards<int>(0xdad, l_cyclicChain5, &l_cyclicChain1) == &l_cyclicChain3);
    }
    SECTION("Find after number of steps")
    {

        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_nullChain1) == &l_nullChain2);
        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_nullChain2) == &l_nullChain3);
        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_nullChain3) == &l_nullChain4);
        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_nullChain4) == &l_nullChain5);
        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_nullChain5) == nullptr);

        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_nullChain1) == &l_nullChain2);
        CHECK(FindNodeNumberOfStepsForwardFromNode(2, l_nullChain1) == &l_nullChain3);
        CHECK(FindNodeNumberOfStepsForwardFromNode(3, l_nullChain1) == &l_nullChain4);
        CHECK(FindNodeNumberOfStepsForwardFromNode(4, l_nullChain1) == &l_nullChain5);
        CHECK(FindNodeNumberOfStepsForwardFromNode(5, l_nullChain1) == nullptr);

        CHECK(FindNodeNumberOfStepsForwardFromNode(0, l_nullChain1) == &l_nullChain1);
        CHECK(FindNodeNumberOfStepsForwardFromNode(0, l_nullChain2) == &l_nullChain2);
        CHECK(FindNodeNumberOfStepsForwardFromNode(0, l_nullChain3) == &l_nullChain3);
        CHECK(FindNodeNumberOfStepsForwardFromNode(0, l_nullChain4) == &l_nullChain4);
        CHECK(FindNodeNumberOfStepsForwardFromNode(0, l_nullChain5) == &l_nullChain5);


        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_nullChain5) == &l_nullChain4);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_nullChain4) == &l_nullChain3);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_nullChain3) == &l_nullChain2);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_nullChain2) == &l_nullChain1);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_nullChain1) == nullptr);

        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_nullChain5) == &l_nullChain4);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(2, l_nullChain5) == &l_nullChain3);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(3, l_nullChain5) == &l_nullChain2);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(4, l_nullChain5) == &l_nullChain1);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(5, l_nullChain5) == nullptr);

        CHECK(FindNodeNumberOfStepsBackwardFromNode(0, l_nullChain1) == &l_nullChain1);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(0, l_nullChain2) == &l_nullChain2);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(0, l_nullChain3) == &l_nullChain3);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(0, l_nullChain4) == &l_nullChain4);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(0, l_nullChain5) == &l_nullChain5);



        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_cyclicChain1) == &l_cyclicChain2);
        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_cyclicChain2) == &l_cyclicChain3);
        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_cyclicChain3) == &l_cyclicChain4);
        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_cyclicChain4) == &l_cyclicChain5);
        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_cyclicChain5) == &l_cyclicChain1);

        CHECK(FindNodeNumberOfStepsForwardFromNode(1, l_cyclicChain1) == &l_cyclicChain2);
        CHECK(FindNodeNumberOfStepsForwardFromNode(2, l_cyclicChain1) == &l_cyclicChain3);
        CHECK(FindNodeNumberOfStepsForwardFromNode(3, l_cyclicChain1) == &l_cyclicChain4);
        CHECK(FindNodeNumberOfStepsForwardFromNode(4, l_cyclicChain1) == &l_cyclicChain5);
        CHECK(FindNodeNumberOfStepsForwardFromNode(5, l_cyclicChain1) == &l_cyclicChain1);

        CHECK(FindNodeNumberOfStepsForwardFromNode(0, l_cyclicChain1) == &l_cyclicChain1);
        CHECK(FindNodeNumberOfStepsForwardFromNode(0, l_cyclicChain2) == &l_cyclicChain2);
        CHECK(FindNodeNumberOfStepsForwardFromNode(0, l_cyclicChain3) == &l_cyclicChain3);
        CHECK(FindNodeNumberOfStepsForwardFromNode(0, l_cyclicChain4) == &l_cyclicChain4);
        CHECK(FindNodeNumberOfStepsForwardFromNode(0, l_cyclicChain5) == &l_cyclicChain5);


        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_cyclicChain5) == &l_cyclicChain4);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_cyclicChain4) == &l_cyclicChain3);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_cyclicChain3) == &l_cyclicChain2);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_cyclicChain2) == &l_cyclicChain1);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_cyclicChain1) == &l_cyclicChain5);

        CHECK(FindNodeNumberOfStepsBackwardFromNode(1, l_cyclicChain5) == &l_cyclicChain4);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(2, l_cyclicChain5) == &l_cyclicChain3);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(3, l_cyclicChain5) == &l_cyclicChain2);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(4, l_cyclicChain5) == &l_cyclicChain1);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(5, l_cyclicChain5) == &l_cyclicChain5);

        CHECK(FindNodeNumberOfStepsBackwardFromNode(0, l_cyclicChain1) == &l_cyclicChain1);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(0, l_cyclicChain2) == &l_cyclicChain2);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(0, l_cyclicChain3) == &l_cyclicChain3);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(0, l_cyclicChain4) == &l_cyclicChain4);
        CHECK(FindNodeNumberOfStepsBackwardFromNode(0, l_cyclicChain5) == &l_cyclicChain5);


    }

}
