#include <catch2/catch.hpp>

#include "../../include/IO.hpp"

using namespace Library;
using namespace Library::IO;

TEST_CASE("Standard streams", "[IO][Stream][Standard]")
{

    Byte l_buffer[5];

    g_StandardInputStream.m_ReadBytesFromThing(l_buffer, 5, g_StandardInputStream.m_Thing);
    g_StandardOutputStream.m_WriteBytesToThing(l_buffer, 5, g_StandardOutputStream.m_Thing);
    g_StandardErrorStream.m_WriteBytesToThing(l_buffer, 5, g_StandardErrorStream.m_Thing);

}
