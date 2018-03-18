#ifndef segment_tree_hpp
#define segment_tree_hpp
#include<memory>
#include<vector>
#include<algorithm>

namespace st
{
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
				virtual void pushup( std::vector<node<T>> &segtree , int root ) = 0 ;
				virtual void pushdown1( std::vector<node<T>> &segtree,int root ) = 0 ; 
				int left_child( int root ) const { return root * 2 + 1 ; } ;
				int right_child(int root ) const { return root * 2 + 2 ; } ; 
				virtual T newvalue( T newmark , const node<T> &root) const { return newmark ; } ; 
		};

	template< typename T > 
		class Max: public basic_operator<T> 
	{
		public:
			const static int INFINITE = -0x7fffffff;
			T operator() ( const T &a , const T &b ) const 
			{ 
				if( a != INFINITE && b != INFINITE )
					return std::max(a,b) ; 
				else if( a == INFINITE && b != INFINITE )
					return b ;
				else if( a != INFINITE && b == INFINITE )
					return a ;
				else if( a == INFINITE && b == INFINITE )
					throw " two INFINITE! " ; // TODO 
				return INFINITE ; 
			}
			T _Max( const T &a , const T &b ) const 
			{ 
				if( a != INFINITE && b != INFINITE )
					return std::max(a,b) ; 
				else if( a == INFINITE && b != INFINITE )
					return b ;
				else if( a != INFINITE && b == INFINITE )
					return a ;
				else if( a == INFINITE && b == INFINITE )
					throw " two INFINITE! " ; // TODO 
				return INFINITE ; 
			}

			void pushup( std::vector<node<T>> &segtree , int root ) 
			{
				segtree[root].value = 
					_Max( segtree[this->left_child(root)].value ,
							segtree[this->right_child(root)].value);
				segtree[root].l = segtree[this->left_child(root)].l;
				segtree[root].r = segtree[this->right_child(root)].r;
			}

			void pushdown1(std::vector<node<T>> &segtree , int root ) 
			{
				if( segtree[root]._lazytag && segtree[root].r - segtree[root].l > 1 )
				{
					segtree[this->left_child(root)].lazytag += segtree[root].lazytag;
					segtree[this->left_child(root)].value += segtree[root].lazytag ;
					segtree[this->right_child(root)].lazytag += segtree[root].lazytag;
					segtree[this->right_child(root)].value += segtree[root].lazytag ;
					segtree[root]._lazytag = false; 
					segtree[root].lazytag = 0 ; 
					// TODO 0 is not a good INFINITE number , but I don't know what to do better .  
				}
			}
	};

	template< typename T > 
		class Min: public basic_operator<T> 
	{
		public:
			const static int INFINITE = 0x7fffffff;
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
				return INFINITE ; 
			}
			T _Min( const T &a , const T &b ) const 
			{ 
				if( a!= INFINITE && b != INFINITE )
					return std::min(a,b);
				else if( a == INFINITE && b != INFINITE )
					return b ;
				else if( a != INFINITE && b == INFINITE )
					return a ;
				else if( a == INFINITE && b == INFINITE )
					throw " two INFINITE! " ; 
				return INFINITE ; 
			}
			void pushup( std::vector<node<T>> &segtree , int root ) 
			{
				segtree[root].value = 
					_Min( segtree[this->left_child(root)].value , 
							segtree[this->right_child(root)].value);
				segtree[root].l = segtree[this->left_child(root)].l;
				segtree[root].r = segtree[this->right_child(root)].r;
			}

			void pushdown1(std::vector<node<T>> &segtree , int root ) 
			{
				if( segtree[root]._lazytag && segtree[root].r - segtree[root].r > 1 )
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
			const static int INFINITE = 0 ; 
			T operator() ( const T &a , const T &b ) const 
			{
				if( a!= INFINITE && b != INFINITE )
					return a+b;
				else if( a == INFINITE && b != INFINITE )
					return b ;
				else if( a != INFINITE && b == INFINITE )
					return a ;
				else if( a == INFINITE && b == INFINITE )
					;
				return INFINITE ; 
			}
			T _Plus( const T &a , const T &b ) const 
			{
				if( a!= INFINITE && b != INFINITE )
					return a+b;
				else if( a == INFINITE && b != INFINITE )
					return b ;
				else if( a != INFINITE && b == INFINITE )
					return a ;
				else 
					return INFINITE ; 
			}
			void pushup( std::vector<node<T>> &segtree , int root ) 
			{
				segtree[root].value = 
					_Plus( segtree[this->left_child(root)].value , 
							segtree[this->right_child(root)].value);
				segtree[root].l = segtree[this->left_child(root)].l;
				segtree[root].r = segtree[this->right_child(root)].r;
			}
			void pushdown1(std::vector<node<T>> &segtree , int root ) 
			{
				if( segtree[root]._lazytag && segtree[root].r - segtree[root].l  + 1 >= 1 )
				{
					segtree[this->left_child(root)].lazytag += segtree[root].lazytag;

					// solve the closed interval ;

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

			T newvalue( T newmark , const node<T> &root ) const override
			{
				return newmark*(root.r - root.l + 1 ) ; 
			}

	};
	template <typename T1 , typename T2 > class segment_tree
	{
		public:
			segment_tree() {};
			~segment_tree(){ segtree.resize(0);}// TODO maybe this is unnecessary?
			void build( std::vector<T1> const & a , int l , int r ){ build( a , 0 , l , r ) ; } ;
			T1 query( int l , int r ) { return query( 0 , l , r ) ; } ; 
			void modify1( int l , int r , T1 newmark ) {  modify1( 0 , l , r , newmark ) ; } ;  

		private:
			T1 query( int root , int l , int r ) ;
			void build( std::vector<T1> const & a , int root , int l , int r );
			void modify1( int root , int l , int r , T1 newmark ) ;
			std::vector< node<T1> > segtree ; 
			T2 _operator ; 
			bool uninit= true ; 
	};
	template<typename T1,typename T2 > 
		void segment_tree<T1,T2>::
		build( std::vector<T1> const &a , int root , int l , int r )  
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
					segtree[root]._lazytag = false ; 
					segtree[root].l = l , segtree[root].r = r ; 
					return ;
				}

				else
				{
					segtree[root].lazytag = 0 ; 
					segtree[root]._lazytag = false ; 
					int mid = ( l + r ) / 2 ; 
					build( a , _operator.left_child(root) , l , mid ) ;
					build( a , _operator.right_child(root) , mid + 1 , r ) ; 
					_operator.pushup(segtree,root);
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
				return _operator.INFINITE ;
			else 
			{
				_operator.pushdown1(segtree,root);
				T1 ans = _operator( query( _operator.left_child(root), l , r) , 
						query(_operator.right_child(root), l , r ) ) ;
				_operator.pushup(segtree,root);
				return ans ; 
			}
		}
	template<typename T1,typename T2>
		void segment_tree<T1,T2>::modify1( int root , int l , int r , T1 newmark)
		{
			if( l > r )
				std::swap(l,r);
			if( segtree[root].l >= l && segtree[root].r <= r )
			{
				segtree[root]._lazytag = true ; 
				segtree[root].lazytag += newmark;
				segtree[root].value += _operator.newvalue( newmark , segtree[root] ) ;
				return ; 
			}
			else if( segtree[root].l > r || segtree[root].r < l )
				return ;

			_operator.pushdown1( segtree , root ) ; 

			modify1( _operator.left_child(root) , l , r , newmark ) ;
			modify1( _operator.right_child(root) , l , r , newmark);
			_operator.pushup(segtree,root);
		}
};
#endif //segment_tree_hpp
