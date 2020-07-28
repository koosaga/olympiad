// Ivan Carvalho
// Solution to https://dmoj.ca/problem/hci16penguinfood
#include <cstdio>
#include <algorithm>
#define MAXN 1000010
using namespace std;
typedef long long ll;
#define gc getchar_unlocked
void getint(ll &x){
    register ll c = gc();
    x = 0;
    ll neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}
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
void update(ll pos, ll left, ll right,ll idx, ll val){
	if (left == right){
		arvore[pos].total = arvore[pos].maximo_ini = arvore[pos].maximo_fim = arvore[pos].maximo = val;
		return;
	}
	ll mid = (left+right)/2;
	if(idx <= mid) update(2*pos,left,mid,idx,val);
	else update(2*pos+1,mid+1,right,idx,val);
	arvore[pos] = join(arvore[2*pos],arvore[2*pos+1]);
}
int main(){
	ll n,q;
	getint(n);
	for(ll i=1;i<=n;i++) getint(vetor[i]);
	build(1,1,n);
	getint(q);
	while(q--){
		ll b,c;
		getint(b);
		getint(c);
		printf("%lld\n",max(arvore[1].maximo,0LL));
		b++;
		update(1,1,n,b,c);
	}
	printf("%lld\n",max(arvore[1].maximo,0LL));
	return 0;
}