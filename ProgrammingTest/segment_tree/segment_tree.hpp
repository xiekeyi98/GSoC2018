#ifndef segment_tree_hpp
#define segment_tree_hpp
#include<memory>
#include<vector>
#include<algorithm>
#ifdef DEBUG
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std ;
#endif // DEBUG 
namespace st
{
	template<typename T> struct node
	{
		T value;
		int l , r ; 
		T lazytag; 
	};
	template <typename T> class segment_tree
	{
		public:
			segment_tree() {};
			~segment_tree(){};
			void build( std::vector<T> const & a , int root , int l , int r );
			T query( int root , int l , int r ) ;
			void modify( int root , int l , int r , T newmark ) ;
		private:
			std::vector< node<T> > segtree ; 
			bool uninit= true ; 
			int INFINITE = -0x7fffffff; 
			inline int left_child(int root) const { return root * 2 + 1 ; };
			inline int right_child(int root)const { return root * 2 + 2 ; } ; 
			void pushup( int root )
			{
				segtree[root].value = 
					std::max( segtree[left_child(root)].value , segtree[right_child(root)].value);
				segtree[root].l = segtree[left_child(root)].l;
				segtree[root].r = segtree[right_child(root)].r;
			}

			void pushdown( int root )
			{
				if( segtree[root].lazytag )
				{
					segtree[left_child(root)].lazytag = segtree[root].lazytag;
					segtree[left_child(root)].value = segtree[root].lazytag ;
					segtree[right_child(root)].lazytag = segtree[root].lazytag;
					segtree[right_child(root)].value = segtree[root].lazytag ;
					segtree[root].lazytag = 0 ; 
				}

			}
	};
	template<typename T > 
		void segment_tree<T>::build( std::vector<T> const &a , int root , int l , int r )  
		{
			if( l > r )
				throw "sorry,l must not more than r " ; 
			if( uninit )
			{
				segtree.resize( 4 * ( r - l ) ) ;
				uninit = false ;
			}

			if( !uninit )
			{
				if( l == r )
				{
					segtree[root].value = l ;
					segtree[root].lazytag = 0 ;
					segtree[root].l = l , segtree[root].r = r ; 
					return ;
				}

				else
				{
					segtree[root].lazytag = 0 ; 
					int mid = ( l + r ) / 2 ; 
					build( a , left_child(root) , l , mid ) ;
					build( a , right_child(root) , mid + 1 , r ) ; 
					pushup(root);
				}
			}
		}

	template<typename T>
		T segment_tree<T>::query( int root , int l , int r )
		{
			if( l > r )
				std::swap( l , r ) ; 

			if( segtree[root].l >= l && segtree[root].r <= r )
				return segtree[root].value;
			else if( segtree[root].l > r || segtree[root].r < l )
				return INFINITE ;
			else 
			{
				pushdown(root);
				return std::max( query( left_child(root), l , r) , query(right_child(root), l , r ) ) ;
				pushup(root);
			}
		}
	template<typename T>
		void segment_tree<T>::modify( int root , int l , int r , T newmark)
		{
			if( l > r )
				std::swap(l,r);
			if( segtree[root].l >= l && segtree[root].r <= r )
			{
				segtree[root].lazytag = newmark;
				segtree[root].value = newmark;
			}

			else if( segtree[root].l > r || segtree[root].r < l )
				return ;
			else 
			{
				modify( left_child(root) , l , r , newmark ) ;
				modify( right_child(root) , l , r , newmark);
			}
		}
};
#endif //segment_tree_hpp
