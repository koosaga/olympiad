#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

int n, s;

struct event{
	int mode, pos, x, y, dx;
	bool operator<(const event &e)const{
		return pos < e.pos;
	}
};

vector<event> v;
vector<int> pt;

lint tot, coeff;

void add(event e){
	if(e.mode == 1){
		tot += e.dx * e.y;
	}
	if(e.mode == 2){
		coeff += e.dx;
		tot -= e.dx * e.x;
	}
	if(e.mode == 3){
		coeff -= e.dx;
		tot += e.dx * e.x;
	}
	if(e.mode == 4){
		tot += e.dx * e.y;
	}
	if(e.mode == 5){
		tot += e.dx * (e.x + e.y + s);
		coeff -= e.dx;
	}
	if(e.mode == 6){
		tot += e.dx * (s - e.x - e.y);
		coeff += e.dx;
	}
	if(e.mode == 7){
		tot += e.dx * (s - e.y + e.x);
		coeff -= e.dx;
	}
	if(e.mode == 8){
		tot += e.dx * (s + e.y - e.x);
		coeff += e.dx;
	}
}

int main(){
	cin >> n >> s;
	for(int i=0; i<n; i++){
		int x, y;
		scanf("%d %d",&y,&x);
		y = abs(y);
		tot += y;
		if(y >= s){
			pt.push_back(x-y);
			pt.push_back(x);
			pt.push_back(x+y);
			v.push_back({3, x-y, x, y, 1});
			v.push_back({2, x, x, y, 1});
			v.push_back({1, x+y, x, y, 1});
			v.push_back({4, x-y, x, y, -1});
			v.push_back({3, x, x, y, -1});
			v.push_back({2, x+y, x, y, -1});
		}
		else{
			pt.push_back(x-y);
			pt.push_back(x);
			pt.push_back(x+y);
			pt.push_back(x-s);
			pt.push_back(x+s);
			v.push_back({8, x-s, x, y, 1});
			v.push_back({7, x-y, x, y, 1});
			v.push_back({6, x, x, y, 1});
			v.push_back({5, x+y, x, y, 1});
			v.push_back({1, x+s, x, y, 1});
			v.push_back({4, x-s, x, y, -1});
			v.push_back({8, x-y, x, y, -1});
			v.push_back({7, x, x, y, -1});
			v.push_back({6, x+y, x, y, -1});
			v.push_back({5, x+s, x, y, -1});
		}
	}
	lint ret = tot;
	sort(pt.begin(), pt.end());
	sort(v.begin(), v.end());
	pt.resize(unique(pt.begin(), pt.end()) - pt.begin());
	int p = 0;
	for(int i=0; i<pt.size(); i++){
		while(p < v.size() && pt[i] == v[p].pos){
			add(v[p++]);
		}
		ret = min(ret, tot + 1ll * pt[i] * coeff);
	}
	cout << ret;
}