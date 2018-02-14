#ifndef segment_tree_hpp
#define segment_tree_hpp

#define DEBUG 

#include<memory>
#ifdef DEBUG
#include<iostream>
using namespace std ;
#endif // DEBUG 
namespace st
{

	template<typename T> struct node
	{
		T value;
		T *left , *right ;
	};
	template <typename T> class segment_tree
	{
		public:
			segment_tree() {} ;
			~segment_tree(){};
#ifdef DEBUG
			void show() const { cout << head.value << endl; } ;
			void input( const T &a ){ head.value = a; }; 
#endif // DEBUG 
		private:
			struct node<T>  head ; 
	};
};
#endif //segment_tree_hpp
