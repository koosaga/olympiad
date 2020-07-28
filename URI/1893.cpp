// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1893
#include <cstdio>
int main() {
	int a,b;
	scanf( "%d%d", &a, &b );
	if( 3 <= b && b <= 96 && b > a ) printf( "crescente\n" );
	else if( 3 <= b && b <= 96 && b < a ) printf( "minguante\n" );
	else if( 0 <= b && b <= 2 ) printf( "nova\n" );	
	else if( 97 <= b && b <= 100 ) printf( "cheia\n" );
	return 0;
}
