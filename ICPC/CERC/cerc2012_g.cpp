#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int inf = 1e9 + 100;

vector<pi> pnt, cnt[200005];
int n, k;

struct seg{
	int s, e, h;
};

vector<seg> qry;
vector<int> vx;

struct bit{
	int tree[200005], lim;
	void init(int n){
		lim = n;
		for(int i=1; i<=n; i++) tree[i] = 0;
	}
	void add(int x, int v = 1){
		while(x <= lim){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int solve(){
	vx.clear();
	for(auto &i : pnt){
		vx.push_back(i.first);
	}
	sort(vx.begin(), vx.end());
	vx.erase(unique(vx.begin(), vx.end()), vx.end());
	for(auto &i : pnt){
		i.first = lower_bound(vx.begin(), vx.end(), i.first) - vx.begin() + 1;
	}
	bit.init(vx.size());
	sort(pnt.begin(), pnt.end(), [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	sort(qry.begin(), qry.end(), [&](const seg &a, const seg &b){
		return a.h < b.h;
	});
	int ret = 0, p = 0;
	for(auto &i : qry){
		while(p < pnt.size() && pnt[p].second <= i.h){
			bit.add(pnt[p].first);
			p++;
		}
		int p = lower_bound(vx.begin(), vx.end(), i.s) - vx.begin();
		int q = upper_bound(vx.begin(), vx.end(), i.e) - vx.begin();
		ret = max(ret, bit.query(q) - bit.query(p));
	}
	return ret;
}

int main(){
	int t;
	cin >> t;
	while(t--){
		scanf("%d %d",&n,&k);
		for(int i=0; i<n; i++){
			int x, y, c;
			scanf("%d %d %d",&x,&y,&c);
			pnt.push_back({x, y});
			cnt[c].push_back({x, y});
		}
		for(int i=1; i<=k; i++){
			sort(cnt[i].begin(), cnt[i].end());
			vector<pi> tmp;
			tmp.push_back({0, 0});
			for(int j=0; j<cnt[i].size(); j++){
				if(!tmp.empty() && tmp.back().first == cnt[i][j].first){
					continue;
				}
				tmp.push_back(cnt[i][j]);
			}
			tmp.push_back({inf, 0});
			for(int i=1; i<tmp.size(); i++){
				qry.push_back({tmp[i-1].first + 1, tmp[i].first - 1, inf});
			}
			stack<pi> stk;
			for(auto &j : tmp){
				while(!stk.empty() && stk.top().second >= j.second){
					auto up = stk.top();
					stk.pop();
					int lft = (stk.size() ? stk.top().first : 0);
					qry.push_back({lft + 1, j.first - 1, up.second - 1});
				}
				stk.push(j);
			}
		}
		printf("%d\n", solve());
		for(int i=1; i<=k; i++){
			cnt[i].clear();
		}
		pnt.clear(); qry.clear();
	}
}