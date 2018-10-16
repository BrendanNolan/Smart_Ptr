My Smart_Ptr class is based very loosely on the Ptr class from the book "Accelerated 
C++" by Kenig and Moo. Smart_Ptr differs from Ptr in several ways, most notably that it 
implements reference counting using a pointer-like class (called size_Ptr) which 
manages both the control block's count and the memory allocated for the control 
block. This simplifies most of the methods in the Smart_Ptr class in comparison 
with the methods in the Ptr class; for example, the appropriate copy constructor 
for the Smart_Ptr class is the compiler-defined shallow copy (though in order to 
obey the rule of three, we write the definition of the Smart_Ptr copy 
constructor rather than allowing the compiler to define it silently).