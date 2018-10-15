#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <cstdlib>
#include <stdexcept>

#include "size_Ptr.h"

// Begin definitions of global utility functions -------------------------------

template <typename T>
T* clone(const T* p)
{
    if (p)
        return p->clone();
    
    throw std::runtime_error("unbound pointer passed to global clone function");
}

// End definitions of global utility functions ---------------------------------



// Begin Smart_Ptr class =======================================================

// Begin Smart_Ptr class main body ---------------------------------------------

template <typename T>
class Smart_Ptr 
{
public: 
    // The default constructor and the constructor taking a raw pointer 
    // need not worry about the ref_counter member - this is default initialized
    // and that default initalization does what we want.
    Smart_Ptr(): raw_ptr(0) {}
    Smart_Ptr(T* other_raw): raw_ptr(other_raw) {}
    // The compiler-defined shallow copy is what we want, due to the design of 
    // the size_Ptr class. However, in order to obey the rule of three, we 
    // define this shallow copy constructor
    Smart_Ptr(const Smart_Ptr&);

    // When the Smart_Ptr destructor is finished running, it will run the 
    // destructor for ref_counter; this will conditionally free the memory where 
    // ref_counter (or rather its raw_s_ptr member) points. 
    ~Smart_Ptr() { if (ref_count() == 1) delete raw_ptr; }


    Smart_Ptr& operator=(const Smart_Ptr&);
    T& operator*() const;
    T* operator->() const;
    operator bool() const { return raw_ptr; }


    std::size_t ref_count() const { return ref_counter.pointee_val(); }
    void make_unique();

private:
    T* raw_ptr;
    size_Ptr ref_counter;    
};

// End Smart_Ptr class main body -----------------------------------------------

// Begin definitions of Smart_Ptr class methods --------------------------------

template <typename T>
Smart_Ptr<T>::Smart_Ptr(const Smart_Ptr& o): raw_ptr(o.raw_ptr), 
    ref_counter(o.ref_counter) 
{}


template <typename T>
Smart_Ptr<T>& Smart_Ptr<T>::operator=(const Smart_Ptr& rhs)
{
    std::size_t original_lhs_ref_count = ref_count();
    std::size_t original_rhs_ref_count = rhs.ref_count();

    ref_counter = rhs.ref_counter; // this updates the count automatically

    // if self-assignment has not occured and the assignment has lowered the
    // reference count to zero
    if (original_lhs_ref_count == 1 && ref_count() > original_rhs_ref_count) 
        delete raw_ptr;

    raw_ptr = rhs.raw_ptr;

    return *this;
}


template <typename T>
T& Smart_Ptr<T>::operator*() const 
{
    if (raw_ptr)
        return *raw_ptr;
    throw std::runtime_error("cannot dereference unbound Smart_Ptr");
}

template <typename T>
T* Smart_Ptr<T>::operator->() const 
{
    if (raw_ptr)
        return raw_ptr;
    throw std::runtime_error("unbound Smart_Ptr");
}

template <typename T>
void Smart_Ptr<T>::make_unique()
{
    if (ref_count() != 1)
    { 
        raw_ptr = clone(raw_ptr);

        // construct a size_Ptr object from a size_t* and assigns it to 
        // ref_counter (the assignment increments the pointee from 0 to 1).
        ref_counter = new std::size_t(0);
    }
}

// End definitions of Smart_Ptr class methods ----------------------------------

// End Smart_Ptr class =========================================================



#endif