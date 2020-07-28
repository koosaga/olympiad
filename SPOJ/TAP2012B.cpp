// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2012B/
#include <cstdio>
#include <algorithm>
#define MAXN 10000
using namespace std;
int modos[MAXN+1];
int main(){
	for(int a=1;a <= MAXN;a++){
		for(int b=0;b <= min(a,MAXN/a);b++){
			for(int c=0;c <= min((MAXN - a*b)/(a+b),b);c++){
				int val = a*b+a*c+b*c;
				if(val <= MAXN) modos[val]++;
			}
		}
	}
	int n;
	while(scanf("%d",&n) && n >= 0){
		printf("%d\n",modos[n]);
	}
	return 0;
}