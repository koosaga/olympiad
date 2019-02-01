#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;

struct intv{int s, e, x;}a[5005];
int n;

vector<pi> v;

bool ok(){
	vector<pi> w = v;
	sort(w.begin(), w.end(), [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	set<int> s;
	for(int i=1; i<=4999; i++) s.insert(i);
	for(int i=0; i<w.size(); i++){
		auto it = s.lower_bound(w[i].first);
		if(it != s.end() && *it < w[i].second){
			s.erase(it);
		}
		else return 0;
	}
	return 1;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].s >> a[i].e >> a[i].x;
	}
	sort(a, a+n, [&](const intv &a, const intv &b){
		return a.x > b.x;
	});
	int ret = 0;
	for(int i=0; i<n; i++){
		v.push_back(pi(a[i].s, a[i].e));
		if(!ok()) v.pop_back();
		else ret += a[i].x;
	}
	cout << ret;
}
