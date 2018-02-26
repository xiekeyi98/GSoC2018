# Demo
This is a folder which saved the draft . **This is for your reference only.**


# segment\_tree

## test.cpp

An easy test for serious mistakes. Many latent faults can not be found by this cpp.
This cpp is just used to check mistakes such as grammar ans so on.  

## segment\_tree.hpp

**Implementation of the segment_tree.** 

### struct node

An node for the tree.

### basic\_operator 

An virtual base class for generic.

### Max

Inherit from the basic\_operator. 

template< typename T > class Max.
T is a type of the elements.

This class is used to solve interval maximum value.

### Min
Inherit from the basic\_operator.

template< typename T > class Min.
T is a type of the elements. 

This class is used to solve interval minimum value.

### Plus
Inherit from the basic\_operator.

template< typename T > class Plus.
T is a type of the elements.

This class is uesd to solve interval sum.


### segment\_tree

template< typename T1 , typename T2 >
	class segment_tree ;

T1 is type of the elements.

T2 is an class such as Max , Min , Plus. 


#### void build( std::vector< T1 > , int l , int r ) :

build the tree , the interval is l to r ( left and right closed ) .

#### T1 query( int l , int r ) :

return the interval( [l,r] ) value. Max , min or sum depends on the T2 .

#### void modify( int l , int r , T1 newmark) :

make the interval( [l,r] ) all add the newmark .

# TODO
1. Unit test.
2. INFINITE num is dissatisfactory.
