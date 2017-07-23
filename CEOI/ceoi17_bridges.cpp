#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int MAXN = 100005;

int n, a[MAXN];
lint b[MAXN], dp[MAXN];

struct cht{
	vector<pi> buf;
	vector<pi> cht;
	bool ccw(pi a, pi b, pi c){
		lint dx1 = b.first - a.first;
		lint dy1 = b.second - a.second;
		lint dx2 = c.first - b.first;
		lint dy2 = c.second - b.second;
		return -dy1 * dx2 >= -dy2 * dx1;
	}
	void renew(){
		sort(buf.begin(), buf.end());
		vector<pi> nxt(buf.size() + cht.size());
		merge(buf.begin(), buf.end(), cht.begin(), cht.end(), nxt.begin());
		buf.clear();
		cht.clear();
		for(auto &i : nxt){
			if(!cht.empty() && cht.back().first == i.first) cht.pop_back();
			while(cht.size() >= 2 && ccw(cht[cht.size() - 2], cht.back(), i)){
				cht.pop_back();
			}
			cht.push_back(i);
		}
	}
	void add(lint x, lint y){
		buf.push_back(pi(x, y));
		if(buf.size() == 400) renew();
	}
	lint query(int x){
		lint ret = -1e18;
		for(auto &i : buf) ret = max(ret, i.first * x + i.second);
		if(!cht.empty()){
			int s = 0, e = cht.size() - 1;
			while(s != e){
				int m = (s+e)/2;
				if(cht[m].first * x + cht[m].second > cht[m+1].first * x + cht[m+1].second){
					e = m;
				}
				else s = m+1;
			}
			ret = max(ret, cht[s].first * x + cht[s].second);
		}
		return ret;
	}
}cht;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	for(int i=0; i<n; i++) scanf("%lld",&b[i]), b[i] += (i ? b[i-1] : 0);
	for(int i=1; i<n; i++){
		cht.add(2 * a[i-1], -(dp[i-1] + 1ll * a[i-1] * a[i-1] - b[i-1]));
		dp[i] = -cht.query(a[i]) + 1ll * a[i] * a[i] + b[i-1];
	}
	cout << dp[n-1];
}
