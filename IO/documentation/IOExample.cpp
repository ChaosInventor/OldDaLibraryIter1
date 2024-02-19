//TODO: Decide if to keep this file or not.

#include "../include/IO.hpp"
#include <IO.hpp>

using namespace Library::IO;

int main()
{

    Byte l_bytes[4];

    //Reads them.
    g_StandardInputStream.m_ReadBytesFromThing(l_bytes, 4, g_StandardInputStream.m_Thing);

    //Multiplies
    for(Size i = 0; i < 4; ++i)
    {
        l_bytes[i] *= 2;
    }

    //Writes them
    g_StandardOutputStream.m_WriteBytesToThing(l_bytes, 4, g_StandardOutputStream.m_Thing);

    return 0;

}