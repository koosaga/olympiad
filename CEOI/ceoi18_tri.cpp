#include <bits/stdc++.h>
#include "trilib.h"
using namespace std;
int n;

bool ccw(int a, int b, int c){ 
	return is_clockwise(a + 1, b + 1, c + 1);
}

vector<int> hull(vector<int> v){
	sort(v.begin() + 1, v.end(), [&](const int &a, const int &b){
		return ccw(v[0], a, b); 
	});
	vector<int> h;
	for(auto &i : v){
		while(h.size() >= 2 && !ccw(h[h.size()-2], h.back(), i)) h.pop_back();
		h.push_back(i);
	}
	return h;
}

void compute(int x){
	vector<int> v = {x};
	for(int i=0; i<n; i++) if(x != i) v.push_back(i);
	give_answer(hull(v).size());
	exit(0);
}

int main(){
	n = get_n();
	vector<int> up, dn;
	for(int i=2; i<n; i++){
		if(ccw(0, 1, i)) up.push_back(i);
		else dn.push_back(i);
	}
	if(up.empty() || dn.empty()) compute(0);
	if(up.size() == 1) compute(up[0]);
	if(dn.size() == 1) compute(dn[0]);
	up.insert(up.begin(), 1);
	dn.insert(dn.begin(), 0);
	up = hull(up);
	dn = hull(dn);
	auto proc = [&](){
		int st = 0, ed = dn.size() - 1;
		for(int i=0; i<up.size(); i++){
			while(st <= ed && ccw(up[i], up[(i+1)%up.size()], dn[st])) st++;
			while(st <= ed && ccw(up[i], up[(i+1)%up.size()], dn[ed])) ed--;
			if(st > ed){
				bool bad = false;
				for(auto &j : dn){
					if(!ccw(up[i], up[(i+1)%up.size()], j)){
						bad = true;
						break;
					}
				}
				if(bad) break;
				st = 0, ed = dn.size() - 1;
				int range_st = i, range_ed = (i + 1) % up.size();
				for(int i=up.size()-1; i>=0; i--){
					while(st <= ed && ccw(up[i], up[(i+1)%up.size()], dn[st])) st++;
					while(st <= ed && ccw(up[i], up[(i+1)%up.size()], dn[ed])) ed--;
					if(st > ed){
						range_ed = (i + 1) % up.size();
						break;
					}
				}
				int ans = 2;
				for(int i=0; i<dn.size(); i++){
					if(ccw(up[range_st], dn[i], dn[(i+1)%dn.size()]) &&
							ccw(up[range_ed], dn[i], dn[(i+1)%dn.size()])){
						ans++;
					}
				}
				do{
					ans++;
					range_st++;
					range_st %= up.size();
				}while(range_st != range_ed);
				give_answer(ans);
				exit(0);
			}
		}
	};
	proc();
	swap(up, dn);
	proc();
	assert(0);
}
