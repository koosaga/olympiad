#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;

struct foo{
	int s, e, x;
	bool operator<(const foo &f)const{
		return s < f.s;
	}
};

lint s[MAXN];

int main(){
	int n, k, x;
	scanf("%d %d %d",&n,&k,&x);
	vector<foo> v;
	for(int i = 0; i < n; i++){
		int l, r, t; scanf("%d %d %d",&l,&t,&r);
		r++;
		int m = min(l + t, r);
		v.push_back({l, +1, 0});
		v.push_back({m, 0, +1});
		v.push_back({r, -1, -1});
	}
	sort(all(v));
	vector<foo> intv;
	{
		int ret = 0;
		int xs = 0;
		for(int i = 1; i < sz(v); i++){
			ret += v[i-1].e;
			xs += v[i-1].x;
			if(ret >= k && v[i-1].s != v[i].s){
				intv.push_back({v[i-1].s, v[i].s, xs});
			}
		}
	}
	lint ret = 0;
	for(int i = 0; i < 2; i++){
		for(int i = 0; i < sz(intv); i++){
			s[i + 1] = s[i] + 1ll * (intv[i].e - intv[i].s) * intv[i].x;
		}
		int j = 0;
		for(int i = 0; i < sz(intv); i++){
			while(j < sz(intv) && intv[j].e - intv[i].s <= x){
				j++;
			}
			lint sum = s[j] - s[i];
			if(j < sz(intv)){
				int l = intv[j].s;
				int r = min(intv[i].s + x, intv[j].e);
				if(l < r) sum += 1ll * (r - l) * intv[j].x;
			}
				ret = max(ret, sum);
		}
		reverse(all(intv));
		for(auto &i : intv){
			tie(i.s, i.e) = pi(1000000000 - i.e, 1000000000 - i.s);
		}
	}
	cout << ret << endl;
}
