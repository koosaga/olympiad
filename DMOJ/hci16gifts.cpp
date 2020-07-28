// Ivan Carvalho
// Solution to https://dmoj.ca/problem/hci16gifts
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 10;
ll vetor[MAXN],seg[4*MAXN],n,k,resp;
struct node{
	ll mi,mf,mx,tot;
};
node arvore[4*MAXN];
node join(node A,node B){
	node C;
	C.tot = A.tot + B.tot;
	C.mi = max(A.mi,A.tot + B.mi);
	C.mf = max(B.mf,A.mf + B.tot);
	C.mx = max(max(A.mx,B.mx), A.mf + B.mi );
	return C;
}
void build_kadane(int p,int l,int r){
	if(l == r){
		arvore[p].mi = arvore[p].mf = arvore[p].mx = arvore[p].tot = vetor[l];
		return;
	}
	int m = (l+r)/2;
	build_kadane(2*p,l,m);
	build_kadane(2*p+1,m+1,r);
	arvore[p] = join(arvore[2*p],arvore[2*p+1]);
}
node query_kadane(int p,int l,int r,int i,int j){
	if(l >= i && r <= j){
		return arvore[p];
	}
	int m = (l+r)/2;
	if(j <= m){
		return query_kadane(2*p,l,m,i,j);
	}
	else if(i >= m + 1){
		return query_kadane(2*p+1,m+1,r,i,j);
	}
	else{
		return join(query_kadane(2*p,l,m,i,j),query_kadane(2*p+1,m+1,r,i,j));
	}
}
void build_max(int p,int l,int r){
	if(l == r){
		seg[p] = vetor[l];
		return;
	}
	int m = (l+r)/2;
	build_max(2*p,l,m);
	build_max(2*p+1,m+1,r);
	seg[p] = max(seg[2*p],seg[2*p+1]);
}
ll query_max(int p,int l,int r,int i,int j){
	if(l >= i && r <= j){
		return seg[p];
	}
	int m = (l+r)/2;
	if(j <= m){
		return query_max(2*p,l,m,i,j);
	}
	else if(i >= m + 1){
		return query_max(2*p+1,m+1,r,i,j);
	}
	else{
		return max(query_max(2*p,l,m,i,j),query_max(2*p+1,m+1,r,i,j));
	}
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k;
	for(ll i=1;i<=n;i++){
		cin >> vetor[i];
		vetor[i+n] = vetor[i]; 
	}
	n *= 2;
	build_kadane(1,1,n);
	for(ll i = 1;i<=n;i++){
		ll ini = i,fim  = i + k - 1;
		fim = min(fim,n);
		vetor[i] = max(0LL,query_kadane(1,1,n,ini,fim).mx);
	}
	build_max(1,1,n);
	for(ll i = 1;i <= n/2;i++){
		ll best = vetor[i];
		ll ini = i + k;
		ll fim = i + n/2 - k;
		ll secondbest = query_max(1,1,n,ini,fim);
		if(ini > fim) secondbest = 0;
		//printf("%lld %lld\n",best,secondbest);
		resp = max(resp,best + secondbest);
	}
	cout << resp << endl;
	return 0;
}esp << endl;
	return 0;
}