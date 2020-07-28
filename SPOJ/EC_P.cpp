// Ivan Carvalho
// Solution to https://www.spoj.com/problems/EC_P/
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int MAXN = 1010;
typedef pair<int,int> ii;
vector<int> grafo[MAXN];
vector<ii> pontes;
map<int,int> mapa[MAXN];
int num[MAXN],low[MAXN],n,m,TC,counter;
void dfs(int v,int p){
	num[v] = low[v] = ++counter;
	for(int u : grafo[v]){
		if(u == p) continue;
		if(num[u] == 0){
			dfs(u,v);
			if(low[u] > num[v] && mapa[u][v] == 1){
				pontes.push_back(ii(min(v,u),max(v,u)));
			}
			low[v] = min(low[v],low[u]);
		}
		else{
			low[v] = min(low[v],num[u]);
		}
	}
}
int main(){
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	cin >> TC;
	for(int tc = 1;tc<=TC;tc++){
		cin >> n >> m;
		counter = 0;
		for(int i = 1;i<=n;i++){
			grafo[i].clear();
			num[i] = low[i] = 0;
			mapa[i].clear();
		}
		pontes.clear();
		for(int i = 1;i<=m;i++){
			int u,v;
			cin >> u >> v;
			grafo[u].push_back(v);
			grafo[v].push_back(u);
			mapa[u][v]++;
			mapa[v][u]++;
		}
		for(int i = 1;i<=n;i++){
			if(num[i] == 0) dfs(i,-1);
		}
		//cout << "Foi" << endl;
		cout << "Caso #" << tc << endl;
		sort(pontes.begin(),pontes.end());
		if(pontes.empty()){
			cout << "Sin bloqueos" << endl;
		}
		else{
			cout << pontes.size() << endl;
		}
		for(ii par : pontes){
			cout << par.first << " " << par.second << endl;
		}
	}
	return 0;
} 