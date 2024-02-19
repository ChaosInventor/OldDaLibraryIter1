#include "../include/Thread.hpp"

/*
#ifdef __unix__
#include "platform_specific/POSIXThread.cpp"
#else
#error Current platfrom not supported!
#endif
*/

namespace Library::Asynchronous
{

    #ifdef DEBUG
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const Stack& p_stack)
    {

        p_log << (void*)&p_stack << " {";
        p_log << " m_Address = " << p_stack.m_Address;
        p_log << " m_Size = " << p_stack.m_Size;
        p_log << " }";

        return p_log;

    }
    #endif // DEBUG

}
