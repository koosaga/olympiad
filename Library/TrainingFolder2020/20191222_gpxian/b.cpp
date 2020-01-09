#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int mod = 998244353;

int n, l;

struct level{
	int s, e, l, r;
	bool operator<(const level &l)const{
		return s < l.s;
	}
};

int main(){
	scanf("%d %d",&n,&l);
	set<level> s;
	vector<pi> v;
	for(int i=0; i<n; i++){
		int x; scanf("%d",&x);
		v.emplace_back(x, i);
	}
	sort(all(v));
	int ptr = 0;
	lint dap = 0;
	for(int i = 1; ; i++){
		if(s.empty()){
			if(ptr == sz(v)) break;
			i = v[ptr].first;
		}
		int e = ptr;
		while(e < sz(v) && v[e].first == i) e++;
		for(int j=ptr; j<e; j++) s.insert({a[j].second, a[j].second, 1, 1});
		auto itr = s.begin();
		set<level> ns;
		while(itr != s.end()){
			auto nitr = itr;
			while(nitr != s.end() && next(nitr)->first == nitr->second + 1) nitr++;
			vector<level> tmp;
			while(itr != nitr){
				tmp.push_back(*itr); itr++;
			}
		}
		s = ns;
		ptr = e;
	}
	cout << dap << endl;
}
