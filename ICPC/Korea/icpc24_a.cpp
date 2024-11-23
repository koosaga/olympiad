#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int N, M;
	cin >> N >> M;
	vector<vector<pair<int, int> > > people(M);
	for(int i = 0; i < N; i++){
		vector<int> range;
		int cur = 0;
		for(int j = 0; j < M; j++){
			int x;
			cin >> x;
			people[j].push_back({cur, cur + x});
			cur += x;
		}
	}
	for(int j = 0; j < M; j++){
		map<int, int> freq;
		for(auto [l, r] : people[j]){
			freq[l]++;
			freq[r]--;
		}
		int ans = 0;
		int cur = 0;
		for(auto [x, f] : freq){
			cur += f;
			ans = max(ans, cur);
		}
		cout << ans << " \n"[j == M-1];
	}
}
