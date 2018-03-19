// this code is for my homework in algorithm class.
// Just for my reference.
#include<bits/stdc++.h>
using namespace std ;
typedef unsigned int   ll ; 
const int maxn = 9e5; 
struct node
{
	ll value ;
	ll lazytag = 0  ;
	ll l,r;
	ll lchild = 0 ,rchild = 0 ;
}tree[maxn];
int point = 2 ; 

inline void init( node &a , int l , int r   )
{
	a.value = 0;
	a.lazytag = 0 ;
	a.l = l , a.r = r ;
	a.lchild = 0 , a.rchild = 0 ; 
}

inline void pushdown( node &root , int l , int r )
{
	if( root.lchild == 0 )
	{
		root.lchild = point++;
		init( tree[root.lchild] , root.l , (root.l+root.r)/2 ) ;
	}
	if( root.rchild == 0 )
	{
		root.rchild = point++;
		init( tree[root.rchild] , (root.l+root.r)/2 + 1 , root.r );
	}
	if( root.lazytag ) 
	{
		int mid = ( l + r ) / 2 ; 
		tree[root.lchild].value = root.lazytag * ( mid - l + 1 ) ;   ;
		tree[root.lchild].lazytag = root.lazytag;
		tree[root.rchild].value = root.lazytag * ( r - mid ) ;
		tree[root.rchild].lazytag = root.lazytag;
		root.lazytag = 0 ; 
	}
}


inline void pushup( node &root )
{
	root.value = tree[root.lchild].value + tree[root.rchild].value;
}

void modify( node &root  , int ql , int qr , int newmark)
{
	if( root.l >= ql && root.r <= qr )
	{
		root.value = newmark * ( root.r - root.l + 1 ) ;
		root.lazytag = newmark;
	}
	else if( root.l > qr || root.r < ql )
		return ;
	else
	{
		pushdown( root , root.l , root.r) ; 
		modify( tree[root.lchild] , ql , qr , newmark );
		modify( tree[root.rchild] , ql , qr , newmark ) ; 
		pushup( root ) ; 
	}
}


ll query( node &root , int ql , int qr )
{
	if( root.l >= ql && root.r <= qr )
		return root.value;
	else
	{
		pushdown(root , root.l , root.r);
		ll ans = query( tree[root.lchild] , ql , qr ) + query( tree[root.rchild] , ql , qr ) ;
		pushup(root);
		return ans ; 
	}
}




int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n , m ;
	cin >> n >> m ;
	init( tree[1], 0 , n ) ; 
	for( int i = 1 ; i <= m ; i++)
	{
		int t1,t2;
		cin >> t1 >> t2;
		modify( tree[1], t1 ,t2 , 1 );
	}

	ll ans = n + 1 ;
	ans -= query( tree[1] , 0 , n ) ;
	cout << ans << endl ;
	return 0 ;
}
