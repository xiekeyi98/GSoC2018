#include<bits/stdc++.h>
using namespace std ;
const int maxn = 100000 + 20 ;
const int INFINITE = 0 ;

struct node
{
	int lazytag ;
	int value ;
}segtree[ 4 * maxn ] ; 

// update a node whose children are updated 
inline void pushup( int root )
{
	segtree[root].value = max( segtree[root*2].value , segtree[root*2+1].value ) ;
}

// update the node when query it  
inline void pushdown( int root ) 
{
	if( segtree[root].lazytag )
	{
		segtree[root*2].lazytag = segtree[root].lazytag;
		segtree[root*2+1].lazytag = segtree[root].lazytag ;

		segtree[root*2].value += segtree[root].lazytag ;
		segtree[root*2+1].value += segtree[root].lazytag ;

		segtree[root].lazytag = 0 ;
	}

}

void build( int root , int a[],  int nstart , int nend )
{
	segtree[root].lazytag = 0;
	if( nstart == nend )
	{
		segtree[root].value = a[nstart] ; 
		return ;
	}


	int mid = ( nstart + nend ) / 2 ;

	build( root * 2 , a , nstart , mid );
	build( root * 2 + 1 , a,mid + 1 , nend );

	pushup(root);
}


void update( int root , int nstart , int nend , int ustart , int uend , int newmark )
{

	if( nstart > uend || nend < ustart )
		return ; 

	if( nstart >= ustart && nend <= uend )
	{
		segtree[root].value += newmark ;
		segtree[root].lazytag = newmark;
		return ; 
	}

	pushdown( root ) ;

	int mid = ( nstart + nend ) / 2 ;

	update( root * 2 , nstart , mid , ustart , uend , newmark ) ;
	update( root * 2 + 1 , mid + 1 , nend , ustart , uend , newmark ) ;

	pushup(root);
}


int query( int root , int nstart , int nend ,int qstart , int qend ) 
{
	if( nstart > qstart || nend < qstart )
		return INFINITE ;
	if( nstart >= qstart && nend <= qend )
		return segtree[root].value ;

	pushdown(root); 

	int mid = ( nstart + nend ) / 2 ;

	int ans = query( root * 2 , nstart , mid , qstart , qend ) +
		query( root * 2 + 1 , mid + 1 , nend ,qstart , qend );

	pushup(root);

	return ans ; 
}


// TEST ;
int main()
{

	int t ;
	scanf("%d",&t);
	int kase = 0 ;
	while(t--)
	{
		memset( segtree , 0 , sizeof(segtree) ) ; 
		int n ;
		scanf("%d",&n);

		//build( 1 , 1 , n ) ;

		int q ;
		scanf("%d",&q);

		while(q--)
		{
			int x , y , z ;
			scanf("%d%d%d",&x,&y,&z);
			update( 1 , 1 , n ,  x , y , z ) ;

		}

		printf( "Case %d: The total value of the hook is %d.\n" , ++kase , query( 1 , 1 , n , 1 , n ) ) ; 
	}

	return 0 ; 
}

