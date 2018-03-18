#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TEST_SEGMENT_TREE 
#include <boost/test/unit_test.hpp>
#include "segment_tree.hpp"
#include<vector>
#include<iostream>
using namespace std ;
using namespace st ; // segment_tree ;
using namespace boost ;
// g++ -std=gnu++11 unit_test.cpp -lboost_unit_test_framework
BOOST_AUTO_TEST_CASE( MAX )
{
	vector<int> a;
	for( int i = 0 ; i < 10 ; i++)
	{
		a.push_back(i);
	}
	segment_tree< int , Max<int> > *st = new segment_tree< int , Max<int> > ; 
	st->build( a , 0 , 9 ) ;
	BOOST_CHECK_MESSAGE( st->query( 0,0 ) == 0 ,   
			"st.query(..) result: " << st->query(0,0) ); // check border zero 
	BOOST_CHECK_MESSAGE( st->query( 0,9 ) == 9 ,   
			"st.query(..) result: " << st->query(0,9) ); // check all segment ; 
	BOOST_CHECK_MESSAGE( st->query(1,5) == 5 ,   
			"st.query(..) result: " << st->query(1,5) ); // check a segment ; 
	st->modify1(1,5,100); // add [1,5] to 100 ; 
	BOOST_CHECK_MESSAGE( st->query(1,5) == 105 ,   
			"st.query(..) result: " << st->query(1,5) ); // check the modify correct; 
	BOOST_CHECK_MESSAGE( st->query(8,8) == 8,   
			"st.query(..) result: " << st->query(8,8) ); // check the not modify node ; 
	BOOST_CHECK_MESSAGE( st->query(6,9) == 9,   
			"st.query(..) result: " << st->query(6,9) ); // check the not modify segment ; 
	st->modify1(1,5,-100); // add [[1,5] to -100 ; 
	BOOST_CHECK_MESSAGE( st->query(0,9) == 9,   
			"st.query(..) result: " << st->query(0,9) ); //; check the modify ;  
	delete st;
}

BOOST_AUTO_TEST_CASE( MIN )
{
	vector<int> a;
	for( int i = 0 ; i < 10 ; i++)
	{
		a.push_back(i);
	}
	segment_tree< int , Min<int> > *st = new segment_tree< int , Min<int> > ; 
	st->build( a , 0 , 9 ) ;
	BOOST_CHECK_MESSAGE( st->query( 0,0 ) == 0 ,   
			"st.query(..) result: " << st->query(0,0) ); // check border zero 
	BOOST_CHECK_MESSAGE( st->query( 0,9 ) == 0 ,   
			"st.query(..) result: " << st->query(0,9) ); // check all segment ; 
	BOOST_CHECK_MESSAGE( st->query(1,5) == 1 ,   
			"st.query(..) result: " << st->query(1,5) ); // check a segment ; 
	st->modify1(1,5,100); // add [1,5] to 100 ; 
	BOOST_CHECK_MESSAGE( st->query(1,5) == 101,   
			"st.query(..) result: " << st->query(1,5) ); // check the modify correct; 
	BOOST_CHECK_MESSAGE( st->query(8,8) == 8,   
			"st.query(..) result: " << st->query(8,8) ); // check the not modify node ; 
	BOOST_CHECK_MESSAGE( st->query(6,9) == 6,   
			"st.query(..) result: " << st->query(6,9) ); // check the not modify segment ; 
	st->modify1(1,5,-200); // add [[1,5] to -100 ; 
	BOOST_CHECK_MESSAGE( st->query(0,9) == -99,   
			"st.query(..) result: " << st->query(0,9) ); //; check the modify ;  
	delete st;
}

BOOST_AUTO_TEST_CASE( PLUS )
{
	vector<int> a;
	for( int i = 0 ; i < 10 ; i++)
	{
		a.push_back(i);
	}
	segment_tree< int , Plus<int> > *st = new segment_tree< int , Plus<int> > ; 
	st->build( a , 0 , 9 ) ;
	BOOST_CHECK_MESSAGE( st->query( 0,0 ) == 0  ,   
			"st.query(..) result: " << st->query(0,0) ); // check border zero 
	BOOST_CHECK_MESSAGE( st->query( 0,9 ) == 45 ,   
			"st.query(..) result: " << st->query(0,9) ); // check all segment ; 
	BOOST_CHECK_MESSAGE( st->query(1,5) == 15 ,   
			"st.query(..) result: " << st->query(1,5) ); // check a segment ; 
	st->modify1(1,5,100); // add [1,5] to 100 ; 
	BOOST_CHECK_MESSAGE( st->query(1,5) == 515,   
			"st.query(..) result: " << st->query(1,5) ); // check the modify correct; 
	BOOST_CHECK_MESSAGE( st->query(8,8) == 8,   
			"st.query(..) result: " << st->query(8,8) ); // check the not modify node ; 
	BOOST_CHECK_MESSAGE( st->query(6,9) == 30 ,   
			"st.query(..) result: " << st->query(6,9) ); // check the not modify segment ; 
	st->modify1(1,5,-100); // add [[1,5] to -100 ; 
	BOOST_CHECK_MESSAGE( st->query(0,9) == 45,   
			"st.query(..) result: " << st->query(0,9) ); //; check the modify ;  
	delete st;
}
