#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

int px;

struct seg{
	int x1, y1, x2, y2, idx;
	double eval(){
		return y1 + 1.0 * (y2 - y1) / (x2 - x1) * (px - x1);
	}
	bool operator==(const seg &a){
		return x1 == a.x1 && y1 == a.y1 && x2 == a.x2 && y2 == a.y2 && idx == a.idx;
	}
}a[100005];

struct event{
	int pos, mode;
	seg val;
};

vector<event> evnt;

int n;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d %d",&a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
		a[i].idx = i;
		evnt.push_back({a[i].x1, 1, a[i]});
		evnt.push_back({a[i].x2, -1, a[i]});
	}
	sort(evnt.begin(), evnt.end(), [&](const event &a, const event &b){
		return a.pos < b.pos;
	});
	auto cmp = [](seg a, seg b){
		return a.eval() < b.eval();
	};
	set<seg, decltype(cmp) > s(cmp);
	set<int> ret;
	seg current = a[0];
	ret.insert(a[0].idx);
	for(int i=0; i<evnt.size(); i++){
		int e = i;
		while(e < evnt.size() && evnt[i].pos == evnt[e].pos) e++;
		px = evnt[i].pos;
		bool danger = 0;
		for(int j=i; j<e; j++){
			if(evnt[j].mode == 1){
				s.insert(evnt[j].val);
			}
			else{
				if(evnt[j].val == current){
					danger = 1;
				}
				s.erase(evnt[j].val);
			}
		}
		if(danger){
			auto t = s.lower_bound(current);
			if(t == s.begin()) break;
			t--;
			current = *t;
			ret.insert(current.idx);
		}
		i = e-1;
	}
	cout << ret.size();
}