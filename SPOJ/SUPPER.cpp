// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SUPPER/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
int LIS[MAXN],LDS[MAXN],V[MAXN],seg[4*MAXN+8],n,maior;
void update(int pos,int left,int right,int x,int y){
	seg[pos] = max(seg[pos],y);
	if(left == right) return;
	int mid = (left+right)/2;
	if(x <= mid) update(2*pos,left,mid,x,y);
	else update(2*pos+1,mid+1,right,x,y);
}
int query(int pos,int left,int right,int i,int j){
	if(left >= i && right <= j) return seg[pos];
	int mid = (left+right)/2;
	if(j <= mid) return query(2*pos,left,mid,i,j);
	else if(i >= mid + 1) return query(2*pos+1,mid+1,right,i,j);
	else return max(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
int main(){
	while(scanf("%d",&n) != EOF){
		memset(seg,0,sizeof(seg));
		maior = 0;
		for(int i = 1;i<=n;i++){
			LIS[i] = LDS[i] = 0;
			scanf("%d",&V[i]);
			 LIS[i] = query(1,0,n+1,0,V[i]-1) + 1;
			 update(1,0,n+1,V[i],LIS[i]);
			 maior = max(maior,LIS[i]); 
		}
		vector<int> resp;
		memset(seg,0,sizeof(seg));
		for(int i = n;i>=1;i--){
			LDS[i] = query(1,0,n+1,V[i]+1,n+1) + 1;
			update(1,0,n+1,V[i],LDS[i]);
			if(LIS[i] + LDS[i] - 1 == maior) resp.push_back(V[i]);
		}
		sort(resp.begin(),resp.end());
		printf("%d\n",resp.size());
		for(int i : resp) printf("%d ",i);
		printf("\n");
	}
	return 0;
}