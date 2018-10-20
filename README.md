# Smart_Ptr: a reference-counted shared pointer class

My Smart_Ptr class is based very loosely on the Ptr class from the book "Accelerated 
C++" by Kenig and Moo. Smart_Ptr differs from Ptr in several ways, most notably that 
it implements reference counting using a pointer-like class (called ctrl_block) which 
manages both the control block's count and the memory allocated for the control 
block. This simplifies most of the methods in the Smart_Ptr class in comparison 
with the methods in the Ptr class; for example, the appropriate copy constructor 
for the Smart_Ptr class is the compiler-defined shallow copy (though in order to 
obey the rule of three, I write the definition of the Smart_Ptr copy 
constructor rather than allowing the compiler to define it silently). Smart_Ptr has 
the same interface as Ptr but almost all of Smart_Ptr's methods are simpler due
to the self-managing ctrl_block class used for reference counting. The only 
method definitions shared between Smart_Ptr and Ptr are the * and -> operators and 
the bool conversion operator; both Ptr and Smart_Ptr also use the same definition
for the global clone function. 

If you wish to use `Smart_Ptr<C>` for a class `C` which does not have a 
clone method, then define the following template specialization

`template <>` <br />
`C* clone(const C* ptr)` <br />
`{` <br />
    `return new C(*ptr);` <br />
`}` <br />