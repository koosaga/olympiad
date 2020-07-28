// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2010
#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int> trinca;
const int MAXN = 1e5 + 10;
const int INF = 1e9 + 1e8;
int seg[4*MAXN],lazy[4*MAXN],n,m;
vector<trinca> lojas;
vector<int> prefixo;
void propagate(int pos,int left,int right){
	if(lazy[pos] == INF) return;
	seg[pos] = min(seg[pos],lazy[pos]);
	if(left != right){
		lazy[2*pos] = min(lazy[2*pos],lazy[pos]);
		lazy[2*pos+1] = min(lazy[2*pos+1],lazy[pos]);
	}
	lazy[pos] = INF;
}
void update(int pos,int left,int right,int i,int j,int val){
	if(left>right||left>j||right<i)return;
	if(left >= i && right <= j){
		lazy[pos] = min(lazy[pos],val);
		propagate(pos,left,right);
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j,val);
	update(2*pos+1,mid+1,right,i,j,val);
	seg[pos] = min(seg[2*pos],seg[2*pos+1]);
}
int get(int pos,int left,int right,int alvo){
	propagate(pos,left,right);
	if(left == right) return seg[pos];
	int mid = (left+right)/2;
	if(alvo <= mid) return get(2*pos,left,mid,alvo);
	return get(2*pos+1,mid+1,right,alvo);
}
int main(){
	cin.tie(0);ios_base::sync_with_stdio(0);
	cin >> n >> m;
	prefixo.push_back(0);
	for(int i = 1;i<= 4*n + 8;i++){
		seg[i] = lazy[i] = INF;
	}
	update(1,0,n,0,0,0);
	for(int i = 1;i<=n;i++){
		int x;
		cin >> x;
		prefixo.push_back(prefixo.back()+x);
	}
	for(int i = 1;i<=m;i++){
		int l,n,s;
		cin >> l >> n >> s;
		lojas.push_back(make_tuple(l,n,s));
	}
	sort(lojas.begin(),lojas.end());
	for(int i = 0;i<lojas.size();i++){
		int pos = get<0>(lojas[i]),forca = get<1>(lojas[i]),preco = get<2>(lojas[i]);
		int real = preco + get(1,0,n,pos-1);
		int alcanca = prev(upper_bound(prefixo.begin(),prefixo.end(), prefixo[pos-1] + forca )) - prefixo.begin();
		if(pos <= alcanca) update(1,0,n,pos,alcanca,real);
	}
	int resp = get(1,0,n,n);
	if(resp == INF) resp = -1;
	cout << resp << endl;
	return 0;
}
