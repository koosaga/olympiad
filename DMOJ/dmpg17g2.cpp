// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg17g2
#include <cstdio>
#include <algorithm>
#define MAXN 100010
using namespace std;
typedef long long ll;
typedef struct node{
	ll total;
	ll maximo_ini;
	ll maximo_fim;
	ll maximo;
}no;
no arvore[4*MAXN];
ll vetor[MAXN];
no join(no a, no b){
	no resultado;
	resultado.total = a.total + b.total;
	resultado.maximo_ini = max(a.maximo_ini,a.total+b.maximo_ini);
	resultado.maximo_fim = max(b.maximo_fim,b.total+a.maximo_fim);
	resultado.maximo = max(max(a.maximo,b.maximo),a.maximo_fim+b.maximo_ini);
	return resultado;
}
void build(ll pos, ll left, ll right){
	if (left == right){
		arvore[pos].total = arvore[pos].maximo_ini = arvore[pos].maximo_fim = arvore[pos].maximo = vetor[left];
		return;
	}
	ll mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = join(arvore[2*pos],arvore[2*pos+1]);
}
no query(ll pos, ll left, ll right, ll i, ll j){
	if (left >= i && right <= j){
		return arvore[pos];
	}
	ll mid = (left + right) / 2;
	if (left > mid || left > j || mid < i){
		return query(2*pos+1,mid+1,right,i,j);
	}
	if (mid + 1 > right || mid + 1 > j || right < i){
		return query(2*pos,left,mid,i,j);
	}
	return join(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
void update(ll pos, ll left, ll right,ll idx, ll val){
	if(left > right || left > idx || right < idx) return;
	if (left == right){
		arvore[pos].total = arvore[pos].maximo_ini = arvore[pos].maximo_fim = arvore[pos].maximo = val;
		return;
	}
	ll mid = (left+right)/2;
	update(2*pos,left,mid,idx,val);
	update(2*pos+1,mid+1,right,idx,val);
	arvore[pos] = join(arvore[2*pos],arvore[2*pos+1]);
}
int main(){
	ll n,q;
	scanf("%lld %lld",&n,&q);
	for(ll i=1;i<=n;i++) scanf("%lld",&vetor[i]);
	build(1,1,n);
	while(q--){
		char op;
		ll b,c;
		scanf(" %c %lld %lld",&op,&b,&c);
		if (op == 'S') update(1,1,n,b,c);
		else printf("%lld\n",query(1,1,n,b,c).maximo);
	}
	return 0;
}
}