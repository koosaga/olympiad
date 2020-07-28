// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1026
#include <cstdio>
int main(){
	unsigned int x,y;
	while(scanf("%u %u",&x,&y) != EOF) printf("%u\n",(x^y));
	return 0;
}
