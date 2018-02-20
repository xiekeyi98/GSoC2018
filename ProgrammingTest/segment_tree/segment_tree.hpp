#ifndef segment_tree_hpp
#define segment_tree_hpp
#include<memory>
#include<vector>
#include<algorithm>

#ifdef DEBUG
using namespace std ;
#endif // DEBUG 
namespace st
{
	static double INFINITE = 0xFFFFFFFFFFFFFFFF;
	template<typename T> struct node
	{
		T value;
		int l , r ; 
		T lazytag; 
		bool _lazytag = false; 
	};

	template< typename T  > 
		class basic_operator
		{
			public:
				virtual void pushup( std::vector<T> &segtree , int root ) = 0 ;
				// 1 is to make a segment to be the number ;
				// 2 is to make a segment to add the number; TODO 2 is unnecessary;
				virtual void pushdown1( std::vector<T> &segtree,int root ) = 0 ; 
				//virtual void pushdown2( std::vector<T> &segtree,int root ) = 0 ; 
			protected:
				int left_child( int root ) const { return root * 2 + 1 ; } ;
				int right_child(int root ) const { return root * 2 + 2 ; } ; 
		};

	template< typename T > 
		class Max: public basic_operator<T> 
	{
		public:
			T operator() ( const T &a , const T &b ) const 
			{ 
				if( a!= INFINITE && b != INFINITE )
					return std::max(a,b);
				else if( a == INFINITE && b != INFINITE )
					return b ;
				else if( a != INFINITE && b == INFINITE )
					return a ;
				else if( a == INFINITE && b == INFINITE )
					throw " two INFINITE! " ; 
			}

			void pushup( std::vector<node<T>> &segtree , int root ) 
			{
				segtree[root].value = 
					Max( segtree[this->left_child(root)].value , segtree[this->right_child(root)].value);
				segtree[root].l = segtree[this->left_child(root)].l;
				segtree[root].r = segtree[this->right_child(root)].r;
			}

			void pushdown1(std::vector<node<T>> &segtree , int root ) 
			{
				if( segtree[root]._lazytag)
				{
					segtree[this->left_child(root)].lazytag = segtree[root].lazytag;
					segtree[this->left_child(root)].value = segtree[root].lazytag ;
					segtree[this->right_child(root)].lazytag = segtree[root].lazytag;
					segtree[this->right_child(root)].value = segtree[root].lazytag ;
					segtree[root]._lazytag = false; 
					segtree[root].lazytag = 0 ; 
					// 0 is not a good INFINITE number , but I don't know what to do better .  
				}
			}

			void pushdown2(std::vector<node<T>> &segtree , int root ) 
			{
				if( segtree[root]._lazytag)
				{
					segtree[this->left_child(root)].lazytag += segtree[root].lazytag;
					segtree[this->left_child(root)].value += segtree[root].lazytag ;
					segtree[this->right_child(root)].lazytag += segtree[root].lazytag;
					segtree[this->right_child(root)].value += segtree[root].lazytag ;
					segtree[root]._lazytag = false; 
					segtree[root].lazytag = 0 ; 
				}
			}
	};

	template< typename T > 
		class Min: public basic_operator<T> 
	{
		public:
			T operator() ( const T &a , const T &b ) const 
			{ 
				if( a!= INFINITE && b != INFINITE )
					return std::min(a,b);
				else if( a == INFINITE && b != INFINITE )
					return b ;
				else if( a != INFINITE && b == INFINITE )
					return a ;
				else if( a == INFINITE && b == INFINITE )
					throw " two INFINITE! " ; 
			}
			void pushup( std::vector<node<T>> &segtree , int root ) 
			{
				segtree[root].value = 
					Min( segtree[this->left_child(root)].value , 
							segtree[this->right_child(root)].value);
				segtree[root].l = segtree[this->left_child(root)].l;
				segtree[root].r = segtree[this->right_child(root)].r;
			}

			void pushdown1(std::vector<node<T>> &segtree , int root ) 
			{
				if( segtree[root]._lazytag)
				{
					segtree[this->left_child(root)].lazytag = segtree[root].lazytag;
					segtree[this->left_child(root)].value = segtree[root].lazytag ;
					segtree[this->right_child(root)].lazytag = segtree[root].lazytag;
					segtree[this->right_child(root)].value = segtree[root].lazytag ;
					segtree[root]._lazytag = false; 
					segtree[root].lazytag = 0 ; 
				}
			}

			void pushdown2(std::vector<node<T>> &segtree , int root ) 
			{
				if( segtree[root]._lazytag)
				{
					segtree[this->left_child(root)].lazytag += segtree[root].lazytag;
					segtree[this->left_child(root)].value += segtree[root].lazytag ;
					segtree[this->right_child(root)].lazytag += segtree[root].lazytag;
					segtree[this->right_child(root)].value += segtree[root].lazytag ;
					segtree[root]._lazytag = false; 
					segtree[root].lazytag = 0 ; 
				}
			}
	};

	template< typename T > 
		class Plus: public basic_operator<T> 
	{
		public:
			T operator() ( const T &a , const T &b ) const 
			{
				if( a!= INFINITE && b != INFINITE )
					return a+b;
				else if( a == INFINITE && b != INFINITE )
					return b ;
				else if( a != INFINITE && b == INFINITE )
					return a ;
				else if( a == INFINITE && b == INFINITE )
					throw " two INFINITE! " ; 
			}
			void pushup( std::vector<node<T>> &segtree , int root ) 
			{
				segtree[root].value = 
					Plus( segtree[this->left_child(root)].value , 
							segtree[this->right_child(root)].value);
				segtree[root].l = segtree[this->left_child(root)].l;
				segtree[root].r = segtree[this->right_child(root)].r;
			}

