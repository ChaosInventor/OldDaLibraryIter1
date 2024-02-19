#include "../Meta/Meta.hpp"

namespace Library
{

    struct Memory
    {

        Byte* m_Location;
        Size m_Size;
        Byte m_Permissions: 3;


        Memory():
        m_Location(nullptr),
        m_Size(0),
        m_Permissions(0)
        { }
        Memory(Byte* const& p_location, const Size& p_size, const Byte& p_permissions):
        m_Location(p_location),
        m_Size(p_size),
        m_Permissions(p_permissions)
        { }

        Memory(const Memory& p_other):
        m_Location(p_other.m_Location),
        m_Size(p_other.m_Size),
        m_Permissions(p_other.m_Permissions)
        { }
        Memory(Memory&& p_other):
        m_Location(p_other.m_Location),
        m_Size(p_other.m_Size),
        m_Permissions(p_other.m_Permissions)
        {
            p_other.m_Location = nullptr;
            p_other.m_Size = 0;
            p_other.m_Permissions = 0;
        }


        Memory& operator=(const Memory& p_other)
        {

            m_Location = p_other.m_Location;
            m_Size = p_other.m_Size;
            m_Permissions = p_other.m_Permissions;
        
            return *this;

        }
        Memory& operator=(Memory&& p_other)
        {

            m_Location = p_other.m_Location;
            m_Size = p_other.m_Size;
            m_Permissions = p_other.m_Permissions;
        
            p_other.m_Location = nullptr;
            p_other.m_Size = 0;
            p_other.m_Permissions = 0;

            return *this;

        }


        bool operator==(const Memory& p_other)
        {
            return 
                m_Location == p_other.m_Location
                &&
                m_Size == p_other.m_Size
                &&
                m_Permissions == p_other.m_Permissions;
        }
        bool operator!=(const Memory& p_other)
        {
            return !(*this == p_other);
        }

    };


    //TODO: Meta memory function


    inline bool MemoryIsReadable(const Memory& p_mem)
    {
        return p_mem.m_Permissions & 1;
    }
    inline bool MemoryIsWritable(const Memory& p_mem)
    {
        return p_mem.m_Permissions & 0b010;
    }
    inline bool MemoryIsExecutable(const Memory& p_mem)
    {
        return p_mem.m_Permissions & 0b100;
    }

    //TODO: Functions that change permissions instead of having to do manual
    //bit wise operations

    //TODO: Should not be inline
    inline void WriteZerosToMemory(const Memory& p_mem)
    {
        for(Size i = 0; i < p_mem.m_Size; ++i)
        {
            p_mem.m_Location[i] = 0;
        }
    }

}
