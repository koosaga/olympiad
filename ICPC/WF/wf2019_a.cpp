#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 500005;
const int mod = 1e9 + 7;

struct point{
	int price, height, idx;
	bool operator<(const point &p)const{
		return pi(price, height) < pi(p.price, p.height);
	}
};

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<point> a(n), b(n);
	vector<int> ret1, ret2;
	for(int i = 0; i < n; i++) cin >> a[i].price;
	for(int i = 0; i < n; i++) cin >> a[i].height;
	for(int i = 0; i < n; i++) cin >> b[i].price;
	for(int i = 0; i < n; i++) cin >> b[i].height;
	for(int i = 0; i < n; i++) a[i].idx = b[i].idx = i + 1;
	sort(all(a));
	sort(all(b));
	int j0 = 0, j1 = 0;
	set<pi> s1, s2;
	for(int i = 0; i < n; i++){
		if(sz(s1) == 0){
			while(j0 < n && a[i].price == a[j0].price){
				s1.emplace(a[j0].height, a[j0].idx);
				j0++;
			}
		}
		if(sz(s2) == 0){
			while(j1 < n && b[i].price == b[j1].price){
				s2.emplace(b[j1].height, b[j1].idx);
				j1++;
			}
		}
		if(sz(s1) < sz(s2)){
			auto hi = *s1.begin(); s1.erase(s1.begin());
			auto it = s2.lower_bound(pi(hi.first, -1));
			if(it == s2.begin()){
				cout << "impossible\n";
				return 0;
			}
			ret1.push_back(hi.second);
			it--;
			ret2.push_back(it->second);
			s2.erase(it);
		}
		else{
			auto hi = *s2.begin(); s2.erase(s2.begin());
			auto it = s1.lower_bound(pi(hi.first + 1, -1));
			if(it == s1.end()){
				cout << "impossible\n";
				return 0;
			}
			ret1.push_back(it->second);
			ret2.push_back(hi.second);
			s1.erase(it);
		}
	}
	for(int i = 0; i < n; i++) cout << ret1[i] << " ";
	cout << "\n";
	for(int i = 0; i < n; i++) cout << ret2[i] << " ";
	cout << "\n";
}
