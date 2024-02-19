#include <catch2/catch.hpp>

#include "../DoublyLinkedListNode.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked;

void SampleAction(int*& p_item, void* p_data)
{
    CHECK(*p_item == 974);
    free(p_item);
    *((bool*)p_data) = true;
}

TEST_CASE("Allocation and deallocation", "[DoublyLinkedListNode][Creation][Destruction]")
{

    Node<int*>* l_node1 = AllocateNodeUsingAllocatorNoErrorCheck<int*>();

    REQUIRE(l_node1 != nullptr);
    
    l_node1->m_Item = nullptr;
    
    SECTION("Defaults")
    {
        DestroyNodeUsingDeallocator<int*>(l_node1);
    }
    SECTION("Customs")
    {
        DestroyNodeUsingDeallocator<int*>(l_node1, free);
    }


}
