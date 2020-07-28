// Ivan Carvalho
// Solution to https://dmoj.ca/problem/boi2011p5
#include <bits/stdc++.h>
using namespace std;

typedef tuple<int,int,int> trinca;
typedef tuple<double,int,int,int,int> aresta;
typedef tuple<int,int,int,int> quadra;
typedef pair<int,int> ii;

const int MAXN = 210;
const double INF = 1e16;
const double EPS = 1e-6;

map<quadra,ii> valido;
vector<trinca> grafo[MAXN];
int processado[MAXN],N,M,tem_que_exbir;
int matA[MAXN][MAXN],matB[MAXN][MAXN];
vector<quadra> pares;

int Prim(double alpha,int minimiza_b){

	pares.clear();
	priority_queue<aresta, vector<aresta>, greater<aresta> > pq;

	int s1 = 0,s2 = 0;

	for(int i = 0;i<N;i++){
		processado[i] = 0;
	}

	pq.push({0.0,0,0,0,-1});
	while(!pq.empty()){
		aresta davez = pq.top();
		pq.pop();
		int c1 = get<1>(davez),c2 = get<2>(davez);
		int v = get<3>(davez),p = get<4>(davez);
		if(processado[v]) continue;
		processado[v] = 1;
		s1 += c1;
		s2 += c2;
		if(minimiza_b) swap(c1,c2);
		if(p != -1) pares.push_back({min(p,v),max(p,v),c1,c2});
		for(trinca nxt : grafo[v]){
			int u = get<0>(nxt),l1 = get<1>(nxt),l2 = get<2>(nxt);
			if(minimiza_b) swap(l1,l2);
			if(processado[u]) continue;
			pq.push({alpha*l1 + (1.0 - alpha)*l2,l1,l2,u,v});
		}
	}

	return s1*s2;

}

int checa(double alpha){
	return min(Prim(alpha,0),Prim(1.0 - alpha,1));
}

int main(){

	cin >> N >> M;
	for(int i = 1;i<=M;i++){
		int u,v,w1,w2;
		cin >> u >> v >> w1 >> w2;
		grafo[u].push_back({v,w1,w2});
		grafo[v].push_back({u,w1,w2});
		valido[{min(u,v),max(u,v),w1,w2}] = {u,v};
	}

	double ini = 0.0,fim = 1.0;
	while(fim - ini > EPS){
		double m1 = ini + (fim - ini)/3.0;
		double m2 = fim - (fim - ini)/3.0;
		if(checa(m1) < checa(m2)){
			fim = m2 - EPS;
		}
		else{
			ini = m1 + EPS;
		}
	}

	if(Prim(ini,0) < Prim(1.0 - ini,1)){
		Prim(ini,0);
		int s1 = 0,s2 = 0;
		sort(pares.begin(),pares.end());
		for(quadra davez : pares){
			s1 += get<2>(davez);
			s2 += get<3>(davez);
		}
		printf("%d %d\n",s1,s2);
		for(quadra davez : pares){
			printf("%d %d\n",valido[davez].first,valido[davez].second);
		}
	}
	else{
		Prim(1.0 - ini,1);
		int s1 = 0,s2 = 0;
		sort(pares.begin(),pares.end());
		for(quadra davez : pares){
			s1 += get<2>(davez);
			s2 += get<3>(davez);
		}
		printf("%d %d\n",s1,s2);
		for(quadra davez : pares){
			printf("%d %d\n",valido[davez].first,valido[davez].second);
		} 
	}

	return 0;
}
