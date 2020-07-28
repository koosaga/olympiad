// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg18g6
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
const int MAXN = 1e5 + 10;
vector<ii> grafo[4*MAXN],classe[MAXN];
ll N,C,K,valor[MAXN],ponteiro,distancia[4*MAXN],processado[4*MAXN];
int main(){
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	cin >> N >> C >> K;
	for(int i = 1;i<=N;i++){
		cin >> valor[i];
		distancia[i] = -1;
	}
	for(int i = 1;i<=N;i++){
		ll qtd;
		cin >> qtd;
		while(qtd--){
			ll x;
			cin >> x;
			classe[x].push_back(ii(valor[i],i));
		}
	}
	ponteiro = N;
	for(int numero = 1;numero<=C;numero++){
		ll qtd = classe[numero].size();
		sort(classe[numero].begin(),classe[numero].end());
		for(ll vertice = ponteiro+1;vertice < ponteiro + qtd;vertice++){
			ll x = classe[numero][vertice - ponteiro - 1].second;
			ll y = classe[numero][vertice - ponteiro].second;
			ll diferenca = abs(valor[y] - valor[x]);
			grafo[vertice].push_back(ii(vertice+1,diferenca));
			grafo[vertice+1].push_back(ii(vertice,diferenca));
		}
		for(ll vertice = ponteiro + 1;vertice<=ponteiro+qtd;vertice++){
			ll x = classe[numero][vertice - ponteiro - 1].second;
			grafo[x].push_back(ii(vertice,0));
			grafo[vertice].push_back(ii(x,K));
		}
		ponteiro += qtd;
	}
	priority_queue<ii, vector<ii>, greater<ii> > pq;
	pq.push(ii(0,1));
	while(!pq.empty()){
		ii davez = pq.top();
		pq.pop();
		ll v = davez.second, d = davez.first;
		if(processado[v]) continue;
		processado[v] = 1;
		distancia[v] = d;
		for(ii aresta : grafo[v]){
			ll u = aresta.first,w = aresta.second;
			if(!processado[u]) pq.push(ii(d+w,u));
		}
	}
	for(int i = 1;i<=N;i++) cout << distancia[i] << endl;
	return 0;
}
