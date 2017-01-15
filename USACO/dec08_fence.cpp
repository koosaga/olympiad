#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

int n;
pi a[255], st;
vector<pi> v;
int dp[255][255];

int solve(int p){
	v.clear();
	for(int i=p; i<n; i++) v.push_back(a[i]);
	sort(v.begin()+1, v.end(), [&](const pi &a, const pi &b){
			return ccw(v[0], a, b) > 0;
			});
	int ret = 1;
	for(int i=0; i<v.size(); i++){
		vector<int> lo, hi;
		for(int j=0; j<i; j++) lo.push_back(j);
		for(int j=i+1; j<v.size(); j++) hi.push_back(j);
		sort(lo.begin(), lo.end(), [&](const int &a, const int &b){
				return ccw(v[i], v[a], v[b]) > 0;
				});
		sort(hi.begin(), hi.end(), [&](const int &a, const int &b){
				return ccw(v[i], v[a], v[b]) > 0;
				});
		int p = 0, w = 0;
		if(i == 0) w = 2;
		for(auto &j : hi){
			while(p < lo.size() && ccw(v[lo[p]], v[i], v[j]) > 0){
				w = max(w, dp[lo[p++]][i] + 1);
			}
			dp[i][j] = w;
		}
		for(int j=0; j<i; j++){
			if(ccw(v[j], v[i], v[0]) > 0) ret = max(ret, dp[j][i]);
		}
	}
	return ret;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
	}
	sort(a, a+n);
	int ret = 0;
	for(int i=0; i<n; i++){
		ret = max(ret, solve(i));
	}
	cout << ret;
}

