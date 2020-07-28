// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c4p6
#include <bits/stdc++.h>
using namespace std;
typedef struct node* pnode;
typedef pair<int,int> ii;
typedef tuple<int,int,int> trinca;
struct node{
	pnode l,r;
	int key,prior,size;
	ii puro,junta;
	node(int _key,ii _puro) : key(_key),puro(_puro),junta(_puro),prior((rand() ^ (rand() << 16))),size(1),l(NULL),r(NULL){}
};
inline int get_size(pnode t){return t ? t->size : 0;}
inline ii get_junta(pnode t){return t ? t->junta : ii(-1,-1);}
void update(pnode t){
	if(!t) return;
	t->size = get_size(t->l) + 1 + get_size(t->r);
	t->junta = max(max(get_junta(t->l),t->puro), get_junta(t->r) );
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
void insert(pnode &t,int key,ii puro){
	pnode L,mid,R;
	split(t,key-1,L,R);
	split(R,key,mid,R);
	if(mid){
		mid->puro = max(mid->puro,puro);
	}
	else{
		mid = new node(key,puro);
	}
	merge(t,L,mid);
	merge(t,t,R);
}
ii find(pnode &t,int b){
	if(get_junta(t->l).first >= b){
		//printf("%d %d Esquerda\n",t->puro.first,t->puro.second);
		return find(t->l,b);
	}
	if(t->puro.first >= b) return t->puro;
	return find(t->r,b);
}
//void preordem(pnode t){
//	if(!t) return;
//	preordem(t->l);
//	printf("(%d,%d) ",t->puro.first,t->puro.second);
//	preordem(t->r);
//}
int query(pnode &t,int a,int b){
	pnode L ,mid,R;
	split(t,a-1,L,R);
	split(R,a,mid,R);
	int ret = -1;
	if(get_junta(mid).first > b) ret = get_junta(mid).second;
	else if(get_junta(R).first >= b) ret = find(R,b).second;
	//preordem(R);
	//printf("\n");
	merge(t,L,mid);
	merge(t,t,R);
	return ret;
}
map<int,ii> mapa;
set<trinca> conjunto;
int main(){
	int N;
	pnode raiz = NULL;
	scanf("%d",&N);
	int atualaluno = 0;
	while(N--){
		char op;
		scanf(" %c",&op);
		if(op == 'D'){
			int A,B;
			scanf("%d %d",&A,&B);
			swap(A,B);
			mapa[++atualaluno] = ii(A,B);
			insert(raiz,A,ii(B,atualaluno));
			conjunto.insert(make_tuple(A,B,atualaluno));
		}
		else if(op == 'P'){
			int x;
			scanf("%d",&x);
			int a = mapa[x].first, b = mapa[x].second;
			int exibe = query(raiz,a,b);
			if(exibe == -1){
				printf("NE\n");
			}
			else{
				int aa = mapa[exibe].first;
				//printf("Exibe %d\n",exibe);
				if(aa == a) b++;
				trinca nova = make_tuple(aa,b,0);
				trinca davez = *conjunto.lower_bound(nova);
				printf("%d\n",get<2>(davez));
			}
		}
	}
	return 0;
}		printf("%d\n",get<2>(davez));
			}
		}
	}
	return 0;
}