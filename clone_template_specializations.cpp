#include "Smart_Ptr.h"

/*
If you wish to use Smart_Ptr<C> for a class C which does not have a 
clone method, then define the following template specialization

template <>
C* clone(const C* ptr)
{
    return new C(*ptr);
}

*/

























template <>
Vec<char>* clone(const Vec<char>* svc_ptr)
{
    return new Vec<char>(*svc_ptr);
}