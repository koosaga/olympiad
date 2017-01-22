#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;

int n, a[530000];

map<int, int> sol[200005];

int solve(int x, int r){
	if(x > n) return -1;
	if(sol[x].find(r) != sol[x].end()) return sol[x][r];
	int minval = min({r, a[2*x], a[2*x+1]});
	if(minval == r){
		solve(2*x, a[2*x]);
		solve(2*x+1, a[2*x+1]);
		return sol[x][r] = x;
	}
	else if(minval == a[2*x]){
		int ret = solve(2*x, r);
		solve(2*x+1, a[2*x+1]);
		return sol[x][r] = ret;
	}
	else{
		int k1 = solve(2*x, r);
		int k2 = solve(2*x+1, a[2*x]);
		int k3 = solve(2*x, a[2*x]);
		int k4 = solve(2*x+1, r);
		if(min(k1, k2) < min(k3, k4)){
			return sol[x][r] = k1;
		}
		if(min(k1, k2) > min(k3, k4)){
			return sol[x][r] = k4;
		}
		if(r < a[2*x]){
			if(k1 < k4){
				return sol[x][r] = k1;
			}
			else{
				return sol[x][r] = k4;
			}
		}
		else{
			if(k2 < k3){
				return sol[x][r] = k1;
			}
			else{
				return sol[x][r] = k4;
			}
		}
	}
}

void fmerge(vector<int> &ret, vector<int> &v1, vector<int> &v2){
	int pnt = 0;
	for(int i=1; pnt < max(v1.size(), v2.size()); i<<=1){
		for(int j=pnt; j<pnt + i && j < v1.size(); j++){
			ret.push_back(v1[j]);
		}
		for(int j=pnt; j<pnt + i && j < v2.size(); j++){
			ret.push_back(v2[j]);
		}
		pnt+=i;
	}
}

vector<int> track(int x, int r){
	if(x > n) return vector<int>();
	int minval = min({r, a[2*x], a[2*x+1]});
	if(minval == r){
		auto a1 = vector<int>{r};
		auto a2 = track(2*x, a[2*x]);
		auto a3 = track(2*x+1, a[2*x+1]);
		fmerge(a1, a2, a3);
		return a1;
	}
	else if(minval == a[2*x]){
		auto a1 = vector<int>{a[2*x]};
		auto a2 = track(2*x, r);
		auto a3 = track(2*x+1, a[2*x+1]);
		fmerge(a1, a2, a3);
		return a1;
	}
	else{
		int k1 = solve(2*x, r);
		int k4 = solve(2*x+1, r);
		if(sol[x][r] == k1){
			auto a1 = vector<int>{a[2*x+1]};
			auto a2 = track(2*x, r);
			auto a3 = track(2*x+1, a[2*x]);
			fmerge(a1, a2, a3);
			return a1;
		}
		else{
			auto a1 = vector<int>{a[2*x+1]};
			auto a2 = track(2*x, a[2*x]);
			auto a3 = track(2*x+1, r);
			fmerge(a1, a2, a3);
			return a1;
		}
	}
}


int main(){
	memset(a, 0x3f, sizeof(a));
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	solve(1, a[1]);
	auto w = track(1, a[1]);
	for(auto &i : w){
		printf("%d ",i);
	}
}
