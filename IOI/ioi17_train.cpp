#include "train.h"
#include <bits/stdc++.h>
using namespace std;
 
int n, m;
vector<int> gph[5005];
vector<int> proc;
 
vector<int> always(vector<int> &a, vector<int> &v, int winner){
	vector<int> deg(n);
	queue<int> que;
	for(int i=0; i<n; i++){
		if(proc[i]) continue;
		for(auto &j : gph[i]){
			if(!proc[j]) deg[j]++;
		}
	}
	for(auto &i : v){
		if(deg[i] > 0){
			deg[i] = 0;
		}
		que.push(i);
	}
	vector<int> ret;
	while(!que.empty()){
		int x = que.front(); que.pop();
		ret.push_back(x);
		for(auto &i : gph[x]){
			if(proc[i]) continue;
			if(a[i] == winner && deg[i] > 0){
				deg[i] = 0;
				que.push(i);
			}
			else if(a[i] != winner){
				deg[i]--;
				if(deg[i] == 0) que.push(i);
			}
		}
	}
	return ret;
}
 
vector<int> who_wins(vector<int> a, vector<int> r, vector<int> u, vector<int> v){
	n = a.size();
	m = u.size();
	vector<int> ret(n);
	proc.resize(n);
	for(int i=0; i<m; i++){
		gph[v[i]].push_back(u[i]);
	}
	while(true){
		int unproc = count(proc.begin(), proc.end(), 0);
		if(unproc == 0) break;
		vector<int> R;
		for(int i=0; i<n; i++) if(!proc[i] && r[i]) R.push_back(i);
		R = always(a, R, 1);
		if(R.size() == unproc){
			for(auto &i : R) proc[i] = 1, ret[i] = 1;
		}
		else{
			vector<int> rem(n);
			for(auto &i : R) rem[i] = 1;
			R.clear();
			for(int i=0; i<n; i++){
				if(!proc[i] && !rem[i]) R.push_back(i);
			}
			R = always(a, R, 0);
			for(auto &i : R) proc[i] = 1, ret[i] = 0;
		}
	}
	return ret;
}
