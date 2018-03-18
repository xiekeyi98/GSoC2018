#include<bits/stdc++.h>
#include"segment_tree.hpp"
using namespace std ;
using namespace st ;

int main()
{
	vector<int> a; for( int i = 0 ; i < 10 ; i++)
	{
		a.push_back(i);
	}
	segment_tree< int , Plus<int> > *st = new segment_tree< int , Plus<int> > ; 
	st->build( a , 0 , 9 ) ;
	cout << st->query( 1 , 5 ) << endl ;
	st->modify1( 1 , 5 , 100 ) ; 
	cout << st->query( 1 , 5 ) << endl ; 
//	cout << st.query( 0 , 0 ) << endl ;
//	cout << st.query( 5 , 5 ) << endl ;
//	cout << st.query( 0 , 9 ) << endl ;
//	st.modify1(1,5,100);
//	cout << st.query( 1, 5 ) << endl ;
//	cout << st.query(8,8) << endl ; 
//
//	cout << "*****" << endl ; 
//	segment_tree< int , Min<int> > st2;
//
//	st2.build( a ,0 , 9 ) ; 
//	cout << st2.query( 0 , 0 ) << endl ; 
//	cout << st2.query( 1 , 1 ) << endl ; 
//	cout << st2.query( 0 , 9 ) << endl ; 
//	cout << st2.query( 0 , 0 ) << endl ;
//	cout << st2.query( 5 , 5 ) << endl ;
//	cout << st2.query( 0 , 9 ) << endl ;
//	st2.modify1(0,5,100);
//	cout << st2.query( 0, 5 ) << endl ;
//	cout << st2.query(8,8) << endl ; 
//
//	cout << "*****" << endl ; 
//	segment_tree< int , Plus<int> > st3;
//	st3.build( a , 0 , 9 ) ; 
//	cout << st3.query( 0 , 0 ) << endl ;
//	cout << st3.query( 5 , 5 ) << endl ;
//	cout << st3.query( 0 , 9 ) << endl ;
//	cout << st3.query(1,5) << endl ; 
//	st3.modify1(1,5,100);
//	cout << st3.query( 0, 5 ) << endl ;
//	cout << st3.query(8,8) << endl ; 

	return  0;
}

