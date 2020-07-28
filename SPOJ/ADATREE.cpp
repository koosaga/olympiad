// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADATREE/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3*1e5 + 10;
typedef tuple<int,int,int,int> quadra;
typedef pair<int,int> ii;
vector<ii> atualizacoes;
vector<quadra> queries;
int n,m,ptr,resp[MAXN],seg[4*MAXN];
void update(int pos,int left,int right,int x,int val){
	if(left == right){
		seg[pos] = val;
		return;
	}
	int mid = (left+right)/2;
	seg[pos] = max(seg[pos],val);
	if(x <= mid){
		update(2*pos+1,left,mid,x,val);
	}
	else{
		update(2*pos+2,mid+1,right,x,val);
	}
}
int query(int pos,int left,int right,int i,int j){
	if(left >= i && right <= j){
		return seg[pos];
	}
	int mid = (left+right)/2;
	if(j <= mid){
		return query(2*pos+1,left,mid,i,j);
	}
	else if(i >= mid + 1){
		return query(2*pos+2,mid+1,right,i,j);
	}
	else{
		return max(query(2*pos+1,left,mid,i,j),query(2*pos+2,mid+1,right,i,j));
	}
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i = 0;i<n;i++){
		int x;
		scanf("%d",&x);
		atualizacoes.push_back(ii(x,i));
	}
	sort(atualizacoes.begin(),atualizacoes.end());
	for(int i = 0;i<m;i++){
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		queries.push_back(make_tuple(c,a,b,i));
	}
	sort(queries.begin(),queries.end());
	for(int i = 0;i<m;i++){
		int h = get<0>(queries[i]),a = get<1>(queries[i]),b = get<2>(queries[i]), idx = get<3>(queries[i]);
		while(ptr < n && atualizacoes[ptr].first <= h){
			update(0,0,n-1,atualizacoes[ptr].second,atualizacoes[ptr].first);
			ptr++;
		}
		resp[idx] = query(0,0,n-1,a,b);
	}
	for(int i =0;i<m;i++) printf("%d\n",resp[i]);
	return 0;
}