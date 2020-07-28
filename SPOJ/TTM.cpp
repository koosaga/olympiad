// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TTM/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

typedef tuple<int,int,int> trinca;
typedef tuple<int,int,int,int> quadra;
typedef long long ll;

vector<trinca> perguntas[MAXN];
vector<quadra> grafo[MAXN];

ll seg[4*MAXN],lazy[4*MAXN],respostas[MAXN];
int N,M,ptratual,vetor[MAXN],qualno[MAXN],tempoatual,ehpergunta[MAXN];

void build(int pos,int left,int right){
	if(left == right){
		seg[pos] = vetor[left];
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	seg[pos] = seg[2*pos] + seg[2*pos+1];
}

void propagate(int pos, int left,int right){
	if(lazy[pos] == 0) return;
	seg[pos] += (right - left + 1)*lazy[pos];
	if(left != right){
		lazy[2*pos] += lazy[pos];
		lazy[2*pos+1] += lazy[pos];
	}
	lazy[pos] = 0;
	return;
}

void update(int pos,int left,int right,int i,int j,int delta){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return;
	if(left >= i && right <= j){
		lazy[pos] += delta;
		propagate(pos,left,right);
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j,delta);
	update(2*pos+1,mid+1,right,i,j,delta);
	seg[pos] = seg[2*pos] + seg[2*pos+1];
}

ll query(int pos,int left,int right,int i,int j){
	propagate(pos,left,right);
	if(left >= i && right <= j) return seg[pos];
	int mid = (left+right)/2;
	if(j <= mid) return query(2*pos,left,mid,i,j);
	else if(i >= mid + 1) return query(2*pos+1,mid+1,right,i,j);
	else return query(2*pos,left,mid,i,j) + query(2*pos+1,mid+1,right,i,j);
}

void dfs(int v){
	for(trinca davez : perguntas[v]){
		respostas[get<0>(davez)] = query(1,1,N,get<1>(davez),get<2>(davez));
	}
	for(quadra aresta : grafo[v]){
		update(1,1,N,get<1>(aresta),get<2>(aresta),get<3>(aresta));
		dfs(get<0>(aresta));
		update(1,1,N,get<1>(aresta),get<2>(aresta),-get<3>(aresta));
	}
}

int main(){
	scanf("%d %d",&N,&M);
	for(int i = 1;i<=N;i++){
		scanf("%d",&vetor[i]);
	}
	for(int i = 1;i<=M;i++){
		char op;
		scanf(" %c",&op);
		if(op == 'C'){
			tempoatual++;
			qualno[tempoatual] = ++ptratual;
			int l,r,d;
			scanf("%d %d %d",&l,&r,&d);
			grafo[qualno[tempoatual-1]].push_back(make_tuple(qualno[tempoatual],l,r,d));
		}
		else if(op == 'Q'){
			ehpergunta[i] = 1;
			int l,r;
			scanf("%d %d",&l,&r);
			perguntas[qualno[tempoatual]].push_back(make_tuple(i,l,r));
		}
		else if(op == 'H'){
			ehpergunta[i] = 1;
			int l,r,t;
			scanf("%d %d %d",&l,&r,&t);
			perguntas[qualno[t]].push_back(make_tuple(i,l,r));
		}
		else if(op == 'B'){
			int volta;
			scanf("%d",&volta);
			tempoatual = volta;
		}
	}
	build(1,1,N);
	dfs(0);
	for(int i = 1;i<=M;i++) if(ehpergunta[i]) printf("%lld\n",respostas[i]);
	return 0;
}