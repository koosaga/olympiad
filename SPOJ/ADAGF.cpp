// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAGF/
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;
int gcd(int a,int b){
	if(a < b) swap(a,b);
	if(b == 0) return a;
	return gcd(b,a%b);
}
int main(){
	long long resp = 0;
	int n;
	scanf("%d",&n);
	map<int,int> velho,novo;
	for(int i=1;i<=n;i++){
		novo.clear();
		velho[0]++;
		int x;
		scanf("%d",&x);
		for(map<int,int>::iterator it = velho.begin();it != velho.end();it++){
			int y = (*it).first;
			int qtd = (*it).second;
			int mdc = gcd(x,y);
			resp += 1LL*qtd*mdc;
			novo[mdc] += qtd;
		}
		velho = novo;
	}
	printf("%lld\n",resp);
	return 0;
}