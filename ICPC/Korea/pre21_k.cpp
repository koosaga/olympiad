#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main(){
	int n;
	scanf("%*d %*d %d",&n);
	vector<pi> a(n);
	for(auto &[x, y] : a) scanf("%d %d",&x,&y);
	sort(all(a));
	vector<int> v;
	for(auto &[x, y] : a){
		auto t = lower_bound(all(v), -y);
		if(t == v.end()) v.push_back(-y);
		else *t = -y;
	}
	cout << sz(v) << endl;
}
