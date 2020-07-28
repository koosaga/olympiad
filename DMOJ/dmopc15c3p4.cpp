// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc15c3p4
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 3001;
const ll INF = (ll)1e18;
vector<ll> distancias;
ll matriz[MAXN][MAXN],X[MAXN],Y[MAXN],D[MAXN];
int N,Q,S,processado[MAXN];
inline ll sq(ll x){
	return x*x;
}
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%lld %lld",&X[i],&Y[i]);
	for(int i=1;i<=N;i++){
		for(int j = 1;j<=N;j++){
			matriz[i][j] = sq(X[i] - X[j]) + sq(Y[i] - Y[j]);
		}
	}
	scanf("%d",&S);
	for(int i=1;i<=N;i++) D[i] = matriz[S][i];
	processado[S] = 0;
	while(true){
		int davez = -1;
		ll menor = INF;
		for(int i=1;i<=N;i++){
			if(D[i] < menor && !processado[i]){
				menor = D[i];
				davez = i;
			}
		}
		if(davez == -1) break;
		processado[davez] = 1;
		for(int i=1;i<=N;i++) D[i] = min(D[i], matriz[i][davez] + menor );
	}
	for(int i=1;i<=N;i++){
		distancias.push_back(D[i]);
	}
	sort(distancias.begin(),distancias.end());
	scanf("%d",&Q);
	while(Q--){
		ll t;
		scanf("%lld",&t);
		if(t >= distancias.back()){
			printf("%d\n",N);
			continue;
		}
		int ans = prev(upper_bound(distancias.begin(),distancias.end(),t)) - distancias.begin() + 1;
		printf("%d\n",ans);
	}
	return 0;
}