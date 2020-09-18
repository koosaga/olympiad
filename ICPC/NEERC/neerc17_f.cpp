#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 305;

struct kek{
	pi x[3];
};

vector<kek> solve(int n, int a, int b){
	if(b < 0){
		auto v = solve(n, a, -b);
		for(auto &i : v){
			for(int j=0; j<3; j++){
				i.x[j].second *= -1;
			}
		}
		return v;
	}
	if(a < 0){
		auto v = solve(n, -a, b);
		for(auto &i : v){
			for(int j=0; j<3; j++){
				i.x[j].first *= -1;
			}
		}
		return v;
	}
	if(a < b){
		auto v = solve(n, b, a);
		for(auto &i : v){
			swap(i.x[0], i.x[2]);
			for(int j=0; j<3; j++){
				swap(i.x[j].first, i.x[j].second);
			}
		}
		return v;
	}
	int K = (a + b) / (2 * n - 1) + 1;
	K = max(K, a / n + 1);
	vector<kek> v;
	for(int i=0; i<K; i++){
		v.push_back({pi(i * n, i * (n - 1)), pi(i * n, (i + 1) * (n - 1)), pi(i * n + n - 1, (i + 1) * (n - 1))});
	}
	if((K - 1) * (n - 1) <= b && a <= K * n - 1){
		int delta_x = K * n - 1 - a;
		int delta_y = b - (K - 1) * (n - 1);
		int delta = max(delta_x, delta_y);
		if(delta < n - 1){
			for(int j = 0; j < sz(v); j++){
				for(int k = 0; k < 3; k++){
					v[j].x[k].second -= n - 1 - delta_y;
				}
			}
		}
		else{
			delta = K + n - 2 - delta;
			if(delta > 0){
				for(int j = sz(v) - delta; j < sz(v); j++){
					v[j].x[0] = v[j - 1].x[0]; v[j].x[0].second++;
					v[j].x[1] = v[j].x[0]; v[j].x[1].second += n - 1;
					v[j].x[2] = v[j].x[1]; v[j].x[2].first += n - 1;
				}
			}
		}
	}
	else{
		for(auto &i : v){
			i.x[2].second = min(i.x[2].second, b);
			i.x[1].second = min(i.x[1].second, b);
			i.x[0].second = i.x[1].second - n + 1;
		}
	}
	return v;
}

int main(){
	int tc; cin >> tc;
	while(tc--){
		int n, a, b; cin >> a >> b >> n;
		auto v = solve(n, a, b);
		printf("%d\n", sz(v));
		for(auto &i : v) printf("%d %d %d %d\n", i.x[0].first, i.x[0].second, i.x[2].first, i.x[2].second);
	}
}
