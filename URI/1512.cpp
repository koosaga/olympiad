// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1512
#include <cstdio>
#include <algorithm>
using namespace std;
int gcd(int a,int b){
	if(a < b) swap(a,b);
	if(b == 0) return a;
	return gcd(b,a%b);
}
int lcm(int x,int y,int z){
	int w = gcd(x,y);
	long long teste = (long long)x / (long long)w;
	teste *= y;
	if(teste > z) return z+1;
	return (int)teste;
}
int main(){
	int n,a,b;
	while(scanf("%d %d %d",&n,&a,&b) &&(a||b||n)){
		printf("%d\n",(n/a)+(n/b)-(n/lcm(a,b,n)));
	}
	return 0;
}
