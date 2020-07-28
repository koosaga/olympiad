// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg16s5
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2*1e5 + 10;
typedef long long ll;
struct node{
	ll mi,mf,tot,mx;
};
node add(node A,node B){
	node C;
	C.tot = A.tot + B.tot;
	C.mi = max(A.mi,A.tot + B.mi);
	C.mf = max(B.mf,A.mf + B.tot);
	C.mx = max(max(A.mx,B.mx), A.mf + B.mi );
	return C;
}
ll vetor[MAXN],n,k;
node seg[4*MAXN];
void build(int p,int l,int r){
	if(l == r){
		seg[p].tot = seg[p].mi = seg[p].mf = seg[p].mx = vetor[l];
		return;
	}
	int m = (l+r)/2;
	build(2*p,l,m);
	build(2*p+1,m+1,r);
	seg[p] = add(seg[2*p],seg[2*p+1]);
}
node query(int p,int l,int r,int i,int j){
	if(l >= i && r <= j){
		return seg[p];
	}
	int m = (l+r)/2;
	if(j <= m){
		return query(2*p,l,m,i,j);
	}
	else if(i >= m + 1){
		return query(2*p+1,m+1,r,i,j);
	}
	else{
		return add(query(2*p,l,m,i,j),query(2*p+1,m+1,r,i,j));
	}
}
int main(){
	cin >> n >> k;
	for(int i=1;i<=n;i++){
		cin >> vetor[i];
		vetor[i+n] = vetor[i];
	}
	n *= 2;
	build(1,1,n);
	ll resp = 0;
	for(int i = 1, j = k;j <= n;i++,j++){
		node davez = query(1,1,n,i,j);
		resp = max(resp,davez.mx);
	}
	cout << resp << endl;
	return 0;
}