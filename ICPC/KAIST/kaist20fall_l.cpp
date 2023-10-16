#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

void solve(vector<int> a, vector<pi> &ret){
	a.push_back(0);
	vector<int> stk;
	for(int i=1; i<sz(a); i++){
		if(a[i-1] == a[i]) continue;
		if(a[i-1] < a[i]){
			stk.push_back(i - 1);
		}
		else{
			while(sz(stk) && a[stk.back()] > a[i]) stk.pop_back();
			if(sz(stk) && a[stk.back()] == a[i]){
				ret.emplace_back(stk.back() + 1, i);
				stk.pop_back();
			}
		}
	}
}

int match(vector<int> p, vector<pi> &v){
	sort(all(v));
	int ptr = 0;
	priority_queue<int, vector<int>, greater<int>> pq;
	int ans = 0;
	for(auto &i : p){
		while(ptr < sz(v) && v[ptr].first <= i) pq.push(v[ptr++].second);
		while(sz(pq) && pq.top() < i) pq.pop();
		if(sz(pq)){
			pq.pop();
			ans++;
		}
	}
	return sz(p) + sz(v) - ans;
}

int main(){
	int n;
	scanf("%d",&n);
	vector<int> a(n), b(n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i],&b[i]);
	}
	vector<int> hz;
	int vtx = 2 * n;
	for(int i=1; i<n; i++){
		if(a[i-1] == a[i]) vtx--;
		if(b[i-1] == b[i]) vtx--;
		if(a[i-1] != a[i] && b[i-1] != b[i]){
			hz.push_back(i);
		}
	}
	vector<pi> vert;
	solve(a, vert);
	solve(b, vert);
	printf("%d\n", vtx - 2 - match(hz, vert));
}
