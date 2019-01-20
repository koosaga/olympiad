#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2505;
using pi = pair<int, int>;

int n;
int a[MAXN];
int dp[250000];

int f(int l){
	vector<vector<pi>> v;
	for(int i=0; i<n; ){
		int e = i;
		int sum = -1;
		while(e < n && sum + a[e] + 1 <= l){
			sum += a[e++] + 1;
		}
		int cur = 0;
		vector<pi> tmp;
		for(int j=i; j<e-1; j++){
			cur += a[j];
			tmp.emplace_back(cur, 1);
			cur++;
		}
		v.push_back(tmp);
		i = e;
	}
	int ret = 0;
	for(int i=1; i<v.size(); i++){
		for(auto &j : v[i-1]) dp[j.first] = j.second;
		for(auto &j : v[i]){
			j.second = max({dp[j.first - 1], dp[j.first], dp[j.first + 1]}) + 1;
		}
		for(auto &j : v[i-1]) dp[j.first] = 0;
	}
	for(auto &i : v) for(auto &j : i) ret = max(ret, j.second);
	return ret;
}

int main(){
	scanf("%d",&n);
	char buf[101];
	int maxl = 0, sum = n - 1;
	for(int i=0; i<n; i++){
		scanf("%s", buf);
		a[i] = strlen(buf);
		sum += a[i];
		maxl = max(maxl, a[i]);
	}
	int cur = -1;
	int yi = -1;
	for(int i=maxl; i<=sum; i++){
		int w = f(i);
		if(w > cur){
			cur = w;
			yi = i;
		}
	}
	printf("%d %d\n", yi, cur);
}
