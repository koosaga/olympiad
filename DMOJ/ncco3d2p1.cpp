// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ncco3d2p1
#include <bits/stdc++.h>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 5*1e4 + 10;
int vetor[MAXN],N,Q;
ii seg[4*MAXN];
ii join(ii A,ii B){
	return ii(max(A.first,B.first),min(A.second,B.second));
}
void build(int pos,int left,int right){
	if(left == right){
		seg[pos] = ii(vetor[left],vetor[left]);
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	seg[pos] = join(seg[2*pos],seg[2*pos+1]);
}
ii query(int pos,int left,int right,int i,int j){
	if(left >= i && right <= j) return seg[pos];
	int mid = (left+right)/2;
	if(j <= mid) return query(2*pos,left,mid,i,j);
	else if(i >= mid + 1) return query(2*pos+1,mid+1,right,i,j);
	else return join(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
int main(){
	scanf("%d %d",&N,&Q);
	for(int i = 1;i<=N;i++) getint(vetor[i]);
	build(1,1,N);
	while(Q--){
		int a,b;
		getint(a);getint(b);
		ii davez = query(1,1,N,a,b);
		printf("%d\n",davez.first - davez.second);
	}
	return 0;
}
