#include <catch2/catch.hpp>

#include "../List.hpp"

using namespace Library::DataStructures::Lists::SinglyLinked::Linear::Uncounted;
using namespace Library::DataStructures::Lists::SinglyLinked;
using namespace Library;

TEST_CASE("Find node at index", "[LinkedList][SinglyLinked][Uncounted][Linear]")
{

    Size l_sizeOfList = GENERATE(take(10, random(2, 100)));
    Size l_indexOfNeededNode = GENERATE_COPY(take<Size>(25, random<Size>(0, l_sizeOfList - 1)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Size l_curIndex = 0;
    Node<int>* l_curNode = l_list.m_FirstNode;
    while(l_curNode != nullptr)
    {
        if(l_curIndex == l_indexOfNeededNode)
        {
            l_curNode->m_Item = 255;
        }
        else
        {
            l_curNode->m_Item = 0;
        }

        l_curNode = l_curNode->m_NextNode;
        ++l_curIndex;
    }

    Node<int>* l_nodeAtIndex = FindNodeAtIndexNoErrorCheckFromList<int>(l_indexOfNeededNode, l_list);
    REQUIRE(l_nodeAtIndex != nullptr);

    CHECK(l_nodeAtIndex->m_Item == 255);

    DestroyList(l_list);

}

TEST_CASE("Find number of nodes in list", "[LinkedList][SinglyLinked][Uncounted][Linear]")
{

    Size l_sizeOfList = GENERATE(take(10, random(0, 100000)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    if(l_sizeOfList > 0)
    {
        REQUIRE(l_list.m_FirstNode != nullptr);
    }

    Size l_result = FindNumberOfNodesInList(l_list);

    CHECK(l_result == l_sizeOfList);

    DestroyList(l_list);

}

TEST_CASE("List is null", "[LinkedList][SinglyLinked][Uncounted][Linear]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;

    List<int> l_null;
    List<int> l_notNull(&l_dummy1, &l_dummy2);

    CHECK(ListIsNull(l_null));
    CHECK_FALSE(ListIsNull(l_notNull));
}
