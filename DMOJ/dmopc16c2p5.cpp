// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc16c2p5
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
int N,M,K,segIt,atual;
vector<int> esq,dir,val,raiz,invertido;
deque<ii> janela;
void update(int velho,int novo,int left,int right,int x,int delta){
	if(left == right){
		val[novo] = delta;
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid){
		esq.push_back(0);dir.push_back(0);val.push_back(0);
		esq[novo] = ++segIt;
		dir[novo] = dir[velho];
		update(esq[velho],esq[novo],left,mid,x,delta);
	}
	else{
		esq.push_back(0);dir.push_back(0);val.push_back(0);
		esq[novo] = esq[velho];
		dir[novo] = ++segIt;
		update(dir[velho],dir[novo],mid+1,right,x,delta);
	}
	val[novo] = val[esq[novo]] + val[dir[novo]];
}
int main(){
	scanf("%d %d %d",&N,&M,&K);
	esq.push_back(0);dir.push_back(0);val.push_back(0);raiz.push_back(0);invertido.push_back(0);janela.push_back(ii(0,0));
	for(int vez = 1;vez<=M;vez++){
		char op;
		scanf(" %c",&op);
		if(op == 'F'){
			int p;
			scanf("%d",&p);
			raiz.push_back(++segIt);esq.push_back(0);dir.push_back(0);val.push_back(0);invertido.push_back(invertido.back());
			update(raiz[vez-1],raiz[vez],1,N,p,1 ^ invertido[vez]);
		}
		else if(op == 'D'){
			int p;
			scanf("%d",&p);
			raiz.push_back(++segIt);esq.push_back(0);dir.push_back(0);val.push_back(0);invertido.push_back(invertido.back());
			update(raiz[vez-1],raiz[vez],1,N,p,0 ^ invertido[vez]);
		}
		else if(op == 'R'){
			int q;
			scanf("%d",&q);
			raiz.push_back(raiz[q]);
			invertido.push_back(invertido[q]);
		}
		else{
			raiz.push_back(raiz[vez-1]);
			invertido.push_back(invertido[vez-1] ^ 1);
		}
		if(invertido[vez] == 0) atual = val[raiz[vez]];
		else atual = N - val[raiz[vez]];
		if(janela.front().first == vez - K) janela.pop_front();
		ii par = ii(vez,atual);
		while(!janela.empty() && janela.back().second <= par.second) janela.pop_back();
		janela.push_back(par);
		printf("%d %d\n",janela.back().second,janela.front().second);
	}
	return 0;
}