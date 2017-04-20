#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int n;
vector<int> v;

set<vector<int> > sol;

void solve(int p, int q, int r){
	multiset<int> ms;
	for(auto &i : v) ms.insert(i);
	ms.erase(ms.find(p+q));
	ms.erase(ms.find(q+r));
	ms.erase(ms.find(p+r));
	vector<int> v = {p, q, r};
	for(int i=3; i<n; i++){
		int l = *ms.begin() - v[0];
		for(auto &j : v){
			if(ms.find(j + l) == ms.end()) return;
			ms.erase(ms.find(j + l));
		}
		if(v.back() >= l) return;
		v.push_back(l);
	}
	sol.insert(v);
}

int main(){
	cin >> n;
	for(int i=0; i<n*(n-1)/2; i++){
		int x;
		cin >> x;
		v.push_back(x);
	}
	sort(v.begin(), v.end());
	for(int i=2; i<n; i++){
		int ab = v[0];
		int ac = v[1];
		int bc = v[i];
		if((ab + ac + bc) % 2 == 0){
			int abc = (ab + ac + bc) / 2;
			solve(abc - bc, abc - ac, abc - ab);
		}
	}
	cout << sol.size() << endl;
	for(auto &i : sol){
		for(auto &j : i) printf("%d ", j);
		puts("");
	}
}
