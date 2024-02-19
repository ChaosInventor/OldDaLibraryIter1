#include "File.hpp"

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

namespace Library::PlatfromAbstractions::File
{

    struct File
    {
        int m_FileDesc;
        off_t m_Size;
        //TODO: This is questionable
        bool m_Readable;
        bool m_Writable;
    };


    File* AllocateFileUsingAllocator(
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {
        LogDebugLine("Allocating file handle.");
        return (File*)p_allocate(sizeof(File));
    }
    Size AllocateFilesAtUsingAllocator(
        File** const& outp_files, const Size& p_files_size,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {
        
        LogDebugLine("Allocating " << p_files_size << " files and putting them at " << (void*)outp_files);

        if(p_files_size == 0)
        {
            LogDebugLine("0 files need to be allocated, returning 0.");
            return 0;
        }

        if(p_files_size > SIZE_MAX / sizeof(File))
        {
            LogDebugLine("Cannot allocate that many files, Size would overflow, returing 0.");
            return 0;
        }

        File* l_memory = (File*)p_allocate(sizeof(File) * p_files_size);
        if(l_memory == nullptr)
        {
            LogDebugLine("Could not allocate memory for files, returning 0.");
            return 0;
        }
        LogDebugLine("Successfully allocated all of the memory required for all"
        " of the files at " << (void*)l_memory);

        for(Size i = 0; i < p_files_size; ++i)
        {
            LogDebugLine("Setting pointer for file " << i);
            outp_files[i] = l_memory;
            l_memory += sizeof(File);
        }

        LogDebugLine("Set all of the pointers for all of the files, returning "
        "the requested number of files.");
        return p_files_size;

    }

    void CreateFilePathUsingFileErrorHandler(
        const char* p_file_path,
        FileErrorHandler p_file_error, void* p_file_error_data
    )
    {
        
        LogDebugLine("Creating file path " << p_file_path);

        int l_fileDesc;
        do
        {
            l_fileDesc = open(
                p_file_path,
                O_CREAT | O_WRONLY | O_CLOEXEC | O_EXCL,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
            );
        } while (l_fileDesc != EINTR);

        if(l_fileDesc < 0)
        {
            LogDebugLine("Could not create the file.");
            if(p_file_error != nullptr)
            {
                LogDebugLine("The file error handler is not null so determening"
                " the error and calling it.");
                
                FileError l_error;
                
                switch(errno)
                {
                    case EACCES:
                    {
                        l_error = FileError::NoPermission;
                        break;
                    }
                    case EBUSY:
                    {
                        //TODO: ???
                        break;
                    }
                    case EDQUOT:
                    {
                        l_error = FileError::NoMoreSpace;
                        break;
                    }
                    case EEXIST:
                    {
                        l_error = FileError::Exists;
                        break;
                    }
                    case EFAULT:
                    {
                        l_error = FileError::InvalidArguments;
                        break;
                    }
                    case EFBIG:
                    case EOVERFLOW:
                    {
                        //TODO: ??
                        break;
                    }
                    case EINVAL:
                    {
                        //TODO: Might be better to do low level error for this.
                        l_error = FileError::InvalidArguments;
                        break;
                    }
                    case EISDIR:
                    {
                        l_error = FileError::Directory;
                        break;
                    }
                    case :

                    default:
                    {
                        l_error = FileError::LowLevelError;
                        break;
                    }
                }

                p_file_error(l_error, p_file_error_data, nullptr, p_file_path);
                return;
            }
        }

        close(l_fileDesc);

    }


    bool FileIsReadable(File& p_file)
    {
        return p_file.m_Readable;
    }
    bool FileIsWritable(File& p_file)
    {
        return p_file.m_Writable;
    }

    Offset GetLengthOfFile(File& p_file)
    {
        return p_file.m_Size;
    }


    void CloseFile(File& p_file)
    {
        LogDebugLine("Closing file descriptor " << p_file.m_FileDesc);
        close(p_file.m_FileDesc);
    }

    void DeleteFilePathUsingFileErrorHandler(
        const char* p_file_path,
        FileErrorHandler p_file_error, void* p_file_error_data
    )
    {

        LogDebugLine("Deleting the file path: " << p_file_path);
        if(unlink(p_file_path) == -1)
        {
            LogDebugLine("Unlinking failed with errorno = " << errno);
            if(p_file_error != nullptr)
            {
                LogDebugLine("File error handler is not null, so finding cause "
                "of error and calling it.");
                
                //TODO: This should be seperated into a function that handles all cases of errno.
                FileError l_error;
                switch (errno)
                {
                    case EACCES:
                    case EPERM:
                    case EROFS:
                    {
                        l_error = FileError::NoPermission;
                        break;
                    }
                    case EBUSY:
                    {
                        l_error = FileError::InUseByOther;
                        break;
                    }
                    case EFAULT:
                    case ENOENT:
                    case ENOTDIR:
                    case ELOOP:
                    {
                        l_error = FileError::InvalidArguments;
                        break;
                    }
                    case EIO:
                    {
                        l_error = FileError::LowLevelError;
                        break;
                    }
                    case EISDIR:
                    {
                        l_error = FileError::Directory;
                        break;
                    }
                    case ENAMETOOLONG:
                    {
                        l_error = FileError::FilePathTooLong;
                        break;
                    }
                    case ENOMEM:
                    {
                        l_error = FileError::TooManyOpenFiles;
                        break;
                    }
                }
                
                p_file_error(l_error, p_file_error, nullptr, p_file_path);
            }
        }

    }

    void DeallocateFileUsingDeallocator(File& p_handle, Deallocator p_deallocate)
    {
        LogDebugLine("Deallocating file handle at " << &p_handle);
        p_deallocate(&p_handle);
    }
    void DeallocateFilesUsingDeallocator(
        File* const* const& p_files, const Size& p_files_size,
        Deallocator p_deallocate
    )
    {
        LogDebugLine("Deallocating " << p_files_size << " at " << (void*)p_files);

        for(Size i = 0; i < p_files_size; ++i)
        {
            LogDebugLine("Deallocating file " << 0);
            p_deallocate(p_files[i]);
        }
    }

}
