// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1884
#include <cstdio>
#include <vector>
#include <algorithm>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
#define MAXN 2001
using namespace std;
typedef long long ll;
const ll INF = 1e9 + 1;
const ll NEG = -INF;
ll X[MAXN],Y[MAXN],recompensa[MAXN];
bool disponivel[MAXN];
vector<int> resta;
bool comp(int x, int y){
	return X[x] > X[y];
}
ll dp[MAXN][MAXN];
ll solve(ll cara, ll k){
	if(dp[cara][k] != -1) return dp[cara][k];
	if(cara == resta.size() - 1){
		if(k != 0) return dp[cara][k] = 0;
		return dp[cara][k] = X[resta[cara]];
	}
	ll minimo = max(solve(cara+1,k) - recompensa[resta[cara]],X[resta[cara]]);
	if(k != 0) minimo = min(minimo,solve(cara+1,k-1));
	return dp[cara][k] = minimo;
}
int main(){
	int TC;
	getint(TC);
	while(TC--){
		resta.clear();
		int n,k,jafoi = 0,templife;
		ll life;
		getint(n);
		getint(templife);
		getint(k);
		life = ll(templife);
		for(int i=1;i<=n;i++){
			int tempx,tempy;
			getint(tempx);
			getint(tempy);
			X[i] = ll(tempx);
			Y[i] = ll(tempy);
			disponivel[i] = true;
			recompensa[i] = Y[i] - X[i];
		}
		while(jafoi != n){
			int escolhido = -1;
			ll maior_recompensa = NEG;
			for(int i=1;i<=n;i++){
				if(!disponivel[i]) continue;
				if(life >= X[i] && recompensa[i] > maior_recompensa){
					escolhido = i;
					maior_recompensa = recompensa[i];
				}
			}
			if(maior_recompensa >= 0){
				jafoi++;
				life += recompensa[escolhido];
				disponivel[escolhido] = false;
				continue;
			}
			else break;
		}
		if(jafoi == n){
			printf("Y\n");
			continue;
		}
		for(int i=1;i<=n;i++){
			if(disponivel[i]) resta.push_back(i);
		}
		sort(resta.begin(),resta.end(),comp);
		for(int i=0;i < resta.size();i++){
			for(int j=0;j<=k;j++){
				dp[i][j] = -1;
			}
		}
		if(life > solve(0,k)) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}
