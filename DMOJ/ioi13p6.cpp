// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi13p6
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef struct node* pnode;
typedef struct seg* pseg;
long long gcd2(long long X, long long Y) {
    long long tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}
struct node{
	pnode l,r;
	int prior,key;
	ll pure,val;
	node(int _key,ll _pure) : l(NULL),r(NULL),prior(rand()),key(_key),pure(_pure),val(_pure){}
};
ll operation(pnode t){
	if(t == NULL) return 0LL;
	return t->val;
}
void update(pnode t){
	if(t){
		t->val = gcd2(t->pure, gcd2(operation(t->l),operation(t->r)) );
	}
}
void split(pnode t,int key,pnode &l,pnode &r){
	if(t == NULL){
		l = r = NULL;
	}
	else{
		if(key < t->key){
			split(t->l,key,l,t->l);
			r = t;
		}
		else{
			split(t->r,key,t->r,r);
			l = t;
		}
	}
	update(t);
}
void merge(pnode &t,pnode l,pnode r){
	if(l == NULL){
		t = r;
	}
	else if(r == NULL){
		t = l;
	}
	else if(l->prior > r->prior){
		merge(l->r,l->r,r);
		t = l;
	}
	else{
		merge(r->l,l,r->l);
		t = r;
	}
	update(t);
}
ll find(pnode t,int key){
	if(t == NULL) return 0LL;
	if(t->key == key) return t->pure;
	if(key < t->key) return find(t->l,key);
	return find(t->r,key);
}
void TrueInsert(pnode &t,pnode aux){
	if(t == NULL){
		t = aux;
	}
	else{
		if(aux->prior > t->prior){
			split(t,aux->key,aux->l,aux->r);
			t = aux;
		}
		else{
			if(aux->key < t->key) TrueInsert(t->l,aux);
			else TrueInsert(t->r,aux);
		}
	}
	update(t);
}
bool modify(pnode &t,int key,ll pure){
	if(t == NULL){
		return false;
	}
	else if(t->key == key){
		t->pure = pure;
		update(t);
		return true;
	}
	if(key < t->key){
		bool ret = modify(t->l,key,pure);
		update(t);
		return ret;
	}
	else{
		bool ret = modify(t->r,key,pure);
		update(t);
		return ret;
	}
}
void insert(pnode &t,int key,ll pure){
	if(modify(t,key,pure)) return;
	pnode aux = new node(key,pure);
	TrueInsert(t,aux);
}
ll get_gcd(pnode t,int hi){
	if(t == NULL) return 0;
	if(t->key <= hi){
		ll ret = gcd2(operation(t->l),t->pure);
		if(ret == 1LL) return 1LL;
		return gcd2(ret, get_gcd(t->r,hi) );
	}
	return get_gcd(t->l,hi);
}
ll tquery(pnode &t,int a,int b){
	pnode L,R;
	split(t,a-1,L,R);
	ll ret = get_gcd(R,b);
	merge(t,L,R);
	return ret;
}
struct seg{
	pnode val;
	pseg l,r;
	seg() : val(NULL),l(NULL),r(NULL){}
	void update(int left,int right,int x,int y,ll delta){
		if(left == right){
			insert(val,y,delta);
			return;
		}
		else{
			int mid = (left+right)/2;
			if(x <= mid){
				if(l == NULL) l = new seg;
				l->update(left,mid,x,y,delta);
			}
			else{
				if(r == NULL) r = new seg;
				r->update(mid+1,right,x,y,delta);
			}
			ll t1 = find((l == NULL) ? NULL : l->val, y );
			if(t1 == 1LL){
				insert(val,y,1LL);
			}
			else{
				insert(val, y, gcd2( t1 , find((r == NULL) ? NULL : r->val,y) ) );
			}
		}
	}
	ll query(int left,int right,int i,int j,int p,int q){
		if(left >= i && right <= j) return tquery(val,p,q);
		int mid = (left+right)/2;
		if(j <= mid){
			return (l == NULL) ? 0LL : l->query(left,mid,i,j,p,q);
		}
		else if(i >= mid + 1){
			return (r == NULL) ? 0LL : r->query(mid+1,right,i,j,p,q);
		}
		else{
			ll t1 = (l == NULL) ? 0LL : l->query(left,mid,i,j,p,q);
			if(t1 == 1LL) return 1LL;
			else return gcd2(t1,(r == NULL) ? 0LL : r->query(mid+1,right,i,j,p,q));
		}
	}
};
pseg raiz;
int R,C;
void init(int RR,int CC){
	R = RR;
	C = CC;
	raiz = new seg;
}
void update(int x,int y,ll delta){
	raiz->update(0,R-1,x,y,delta);
}
long long calculate(int P, int Q, int U, int V){
	return raiz->query(0,R-1,P,U,Q,V);
}
int main(){
	return 0;
}
}
long long calculate(int P, int Q, int U, int V){
	return raiz->query(0,R-1,P,U,Q,V);
}
int main(){
	return 0;
}