#include <catch2/catch.hpp>

#include "../../../../../../IO/IO.hpp"
#include "../DoublyLinkedCountedCachedList.hpp"
#include "../../../../../Strings/ASCIIString/ASCIIString.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked::Counted::Cached;
using namespace Library::DataStructures::Lists::DoublyLinked;
using namespace Library::DataStructures::Strings;
using namespace Library::DataStructures::Array;
using namespace Library::IO;
using namespace Catch::Generators;

TEST_CASE("Writing list chache", "[DoublyLinked][Counted][Cache][IO]")
{

    OutputStream l_outStream;
    OpenOutputStreamAtForWritingWithFileName(l_outStream, "TestFile1.txt");
    REQUIRE(l_outStream != nullptr);

    Node<int> l_dummy1;
    Size l_dummyIndex = GENERATE(range(1, 10));

    ListCache<int> l_cache(&l_dummy1, l_dummyIndex);

    l_outStream << l_cache;
    CloseOutputStream(l_outStream);


    InputStream l_inStream;
    OpenInputStreamAtWithFileName(l_inStream, "TestFile1.txt");
    REQUIRE(l_inStream != nullptr);

    void* l_pointer;

    ASCIIString l_string;
    CreateASCIIStringAtOfCapacity(l_string, 12);
    REQUIRE(l_string != nullptr);


    l_inStream >> &l_pointer;
    CHECK(l_pointer == &l_cache);

    l_inStream >> l_string;
    CHECK(l_string == " { m_Node = ");

    l_inStream >> &l_pointer;
    CHECK(l_pointer == &l_dummy1);

    ResizeArrayToCapacity<char>(l_string, 16);
    l_string.m_Array.m_Size = 0;
    l_inStream >> l_string;
    CHECK(l_string == ", m_NodeIndex = ");

    Size l_index;
    l_inStream >> l_index;
    CHECK(l_index == l_dummyIndex);

    ResizeArrayToCapacity<char>(l_string, 2);
    l_string.m_Array.m_Size = 0;
    l_inStream >> l_string;
    CHECK(l_string == " }");

    CHECK(getc(l_inStream) == EOF);

    CloseInputStream(l_inStream);
    DestroyASCIIString(l_string);

}
