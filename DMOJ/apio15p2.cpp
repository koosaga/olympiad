// Ivan Carvalho
// Solution to https://dmoj.ca/problem/apio15p2
#include <bits/stdc++.h>
#define MT make_tuple
using namespace std;
typedef tuple<int,int,int> trinca;
typedef pair<trinca,int> Ttrinca;
const int MAXN = 30010;
const int BUCKET = 200;
vector<trinca> grafo[MAXN];
queue<trinca> filas[BUCKET];
priority_queue<Ttrinca, vector<Ttrinca> , greater<Ttrinca> > Dijkstra;
int processado[MAXN][BUCKET],N,M,origem,destino;
trinca top(){
	return Dijkstra.top().first;
}
void pop(){
	int peso = Dijkstra.top().second;
	Dijkstra.pop();
	filas[peso].pop();
	if(!filas[peso].empty()) Dijkstra.push(make_pair(filas[peso].front(),peso));
}
void push(int peso,trinca davez){
	if(filas[peso].empty()) Dijkstra.push(make_pair(davez,peso));
	filas[peso].push(davez);
}
bool empty(){
	return Dijkstra.empty();
}
int main(){
	scanf("%d %d",&N,&M);
	for(int i = 0;i<M;i++){
		int B,P;
		scanf("%d %d",&B,&P);
		if(i == 0) origem = B;
		else if(i == 1) destino = B;
		if(P < BUCKET){
			grafo[B].push_back(MT(B,P,0));
		}
		else{
			for(int j = 1;B - j*P >= 0;j++){
				grafo[B].push_back(MT(B - j*P,0,j));
			}
			for(int j = 1;B + j*P < N;j++){
				grafo[B].push_back(MT(B + j*P,0,j));
			}
		}
	}
	priority_queue<trinca, vector<trinca>, greater<trinca> > Dijkstra;
	push(0,MT(0,origem,0));
	while(!empty()){
		trinca davez = top();
		pop();
		int dist = get<0>(davez), v = get<1>(davez), power = get<2>(davez);
		if(processado[v][power] == 1) continue;
		processado[v][power] = 1;
		if(!processado[v][0]){
			push(0,MT(dist,v,0));
		}
		if(power < BUCKET && v - power >= 0){
			if(!processado[v - power][power]) push(1,MT(dist+1,v - power,power));
		}
		if(power < BUCKET && v + power < N){
			if(!processado[v + power][power]) push(1,MT(dist+1,v + power,power));
		}
		if(v == destino){
			printf("%d\n",dist);
			return 0;
		}
		if(power != 0) continue;
		for(trinca nova : grafo[v]){
			int nv = get<0>(nova), npower = get<1>(nova), nadd = get<2>(nova);
			if(v == nv){
				if(processado[v][npower]) continue;
				processado[v][npower] = 1;
				if(npower < BUCKET && v - npower >= 0){
					if(!processado[v - npower][npower]) push(1,MT(dist+1,v - npower,npower));
				}
				if(npower < BUCKET && v + npower < N){
					if(!processado[v + npower][npower]) push(1,MT(dist+1,v + npower,npower));
				}
				continue;
			}
			if(!processado[nv][npower]) push(nadd,MT(dist+nadd,nv,npower));
		}
	}
	printf("-1\n");
	return 0;
}
