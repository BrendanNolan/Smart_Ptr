#ifndef SIZE_PTR_H
#define SIZE_PTR_H

/*
What you need to worry about in this class and in the Smart_Ptr class that uses  
it is the possibility that the ref_count can reach zero without the space being 
freed, be that the space storing the count or the space storing the object which
that Smart_Ptr (or rather its raw_ptr member) is pointing to. 

This class should not have pointer interface I think. It should seem like just a 
size_t.
*/

#include <cstdlib>
#include <stdexcept>

// -----------------------------------------------------------------------------
// Begin size_Ptr class --------------------------------------------------------

// Begin size_Ptr class main body ----------------------------------------------

class size_Ptr 
{
public:
    size_Ptr(): raw_s_ptr(new std::size_t(1)) {}
    size_Ptr(std::size_t* other_s_ptr): raw_s_ptr(other_s_ptr) {}
    size_Ptr(const size_Ptr& o): raw_s_ptr(o.raw_s_ptr) { ++*raw_s_ptr; }
    ~size_Ptr();

    size_Ptr& operator=(const size_Ptr&);

    std::size_t pointee_val() const { return *raw_s_ptr; }
    
    // increment pointee, then returns *this
    const size_Ptr& inc() const;
    // decrement pointee, if pointee reaches 0, delete raw_s_ptr and set to 0,
    // then return *this
    size_Ptr& dec();

    operator bool() const { return raw_s_ptr; }
private:
    std::size_t* raw_s_ptr;
};

// End size_Ptr class main body ------------------------------------------------

// End size_Ptr class ----------------------------------------------------------
// -----------------------------------------------------------------------------

#endif