// Ivan Carvalho
// Solution to https://dmoj.ca/problem/hci16stacker
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 1000010;
vector<ll> comp;
ll W[MAXN],V[MAXN],n,seg[4*MAXN];
void update(int p,int l,int r,int x,ll delta){
	if(l == r){
		seg[p] = max(delta,seg[p]);
		return;
	}
	int m = (l+r)/2;
	if(x <= m )update(2*p,l,m,x,delta);
	else update(2*p+1,m+1,r,x,delta);
	seg[p] = max(seg[2*p],seg[2*p+1]);
}
ll query(int p,int l,int r,int i,int j){
	if(l>r||l>j||r<i) return 0;
	if(l >= i && r <= j){
		return seg[p];
	}
	int m = (l+r)/2;
	return max(query(2*p,l,m,i,j),query(2*p+1,m+1,r,i,j));
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	ll resp = 0;
	for(int i=1;i<=n;i++){
		cin >> W[i];
		comp.push_back(W[i]);
	}
	for(int i=1;i<=n;i++) cin >> V[i];
	sort(comp.begin(),comp.end());
	comp.erase(unique(comp.begin(),comp.end()),comp.end());
	for(ll i = 1;i<=n;i++){
		W[i] = lower_bound(comp.begin(),comp.end(),W[i]) - comp.begin() + 1;
		ll best = query(1,1,n,W[i] + 1,n);
		resp = max(resp,best + V[i]);
		update(1,1,n,W[i],best + V[i]);
	}
	cout << resp << endl;
	return 0;
}