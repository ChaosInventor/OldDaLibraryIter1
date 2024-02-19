//TODO: Rework needed

/*
#include <catch2/catch.hpp>

#include "../ASCIIString.hpp"
#include "../../../../IO/IO.hpp"
#include "../../../Array/Array.hpp"

using namespace Library::DataStructures::Strings;
using namespace Library::DataStructures::Array;
using namespace Library::IO;

TEST_CASE("Reading and writing an ASCII string", "[ASCIIString][IO]")
{

    OutputStream l_out;
    OpenOutputStreamAtForWritingWithFileName(l_out, "TestFileASCIIStringIO.txt");
    REQUIRE(l_out != nullptr);

    ASCIIString l_string("String");
    REQUIRE(l_string != nullptr);

    const OutputStream& l_returnOut = (l_out << l_string);
    CHECK(&l_returnOut == &l_out);

    CloseOutputStream(l_out);


    InputStream l_in;
    OpenInputStreamAtWithFileName(l_in, "TestFileASCIIStringIO.txt");
    REQUIRE(l_in != nullptr);

    ASCIIString l_result;
    CreateArrayAtOfCapacity<char>(l_result, l_string.m_Array.m_Size);
    REQUIRE(l_result != nullptr);

    const InputStream& l_returnIn = (l_in >> l_result);
    CHECK(&l_returnIn == &l_in);

    CHECK(l_result == l_string);

    CloseInputStream(l_in);


    DestoryArray<char>(l_string);
    DestoryArray<char>(l_result);

}

*/