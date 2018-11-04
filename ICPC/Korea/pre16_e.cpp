#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using real_t = long double;
const int MAXN = 100005;

pi gakdo;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

struct seg{
	pi x, y;
	int idx;
};

real_t func(seg s){
	real_t a = s.y.second - s.x.second; 
	real_t b = s.x.first - s.y.first;
	real_t c = a * s.x.first + b * s.x.second; 
	real_t x = gakdo.first;
	real_t y = gakdo.second;
	return (c * y) / (a * x + b * y);
}

auto cmp = [](seg a, seg b){ return func(a) < func(b); };
set<seg, decltype(cmp)> s(cmp);

int visible[MAXN];
vector<seg> ins, del;

int main(){
	int n; scanf("%d",&n);
	vector<pi> ev;
	for(int i=0; i<n; i++){
		int m; scanf("%d",&m);
		vector<pi> v(m);
		for(auto &j : v) scanf("%d %d",&j.first,&j.second);
		for(int j=0; j<v.size(); j++){
			if(ccw(pi(0, 0), v[j], v[(j+1)%m]) < 0){
				ins.push_back({v[j], v[(j+1)%m], i});
				del.push_back({v[j], v[(j+1)%m], i});
				ev.push_back(v[j]);
				ev.push_back(v[(j+1)%m]);
			}
		}
	}
	sort(ev.begin(), ev.end(), [&](const pi &a, const pi &b){
		return ccw(pi(0, 0), a, b) < 0;
	});
	sort(ins.begin(), ins.end(), [&](const seg &a, const seg &b){
		return ccw(pi(0, 0), a.x, b.x) < 0;
	});
	sort(del.begin(), del.end(), [&](const seg &a, const seg &b){
		return ccw(pi(0, 0), a.y, b.y) < 0;
	});
	ev.resize(unique(ev.begin(), ev.end()) - ev.begin());
	int p = 0, q = 0;
	for(auto &i : ev){
		gakdo = i;
		while(q < del.size() && ccw(pi(0, 0), del[q].y, i) <= 0){
			auto k = s.lower_bound(del[q]);
			if(k != s.begin()) k--;
			while(true){
				if(k->x == del[q].x && k->y == del[q].y && k->idx == del[q].idx){
					s.erase(k);
					break;
				}
				k = next(k);
				assert(k != s.end());
			}
			q++;
		}
		while(p < ins.size() && ccw(pi(0, 0), ins[p].x, i) <= 0){
			s.insert(ins[p++]);
		}
		if(!s.empty()){
			visible[s.begin()->idx] = 1;
		}
	}
	cout << count(visible, visible + n, 0) << endl;
}
