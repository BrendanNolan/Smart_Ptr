#include "size_Ptr.h"

// Begin definitions of size_Ptr methods ---------------------------------------

size_Ptr::~size_Ptr() 
{
    if (raw_s_ptr)
    {
        if (--*raw_s_ptr == 0)
            delete raw_s_ptr;
    }
}

size_Ptr& size_Ptr::operator=(const size_Ptr& rhs)
{
    // if rhs is unbound, delete raw_s_ptr and set it to 0, then return *this
    if (!rhs)
    {
        delete raw_s_ptr;
        raw_s_ptr = 0;
        return *this;
    }

    ++*(rhs.raw_s_ptr);
    
    if (raw_s_ptr)
    {
        if (--*raw_s_ptr == 0)
            delete raw_s_ptr;
    }
    
    raw_s_ptr = rhs.raw_s_ptr;
    return *this;
}

// End definitions of size_Ptr methods -----------------------------------------