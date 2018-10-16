#include "size_Ptr.h"

// Begin definitions of size_Ptr friends ---------------------------------------

bool operator==(const size_Ptr& a, const size_Ptr& b)
{
    return a.raw_s_ptr == b.raw_s_ptr;
}

bool operator!=(const size_Ptr& a, const size_Ptr& b)
{
    return !(a == b);
}

// End definitions of size_Ptr friends -----------------------------------------

// Begin definitions of size_Ptr methods ---------------------------------------

size_Ptr::~size_Ptr() 
{
    if (--*raw_s_ptr == 0)
        delete raw_s_ptr;
}

size_Ptr& size_Ptr::operator=(const size_Ptr& rhs)
{
    if (*this != rhs)
    {
        if (--*raw_s_ptr == 0)
            delete raw_s_ptr;
        raw_s_ptr = rhs.raw_s_ptr;
        ++*raw_s_ptr;
    }
    return *this;
}

// End definitions of size_Ptr methods -----------------------------------------