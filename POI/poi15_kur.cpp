#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using ll = long long;
const int MAXN = 1000005;

int n, a, b, p, m;
vector<int> w;

int f(int x){
	if(x < 0) return 0;
	return x + 1 - (int)(lower_bound(all(w), x + 1) - w.begin());
}

int main(){
	char str[MAXN];
	scanf("%d %d %d %d %d",&n,&a,&b,&p,&m);
	for(int i=n-m+1; i<n; i++) w.emplace_back(1ll * a * i % n);
	sort(all(w));
	scanf("%s", str);
	vector<pi> v;
	for(int i=0; i<m; i++){
		lint s, e;
		if(str[i] == '0') s = 0, e = p - 1;
		else s = p, e = n - 1;
		lint cur = (1ll * a * i + b) % n;
		s = (s - cur + n) % n;
		e = (e - cur + n) % n;
		if(s <= e){
			v.emplace_back(s, +1);
			v.emplace_back(e + 1, -1);
		}
		else{
			v.emplace_back(0, +1);
			v.emplace_back(e + 1, -1);
			v.emplace_back(s, +1);
			v.emplace_back(n, -1);
		}
	}
	sort(all(v));
	lint ret = 0;
	lint sum = 0;
	for(int i=0; i+1<sz(v); i++){
		sum += v[i].second;
		if(sum == m){
			ret += f(v[i+1].first - 1);
			ret -= f(v[i].first - 1);
		}
	}
	cout << ret << endl;
}

