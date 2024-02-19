#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../../include/IO.hpp"

using namespace Library;
using namespace Library::IO;

Size DummyRead(Byte*, const Size&, void*)
{
    return 0;
}
Size DummyWrite(const Byte*, const Size&, void*)
{
    return 0;
}

const char* DummyError(void*)
{
    return "Oowpsie!!!! :3 I made a big stinky OwO";
}

bool DummyEnd(void*)
{
    return false;
}


TEST_CASE("Default constructor", "[IO][Stream][Member]")
{

    Stream l_stream;

    CHECK(l_stream.m_ReadBytesFromThing == nullptr);
    CHECK(l_stream.m_WriteBytesToThing == nullptr);
    CHECK(l_stream.m_EndOfThing == nullptr);
    CHECK(l_stream.m_Thing == nullptr);
    CHECK(l_stream.m_GetLastErrorFromThing == nullptr);

}

TEST_CASE("Read and write constructor", "[IO][Stream][Member]")
{

    int l_dummyThing;
    Stream l_stream(&DummyRead, &DummyWrite, &DummyEnd, &DummyError, &l_dummyThing);

    CHECK(l_stream.m_ReadBytesFromThing == &DummyRead);
    CHECK(l_stream.m_WriteBytesToThing == &DummyWrite);
    CHECK(l_stream.m_EndOfThing == &DummyEnd);
    CHECK(l_stream.m_Thing == &l_dummyThing);
    CHECK(l_stream.m_GetLastErrorFromThing == &DummyError);

}

TEST_CASE("Copying and moving", "[IO][Stream][Member]")
{

    int l_dummyThing;
    Stream l_stream(&DummyRead, &DummyWrite, &DummyEnd, &DummyError, &l_dummyThing);

    Stream l_to;

    SECTION("Copy constructor")
    {
        l_to = Stream(l_stream);
    }
    SECTION("Copy operator")
    {
        l_to = l_stream;
    }
    SECTION("Moving")
    {
        SECTION("Constructor")
        {
            l_to = Stream((Stream&&)l_stream);
        }
        SECTION("Operator")
        {
            l_to = (Stream&&)l_stream;
        }

        CHECK(l_stream.m_ReadBytesFromThing == nullptr);
        CHECK(l_stream.m_WriteBytesToThing == nullptr);
        CHECK(l_stream.m_EndOfThing == nullptr);
        CHECK(l_stream.m_Thing == nullptr);
    }

    CHECK(l_to.m_ReadBytesFromThing == &DummyRead);
    CHECK(l_to.m_WriteBytesToThing == &DummyWrite);
    CHECK(l_to.m_EndOfThing == &DummyEnd);
    CHECK(l_to.m_Thing == &l_dummyThing);
    CHECK(l_to.m_GetLastErrorFromThing == &DummyError);

}

TEST_CASE("Read only constructor", "[IO][Stream][Member]")
{

    int l_dummyThing;
    Stream l_stream(&DummyRead, &DummyEnd, &DummyError, &l_dummyThing);

    CHECK(l_stream.m_ReadBytesFromThing == &DummyRead);
    CHECK(l_stream.m_WriteBytesToThing == nullptr);
    CHECK(l_stream.m_EndOfThing == &DummyEnd);
    CHECK(l_stream.m_Thing == &l_dummyThing);
    CHECK(l_stream.m_GetLastErrorFromThing == &DummyError);


}

TEST_CASE("Write only constructor", "[IO][Stream][Member]")
{

    int l_dummyThing;
    Stream l_stream(&DummyWrite, &DummyEnd, &DummyError, &l_dummyThing);

    CHECK(l_stream.m_ReadBytesFromThing == nullptr);
    CHECK(l_stream.m_WriteBytesToThing == &DummyWrite);
    CHECK(l_stream.m_EndOfThing == &DummyEnd);
    CHECK(l_stream.m_Thing == &l_dummyThing);
    CHECK(l_stream.m_GetLastErrorFromThing == &DummyError);

}
