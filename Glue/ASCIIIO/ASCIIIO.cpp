#include "ASCIIIO.hpp"

using namespace Library::IO;
using namespace Library::DataStructures::Strings;
using namespace Library::DataStructures::Array;

namespace Library::Glue::ASCII_IO
{
    
    const Stream& operator<<(
        const Stream& p_stream,
        ASCIIString& p_string
    )
    {

        if(p_string.m_Array.m_Size == 0)
        {
            return p_stream;
        }

        //HACK: Confirm that char* can be converted to Byte*
        Size l_charsWritten = p_stream.m_WriteBytesToThing(
            (const Byte*)p_string.m_Array.m_Buffer, p_string.m_Array.m_Size,
            p_stream.m_Thing
        );
        //TODO: Shift items left.
        p_string.m_Array.m_Size -= l_charsWritten;

        return p_stream;

    }
    const Stream& operator<<(
        ASCIIString& p_string,
        const Stream& p_stream
    )
    {

        if(p_string.m_Array.m_Capacity == 0)
        {
            return p_stream;
        }

        //HACK: Confirm that char* can be converted to Byte*
        Size l_charsRead = p_stream.m_ReadBytesFromThing(
            (Byte*)p_string.m_Array.m_Buffer + p_string.m_Array.m_Size,
            p_string.m_Array.m_Capacity - p_string.m_Array.m_Size,
            p_stream.m_Thing
        );
        p_string.m_Array.m_Size += l_charsRead;

        return p_stream;

    }

    const Stream& operator>>(
        const Stream& p_stream,
        ASCIIString& p_string
    )
    {

        if(p_string.m_Array.m_Capacity == 0)
        {
            return p_stream;
        }

        return p_stream;

    }
    const Stream& operator>>(
        ASCIIString& p_string,
        const Stream& p_stream
    )
    {

        if(p_string.m_Array.m_Size == 0)
        {
            return p_stream;
        }

        ReverseArray<char>(p_string);

        //HACK: Confirm that char* can be converted to Byte*
        Size l_charsWritten = p_stream.m_WriteBytesToThing(
            (const Byte*)p_string.m_Array.m_Buffer, p_string.m_Array.m_Size,
            p_stream.m_Thing
        );

        ReverseArray<char>(p_string);
        p_string.m_Array.m_Size -= l_charsWritten;

        return p_stream;

    }

}