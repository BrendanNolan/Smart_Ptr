#ifndef SIZE_PTR_H
#define SIZE_PTR_H

/*
This class should have no pointer interface. To the user, it should seem like a 
self-updating std::size_t. 
*/

#include <cstdlib>
#include <stdexcept>

// Begin size_Ptr class ========================================================

// Begin size_Ptr class main body ----------------------------------------------

class size_Ptr 
{
friend bool operator==(const size_Ptr&, const size_Ptr&);
friend bool operator!=(const size_Ptr&, const size_Ptr&);

public:
    size_Ptr(): raw_s_ptr(new std::size_t(1)) {}
    size_Ptr(std::size_t n): raw_s_ptr(new std::size_t(n)) {}
    size_Ptr(const size_Ptr& o): raw_s_ptr(o.raw_s_ptr) { ++*raw_s_ptr; }
    ~size_Ptr();

    size_Ptr& operator=(const size_Ptr&);

    std::size_t val() const { return *raw_s_ptr; }

    operator bool() const { return raw_s_ptr; }

private:
    std::size_t* raw_s_ptr;
};

// End size_Ptr class main body ------------------------------------------------

// End size_Ptr class ==========================================================

#endif