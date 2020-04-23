#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
const int mod = 1e9 + 7;
const int MAXN = 400005;

int n, a[MAXN], b[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	for(int i=0; i<n; i++) scanf("%d",&b[i]);
	set<pi> s;
	auto getIntv = [&](int x){
		auto l = s.lower_bound(pi(x + 1, -1));
		auto r = s.lower_bound(pi(x, -1));
		lint X = (r == s.begin() ? -2e9 : prev(r)->first);
		lint Y = x;
		lint Z = (l == s.end() ? 2e9 : l->first);
		int st = upper_bound(b, b + n, (X + Y) / 2) - b;
		int ed = upper_bound(b, b + n, (Y + Z) / 2) - b;
		return pi(st, ed);
	};
	{
		lint tot = 0;
		for(int i=0; i<n; i++){
			s.emplace(a[i], i);
			tot += abs(a[i] - b[i]);
		}
		cout << tot << endl;
	}
	queue<int> que;
	auto enq = [&](int x){
		auto it = getIntv(a[x]);
		if(it.first <= x && x < it.second) que.push(x);
	};
	for(int i=0; i<n; i++){
		enq(i);
	}
	while(sz(que)){
		int x = que.front(); que.pop();
		if(!s.count(pi(a[x], x))) continue;
		printf("%d ", x + 1);
		s.erase(pi(a[x], x));
		auto it = s.lower_bound(pi(a[x], x));
		if(it != s.end()) enq(it->second);
		if(it != s.begin()) enq(prev(it)->second);
	}
}
