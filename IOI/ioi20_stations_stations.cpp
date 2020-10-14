#include "stations.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

int find_next_station(int s, int t, std::vector<int> c) {
	if(sz(c) == 1) return c[0];
	if(s < c[0]){ // din
		for(int i=0; i<sz(c)-1; i++){
			if(s <= t && t <= c[i]) return c[i];
		}
		return c.back();
	}
	else{
		for(int i=sz(c)-1; i>=1; i--){
			if(c[i] <= t && t <= s) return c[i];
		}
		return c[0];
	}
}
