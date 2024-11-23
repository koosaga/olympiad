#include <bits/stdc++.h>
using namespace std;

namespace std {

template<class Fun>
class y_combinator_result {
	Fun fun_;
public:
	template<class T>
	explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

	template<class ...Args>
	decltype(auto) operator()(Args &&...args) {
		return fun_(std::ref(*this), std::forward<Args>(args)...);
	}
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
	return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

} // namespace std

#include<bits/stdc++.h>
// #include<bits/extc++.h>
#include <ext/pb_ds/assoc_container.hpp>

struct splitmix64_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}

	size_t operator()(pair<int,int> x) const {
		return splitmix64(x.first) ^ (splitmix64(x.second) << 4);
	}
};

template <typename K, typename V, typename Hash = splitmix64_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = splitmix64_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;


int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int N;
	cin >> N;
	int S = 10001;
	vector<pair<int,int> > pts;

	vector<int> coords;
	for(int i = 0; i < N; i++){
		int x, y;
		cin >> x >> y;
		assert(y % 9999 == 0);
		y /= 9999;
		y += 1;
		pts.push_back({x, y});
		assert(y >= 0 && y <= 2);
		coords.push_back(x);
	}
	sort(coords.begin(), coords.end());
	sort(pts.begin(), pts.end());
	vector<vector<int> > side(3);
	vector<vector<int> > side_idx(3); // index back to pts

	vector<pair<int,int> > where(N); // pointer to side
	for(int i = 0; i < N; i++){
		where[i] = {pts[i].second, side[pts[i].second].size()};
		side[pts[i].second].push_back(pts[i].first);
		side_idx[pts[i].second].push_back(i);
	}
	vector<vector<int> > nxt_points(3, vector<int>(N+1, N));
	for(int i = 0; i < 3; i++){
		int idx = 0;
		for(int j = 0; j < N; j++){
			int loc = pts[j].first;
			while(idx < (int)side[i].size() && side[i][idx] < loc){
				idx++;
			}
			if(idx == (int)side[i].size()){
				nxt_points[i][j] = N;
			} else {
				nxt_points[i][j] = side_idx[i][idx];
			}
		}
	}

	vector<int> go_next(N+1, N);
	for(int i = 0; i < N; i++){
		go_next[i] = lower_bound(coords.begin(), coords.end(), coords[i] + S) - coords.begin();
	}

	hash_map<pair<int,int>, int> dp;

	int vis = 0;
	auto solve = y_combinator([&](auto self, int x, int y) -> int {
		if(dp.find({x, y}) == dp.end()){
			vis += 1;
			dp[{x, y}] = [&]() -> int {
				int nxt_top = nxt_points[0][x];
				int nxt_mid = nxt_points[1][max(x, y)];
				int nxt_bot = nxt_points[2][y];
				if(nxt_top == N && nxt_mid == N && nxt_bot == N){
					return 0;
				}
				if(nxt_top <= nxt_mid && nxt_top <= nxt_bot){
					return 1 + self(go_next[nxt_top], y);
				} else if(nxt_bot <= nxt_top && nxt_bot <= nxt_mid){
					return 1 + self(x, go_next[nxt_bot]);
				} else {	
					return 1 + min(self(go_next[nxt_mid], nxt_mid), self(nxt_mid, go_next[nxt_mid]));
				}
			}();
		}
		return dp[{x, y}];
	});
	int ans = solve(0, 0);
	cout << ans << '\n';
}
