#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXM = 1005;
using pi = pair<int, int>;
#define sz(v) int((v).size())

int n, a[MAXM];

int query(int x, int y, int z){
	printf("%d %d %d\n", x, y, z);
	fflush(stdout);
	int v; cin >> v; return v;
}

int main(){
	cin >> n;
	if(n == 3){
		puts("OK 3 2 1");
		return 0;
	}
	vector<pi> v;
	v.emplace_back(query(2, 3, 4), 1);
	v.emplace_back(query(1, 3, 4), 2);
	v.emplace_back(query(1, 2, 4), 3);
	v.emplace_back(query(1, 2, 3), 4);
	sort(v.begin(), v.end());
	vector<int> R = {v[0].second, v[1].second};
	vector<int> L = {v[2].second, v[3].second};
	for(int i=5; i<=n; i++){
		int trad = query(L[0], L[1], R[0]);
		if(trad > query(L[0], L[1], i)){
			vector<pi> v;
			v.emplace_back(query(R[1], L[0], L[1]), i);
			v.emplace_back(query(i, L[0], L[1]), R[1]);
			v.emplace_back(query(R[1], i, L[1]), L[0]);
			v.emplace_back(query(R[1], L[0], i), L[1]);
			sort(v.begin(), v.end());
			tie(L[0], L[1]) = make_pair(v[2].second, v[3].second);
		}
		int trad2 = query(L[1], R[0], R[1]);
		if(trad2 < query(R[0], R[1], i)){
			vector<pi> v;
			v.emplace_back(query(L[1], R[0], R[1]), i);
			v.emplace_back(query(i, R[0], R[1]), L[1]);
			v.emplace_back(query(L[1], i, R[1]), R[0]);
			v.emplace_back(query(L[1], R[0], i), R[1]);
			sort(v.begin(), v.end());
			tie(R[0], R[1]) = make_pair(v[0].second, v[1].second);
		}
	}
	for(int i=1; i<=n; i++){
		if(i == L[0] || i == L[1] || i == R[0] || i == R[1]) continue;
		a[i] = query(L[0], i, R[1]);
	}
	a[L[0]] = 1;
	a[L[1]] = 2;
	a[R[0]] = n - 1;
	a[R[1]] = n;
	printf("OK");
	for(int i=1; i<=n; i++) printf(" %d", a[i]);
	fflush(stdout);
}

