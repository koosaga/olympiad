// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg15s5
#include <bits/stdc++.h>
#define MP make_pair
using namespace std;
typedef pair<int,int> i2;typedef pair<int,i2> i3;
const int MAXN = 10030;
int seg[4*MAXN][2],lazy[4*MAXN],n,m,resposta,ultimox;
vector<i3> sweep;
void build(int pos,int left,int right){
	if(left == right){
		seg[pos][0] = 1;
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	seg[pos][0] = seg[2*pos][0] + seg[2*pos+1][0]; 
}
void propagate(int pos,int left,int right){
	lazy[pos] %= 2;
	if(lazy[pos] == 0) return;
	swap(seg[pos][0],seg[pos][1]);
	if(left != right){
		lazy[2*pos] += lazy[pos];
		lazy[2*pos+1] += lazy[pos];
	}
	lazy[pos] = 0;
}
void update(int pos,int left,int right,int i,int j){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return;
	if(left >= i && right <= j){
		lazy[pos]++;
		propagate(pos,left,right);
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j);
	update(2*pos+1,mid+1,right,i,j);
	seg[pos][0] = seg[2*pos][0] + seg[2*pos+1][0]; 
	seg[pos][1] = seg[2*pos][1] + seg[2*pos+1][1]; 
}
int main(){
	scanf("%d %d",&n,&m);
	n+=2;
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int x1,y1,w,h;
		scanf("%d %d %d %d",&x1,&y1,&w,&h);
		x1++;
		y1++;
		sweep.push_back(MP(x1,MP(y1,y1+h-1)));
		sweep.push_back(MP(x1+w,MP(y1,y1+h-1)));
	}
	sort(sweep.begin(),sweep.end());
	for(int i=0;i<sweep.size();i++){
		int x = sweep[i].first;
		int l = sweep[i].second.first;
		int r = sweep[i].second.second;
		resposta += seg[1][1]*(x - ultimox);
		ultimox = x;
		update(1,1,n,l,r);
	}
	printf("%d\n",resposta);
	return 0;
}