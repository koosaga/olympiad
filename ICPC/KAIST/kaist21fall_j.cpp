#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

bool shorter_period(vector<int> v){
	for(int i = 1; i < sz(v); i++){
		if(sz(v) % i == 0){
			bool ok = 0;
			for(int j = i; j < sz(v); j++){
				if(v[j] != v[j - i]) ok = 1;
			}
			if(!ok) return 1;
		}
	}
	return 0;
}

int main(){
	int n; scanf("%d",&n);
	vector<pi> a(n);
	for(int i = 0; i < n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	sort(all(a));
	set<int> s;
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			if(a[i].second != a[j].second){
				int val = a[j].first - a[i].first;
				for(int k = 1; k * k <= val; k++){
					if(val % k == 0){
						s.insert(k);
						s.insert(val / k);
					}
				}
			}
		}
	}
	for(int i = 1; i <= n; i++){
		if(s.find(i) != s.end()) continue;
		vector<int> pos(i);
		bool bad = 0;
		for(auto &[x, y] : a){
			int val = (x % i + i) % i;
			if(pos[val] && pos[val] != y){
				bad = 1;
				break;
			}
			pos[val] = y;
		}
		if(bad){
			s.insert(i);
			continue;
		}
		if(count(all(pos), 0) != 0) continue;
		if(shorter_period(pos)) s.insert(i);
	}
	int cnt = 0;
	lint sum = 0;
	for(auto &i : s){
		cnt += 1;
		sum += i;
	}
	printf("%d %lld\n", cnt, sum);
}
