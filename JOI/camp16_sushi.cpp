#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int B = 600;

int n, q, w[400005];
priority_queue<int> pq[705];
priority_queue<int, vector<int>, greater<int> > lazy[705];

void apply(int p){
	for(int i=p*B; i<min(p*B+B, n); i++){
		lazy[p].push(w[i]);
		w[i] = lazy[p].top();
		lazy[p].pop();
	}
	while(!lazy[p].empty()) lazy[p].pop();
}

void remake(int p){
	while(!pq[p].empty()) pq[p].pop();
	for(int i=p*B; i<min(p*B+B, n); i++){
		pq[p].push(w[i]);
	}
}

int update(int s, int e, int x){
	if(s / B == e / B){
		apply(s / B);
		for(int i=s; i<=e; i++){
			if(w[i] > x){
				swap(w[i], x);
			}
		}
		remake(s / B);
		return x;
	}
	apply(s / B);
	apply(e / B);
	for(int i=s; i<(s/B+1)*B; i++){
		if(w[i] > x){
			swap(w[i], x);
		}
	}
	for(int i=s/B+1; i<e/B; i++){
		pq[i].push(x);
		lazy[i].push(x);
		x = pq[i].top();
		pq[i].pop();
	}
	for(int i=(e/B)*B; i<=e; i++){
		if(w[i] > x){
			swap(w[i], x);
		}
	}
	remake(s / B);
	remake(e / B);
	return x;
}

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n; i++){
		scanf("%d",&w[i]);
	}
	for(int i=0; i*B<n; i++){
		remake(i);
	}
	for(int i=0; i<q; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		s--, e--;
		if(s <= e){
			printf("%d\n", update(s, e, x));
		}
		else{
			printf("%d\n", update(0, e, update(s, n-1, x)));
		}
	}
}
