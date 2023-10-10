#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
lint a[30], d;

vector<lint> bktk(int s, int e, lint x){
	if(s == e){
		vector<lint> ans = {x};
		return ans;
	}
	auto m2 = bktk(s+1, e, x);
	auto m1 = m2;
	auto m3 = m2;
	for(auto &i : m1) i -= a[s];
	for(auto &i : m3) i += a[s];
	vector<lint> aux(m1.size() + m2.size());
	merge(m1.begin(), m1.end(), m2.begin(), m2.end(), aux.begin());
	vector<lint> ret(aux.size() + m3.size());
	merge(aux.begin(), aux.end(), m3.begin(), m3.end(), ret.begin());
	return ret;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i];
	cin >> d;
	auto v1 = bktk(0, n/2, 0);
	auto v2 = bktk(n/2, n, 0);
	int st = 0, ed = 0;
	lint ret = 0;
	for(auto &i : v1){
		while(ed < v2.size() && v2[ed] <= i + d) ed++;
		while(st < v2.size() && v2[st] < i - d) st++;
		ret += ed - st;
	}
	cout << ret;
}
