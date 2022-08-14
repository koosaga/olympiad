#include "insects.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
 
int min_cardinality(int n){
	vector<int> v;
	for(int i = 0; i < n; i++){
		move_inside(i);
		if(press_button() > 1) move_outside(i);
		else v.push_back(i);
	}
	int s = 1, e = n / sz(v);
	set<int> cands;
	for(int i = 0; i < n; i++) cands.insert(i);
	for(auto &i : v) cands.erase(i);
	while(s != e){
		int m = (s + e + 1 + (e - s > 5)) / 2;
		vector<int> w;
		vector<int> outs;
		for(auto &i : cands){
			move_inside(i);
			if(press_button() > m){
				move_outside(i);
				outs.push_back(i);
			}
			else w.push_back(i);
		}
		if(sz(w) == sz(v) * (m - s)){
			s = m;
			for(auto &i : w) cands.erase(i);
		}
		else{
			for(auto &i : outs) cands.erase(i);
			for(auto &i : w) move_outside(i);
			e = m - 1;
		}
	}
	return s;
}
