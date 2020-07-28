// Ivan Carvalho
// Solution to https://www.spoj.com/problems/MON2012/
#include <bits/stdc++.h>
using namespace std;
typedef struct node* pnode;
struct node{
	pnode l,r;
	int val,ac;
	node() : l(NULL),r(NULL),val(0),ac(0){}
	void update(int left,int right,int i,int j){
		if(ac) return;
		if(left >= i && right <= j){
			ac = 1;
			val = right - left + 1;
			return;
		}
		else{
			int mid = (left+right)/2;
			if(j <= mid){
				if(l == NULL) l = new node;
				l->update(left,mid,i,min(j,mid));
			}
			else if(i >= mid + 1){
				if(r == NULL) r = new node;
				r->update(mid+1,right,max(mid+1,i),j);
			}
			else{
				if(l == NULL) l = new node;
				l->update(left,mid,i,min(j,mid));
				if(r == NULL) r = new node;
				r->update(mid+1,right,max(mid+1,i),j);
			}
			val = (l == NULL ? 0 : l->val) + (r == NULL ? 0 :  r->val);
		}
	}
	int query(int left,int right,int i,int j){
		if(ac){
			return j - i + 1;
		}
		if(left >= i && right <= j) return val;
		int mid = (left+right)/2;
		if(j <= mid){
			return l == NULL ? 0 : l->query(left,mid,i,min(j,mid));
		}
		else if(i >= mid + 1){
			return r == NULL ? 0 : r->query(mid+1,right,max(mid+1,i),j);
		}
		else{
			return (l == NULL ? 0 : l->query(left,mid,i,min(j,mid))) + (r == NULL ? 0 : r->query(mid+1,right,max(mid+1,i),j));
		}
	}
};
int main(){
	int lo = 1,hi = 1e9, last = 0,m;
	scanf("%d",&m);
	pnode raiz = new node;
	while(m--){
		int op,x,y;
		scanf("%d %d %d",&op,&x,&y);
		x += last;y+=last;
		if(op == 2){
			raiz->update(lo,hi,x,y);
		}
		else if(op == 1){
			last = raiz->query(lo,hi,x,y);
			printf("%d\n",last);
		}
	}
	return 0;
}