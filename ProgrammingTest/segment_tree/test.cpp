#include<bits/stdc++.h>
#include"segment_tree.hpp"
using namespace std ;
using namespace st ;

int main()
{
	vector<int> a;
	for( int i = 0 ; i < 10 ; i++)
	{
		a.push_back(i);
	}
	segment_tree<int> st;
	st.build( a, 0 , 0 , 9) ;
	cout << st.query( 0 , 0 , 0 ) << endl ;
	cout << st.query( 0 , 1 , 1 ) << endl ;
	cout << st.query( 0 , 0 , 9)  << endl ;
	cout << st.query( 0 , 8 , 9) << endl ; 
	cout << st.query( 0 , 1 , 5 ) << endl ;
	st.modify( 0 , 1 , 5, 100 ) ;
	cout << st.query( 0 , 1 , 5 ) << endl ;
	st.modify( 0 , 1 , 5 , -10 );
	st.modify( 0 , 0 , 9 , 1 ) ;
	cout << st.query( 0 , 0 , 9 ) << endl ;

	cout << st.query( 0 , 5 , 1 ) << endl ; 


	return  0;
}

