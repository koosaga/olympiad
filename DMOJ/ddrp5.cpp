// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ddrp5
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;
const int INF = 1e9 + 10;
const int NEG = -INF;

struct node{
	int v1,v2,v3,v4;

	node() : v1(0),v2(0),v3(0),v4(0){}
	node(int _v1,int _v2,int _v3,int _v4) : v1(_v1),v2(_v2),v3(_v3),v4(_v4) {}
	
	node operator+(const node& other)const{
		node novo(v1,v2,v3,v4);
		if(other.v1 > novo.v1){
			novo.v2 = novo.v1;
			novo.v1 = other.v1;
		}
		else if(other.v1 > novo.v2){
			novo.v2 = other.v1;
		}
		if(other.v2 > novo.v2){
			novo.v2 = other.v2;
		}
		if(other.v3 < novo.v3){
			novo.v4 = novo.v3;
			novo.v3 = other.v3;
		}
		else if(other.v3 < novo.v4){
			novo.v4 = other.v3;
		}
		if(other.v4 < novo.v4){
			novo.v4 = other.v4;
		}
		return novo;
	}

	int soma_max(){
		return v1 + v2;
	}

	int soma_min(){
		return v3 + v4;
	}

};

int vetor[MAXN],N,M,Q;
node seg[4*MAXN];

void build(int pos,int left,int right){
	//printf("P %d L %d R %d\n",pos,left,right);
	if(left == right){
		seg[pos].v1 = seg[pos].v3 = vetor[left];
		seg[pos].v2 = NEG;
		seg[pos].v4 = INF;
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	seg[pos] = seg[2*pos] + seg[2*pos+1];
}

void update(int pos,int left,int right,int x,int val){
	if(left == right){
		seg[pos].v1 = seg[pos].v3 = val;
		seg[pos].v2 = NEG;
		seg[pos].v4 = INF;
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid) update(2*pos,left,mid,x,val);
	else update(2*pos+1,mid+1,right,x,val);
	seg[pos] = seg[2*pos] + seg[2*pos+1];
}

node query(int pos,int left,int right,int i,int j){
	//printf("P %d L %d R %d I %d J %d\n",pos,left,right,i,j);
	if(left >= i && right <= j) return seg[pos];
	int mid = (left+right)/2;
	if(j <= mid) return query(2*pos,left,mid,i,j);
	else if(i >= mid + 1) return query(2*pos+1,mid+1,right,i,j);
	else return query(2*pos,left,mid,i,j) + query(2*pos+1,mid+1,right,i,j);
}

int main(){
	scanf("%d %d",&N,&Q);
	M = (int)ceil(sqrt(N));
	for(int i = 1;i<=N;i++) scanf("%d",&vetor[i]);
	build(1,1,N);
	int last = 0;
	while(Q--){
		int op,a,b;
		scanf("%d %d %d",&op,&a,&b);
		a ^= last;b ^= last;
		if(op == 1){
			update(1,1,N,a,b);
		}
		else if(op == 2){
			a = (a-1)*M + 1;
			b *= M;
			last = query(1,1,N,a,b).soma_min();
			printf("%d\n",last);
		}
		else{
			a = (a-1)*M + 1;
			b *= M;
			last = query(1,1,N,a,b).soma_max();
			printf("%d\n",last);
		}
	}
	return 0;
}