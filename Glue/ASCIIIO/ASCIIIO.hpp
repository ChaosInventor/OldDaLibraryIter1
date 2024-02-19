#ifndef ASCII_IO__GLUE_ASCII_IO_ASCII_IO_HPP
#define ASCII_IO__GLUE_ASCII_IO_ASCII_IO_HPP

#include "../../DataStructures/Strings/ASCIIString/ASCIIString.hpp"
#include "../../IO/include/IO.hpp"

namespace Library::Glue::ASCII_IO
{
    
    const IO::Stream& operator<<(
        const IO::Stream& p_stream,
        DataStructures::Strings::ASCIIString& p_string
    );
    const IO::Stream& operator<<(
        DataStructures::Strings::ASCIIString& p_string,
        const IO::Stream& p_stream
    );

    const IO::Stream& operator>>(
        const IO::Stream& p_stream,
        DataStructures::Strings::ASCIIString& p_string
    );
    const IO::Stream& operator>>(
        DataStructures::Strings::ASCIIString& p_string,
        const IO::Stream& p_stream
    );


    void ReadFromStreamToASCIIStringUntilReadASCIIString(
        const IO::Stream& p_stream,
        const DataStructures::Strings::ASCIIString& p_string,
        const DataStructures::Strings::ASCIIString& p_characters
    );

    void WriteFromASCIIStringToStreamUntilWriteASCIIString(
        const DataStructures::Strings::ASCIIString& p_string,
        const IO::Stream& p_stream,
        const DataStructures::Strings::ASCIIString& p_characters
    );

    void ReadFromStreamToASCIIStringAfterIndex();

    void WriteFromASCIIStringFromIndexToStream();

}

#endif //ASCII_IO__GLUE_ASCII_IO_ASCII_IO_HP