#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

void minconv(vector<lint> &v, int cnt, int d){
	for(int i = 1; i <= cnt; i *= 2){
		for(int j = sz(v) - 1; j >= i * d; j--){
			v[j] = min(v[j], v[j - i * d] + i);
		}
		cnt -= i;
	}
	for(int j = sz(v) - 1; j >= cnt * d; j--){
		v[j] = min(v[j], v[j - cnt * d] + cnt);
	}
}

void maxconv(vector<lint> &v, int cnt, int d){
	for(int i = 1; i <= cnt; i *= 2){
		for(int j = sz(v) - 1; j >= i * d; j--){
			v[j] = max(v[j], v[j - i * d] + i);
		}
		cnt -= i;
	}
	for(int j = sz(v) - 1; j >= cnt * d; j--){
		v[j] = max(v[j], v[j - cnt * d] + cnt);
	}
}

vector<lint> solve(vector<lint> v, lint L, int thres){
	if(L < 0){
		vector<lint> ans(thres + 1, -1e18);
		return ans;
	}
	if(L - thres < 0){
		vector<lint> up(L + 1, -1e18);
		up[0] = 0;
		for(int j = 0; j < sz(v); j++){
			maxconv(up, min(L, v[j]), j + 1);
		}
		while(sz(up) <= thres) up.insert(up.begin(), -1e18);
		return up;
	}
	L -= thres;
	lint sum = 0;
	for(int i = 0; i < sz(v); i++){
		lint delta = L / (i + 1);
		if(delta <= v[i]){
			sum += delta;
			L %= (i + 1); 
			vector<lint> up(1 + 2 * sz(v) * sz(v), 1e18);
			vector<lint> dn(1 + 2 * sz(v) * sz(v), -1e18);
			up[0] = dn[0] = 0;
			for(int j = 0; j <= i; j++){
				lint val = (j < i ? v[j] : delta);
				val = min(val, 2 * (lint)sz(v));
				minconv(up, val, j + 1);
			}
			for(int j = i; j < sz(v); j++){
				lint val = (j > i ? v[j] : (v[j] - delta));
				val = min(val, 2 * (lint)sz(v));
				maxconv(dn, val, j + 1);
			}
			vector<lint> ans(thres + 1, -1e18);
			for(int p = 0; p <= thres; p++){
				for(int x = L; x < sz(dn); x++){
					ans[p] = max(ans[p], dn[x] - up[x - L] + sum); 
				}
				L++;
			}
			return ans;
		}
		else{
			sum += v[i];
			L -= (i + 1) * v[i];
		}
	}
	vector<lint> ans(thres + 1, -1e18);
	return ans;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lint m, l;
	cin >> m >> l;
	vector<lint> lo(m), hi(m); lint zero;
	lint negsum = 0, possum = 0;
	for(int i = m - 1; i >= 0; i--){
		cin >> lo[i];
		negsum += lo[i] * (i + 1);
	}
	cin >> zero;
	for(int i = 0; i < m; i++){
		cin >> hi[i];
		possum += hi[i] * (i + 1);
	}
	if(l < -negsum || possum < l){
		cout << "impossible\n";
		return 0;
	}
	lint ans = -1e18;
	auto sol0 = solve(lo, negsum, m);
	auto sol1 = solve(hi, l + negsum, m);
	auto sol2 = solve(hi, possum, m);
	auto sol3 = solve(lo, possum - l, m);
	for(int i = 0; i <= m; i++){
		ans = max(ans, sol0[i] + sol1[i]);
		ans = max(ans, sol2[i] + sol3[i]);
	}
	ans += zero;
	if(ans < 0) cout << "impossible\n";
	else cout << ans << "\n";
}
