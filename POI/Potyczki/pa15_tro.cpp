#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 2005;

lint dot(pi a, pi b){
	return 1ll * a.first * b.first + 1ll * a.second * b.second;
}

lint ccw(pi a, pi b){
	return 1ll * a.first * b.second - 1ll * b.first * a.second;
}

lint solve(vector<pi> &v, lint x){
	int p = 0;
	lint ret = 0;
	for(int i=0; i<v.size(); ){
		while(p < v.size() && dot(v[i], v[p]) > 0) p++;
		int q = p;
		while(q < v.size() && dot(v[i], v[q]) >= 0) q++;
		int e = i;
		while(e < v.size() && ccw(v[i], v[e]) == 0) e++;
		for(int j=i; j<e; j++){
			int s = p, e = q;
			while(s != e){
				int m = (s+e)/2;
				if(ccw(v[j], v[m]) > x) e = m;
				else s = m+1;
			}
			ret += s - p;
		}
		i = e;
	}
	return ret;
}

int n, x[MAXN], y[MAXN];
lint l, r;

int main(){
	scanf("%d %lld %lld",&n,&l,&r);
	l <<= 1;
	r <<= 1;
	for(int i=0; i<n; i++){
		scanf("%d %d",&x[i],&y[i]);
	}
	lint ans = 0;
	for(int i=0; i<n; i++){
		vector<pi> v;
		for(int j=0; j<n; j++){
			if(i == j) continue;
			if(pi(x[j], y[j]) < pi(x[i], y[i])){
				v.push_back(pi(x[i] - x[j], y[i] - y[j]));
			}
			else{
				v.push_back(pi(x[j] - x[i], y[j] - y[i]));
			}
		}

			sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
				lint k = ccw(a, b);
				if(k != 0) return k > 0;
				return dot(a, a) < dot(b, b);
			});
			ans += solve(v, r) - solve(v, l-1);
	}
	cout << ans << endl;
}
