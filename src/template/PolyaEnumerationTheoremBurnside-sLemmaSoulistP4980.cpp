#include<bits/stdc++.h>
using namespace std ;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 1e9 + 7 ; 
int T, n ; 
int fpow( int x, int k ) {
	int ans = 1, base = x ; 
	while( k ) {
		if( k & 1 ) ans = 1ll * ans * base % P ; 
		base = base * base % P, k >>= 1 ; 
	} return ans ; 
}
int phi( int x ) {
	int ans = x ; 
	for( re int i = 2; i <= sqrt(x); ++ i ) {
		if( x % i ) continue ;
		ans = ans - ans / i ;
		while( x % i == 0 ) x /= i ;
	}
	if( x != 1 ) ans = ans - ans / x ;
	return ans ; 
}
void inc( int &x, int y ) {
	( ( x += y ) >= P ) && ( x -= P ) ;
}
signed main()
{
	int T = gi() ; 
	while( T-- ) {
		int n = gi(), cnt = sqrt(n), Ans = 0 ; 
		for( re int i = 1; i <= cnt; ++ i ) {
			if( n % i ) continue ;
			int p1 = phi(i), f1 = fpow( n, n / i ) ; 
			f1 = f1 * p1 % P, inc( Ans, f1 ) ;
			if( i * i != n ) {
				int p2 = phi( n / i ), f2 = fpow( n, i ) ;
				f2 = f2 * p2 % P, inc( Ans, f2 ) ;
			}
		}
		cout << Ans * fpow( n, P - 2 ) % P << endl ; 
	}
	return 0 ;
}
