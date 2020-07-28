// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1378
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> ii;
ll X[1010],Y[1010];
ll sq(ll val){return val*val;}
int main(){
	ll n;
	while(scanf("%lld",&n) && n){
		for(int i = 1;i<=n;i++) scanf("%lld %lld",&X[i],&Y[i]);
		int resp = 0;
		for(int i = 1;i<=n;i++){
			vector<ii> truque;
			for(int j=1;j<=n;j++){
				if(i==j) continue;
				ll dist = sq(X[i] - X[j]) + sq(Y[i] - Y[j]);
				truque.push_back(ii(dist,1));
			}
			sort(truque.begin(),truque.end());
			vector<ii> rapido;
			for(int i = 0;i<truque.size();i++){
				if(rapido.empty() || rapido.back().first != truque[i].first){
					rapido.push_back(truque[i]);
				}
				else{
					resp += rapido.back().second;
					rapido.back().second++;
				}
			} 
		}
		printf("%d\n",resp);
	}
	return 0;
}
