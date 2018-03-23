#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
typedef long long lint;
typedef pair<lint, int> pi;
const int mod = 1e9 + 7;
const lint inf = 1e15;

int n, a[MAXN];

struct node{
	int st, ed;
	lint cost;
	bool operator<(const node &n)const{
		return pi(cost, st) < pi(n.cost, n.st);
	}
};

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	auto cmp = [&](node s, node e){
		return s.st < e.st;
	};
	set<node> pq;
	set<node, decltype(cmp)> s(cmp);
	auto InsertNode = [&](int st, int ed, lint x){
		s.insert({st, ed, x});
		pq.insert({st, ed, x});
	};
	InsertNode(0, 0, -inf);
	for(int i=1; i<=n; i++){
		InsertNode(i, i, a[i]);
	}
	InsertNode(n+1, n+1, -inf);
	lint ans = 0;
	for(int i=1; i<=(n+1)/2; i++){
		auto nd = *--pq.end();
		pq.erase(nd);
		s.erase(nd);
		ans += nd.cost;
		printf("%lld\n", ans);
		nd.cost *= -1;
		int pst = nd.st, ped = nd.ed;
		auto it = --s.lower_bound({pst, -1, -1});
		nd.st = it->st;
		nd.cost += it->cost;
		pq.erase(*it);
		s.erase(it);
		it = s.lower_bound({ped + 1, -1, -1});
		nd.ed = it->ed;
		nd.cost += it->cost;
		pq.erase(*it);
		s.erase(it);
		InsertNode(nd.st, nd.ed, nd.cost);
	}
}
