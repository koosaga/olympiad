#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<int> a(n);
	vector<int> cnt(n);
	vector<vector<int>> Q(n);
	set<pi> ordIndex, ordCount;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i]--;
		cnt[a[i]]++;
		Q[a[i]].push_back(i + 1);
		if(cnt[a[i]] > (n + 1) / 2){
			cout << "-1\n";
			return 0;
		}
	}
	for(int i = 0; i < n; i++){
		if(cnt[i] == 0) continue;
		reverse(all(Q[i]));
		ordIndex.emplace(Q[i].back(), i);
		ordCount.emplace(cnt[i], i);
	}
	int prev = -1;
	for(int i = 0; i < n; i++){
		int i1 = ordIndex.begin()->second;
		if(i1 == prev) i1 = next(ordIndex.begin())->second;
		int i2 = ordCount.rbegin()->second;
		auto canStart = [&](int P){
			if(P == prev) return false;
			auto ptr = ordCount.rbegin();
			for(int it = 0; it < 3 && ptr != ordCount.rend(); it++){
				if(ptr->second != P && ptr->first > (n - i) / 2) return false;
				ptr++;
			}
			return true;
		};
		auto insert = [&](int P){
			ordIndex.erase(pi(Q[P].back(), P));
			ordCount.erase(pi(cnt[P], P));
			cnt[P]--;
			cout << Q[P].back() << " ";
			Q[P].pop_back();
			if(cnt[P] > 0){
				ordCount.emplace(cnt[P], P);
				ordIndex.emplace(Q[P].back(), P);
			}
			prev = P;
		};
		if(canStart(i1)) insert(i1);
		else insert(i2);
	}
}
