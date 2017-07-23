#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

void my_assert(bool p){
	if(p == 0){
		puts("0");
		exit(0);
	}
}

int n, s, e;

auto cmp = [&](const pi &a, const pi &b){
	return a.first == b.first ? ((a.second == e) < (b.second == e)) : (a.first < b.first);
};

priority_queue<pi, vector<pi>, decltype(cmp)> pq(cmp);

int main(){
	cin >> n >> s >> e;
	if(n == 1){
		int x;
		cin >> x;
		my_assert(x == 1);
		printf("1");
		return 0;
	}
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		if(i == s) x--;
		if(i == e) x--;
		my_assert(x >= 0);
		if(x > 0) pq.push(pi(x, i));
	}
	vector<int> seq;
	seq.push_back(s);
	while(!pq.empty()){
		pi x;
		if(pq.top().second == seq.back()){
			auto t = pq.top(); pq.pop();
			my_assert(!pq.empty());
			x = pq.top();
			pq.pop();
			pq.push(t);
		}
		else{
			x = pq.top();
			pq.pop();
		}
		seq.push_back(x.second);
		x.first--;
		if(x.first) pq.push(x);
	}
	my_assert(seq.back() != e);
	seq.push_back(e);
	for(auto &i : seq) printf("%d ", i);
}
