#include "minerals.h"
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3000005;

void dnc(vector<int> l, vector<int> r, int toggle){
	if(l.size() == 1){
		Answer(l[0], r[0]);
		return;
	}
	int m = 0.35 * l.size(), last = 0;
	vector<int> ll, lr, rr, rl;
	m = max(m, 1); m = min(m, (int)l.size() - 1);
	for(int i=0; i<m; i++){
		last = Query(l[i]);
		ll.push_back(l[i]);
	}
	for(int i=m; i<l.size(); i++){
		lr.push_back(l[i]);
	}
	for(int i=0; i<r.size(); i++){
		if(rl.size() == ll.size()){
			rr.push_back(r[i]);
			continue;
		}
		if(rr.size() == lr.size()){
			rl.push_back(r[i]);
			continue;
		}
		int nxt = Query(r[i]);
		if(toggle ^ (nxt != last)){
			rr.push_back(r[i]);
		}
		else rl.push_back(r[i]);
		last = nxt;
	}
	dnc(ll, rl, toggle ^ 1);
	dnc(lr, rr, toggle);
}


void Solve(int N) {
	srand(time(0));
	vector<int> l, r;
	vector<int> perm(2 * N);
	iota(perm.begin(), perm.end(), 1);
	random_shuffle(perm.begin(), perm.end());
	for(auto &i : perm){
		int v = Query(i);
		if(v != l.size()){
			l.push_back(i);
		}
		else{
			r.push_back(i);
		}
	}
	dnc(l, r, 1);
}
