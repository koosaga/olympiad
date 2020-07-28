// Ivan Carvalho
// Solution to https://www.spoj.com/problems/COMDIV/
#include <bits/stdc++.h>
using namespace std;
 
const int MAXN = 1e6 + 10;
 
int divisors[MAXN];
 
int gcd(int x,int y){
	if(x < y) swap(x,y);
	if(y == 0) return x;
	return gcd(y,x%y);
}
 
int main(){
 
	for(int i = 1;i<MAXN;i++){
		for(int j = i;j<MAXN;j+=i) divisors[j]++;
	}
 
	int TC;
	scanf("%d",&TC);
 
	while(TC--){
		int a,b;
		scanf("%d %d",&a,&b);
		printf("%d\n",divisors[gcd(a,b)]);
	}
 
	return 0;
} 
