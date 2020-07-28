// Ivan Carvalho
// Solution to https://www.spoj.com/problems/DYNACON2/
// This is solution also works with DYNACON1
#include <bits/stdc++.h>
using namespace std;
 
typedef pair<int,int> ii;
 
struct edge{
	int l,r;
	int u,v;
	
	edge(int _l = 0,int _r = 0,int _u = 0,int _v = 0){
		l = _l;
		r = _r;
		u = _u;
		v = _v;
	}
	
	bool contido(int a,int b)const{
		return a >= l && b <= r;
	}
	
};
 
const int MAXN = 2*1e5 + 10;
 
char entrada[50];
vector<edge> A;
int pai[MAXN],tamanho[MAXN],oldx[MAXN],oldy[MAXN],oldtamx[MAXN],oldtamy[MAXN],ehatualizacao[MAXN],dsuPtr,N,M;
int e1[MAXN],e2[MAXN],e3[MAXN];
map<ii,int> arestas;
 
int find(int x){
	if(x == pai[x]) return x;
	return find(pai[x]);
}
 
void join(int x,int y){
	//printf("Joining %d %d\n",x,y);
	x = find(x);
	y = find(y);
	dsuPtr++;
	if(x == y){
		//printf("Nao juntei %d %d %d\n",x,y,dsuPtr);
		ehatualizacao[dsuPtr] = 0;
		return;
	}
	ehatualizacao[dsuPtr] = 1;
	
	if(tamanho[x] < tamanho[y]) swap(x,y);
	oldx[dsuPtr] = x;
	oldy[dsuPtr] = y;
	oldtamx[dsuPtr] = tamanho[x];
	oldtamy[dsuPtr] = tamanho[y];
	pai[y] = x;
	tamanho[x] += tamanho[y];
	//printf("X %d Y %d DSU %d\n",x,y,dsuPtr);
}
 
void undo(){
	if(!ehatualizacao[dsuPtr]){
		//printf("Ignorei %d\n",dsuPtr);
		dsuPtr--;
		return;
	}
	int x = oldx[dsuPtr];
	int y = oldy[dsuPtr];
	int tx = oldtamx[dsuPtr];
	int ty = oldtamy[dsuPtr];
	//printf("Desfaz X %d Y %d TX %d TY %d DSU %d\n",x,y,tx,ty,dsuPtr);
	dsuPtr--;
	pai[x] = x;
	pai[y] = y;
	tamanho[x] = tx;
	tamanho[y] = ty;
}
 
void adiciona_aresta(int u,int v,int l,int r){
	edge nova(l,r,u,v);
	A.push_back(nova);
}
 
void solve(int left,int right,vector<edge> E){
	
	//printf("Solving L %d R %d\n",left,right);
	
	vector<edge> L,R;
	int adicionadas = 0;
	int mid = left + (right - left)/2;
	
	for(edge davez : E){
		if(davez.contido(left,right)){
			adicionadas++;
			join(davez.u,davez.v);
			//printf("Adicionei L %d R %d U %d V %d\n",davez.l,davez.r,davez.u,davez.v);
		}
		else{
			if(davez.r <= mid){
				L.push_back(davez);
			}
			else if(davez.l >= mid + 1){
				R.push_back(davez);
			}
			else{
				edge p1(davez.l,mid,davez.u,davez.v);
				L.push_back(p1);
				edge p2(mid+1,davez.r,davez.u,davez.v);
				R.push_back(p2);
			}
		}
	}
	
	if(left == right){
		if(e3[left] == -1) e3[left] = -1;
		else e3[left] = (find(e1[left]) == find(e2[left]));
		//return;
	}
	else{
		solve(left,mid,L);
		solve(mid+1,right,R);
	}
	
	for(int i = 1;i<=adicionadas;i++){
		undo();
		//printf("Desfiz %d %d\n",left,right);
	}
	//printf("Finished L %d R %d\n",left,right);
	
}
 
int main(){
	
	scanf("%d %d",&N,&M);
	
	for(int i = 1;i<=N;i++){
		pai[i] = i;
		tamanho[i] = 1;
	}
	
	for(int i = 1;i<=M;i++){
		scanf("%s %d %d",entrada,&e1[i],&e2[i]);
		
		if(entrada[0] == 'a'){
			e3[i] = -1;
			if(e1[i] > e2[i]) swap(e1[i],e2[i]);
			ii novo = ii(e1[i],e2[i]);
			arestas[novo] = i;
		}
		else if(entrada[0] == 'r'){
			e3[i] = -1;
			if(e1[i] > e2[i]) swap(e1[i],e2[i]);
			ii novo = ii(e1[i],e2[i]);
			int ini = arestas[novo];
			int fim = i;
			adiciona_aresta(novo.first,novo.second,ini,fim);
			arestas.erase(novo);
		}
		else{
			continue;
		}
		
	}
	for(map<ii,int>::iterator it = arestas.begin();it != arestas.end();it++){
		ii davez = (*it).first;
		int ini = (*it).second;
		adiciona_aresta(davez.first,davez.second,ini,M + 1);
	}
	arestas.clear();
 
	//for(edge davez : A) printf("L %d R %d U %d V %d\n",davez.l,davez.r,davez.u,davez.v);
 
	solve(1,M,A);
	for(int i = 1;i<=M;i++){
		if(e3[i] == -1) continue;
		if(e3[i] == 1) printf("YES\n");
		else printf("NO\n");
	}
	
	return 0;
	
} 
