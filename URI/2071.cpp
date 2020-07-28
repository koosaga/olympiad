// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2071
#include <cstdio>
#include <algorithm>
#define MAXN 100010
#define MP make_pair
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}
using namespace std;
typedef pair<int,int> ii;
typedef struct node{
	ii total;
	ii maximo_ini;
	ii maximo_fim;
	ii maximo;
}no;
int vetor[MAXN];
no arvore[4*MAXN];
ii add(ii a, ii b){
	return MP(a.first + b.first, a.second+b.second);
}
no join(no a, no b){
	no resultado;
	resultado.total = add(a.total,b.total);
	resultado.maximo_ini = max(a.maximo_ini,add(a.total,b.maximo_ini));
	resultado.maximo_fim = max(b.maximo_fim,add(a.maximo_fim,b.total));
	resultado.maximo = max(max(a.maximo,b.maximo),add(a.maximo_fim,b.maximo_ini));
	return resultado;
}
void build(int pos, int left, int right){
	if (left == right){
		arvore[pos].total = arvore[pos].maximo_ini = arvore[pos].maximo_fim = arvore[pos].maximo = MP(vetor[left],1);
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = join(arvore[2*pos],arvore[2*pos+1]);
}
no query(int pos, int left, int right, int i, int j){
	if (left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	if (left > mid || left > j || mid < i){
		return query(2*pos+1,mid+1,right,i,j);
	}
	if (mid+1 > right || mid+1 > j || right < i){
		return query(2*pos,left,mid,i,j);
	}
	return join(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
int main(){
	no padrao;
	padrao.total = padrao.maximo_ini = padrao.maximo_fim = padrao.maximo = MP(0,0);
	int casos;
	getint(casos);
	while(casos--){
		int n,q;
		getint(n);
		for(int i=1;i<=n;i++) getint(vetor[i]);
		for(int i=1;i<=4*n;i++) arvore[i] = padrao;
		build(1,1,n);
		getint(q);
		while(q--){
			int x,y;
			getint(x);
			getint(y);
			ii resposta = query(1,1,n,x,y).maximo;
			printf("%d %d\n",resposta.first,resposta.second);
		}
	}
	return 0;
}
