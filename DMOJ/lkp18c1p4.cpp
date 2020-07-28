// Ivan Carvalho
// Solution to https://dmoj.ca/problem/lkp18c1p4
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,int> ii;

const int MAXN = 1e5 + 10;
const int MAXM = 2*1e5 + 10;

vector<int> grafo[MAXN];
int e1[MAXM],e2[MAXM],e3[MAXM],processado[MAXN],N,M,A,B;
ll C;

int checa(int X){

	for(int i = 1;i<=N;i++) processado[i] = 0;

	priority_queue<ii, vector<ii>, greater<ii> > pq;
	pq.push(ii(0,A)); 
	while(!pq.empty()){
		ll dist = pq.top().first;
		int v = pq.top().second;
		pq.pop();
		if(v == B){
			return dist <= C;
		}
		if(processado[v]) continue;
		processado[v] = 1;
		for(int idx : grafo[v]){
			int u = (e1[idx] != v) ? (e1[idx]) : (e2[idx]);
			ll w = e3[idx];
			if(idx > X) continue;
			pq.push(ii(dist+w,u));
		}
	}

	return 0;

}

int main(){

	scanf("%d %d",&N,&M);
	for(int i = 1;i<=M;i++){
		scanf("%d %d %d",&e1[i],&e2[i],&e3[i]);
		grafo[e1[i]].push_back(i);
		grafo[e2[i]].push_back(i);
	}
	scanf("%d %d %lld",&A,&B,&C);

	int ini = 1,fim = M,meio,resp = -1;
	while(ini <= fim){
		meio = (ini+fim)/2;
		if(checa(meio)){
			resp = meio;
			fim = meio - 1;
		}
		else{
			ini = meio + 1;
		}
	}
	printf("%d\n",resp);

	return 0;

}
