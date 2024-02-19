/** @file IO.cpp
 * @brief Defines everything in the @ref IOMod module.
 *
 */

#include "../include/IO.hpp"

namespace Library::IO
{

    #ifdef DEBUG
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const Stream& p_stream)
    {

        p_log << (void*)&p_stream;
        p_log << " { ";
        p_log << " Read = " << *((void**)(&p_stream.m_ReadBytesFromThing));
        p_log << ", Write = " << *((void**)(&p_stream.m_WriteBytesToThing));
        p_log << ", End = " << *((void**)(&p_stream.m_EndOfThing));
        p_log << ", Error = " << *((void**)(&p_stream.m_GetLastErrorFromThing));
        p_log << ", Thing = " << p_stream.m_Thing;
        p_log << " }";

        return p_log;

    }
    #endif //DEBUG



    static Size NullStreamReadBytes(Byte* p_bytes, const Size& p_bytes_size, void* p_thing)
    {

        LogDebugLine("Reading from null stream, bytes = " << (void*)p_bytes
        << " p_bytes_size = " << p_bytes_size << " p_thing = " << p_thing);

        //The case where the byte size is 0 is covered by the for loop it's self.
        if(p_bytes == nullptr)
        {
            LogDebugLine("Buffer is null, returning.");
            return p_bytes_size;
        }

        for(Size i = 0; i < p_bytes_size; ++i)
        {
            LogDebugLine("Setting byte at index " << i << " to 0.");
            p_bytes[i] = 0;
        }

        LogDebugLine("Returning p_bytes_size.");
        return p_bytes_size;

    }
    static Size NullStreamWriteBytes(const Byte* p_bytes, const Size& p_bytes_size, void* p_thing)
    {

        LogDebugLine("Writing to null stream, bytes = " << (void*)p_bytes
        << " p_bytes_size = " << p_bytes_size << " p_thing = " << p_thing);

        LogDebugLine("Returning p_bytes_size.");
        return p_bytes_size;

    }

    const Stream g_NullStream = Stream(
        &NullStreamReadBytes,
        &NullStreamWriteBytes,
        nullptr,
        nullptr,
        nullptr //The thing pointer can really be anything.
    );

    //TODO: Make platfrom independent

}

//This checks the current platfrom and includes the appropriate implementation
//for the standard streams.
#if defined __unix__
#include "platform_specific/POSIXStandardStreams.cpp"
#else
#error No IO module implementation for current platfrom!
#endif
