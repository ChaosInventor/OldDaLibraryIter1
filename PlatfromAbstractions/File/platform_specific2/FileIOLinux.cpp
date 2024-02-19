#include "../../include/FileIO.hpp"

#include "../../include/platform_specific/FileIOLinux.hpp"

#include <errno.h>
#include <limits.h>

namespace Library::IO
{

    #ifdef DEBUG
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const File& p_file)
    {

        p_log << &p_file << " { ";
        p_log << "m_FileDescriptor = " << p_file.m_FileDescriptor;
        p_log << ", m_EndOfFile = " << p_file.m_EndOfFile;
        p_log << " }";

        return p_log;

    }
    #endif // DEBUG



    Size ReadBytesFromFile(Byte* p_bytes, const Size& p_bytes_size, void* p_file)
    {

        //TODO: Logging

        if(p_bytes == nullptr || p_bytes_size == 0)
        {
            return 0;
        }

        Size l_bytesReadAmount;
        if(p_bytes_size > SSIZE_MAX)
        {
            l_bytesReadAmount = SSIZE_MAX;
        }
        else
        {
            l_bytesReadAmount = p_bytes_size;
        }
        
        ssize_t l_returnValue = read(
            ((File*)p_file)->m_FileDescriptor,
            p_bytes, l_bytesReadAmount
        );

        if(l_returnValue == -1)
        {
            //TODO: Error handle
            return 0;
        }

        return l_returnValue;

    }
    Size WriteBytesToFile(const Byte* p_bytes, const Size& p_bytes_size, void* p_file)
    {

        //TODO: Logging

        if(p_bytes == nullptr || p_bytes_size == 0)
        {
            return 0;
        }

        Size l_bytesWriteAmount;
        if(p_bytes_size > SSIZE_MAX)
        {
            l_bytesWriteAmount = SSIZE_MAX;
        }
        else
        {
            l_bytesWriteAmount = p_bytes_size;
        }
        
        ssize_t l_returnValue = write(
            ((File*)p_file)->m_FileDescriptor,
            p_bytes, l_bytesWriteAmount
        );

        if(l_returnValue == -1)
        {
            //TODO: Error handle
            return 0;
        }

        return l_returnValue;

    }
    bool EndOfFile(void* p_file)
    {
        return ((File*)p_file)->m_EndOfFile;
    }

    Size ReadBytesFromStandardInput(Byte* p_bytes, const Size& p_bytes_size, void* p_file)
    {

        (void)p_file;

        //TODO: Logging

        if(p_bytes == nullptr || p_bytes_size == 0)
        {
            return 0;
        }

        Size l_bytesReadAmount;
        if(p_bytes_size > SSIZE_MAX)
        {
            l_bytesReadAmount = SSIZE_MAX;
        }
        else
        {
            l_bytesReadAmount = p_bytes_size;
        }
        
        ssize_t l_returnValue = read(
            STDIN_FILENO,
            p_bytes, l_bytesReadAmount
        );

        if(l_returnValue == -1)
        {
            //TODO: Error handle
            return 0;
        }

        return l_returnValue;

    }

    Size WriteBytesToStandardOutput(const Byte* p_bytes, const Size& p_bytes_size, void* p_file)
    {

        (void)p_file;

        //TODO: Logging

        if(p_bytes == nullptr || p_bytes_size == 0)
        {
            return 0;
        }

        Size l_bytesWriteAmount;
        if(p_bytes_size > SSIZE_MAX)
        {
            l_bytesWriteAmount = SSIZE_MAX;
        }
        else
        {
            l_bytesWriteAmount = p_bytes_size;
        }
        
        ssize_t l_returnValue = write(
            STDOUT_FILENO,
            p_bytes, l_bytesWriteAmount
        );

        if(l_returnValue == -1)
        {
            //TODO: Error handle
            return 0;
        }

        return l_returnValue;

    }

    Size WriteBytesToStandardError(const Byte* p_bytes, const Size& p_bytes_size, void* p_file)
    {

        (void)p_file;

        //TODO: Logging

        if(p_bytes == nullptr || p_bytes_size == 0)
        {
            return 0;
        }

        Size l_bytesWriteAmount;
        if(p_bytes_size > SSIZE_MAX)
        {
            l_bytesWriteAmount = SSIZE_MAX;
        }
        else
        {
            l_bytesWriteAmount = p_bytes_size;
        }
        
        ssize_t l_returnValue = write(
            STDERR_FILENO,
            p_bytes, l_bytesWriteAmount
        );

        if(l_returnValue == -1)
        {
            //TODO: Error handle
            return 0;
        }

        return l_returnValue;

    }

    void OpenFileStreamAtWithFileNameFlagsAndModeUsingAllocator(
        Stream& outp_stream,
        const char* p_file_name,
        const int& p_flags,
        const mode_t& p_mode,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {

        LogDebugLine("Opening file stream to path '" << p_file_name << '\'');
        
        //TODO: It might be a good idea to move this into the file functions.
        LogDebugLine("Checking if the given path refers to directory.");
        struct stat l_buffer;
        if(stat(p_file_name, &l_buffer))
        {
            //TODO: Handle this error condition.
            return;
        }
        if(S_ISDIR(l_buffer.st_mode))
        {
            LogDebugLine("The given path refers to a directory, setting error and returning.");
            //TODO: Fix
            outp_stream = Stream(nullptr, nullptr, nullptr, nullptr, (void*)"path refers to a directory");
            return;
        }

        int l_fileDescriptor = open(p_file_name, p_flags, p_mode);

        if(l_fileDescriptor == -1)
        {
            LogDebugLine("Open failed! Finding cause of error.");
            LogDebugLine("Errno = " << errno);
            
            outp_stream = Stream();

            switch (errno)
            {
                case EACCES:
                {
                    outp_stream.m_Thing = (void*)"insufficent permission";
                    break;
                }
                case EEXIST:
                {
                    outp_stream.m_Thing = (void*)"the file already exists";
                    break;
                }
                case EINTR:
                {
                    outp_stream.m_Thing = (void*)"interupted by signal";
                    break;
                }
                case EINVAL:
                {
                    outp_stream.m_Thing = (void*)"invlaid flags";
                    break;
                }
                case EISDIR:
                {
                    outp_stream.m_Thing = (void*)"trying to open directory";
                    break;
                }
                case ELOOP:
                {
                    outp_stream.m_Thing = (void*)"symbolic link could not be followed";
                    break;
                }
                case ENFILE:
                case EMFILE:
                {
                    outp_stream.m_Thing = (void*)"cannot open more file descriptors";
                    break;
                }
                case ENAMETOOLONG:
                {
                    outp_stream.m_Thing = (void*)"path name is too long";
                    break;
                }
                case ENOTDIR:
                case ENOENT:
                {
                    outp_stream.m_Thing = (void*)"invalid path";
                    break;
                }
                case ENOSPC:
                {
                    outp_stream.m_Thing = (void*)"no enough space to create file";
                    break;
                }
                case ENXIO:
                {
                    //TODO: Thing up of a better error message than this.
                    outp_stream.m_Thing = (void*)"bad file and flags";
                    break;
                }
                case EOVERFLOW:
                {
                    outp_stream.m_Thing = (void*)"cannot represent the size of the file";
                    break;
                }
                case EROFS:
                {
                    outp_stream.m_Thing = (void*)"file system is read only";
                    break;
                }

                default:
                outp_stream.m_Thing = (void*)"unknow cause of error :(";   
            }
        }
        else
        {
            LogDebugLine("Open was successful, file descriptor is " << l_fileDescriptor);
            
            LogDebugLine("Allocating File now.");
            
            File* l_file = (File*)p_allocate(sizeof(File));
            if(l_file == nullptr)
            {
                LogDebugLine("Allocation failed! Closing opened file descriptor.");
                
                close(l_fileDescriptor);

                LogDebugLine("Setting up stream.");
                //TODO: Fix
                outp_stream = Stream(nullptr, nullptr, nullptr, nullptr, (void*)"allocation error");
                if(p_alloc_error != nullptr)
                {
                    LogDebugLine("Alloc error is not null so calling it.");
                    p_alloc_error(p_alloc_error_data);
                }

                LogDebugLine("Returning from unsuccessful allocation.");
                return;
            }
        
            LogDebugLine("File successfully allocated, address is " << (void*)l_file);

            LogDebugLine("Setting up file and stream.");
            *l_file = File(l_fileDescriptor);
            outp_stream = Stream(&ReadBytesFromFile, &WriteBytesToFile, &EndOfFile, nullptr, (void*)l_file);
        }

    }

    void OpenFileStreamAtWithFileNameForReadingUsingAllocator(
        Stream& outp_stream,
        const char* p_file_name,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {
        LogDebugLine("Opening file for reading.");
        OpenFileStreamAtWithFileNameFlagsAndModeUsingAllocator(
            outp_stream,
            p_file_name,
            O_RDONLY | O_NONBLOCK,
            0,
            p_allocate, p_alloc_error, p_alloc_error_data
        );
        //Since this is a read only. Also doesn't matter if any failure occurred.
        outp_stream.m_WriteBytesToThing = nullptr;
    }
    void OpenFileStreamAtWithFileNameForWritingUsingAllocator(
        Stream& outp_stream,
        const char* p_file_name,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {
        LogDebugLine("Opening file for writing.");
        OpenFileStreamAtWithFileNameFlagsAndModeUsingAllocator(
            outp_stream,
            p_file_name,
            O_WRONLY | O_NONBLOCK,
            0,
            p_allocate, p_alloc_error, p_alloc_error_data
        );
        //Since this is a write only. Also doesn't matter if any failure occurred.
        outp_stream.m_ReadBytesFromThing = nullptr;
    }
    void OpenFileStreamAtWithFileNameForReadingAndWritingUsingAllocator(
        Stream& outp_stream,
        const char* p_file_name,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {
        LogDebugLine("Opening file for reading and writing.");
        OpenFileStreamAtWithFileNameFlagsAndModeUsingAllocator(
            outp_stream,
            p_file_name,
            O_RDWR | O_NONBLOCK,
            0,
            p_allocate, p_alloc_error, p_alloc_error_data
        );
    }

    void CreateFileStreamAtWithFileNameForReadingUsingAllocator(
        Stream& outp_stream,
        const char* p_file_name,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {
        LogDebugLine("Creating file for reading.");
        OpenFileStreamAtWithFileNameFlagsAndModeUsingAllocator(
            outp_stream,
            p_file_name,
            O_RDONLY | O_NONBLOCK | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,
            p_allocate, p_alloc_error, p_alloc_error_data
        );
        //Since this is a read only. Also doesn't matter if any failure occurred.
        outp_stream.m_WriteBytesToThing = nullptr;
    }
    void CreateFileStreamAtWithFileNameForWritingUsingAllocator(
        Stream& outp_stream,
        const char* p_file_name,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {
        LogDebugLine("Creating file for writing.");
        OpenFileStreamAtWithFileNameFlagsAndModeUsingAllocator(
            outp_stream,
            p_file_name,
            O_WRONLY | O_NONBLOCK | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,
            p_allocate, p_alloc_error, p_alloc_error_data
        );
        //Since this is a write only. Also doesn't matter if any failure occurred.
        outp_stream.m_ReadBytesFromThing = nullptr;
    }
    void CreateFileStreamAtWithFileNameForReadingAndWritingUsingAllocator(
        Stream& outp_stream,
        const char* p_file_name,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {
        LogDebugLine("Creating file for reading and writing.");
        OpenFileStreamAtWithFileNameFlagsAndModeUsingAllocator(
            outp_stream,
            p_file_name,
            O_RDWR | O_NONBLOCK | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH,
            p_allocate, p_alloc_error, p_alloc_error_data
        );
    }


    const char* GetLastErrorFromFileStream(const Stream& p_stream)
    {
        LogDebugLine("Getting last error message text from file stream " << p_stream);
        return ((File*)p_stream.m_Thing)->m_LastErrorText;
    }

    unsigned long GetFileStreamSize(const Stream& p_stream)
    {

        LogDebugLine("Getting the size of file stream " << p_stream);

        struct stat l_buffer;
        if(fstat(((File*)p_stream.m_Thing)->m_FileDescriptor, &l_buffer) < 0)
        {
            //TODO: Errors
            return 0;
        }
        
        if(l_buffer.st_size > ULONG_MAX)
        {
            //TODO: Set last error
            return 0;
        }
        else if (l_buffer.st_size < 0)
        {
            //TODO: Errors
            return 0;
        }
        else
        {
            return l_buffer.st_size;
        }
        
    }

    unsigned long GetFileStreamPosition(const Stream& p_stream)
    {

        LogDebugLine("Getting the file position of file stream " << p_stream);

        off_t l_result = lseek(((File*)p_stream.m_Thing)->m_FileDescriptor, 0, SEEK_CUR);
        if(l_result < 0)
        {
            //TODO: Errors
            return 0;
        }
        
        if(l_result > ULONG_MAX)
        {
            //TODO: Errors
            return 0;
        }

        return l_result;

    }

    unsigned long IncreaseFileStreamPositionByAmount(
        const Stream& p_stream,
        unsigned long p_amount
    )
    {
        //FIXME: p_amount can overflow and lead to some strange errors.
        return lseek(((File*)p_stream.m_Thing)->m_FileDescriptor, p_amount, SEEK_CUR);
    }
    unsigned long DecreaseFileStreamPositionByAmount(
        const Stream& p_stream,
        unsigned long p_amount
    )
    {
        //FIXME: p_amount can overflow and lead to some strange errors.
        off_t l_amountNegative = -((long)p_amount);
        return lseek(((File*)p_stream.m_Thing)->m_FileDescriptor, l_amountNegative , SEEK_CUR);
    }

    //TODO: Maybe better errors?
    bool SetFileStreamPositionToBegining(const Stream& p_stream)
    {
        LogDebugLine("Setting the file position of file stream " << p_stream
        << " to the beginning.");
        return lseek(((File*)p_stream.m_Thing)->m_FileDescriptor, 0, SEEK_SET) < 0;
    }
    bool SetFileStreamPositionToEnd(const Stream& p_stream)
    {
        LogDebugLine("Setting the file position of file stream " << p_stream
        << " to the end.");
        return lseek(((File*)p_stream.m_Thing)->m_FileDescriptor, 0, SEEK_END) < 0;
    }


    //TODO: Maybe better errors?
    bool DeleteFileName(const char* p_file_name)
    {
        return unlink(p_file_name) == 0;
    }

    void CloseFileStreamUsingDeallocator(Stream& p_stream, void (&p_deallocate) (void*))
    {
        
        LogDebugLine("Closing the file stream " << p_stream);

        //FIXME: May not be a good idea to ignore the return value of close.
        close(((File*)p_stream.m_Thing)->m_FileDescriptor);
        p_deallocate(p_stream.m_Thing);
        
        LogDebugLine("Cleared up all of the used system resources, emptying the"
        " stream struct.");

        p_stream = Stream();

    }

}
