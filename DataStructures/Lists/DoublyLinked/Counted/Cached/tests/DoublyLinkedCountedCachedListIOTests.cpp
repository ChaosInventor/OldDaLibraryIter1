#include <catch2/catch.hpp>

#include "../../../../../../IO/IO.hpp"
#include "../../../../../Strings/ASCIIString/ASCIIString.hpp"
#include "../../../../../Array/Array.hpp"
#include "../DoublyLinkedCountedCachedList.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked::Counted::Cached;
using namespace Library::DataStructures::Lists::DoublyLinked;
using namespace Library::DataStructures::Strings;
using namespace Library::DataStructures::Array;
using namespace Library::IO;

TEST_CASE("Writing list", "[DoublyLinked][Counted][Cached][List][IO]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;
    Size l_dummySize = 10;
    ListCache<int> l_dummyCache(&l_dummy1, 2);

    List<int> l_list(&l_dummy1, &l_dummy2, l_dummySize);
    l_list.m_Cache = l_dummyCache;

    OutputStream l_out;
    OpenOutputStreamAtForWritingWithFileName(l_out, "TestFile2.txt");
    REQUIRE(l_out != nullptr);

    l_out << l_list;
    CloseOutputStream(l_out);

    InputStream l_in;
    OpenInputStreamAtWithFileName(l_in, "TestFile2.txt");
    REQUIRE(l_in != nullptr);

    void* l_pointer;
    Size l_size;
    ASCIIString l_string;
    CreateASCIIStringAtOfCapacity(l_string, 17);

    l_in >> &l_pointer;
    CHECK(l_pointer == &l_list);


    l_in >> l_string;
    CHECK(l_string == " { m_FirstNode = ");

    l_in >> &l_pointer;
    CHECK(l_pointer == l_list.m_FirstNode);


    ResizeArrayToCapacity<char>(l_string, 15);
    l_string.m_Array.m_Size = 0;
    l_in >> l_string;
    CHECK(l_string == ", m_LastNode = ");

    l_in >> &l_pointer;
    CHECK(l_pointer == l_list.m_LastNode);


    ResizeArrayToCapacity<char>(l_string, 11);
    l_string.m_Array.m_Size = 0;
    l_in >> l_string;
    CHECK(l_string == ", m_Size = ");

    l_in >> l_size;
    CHECK(l_size == l_list.m_Size);


    ResizeArrayToCapacity<char>(l_string, 12);
    l_string.m_Array.m_Size = 0;
    l_in >> l_string;
    CHECK(l_string == ", m_Cache = ");

    l_in >> &l_pointer;
    CHECK(l_pointer == &l_list.m_Cache);


    ResizeArrayToCapacity<char>(l_string, 12);
    l_string.m_Array.m_Size = 0;
    l_in >> l_string;
    CHECK(l_string == " { m_Node = ");

    l_in >> &l_pointer;
    CHECK(l_pointer == l_list.m_Cache.m_Node);


    ResizeArrayToCapacity<char>(l_string, 16);
    l_string.m_Array.m_Size = 0;
    l_in >> l_string;
    CHECK(l_string == ", m_NodeIndex = ");


    Size l_index;
    l_in >> l_index;
    CHECK(l_index == l_list.m_Cache.m_NodeIndex);


    ResizeArrayToCapacity<char>(l_string, 2);
    l_string.m_Array.m_Size = 0;
    l_in >> l_string;
    CHECK(l_string == " }");

    ResizeArrayToCapacity<char>(l_string, 2);
    l_string.m_Array.m_Size = 0;
    l_in >> l_string;
    CHECK(l_string == " }");

    CHECK(fgetc(l_in) == EOF);

    CloseInputStream(l_in);
    DestroyASCIIString(l_string);

}

