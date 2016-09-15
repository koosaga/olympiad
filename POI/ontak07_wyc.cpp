#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct disj{
	int pa[505];
	void init(int n){
		for(int i=1; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p), q = find(q);
		if(p == q) return 0;
		pa[q]= p; return 1;
	}
}disj;

int n, m, s[50005], e[50005], x[50005];

vector<pi> gph[505];

int ret = 1e9;
vector<int> prnt;
int par[505], dist[505];

void solve(int x){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	memset(dist, 0x3f, sizeof(dist));
	dist[x] = 0;
	pq.push(pi(0, x));
	while(!pq.empty()){
		pi t = pq.top();
		pq.pop();
		for(int i=0; i<gph[t.second].size(); i++){
			pi w = gph[t.second][i];
			if(dist[w.second] > dist[t.second] + w.first){
				dist[w.second] = dist[t.second] + w.first;
				par[w.second] = t.second;
				pq.push(pi(dist[w.second], w.second));
			}
		}
	}
	int tmp = 1e9, pos = -1;
	for(int i=0; i<m; i++){
		if(par[s[i]] == e[i] || par[e[i]] == s[i]) continue;
		if(tmp > dist[s[i]] + dist[e[i]] + ::x[i]){
			tmp = dist[s[i]] + dist[e[i]] + ::x[i];
			pos = i;
		}
	}
	if(pos == -1) return;
	if(tmp < ret){
		ret = tmp;
		vector<int> p, q;
		for(int i=s[pos]; i!=x; i=par[i]){
			p.push_back(i);
		}
		for(int i=e[pos]; i!=x; i=par[i]){
			q.push_back(i);
		}
		p.push_back(x);
		prnt.clear();
		for(int i=0; i<p.size(); i++) prnt.push_back(p[i]);
		for(int i=(int)q.size()-1; i>=0; i--) prnt.push_back(q[i]);
	}
}

int main(){
	cin >> n >> m;
	disj.init(n);
	bool cyc = 0;
	for(int i=0; i<m; i++){
		cin >> s[i] >> e[i] >> x[i];
		if(!disj.uni(s[i], e[i])) cyc = 1;
		gph[s[i]].push_back(pi(x[i], e[i]));
		gph[e[i]].push_back(pi(x[i], s[i]));
	}
	if(!cyc){
		puts("BRAK");
		return 0;
	}
	for(int i=1; i<=n; i++){
		solve(i);
	}
	cout << prnt.size() + 1 << endl;
	for(int i=0; i<prnt.size(); i++){
		printf("%d ", prnt[i]);
	}
	printf("%d",prnt[0]);
}

