#include <catch2/catch.hpp>

#include "../../../../IO/IO.hpp"
#include "../DoublyLinkedListNode.hpp"
#include "../../../Strings/ASCIIString/ASCIIString.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked;
using namespace Library::DataStructures::Strings;
using namespace Library::DataStructures::Array;
using namespace Library::IO;

TEST_CASE("Node writing", "[DoublyLinkedListNode][IO]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;

    Node<int> l_node(&l_dummy1, &l_dummy2, 5);

    OutputStream l_file;
    OpenOutputStreamAtForWritingWithFileName(l_file, "TestFile1.txt");

    l_file << l_node;

    CloseOutputStream(l_file);

    InputStream l_fileIn;
    OpenInputStreamAtWithFileName(l_fileIn, "TestFile1.txt");

    void* l_address;
    ASCIIString l_string;
    CreateASCIIStringAtOfCapacity(l_string, 19);


    l_fileIn >> &l_address;
    CHECK(l_address == &l_node);


    l_fileIn >> l_string;
    CHECK(l_string == "{ m_PreviousNode = ");


    l_fileIn >> &l_address;
    CHECK(l_address == &l_dummy1);


    ResizeArrayToCapacity<char>(l_string, 15);
    l_string.m_Array.m_Size = 0;
    l_fileIn >> l_string;
    CHECK(l_string == ", m_NextNode = ");


    l_fileIn >> &l_address;
    CHECK(l_address == &l_dummy2);


    ResizeArrayToCapacity<char>(l_string, 13);
    l_string.m_Array.m_Size = 0;
    l_fileIn >> l_string;
    CHECK(l_string == ", m_Item = [ ");


    int l_item;
    l_fileIn >> l_item;
    CHECK(l_item == l_node.m_Item);


    ResizeArrayToCapacity<char>(l_string, 5);
    l_string.m_Array.m_Size = 0;
    l_fileIn >> l_string;
    CHECK(l_string == " ] }");

    fgetc(l_fileIn);
    CHECK(feof(l_fileIn));

    DestroyASCIIString(l_string);
    CloseInputStream(l_fileIn);

}
