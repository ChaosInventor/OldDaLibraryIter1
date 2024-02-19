#include <unistd.h>
#include <limits.h>
#include <errno.h>

#include "../../include/IO.hpp"

//TODO: Logging in everything would be nice.
//TODO: Full documentation.

namespace Library::IO
{

    struct StandardStream
    {
        //The file descriptor used by the standard stream.
        int m_FileDescriptor;
        //Whether the end of the standard stream has been reached.
        bool m_End;
        //The current error message.
        const char* m_Error;
    };


    //Generic read function.
    Size ReadBytesFromStandardStream(
        Byte* p_bytes, const Size& p_bytes_size,
        void* p_thing
    )
    {

        Size l_actualReadSize;

        if(p_bytes_size > SSIZE_MAX)
        {
            l_actualReadSize = SSIZE_MAX;
        }
        else
        {
            l_actualReadSize = p_bytes_size;
        }
        

        StandardStream* l_stream = (StandardStream*)p_thing;
        
        ssize_t l_returnValue = read(l_stream->m_FileDescriptor, p_bytes, l_actualReadSize);
        if(l_returnValue == 0)
        {
            l_stream->m_End = true;
            return 0;
        }
        if(l_returnValue < 0)
        {
            switch(errno)
            {
                case EAGAIN:
                {
                    //TODO: It may be worth to try to fix this using fcntl
                    l_stream->m_Error = "File descriptor marked as non blocking and read would block";
                    break;
                }
                case EBADF:
                {
                    l_stream->m_Error = "Invalid file descriptor for standard stream";
                    break;
                }
                case EFAULT:
                {
                    l_stream->m_Error = "Incorrect byte buffer";
                    break;
                }
                case EINTR:
                {
                    //TODO: Maybe try to read again in this case.
                    l_stream->m_Error = "Interupted by signal";
                    break;
                }
                case EINVAL:
                {
                    l_stream->m_Error =
                        "Either cannot read from file descriptor or incorrectly aligned buffer or file offset";
                    break;
                } 
                case EIO:
                {
                    l_stream->m_Error = "Low level IO error";
                    break;
                }    
                case EISDIR:
                {
                    l_stream->m_Error = "The file descriptor for the standard stream refers to a directory";
                    break;
                } 
                default:
                {
                    l_stream->m_Error = "Unknow error";
                    break;
                }
            }

            return 0;
        }

        return l_returnValue;

    }
    //Generic write function.
    Size WriteBytesToStandardStream(
        const Byte* p_bytes, const Size& p_bytes_size,
        void* p_thing
    )
    {

        Size l_actualWriteSize;

        if(p_bytes_size > SSIZE_MAX)
        {
            l_actualWriteSize = SSIZE_MAX;
        }
        else
        {
            l_actualWriteSize = p_bytes_size;
        }
        

        StandardStream* l_stream = (StandardStream*)p_thing;
        
        ssize_t l_returnValue = write(l_stream->m_FileDescriptor, p_bytes, l_actualWriteSize);
        if(l_returnValue < 0)
        {
            switch(errno)
            {
                case EAGAIN:
                {
                    //TODO: It may be worth to try to fix this using fcntl
                    l_stream->m_Error = "File descriptor marked as non blocking and write would block";
                    break;
                }
                case EBADF:
                {
                    l_stream->m_Error = "Invalid file descriptor for standard stream";
                    break;
                }
                case EDESTADDRREQ:
                {
                    //TODO: What do i even write here???!!!
                    l_stream->m_Error = "Error msg for error not implemented yet";
                    break;
                }
                case EDQUOT:
                {
                    l_stream->m_Error = "Quota of disk blocks reached on standard stream.";
                    break;
                }
                case EFAULT:
                {
                    l_stream->m_Error = "Incorrect byte buffer";
                    break;
                }
                case EINTR:
                {
                    //TODO: Maybe try to read again in this case.
                    l_stream->m_Error = "Interupted by signal";
                    break;
                }
                case EINVAL:
                {
                    l_stream->m_Error =
                        "Either cannot read from file descriptor or incorrectly aligned buffer or file offset";
                    break;
                } 
                case EIO:
                {
                    l_stream->m_Error = "Low level IO error";
                    break;
                }    
                case ENOSPC:
                {
                    //TODO: See if this is correct
                    l_stream->m_End = true;
                    break;
                }
                case EPERM:
                {
                    l_stream->m_Error = "Cannot write to standard stream due to file seal";
                    break;
                }
                case EPIPE:
                {
                    l_stream->m_Error = "Cannot write to standard stream because reading end of pipe or socket closed";
                    break;
                }
                default:
                {
                    l_stream->m_Error = "Unknow error";
                    break;
                }
            }

            return 0;
        }

        return l_returnValue;

    }

    //Just returns the m_End field.
    bool EndOfStandardStream(void* p_thing)
    {
        return ((StandardStream*)p_thing)->m_End;
    }
    //Just returns the m_Error field.
    const char* GetLastErrorFromStandardStream(void* p_thing)
    {
        return ((StandardStream*)p_thing)->m_Error;
    }


    StandardStream g_StandardInputData {STDIN_FILENO, false, nullptr};
    const Stream g_StandardInputStream = Stream(
        &ReadBytesFromStandardStream,
        nullptr,
        &EndOfStandardStream,
        &GetLastErrorFromStandardStream,
        &g_StandardInputData
    );
    
    StandardStream g_StandardOutputData {STDOUT_FILENO, false, nullptr};
    const Stream g_StandardOutputStream = Stream(
        nullptr,
        &WriteBytesToStandardStream,
        &EndOfStandardStream,
        &GetLastErrorFromStandardStream,
        &g_StandardOutputData
    );
    
    StandardStream g_StandardErrorData {STDERR_FILENO, false, nullptr};
    const Stream g_StandardErrorStream = Stream(
        nullptr,
        &WriteBytesToStandardStream,
        &EndOfStandardStream,
        &GetLastErrorFromStandardStream,
        &g_StandardErrorData
    );

}
