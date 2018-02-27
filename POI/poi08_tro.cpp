#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 3005;

int n;
pi a[MAXN];

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
	}
	sort(a, a+n);
	lint ans = 0;
	for(int i=0; i<n; i++){
		vector<pi> v;
		for(int j=i+1; j<n; j++){
			v.emplace_back(a[j].first - a[i].first, a[j].second - a[i].second);
		}
		sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
			return a.first * b.second > b.first * a.second;
		});
		lint sx = 0, sy = 0;
		for(int j=0; j<v.size(); j++){
			ans += sx * v[j].second - sy * v[j].first;
			sx += v[j].first;
			sy += v[j].second;
		}
	}
	printf("%lld.%lld\n", ans / 2, (ans % 2) * 5);
}

