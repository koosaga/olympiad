#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, a[10005];

void mergex(int s1, int e1, int s2, int e2, vector<pi> &v){
	int p = 0;
	while(p < e1 - s1 + 1 && p < e2 - s2 + 1 && a[e1-p] > a[s2+p]) p++;
	if(p == 0) return;
	v.push_back({e1 - p + 1, s2 + p - 1});
	for(int i=0; i<p; i++){
		swap(a[s2+i], a[s2-p+i]);
	}
	mergex(s1, e1-p, e1-p+1, e1, v);
	mergex(s2, s2+p-1, s2+p, e2, v);
	return;
}

vector<pi> solve(int s, int e){
	if(s == e) return vector<pi>();
	int m = (s+e)/2;
	vector<pi> l = solve(s, m);
	vector<pi> r = solve(m+1, e);
	vector<pi> v;
	for(auto &i : l) v.push_back(i);
	for(auto &i : r) v.push_back(i);
	mergex(s, m, m+1, e, v);
	return v;
}

void solve(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	vector<pi> v = solve(1, n);
	printf("%d\n", v.size());
	for(auto &i : v){
		printf("%d %d\n",i.first, i.second);
	}
}

int main(){
	int t;
	cin >> t;
	while(t--){
		solve();
	}
}