			void pushdown1(std::vector<node<T>> &segtree , int root ) 
			{
				if( segtree[root]._lazytag)
				{
					segtree[this->left_child(root)].lazytag = segtree[root].lazytag;
					// solve the closed interval ;
					segtree[this->left_child(root)].value = 
						segtree[root].lazytag * 
						(segtree[this->left_child(root)].r - 
						 segtree[this->left_child(root)].l + 1 ) ;
					segtree[this->right_child(root)].lazytag = segtree[root].lazytag;
					segtree[this->right_child(root)].value =
						segtree[root].lazytag * 
						(segtree[this->right_child(root)].r - 
						 segtree[this->right_child(root)].l + 1 ) ;
					segtree[root]._lazytag = false; 
					segtree[root].lazytag = 0 ; 
				}
			}

			void pushdown2(std::vector<node<T>> &segtree , int root ) 
			{
				if( segtree[root]._lazytag)
				{
					segtree[this->left_child(root)].lazytag += segtree[root].lazytag;
					segtree[this->left_child(root)].value += 
						segtree[root].lazytag * 
						(segtree[this->left_child(root)].r - 
						 segtree[this->left_child(root)].l + 1 ) ;
					segtree[this->right_child(root)].lazytag += segtree[root].lazytag;
					segtree[this->right_child(root)].value += 
						segtree[root].lazytag * 
						(segtree[this->right_child(root)].r - 
						 segtree[this->right_child(root)].l + 1 ) ;
					segtree[root]._lazytag = false; 
					segtree[root].lazytag = 0 ; 
				}
			}
	};
	template <typename T1 , typename T2 > class segment_tree
	{
		public:
			segment_tree() {};
			~segment_tree(){ segtree.resize(0);}// maybe this is unnecessary?
			void build( std::vector<T1> const & a , basic_operator<T2> _operator , int root , int l , int r );
			T1 query( int l , int r ) { query( 0 , l , r ) ; } ; 
			void modify( int l , int r , T1 newmark ) {  modify( 0 , l , r , newmark ) ; } ;  

		private:
			T1 query( int root , int l , int r ) ;
			void modify( int root , int l , int r , T1 newmark ) ;
			std::vector< node<T1> > segtree ; 
			basic_operator<T2> _operator ; 
			bool uninit= true ; 
			//int INFINITE = -0x7fffffff;  //TODO this is not a good number . 
			//		inline int left_child(int root) const { return root * 2 + 1 ; };
			//		inline int right_child(int root)const { return root * 2 + 2 ; } ; 
			//		void pushup( int root )
			//		{
			//			segtree[root].value = 
			//				std::max( segtree[left_child(root)].value , segtree[right_child(root)].value);
			//			segtree[root].l = segtree[left_child(root)].l;
			//			segtree[root].r = segtree[right_child(root)].r;
			//		}

			//		void pushdown( int root )
			//		{
			//			if( segtree[root].lazytag )
			//			{
			//				segtree[left_child(root)].lazytag = segtree[root].lazytag;
			//				segtree[left_child(root)].value = segtree[root].lazytag ;
			//				segtree[right_child(root)].lazytag = segtree[root].lazytag;
			//				segtree[right_child(root)].value = segtree[root].lazytag ;
			//				segtree[root].lazytag = 0 ; 
			//			}

			//		}
	};
	template<typename T1,typename T2 > 
		void segment_tree<T1,T2>::
		build( std::vector<T1> const &a , basic_operator<T2> _operator ,int root , int l , int r )  
		{
			if( l > r )
				throw "sorry,l must not more than r " ; 
			if( uninit )
			{
				segtree.resize( 4 * ( r - l ) ) ;
				_operator = this->_operator;
				uninit = false ;
			}

			if( !uninit )
			{
				if( l == r )
				{
					segtree[root].value = l ;
					segtree[root].lazytag = 0 ;
					segtree[root]._lazytag = false ; 
					segtree[root].l = l , segtree[root].r = r ; 
					return ;
				}

				else
				{
					segtree[root].lazytag = 0 ; 
					segtree[root]._lazytag = false ; 
					int mid = ( l + r ) / 2 ; 
					build( a , _operator , _operator.left_child(root) , l , mid ) ;
					build( a , _operator , _operator.right_child(root) , mid + 1 , r ) ; 
					_operator.pushup(segtree,root);
					//pushup(root);
				}
			}
		}

	template<typename T1,typename T2 >
		T1 segment_tree<T1,T2>::query( int root , int l , int r )
		{
			if( l > r )
				std::swap( l , r ) ; 
			if( segtree[root].l >= l && segtree[root].r <= r )
				return segtree[root].value;
			else if( segtree[root].l > r || segtree[root].r < l )
				return INFINITE ;
			else 
			{
				//pushdown(root);
				_operator.pushdown1(segtree,root);
				return _operator( query( _operator.left_child(root), l , r) , 
						query(_operator.right_child(root), l , r ));
				//pushup(root);
				_operator.pushup(segtree,root);
			}
		}
	template<typename T1,typename T2>
		void segment_tree<T1,T2>::modify( int root , int l , int r , T1	newmark)
		{
			if( l > r )
				std::swap(l,r);
			if( segtree[root].l >= l && segtree[root].r <= r )
			{
				segtree[root]._lazytag = true ; 
				segtree[root].lazytag = newmark;
				segtree[root].value = newmark;
			}

			else if( segtree[root].l > r || segtree[root].r < l )
				return ;
			else 
			{
				modify( _operator.left_child(root) , l , r , newmark ) ;
				modify( _operator.right_child(root) , l , r , newmark);
			}
		}
};
#endif //segment_tree_hpp
