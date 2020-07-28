// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADADIGIT/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
const int MAXN = 31625;
ll N;
ll soma1,soma2;
vector<int> V;
vector<ii> fatores;
vector<int> primos;
int crivo[MAXN];
ii mostdivisors,biggestsum;
void tryit(){
	fatores.clear();soma1 = 0;soma2 = 0;
	int x = 0,pot10 = 1;
	for(int i = 0;i<N;i++){
		x += V[i]*pot10;
		pot10 *= 10;
	}
	if(x == 0) return;
	if(x == 1){
		mostdivisors = max(mostdivisors, ii(1,-1) );
		biggestsum = max(biggestsum, ii(1,-1) );
		return;
	}
	int copia = x;
	for(int i : primos){
		if(i * i > x || copia == 1) break;
		if(copia % i == 0){
			fatores.push_back(ii(i,0));
			while(copia % i == 0){
				fatores.back().second++;
				copia = copia/i;
			}
		}
	}
	if(copia != 1) fatores.push_back(ii(copia,1));
	soma1 = 1LL;
	soma2 = 1LL;
	for(int i = 0;i<fatores.size();i++){
		ll fator = fatores[i].first;
		ll qtd = fatores[i].second;
		ll tot = 0;
		ll pot = 1LL;
		for(int j = 0;j<=qtd;j++){
			tot += pot;
			pot *= fator;
		}
		soma2 *= tot;
		soma1 = soma1*(1LL + qtd);
	}
	mostdivisors = max(mostdivisors, ii(soma1,-x) );
	biggestsum = max(biggestsum, ii(soma2,-x) );
}
int main(){
	for(int i = 2;i<MAXN;i++){
		if(!crivo[i]){
			primos.push_back(i);
			for(int j = 2*i;j<MAXN;j+=i) crivo[j] = 1;
		}
	}
	scanf("%lld",&N);
	for(int i = 1;i<=N;i++){
		int x;
		scanf("%d",&x);
		V.push_back(x);
	}
	sort(V.begin(),V.end());
	tryit();
	do{
		tryit();
	}while(next_permutation(V.begin(),V.end()));
	printf("%lld %lld\n",-mostdivisors.second,-biggestsum.second);
	return 0;
} 