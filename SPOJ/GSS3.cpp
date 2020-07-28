// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GSS3/
#include <cstdio>
#include <algorithm>
#define MAXN 50010
using namespace std;
typedef struct node{
	int total;
	int maximo_ini;
	int maximo_fim;
	int maximo;
}no;
no arvore[4*MAXN];
int vetor[MAXN];
no join(no a, no b){
	no resultado;
	resultado.total = a.total + b.total;
	resultado.maximo_ini = max(a.maximo_ini,a.total+b.maximo_ini);
	resultado.maximo_fim = max(b.maximo_fim,b.total+a.maximo_fim);
	resultado.maximo = max(max(a.maximo,b.maximo),a.maximo_fim+b.maximo_ini);
	return resultado;
}
void build(int pos, int left, int right){
	if (left == right){
		arvore[pos].total = arvore[pos].maximo_ini = arvore[pos].maximo_fim = arvore[pos].maximo = vetor[left];
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
	int mid = (left + right) / 2;
	if (left > mid || left > j || mid < i){
		return query(2*pos+1,mid+1,right,i,j);
	}
	if (mid + 1 > right || mid + 1 > j || right < i){
		return query(2*pos,left,mid,i,j);
	}
	return join(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
void update(int pos, int left, int right,int idx, int val){
	if(left > right || left > idx || right < idx) return;
	if (left == right){
		arvore[pos].total = arvore[pos].maximo_ini = arvore[pos].maximo_fim = arvore[pos].maximo = val;
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,idx,val);
	update(2*pos+1,mid+1,right,idx,val);
	arvore[pos] = join(arvore[2*pos],arvore[2*pos+1]);
}
int main(){
	int n,q;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&vetor[i]);
	build(1,1,n);
	scanf("%d",&q);
	while(q--){
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		if (a == 0) update(1,1,n,b,c);
		if (a == 1) printf("%d\n",query(1,1,n,b,c).maximo);
	}
	return 0;
}