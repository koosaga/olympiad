#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 270005;

struct node{
	int x, y, h;
};

bool solve(vector<int> v){
	sort(all(v));
	for(int i = 2; i < sz(v); i++){
		if(v[i - 2] + v[i - 1] > v[i]) return true;
	}
	return false;
}

vector<pi> tree[MAXT];
int lim;

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	for(lim = 1; lim <= n; lim <<= 1);
	vector<int> v;
	vector<node> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i].x >> a[i].y >> a[i].h;
		v.push_back(a[i].x);
	}
	sort(all(v));
	for(int i = 0; i < n; i++){
		a[i].x = lower_bound(all(v), a[i].x) - v.begin();
		for(int j = a[i].x + lim; j >= 1; j >>= 1){
			tree[j].emplace_back(a[i].y, a[i].h);
		}
	}
	for(int i = 0; i < MAXT; i++) sort(all(tree[i]));
	for(int i = 0; i < q; i++){
		int sx, ex, sy, ey;
		cin >> sx >> sy >> ex >> ey;
		sx = lower_bound(all(v), sx) - v.begin();
		ex = upper_bound(all(v), ex) - v.begin() - 1;
		sx += lim;
		ex += lim;
		vector<int> vect;
		auto Do = [&](int v){
			auto l = lower_bound(all(tree[v]), pi(sy, -1));
			while(sz(vect) < 69 && l != tree[v].end() && l->first <= ey){
				vect.emplace_back(l->second);
				l++;
			}
		};
		while(sx < ex){
			if(sx%2 == 1) Do(sx++);
			if(ex%2 == 0) Do(ex--);
			sx >>= 1;
			ex >>= 1;
		}
		if(sx == ex) Do(sx);
		cout << (solve(vect) ? "1" : "0") << "\n";
	}
}
