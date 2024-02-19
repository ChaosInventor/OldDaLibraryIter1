#ifndef SCOPED_OBJECT__SCOPED_OBJECT_SCOPED_OBJECT_HPP
#define SCOPED_OBJECT__SCOPED_OBJECT_SCOPED_OBJECT_HPP

#include <stdlib.h>

template<typename T, void (&tp_destroy) (T&, void (&) (void*)), void (&tp_deallocate) (void*) = free>
struct ScopedObject
{

    T& m_Object;

    ScopedObject(T& p_object) : m_Object(p_object) { }

    ScopedObject(ScopedObject<T, tp_destroy, tp_deallocate>& p_other):
        m_Object(p_other.m_Object)
    { }
    ScopedObject(ScopedObject<T, tp_destroy, tp_deallocate>&& p_other):
        m_Object(p_other.m_Object)
    { }

    ScopedObject& operator= (ScopedObject<T, tp_destroy, tp_deallocate>& p_other)
    {
        m_Object = p_other.m_Object;
        return *this;
    }
    ScopedObject& operator= (ScopedObject<T, tp_destroy, tp_deallocate>&& p_other)
    {
        m_Object = (T&&)p_other.m_Object;
        return *this;
    }

    T& operator= (T& p_object)
    {
        m_Object = p_object;
        return m_Object;
    }

    operator T& ()
    {
        return m_Object;
    }


    ~ScopedObject()
    {
        tp_destroy(m_Object, tp_deallocate);
    }

};


#endif //SCOPED_OBJECT__SCOPED_OBJECT_SCOPED_OBJECT_HPP