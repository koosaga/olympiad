// Ivan Carvalho
// Solution to https://dmoj.ca/problem/apio12p1
#include <bits/stdc++.h>
using namespace std;
const long long MAXN = 100010;
typedef pair<long long,long long> ii;
typedef struct node* pnode;
struct node{
	pnode l,r;
	ii key;
	long long size,prior;
	long long soma;
	node(ii key) : l(NULL),r(NULL),key(key),size(1),prior(rand()),soma((long long)key.first){}
};
inline long long sz(pnode t){
	if(t == NULL) return 0;
	return t->size;
}
inline long long sm(pnode t){
	if(t == NULL) return 0LL;
	return t->soma;
}
void upd(pnode t){
	if(t == NULL) return;
	t->size =  sz(t->l) + 1 + sz(t->r);
	t->soma = (long long)t->key.first + sm(t->l) + sm(t->r);
}
void split(pnode t,ii key,pnode &l,pnode &r){
	if(t == NULL){
		l = r = NULL;
	}
	else{
		if(key < t->key){
			split(t->l,key,l,t->l);
			r = t;
		}
		else{
			split(t->r,key,t->r,r);
			l = t;
		}
	}
	upd(t);
}
void merge(pnode &t,pnode l,pnode r){
	if(l == NULL){t = r;}
	else if(r == NULL){t = l;}
	else if(l->prior > r->prior){
		merge(l->r,l->r,r);
		t = l;
	}
	else{
		merge(r->l,l,r->l);
		t = r;
	}
	upd(t);
}
void insert(pnode &t,ii key){
	pnode L,R;
	pnode aux = new node(key);
	split(t,ii(key.first - 1,MAXN),L,R);
	merge(t,L,aux);
	merge(t,t,R);
}
long long count(pnode t,long long budget){
	if(t == NULL) return 0;
	long long agora = (long long)t->key.first + sm(t->l);
	if(budget == agora) return sz(t->l) + 1;
	if(budget <= agora) return count(t->l,budget);
	return sz(t->l) + 1 + count(t->r,budget - agora);
}
vector<long long> grafo[MAXN];
vector<long long> *conjunto[MAXN];
long long peso[MAXN],lideranca[MAXN],n,m,tam[MAXN];
pnode raiz[MAXN];
long long resp;
void dfs(long long x){
	tam[x] = 1;
	long long big = -1,mx = -1;
	for(long long v : grafo[x]){
		dfs(v);
		tam[x] += tam[v];
		if(tam[v] > mx){
			mx = tam[v];
			big = v;
		}
	}
	if(big == -1){
		conjunto[x] = new vector<long long> ();
		(*conjunto[x]).push_back(x);
		raiz[x] = new node(ii(peso[x],x));
	}
	else{
		raiz[x] = raiz[big];
		conjunto[x] = conjunto[big];
		(*conjunto[x]).push_back(x);
		insert(raiz[x],ii(peso[x],x));
	}
	for(long long v : grafo[x]){
		if(v == big) continue;
		for(long long u : (*conjunto[v])){
			(*conjunto[x]).push_back(u);
			insert(raiz[x],ii(peso[u],u));
		}
	}
	resp = max(resp, 1LL*lideranca[x]*count(raiz[x],(long long)m) );
}
int main(){
	cin.tie(0);ios_base::sync_with_stdio(0);
	cin >> n >> m;
	for(long long i=1;i<=n;i++){
		long long j;
		cin >> j >> peso[i] >> lideranca[i];
		grafo[j].push_back(i);
	}
	dfs(1);
	cout << resp << endl;
	return 0;
}}
	dfs(1);
	cout << resp << endl;
	return 0;
}