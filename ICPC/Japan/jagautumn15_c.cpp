#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 505;

int n, a[MAXN], b[MAXN], chk[MAXN];

int f(int s, int e, int x){
	if(s == e){
		int ret = 0;
		if(a[s] <= x){
			chk[s] = 1;
			ret++;
		}
		return ret;
	}
	int p = max_element(b+s, b+e) - b;
	int ans = f(s, p, b[p]) + f(p+1, e, b[p]);
	int ok = 0;
	for(int i=s; i<=e; i++){
		if(!chk[i] && a[i] <= x){
			ok = 1;
		}
	}
	if(ok){
		ans++;
		for(int i=s; i<=e; i++){
			chk[i] = 1;
		}
	}
	return ans;
}

int main(){
	cin >> n;
	vector<pi> sl, tl;
	for(int i=0; i<n; i++){
		string s; int t;
		cin >> s >> t;
		if(s == "y") sl.push_back(pi(1, t));
		else sl.push_back(pi(2, t));
	}
	for(int i=0; i<sl.size(); ){
		int e = i;
		int minv = 1e9, maxv = -1e9;
		while(e < sl.size() && sl[i].first == sl[e].first){
			minv = min(minv, sl[e].second);
			maxv = max(maxv, sl[e].second);
			e++;
		}
		if(sl[i].first == 1) tl.push_back(pi(1, minv));
		else tl.push_back(pi(2, maxv));
		i = e;
	}
	if(!tl.empty() && tl.front().first == 2) tl.erase(tl.begin());
	if(!tl.empty() && tl.back().first == 2) tl.erase(--tl.end());
	if(tl.size() == 0){
		cout << 0;
		return 0;
	}
	for(int i=0; i+1<tl.size(); i+=2){
		a[i/2] = tl[i].second;
		b[i/2] = tl[i+1].second;
	}
	a[tl.size()/2] = tl.back().second;
	n = tl.size() / 2 + 1;
	cout << f(0, n - 1, 1e9);
}
