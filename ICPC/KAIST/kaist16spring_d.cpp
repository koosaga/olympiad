#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef vector<int> vi;

queue<vector<int> > que;
queue<int> dist;

set<vector<int> > s;

int n;

bool ok(vector<int> &v){
	for(int i=0; i<n; i++){
		if(v[i] != i+1) return 0;
	}
	return 1;
}

vector<int> flip(vector<int> &v, int l){
	vector<int> ret = v;
	reverse(ret.begin(), ret.begin() + l);
	for(int i=0; i<l; i++) ret[i] = -ret[i];
	return ret;
}

int main(){
	cin >> n;
	vector<int> vect(n);
	for(int i=0; i<n; i++){
		int v;
		string t;
		cin >> v >> t;
		if(t == "-") v = -v;
		vect[i] = v;
	}
	que.push(vect);
	dist.push(0);
	s.insert(vect);
	while(!que.empty()){
		auto v = que.front();
		int d = dist.front();
		if(ok(v)){
			printf("%d\n", d);
			return 0;
		}
		que.pop();
		dist.pop();
		for(int i=1; i<=n; i++){
			auto w = flip(v, i);
			if(s.find(w) == s.end()){
				s.insert(w);
				que.push(w);
				dist.push(d + 1);
			}
		}
	}
	assert(0);
	puts("so this never happens?");
}
