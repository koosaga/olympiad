#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
const int mod = 1e9 + 7;

lint ipow(lint x, lint p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

namespace solveA{
	vector<pi> v = {pi(1, 0)};
	pi fx(1, 0);
	void add(lint x){
		if(x == 0){
			fx.first = fx.first * ((mod + 1) / 2) % mod;
			fx.second = (fx.second << 1) % mod;
			pi cur(2, 1);
			cur.second += mod - fx.second;
			cur.first = cur.first * fx.first % mod;
			cur.second = cur.second * fx.first % mod;
			v.push_back(cur);
		}
		else{
			fx.second = (fx.second + x) % mod;
			pi cur(1, 0);
			cur.second += mod - fx.second;
			cur.first = cur.first * fx.first % mod;
			cur.second = cur.second * fx.first % mod;
			v.push_back(cur);
		}
	}
	int query(int x, int g){
		x--;
		lint dap = (v[g].first * x + v[g].second) % mod;
		return (dap * ipow(fx.first, mod - 2) + fx.second) % mod;
	}
}

namespace solveB{
	int tot = 0;
	vector<vector<lint>> grp = { {0} };
	void add(lint x){
		tot++;
		if(x == 0){
			if(grp.back()[0] != 0){
				grp.push_back({0});
			}
			else grp.back().push_back(0);
		}
		else{
			if(grp.back()[0] == 0){
				grp.push_back({x});
			}
			else{
				x += grp.back().back();
				grp.back().push_back(x);
			}
		}
	}
	int query(int x){
		int cnt = 0;
		for(int i=sz(grp)-1; i>=0; i--){
			if(grp[i].back() == 0){
				for(int j=0; j<sz(grp[i]); j++){
					if(x == 0){
						cnt += sz(grp[i]) - j;
						break;
					}
					if(x % 2 == 1) return tot - cnt;
					x /= 2;
					cnt++;
				}
			}
			else{
				if(x >= grp[i].back()){
					x -= grp[i].back();
					cnt += sz(grp[i]);
				}
				else{
					int l = lower_bound(grp[i].begin(), grp[i].end(), grp[i].back() - x) - grp[i].begin();
					cnt += sz(grp[i]) - l - 1;
					return tot - cnt;
				}
			}
		}
		return 0;
	}
}

int main(){
	int q;
	scanf("%d",&q);
	while(q--){
		int t; scanf("%d",&t);
		if(t == 1){
			int x; scanf("%d",&x);
			solveA::add(x);
			solveB::add(x);
		}
		if(t == 2){
			int g, x; scanf("%d %d",&g,&x);
			printf("%d\n", solveA::query(x, g));
		}
		if(t == 3){
			int x; scanf("%d",&x);
			printf("%d\n", solveB::query(x));
		}
	}
}
