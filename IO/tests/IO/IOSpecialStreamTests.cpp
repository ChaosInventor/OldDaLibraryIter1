#include <catch2/catch.hpp>

#include "../../include/IO.hpp"

using namespace Library;
using namespace Library::IO;
using namespace Catch::Generators;

TEST_CASE("Null stream normal case", "[IO][Stream][Special]")
{

    Size l_byteBufferSize = GENERATE(take(10, random(1, 1000)));

    Byte* l_byteBuffer = (Byte*)malloc(l_byteBufferSize);
    REQUIRE(l_byteBuffer != nullptr);

    for(Size i = 0; i < l_byteBufferSize; ++i)
    {
        l_byteBuffer[i] = i * (abs(rand()) % 10);
    }

    Size l_returnValue = g_NullStream.m_WriteBytesToThing(l_byteBuffer, l_byteBufferSize, g_NullStream.m_Thing);
    CHECK(l_returnValue == l_byteBufferSize);

    l_returnValue = g_NullStream.m_ReadBytesFromThing(l_byteBuffer, l_byteBufferSize, g_NullStream.m_Thing);
    CHECK(l_returnValue == l_byteBufferSize);

    for(Size i = 0; i < l_byteBufferSize; ++i)
    {
        CHECK(l_byteBuffer[i] == 0);
    }

}

TEST_CASE("Null stream null buffer", "[IO][Stream][Special]")
{

    Size l_bufferSize = GENERATE(take(10, random(1, 1000)));

    Size l_returnValue = g_NullStream.m_ReadBytesFromThing(nullptr, l_bufferSize, g_NullStream.m_Thing);
    CHECK(l_returnValue == l_bufferSize);

    l_returnValue = g_NullStream.m_WriteBytesToThing(nullptr, l_bufferSize, g_NullStream.m_Thing);
    CHECK(l_returnValue == l_bufferSize);

}

TEST_CASE("Null stream buffer size 0", "[IO][Stream][Special]")
{

    Byte* l_buffer = (Byte*)GENERATE(take(10, random<intptr_t>(0, 1000)));

    Size l_returnValue = g_NullStream.m_ReadBytesFromThing(l_buffer, 0, g_NullStream.m_Thing);
    CHECK(l_returnValue == 0);

    l_returnValue = g_NullStream.m_WriteBytesToThing(l_buffer, 0, g_NullStream.m_Thing);
    CHECK(l_returnValue == 0);

}

TEST_CASE("Null stream null buffer and 0 buffer size", "[IO][Stream][Special]")
{

    Size l_returnValue = g_NullStream.m_ReadBytesFromThing(nullptr, 0, g_NullStream.m_Thing);
    CHECK(l_returnValue == 0);

    l_returnValue = g_NullStream.m_WriteBytesToThing(nullptr, 0, g_NullStream.m_Thing);
    CHECK(l_returnValue == 0);

}

