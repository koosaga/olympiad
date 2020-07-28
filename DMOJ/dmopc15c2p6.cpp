// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc15c2p6
#include <bits/stdc++.h>
#define MP make_pair
using namespace std;
typedef pair<int,int> i2;
typedef pair<int,i2> i3;
typedef pair<int,i3> i4;
const int MAXN = 8035;
const int ADD = 4000;
int XM[11],YM[11],resp,n,m;
int seg[4*MAXN],lazy[4*MAXN];
void propagate(int pos,int left,int right){
	if(lazy[pos] == 0) return;
	seg[pos] += lazy[pos];
	if(left != right){
		lazy[2*pos] += lazy[pos];
		lazy[2*pos+1] += lazy[pos];
	}
	lazy[pos] = 0;
}
void update(int pos,int left,int right,int i,int j,int delta){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return;
	if(left >= i && right <= j){
		lazy[pos] = delta;
		propagate(pos,left,right);
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j,delta);
	update(2*pos+1,mid+1,right,i,j,delta);
	seg[pos] = max(seg[2*pos],seg[2*pos+1]);
}
vector<i4> sweep;
vector<int> compressao;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> m;
	for(int i=1;i<=m;i++) cin >> XM[i] >> YM[i];
	cin >> n;
	for(int i=1;i<=n;i++){
		int x,y,d;
		cin >> x >> y;
		d = abs(x - XM[1]) + abs(y - YM[1]);
		for(int j=2;j<=m;j++) d = min(d, abs(x - XM[j]) + abs(y - YM[j]) );
		d--;
		if(d == -1) continue;
		sweep.push_back(MP(x + y - d,MP(1,MP(y - x - d, y - x + d))));
		sweep.push_back(MP(x + y + d,MP(2,MP(y - x - d,y - x + d))));
	}
	sort(sweep.begin(),sweep.end());
	for(int i=0;i<sweep.size();i++){
		int delta = sweep[i].second.first;
		if(delta == 2) delta = -1;
		int l = sweep[i].second.second.first + ADD;
		int r = sweep[i].second.second.second + ADD;
		l = max(0,l) + 1;
		r = min(2*ADD,r) + 1;
		//cout << l << " " << r << " " << delta << endl;
		update(1,1,MAXN - 20,l,r,delta);
		resp = max(resp,seg[1]);
	}
	cout << resp << endl;
	return 0;
}