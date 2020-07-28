// Ivan Carvalho
// Solution to https://www.spoj.com/problems/DIFERENC/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3*1e5 + 10;
typedef pair<int,int> ii;
typedef long long ll;
ll somatorio;
deque<ll> valores;
int vetor[MAXN],n; 
ii seg_max[4*MAXN],seg_min[4*MAXN];
void build(int pos,int left,int right){
	if(left == right){
		seg_max[pos] = seg_min[pos] = ii(vetor[left],left);
		return;
	}
	int mid = (left + right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	seg_max[pos] = max(seg_max[2*pos],seg_max[2*pos+1]);
	seg_min[pos] = min(seg_min[2*pos],seg_min[2*pos+1]);
}
ii query_max(int pos,int left,int right,int i,int j){
	if(left >= i && right <= j){
		return seg_max[pos];
	}
	int mid = (left+right)/2;
	if(j <= mid){
		return query_max(2*pos,left,mid,i,j);
	}
	else if(i >= mid + 1){
		return query_max(2*pos+1,mid+1,right,i,j);
	}
	else{
		return max(query_max(2*pos,left,mid,i,j),query_max(2*pos+1,mid+1,right,i,j));
	}
}
ii query_min(int pos,int left,int right,int i,int j){
	if(left >= i && right <= j){
		return seg_min[pos];
	}
	int mid = (left+right)/2;
	if(j <= mid){
		return query_min(2*pos,left,mid,i,j);
	}
	else if(i >= mid + 1){
		return query_min(2*pos+1,mid+1,right,i,j);
	}
	else{
		return min(query_min(2*pos,left,mid,i,j),query_min(2*pos+1,mid+1,right,i,j));
	}
}
void solve_max(int l,int r){
	if(l > r || l < 1 || r > n) return;
	int escolhido = query_max(1,1,n,l,r).second;
	int esq = (escolhido - l + 1), dir = (r - escolhido + 1);
	valores.push_back(1LL*esq*dir*vetor[escolhido]);
	solve_max(l,escolhido-1);
	solve_max(escolhido+1,r);
}
void solve_min(int l,int r){
	if(l > r || l < 1 || r > n) return;
	int escolhido = query_min(1,1,n,l,r).second;
	int esq = (escolhido - l + 1), dir = (r - escolhido + 1);
	valores.push_back(-1LL*esq*dir*vetor[escolhido]);
	solve_min(l,escolhido-1);
	solve_min(escolhido+1,r);
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		scanf("%d",&vetor[i]);
	}
	build(1,1,n);
	solve_max(1,n);
	solve_min(1,n);
	sort(valores.begin(),valores.end());
	for(int i = 1;i<=n;i++){
		somatorio += valores.back();
		somatorio += valores.front();
		valores.pop_back();
		valores.pop_front();
	}
	printf("%lld\n",somatorio);
	return 0;
}