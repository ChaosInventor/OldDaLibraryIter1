#ifndef FIXED_ARRAY__DATA_STRUCUTRES_FIXED_ARRAY_FIXED_ARRAY_HPP
#define FIXED_ARRAY__DATA_STRUCUTRES_FIXED_ARRAY_FIXED_ARRAY_HPP

#include "../../../Meta/Meta.hpp"

namespace Library::DataStructures::FixedArray
{

    template<typename T>
    struct FixedArray
    {
        T* m_Buffer;
        Size m_Size;
    };

    

}

#endif //FIXED_ARRAY__DATA_STRUCUTRES_FIXED_ARRAY_FIXED_ARRAY_HPP