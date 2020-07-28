// Ivan Carvalho
// Solution to https://dmoj.ca/problem/lkp18c2p5
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef struct node* pnode;

const int MAXN = 3*1e5 + 10;
const int MAXV = 1e9;

struct node{

	ll val;
	int freq;
	pnode l,r;

	node(){
		val = 0;
		l = r = NULL;
	}

	void update(int left,int right,int x, ll delta){

		val += delta;
		if(delta > 0) freq += 1;
		else freq -= 1;

		if(left == right){
			return;
		}
		
		int mid = (left+right)/2;
		if(x <= mid){
			if(!l) l = new node();
			l->update(left,mid,x,delta);
		}
		else{
			if(!r) r = new node();
			r->update(mid+1,right,x,delta);
		}

		if(l && l->freq == 0){
			delete l;
			l = NULL;
		}
		if(r && r->freq == 0){
			delete r;
			r = NULL;
		}

	}

	int query(int left,int right, ll reqsum){

		//printf("L %d R %d %lld\n",left,right,reqsum);

		if(left == right){
			if(reqsum % left == 0) return reqsum/left;
			return reqsum/left + 1;
		}

		int mid = (left+right)/2;
		if(!r){
			//printf("Case 1\n");
			return l->query(left,mid,reqsum);
		}
		if(r->val >= reqsum){
			//printf("Case 2\n");
			return r->query(mid+1,right,reqsum);
		}

		//printf("Case 3 %d %lld\n",r->freq,r->val);
		return r->freq + l->query(left,mid, reqsum - r->val );

	}

};

int N,Q;
ll B[MAXN],total_sum;
pnode raiz;

int main(){

	raiz = new node();
	scanf("%d %d",&N,&Q);
	for(int i = 1;i<=N;i++){
		scanf("%lld",&B[i]);
		total_sum += B[i];
		raiz->update(1,MAXV,B[i],B[i]);
	}

	printf("%d\n",raiz->query(1,MAXV,total_sum/2 + 1));

	while(Q--){
		int a,b;
		scanf("%d %d",&a,&b);
		total_sum += b - B[a];
		raiz->update(1,MAXV,B[a],-B[a]);
		B[a] = b;
		raiz->update(1,MAXV,B[a],B[a]);
		printf("%d\n",raiz->query(1,MAXV,total_sum/2 + 1));
	}

	return 0;

}