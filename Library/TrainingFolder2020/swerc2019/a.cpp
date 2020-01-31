#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;
const int MAXB = 105;

int N, B;
int dist[MAXN][MAXB];

struct adj{
	int pos, fst, snd;
};

vector<adj> gph[MAXN];
struct node{
	int pos, fst, dist;
	bool operator<(const node &n)const{
		return dist > n.dist;
	}
};

void solve(){
	memset(dist, 0x3f, sizeof(dist));
	priority_queue<node> pq;
	auto enq = [&](int x, int y, int z){
		if(y > B) return;
		if(dist[x][y] > z){
			dist[x][y] = z;
			pq.push({x, y, z});
		}
	};
	enq(0, 0, 0);
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		if(x.pos ==  1){
			cout << x.dist << endl;
			return;
		}
		for(auto &i : gph[x.pos]){
			enq(i.pos, x.fst + i.fst, x.dist + i.snd);
		}
	}
	cout << "-1\n";
}

int main(){
	pi a[MAXN];
	int T, C[MAXN];
	for(int i=0; i<2; i++) cin >> a[i].first >> a[i].second;
	cin >> B;
	cin >> C[0];
	cin >> T;
	for(int i=1; i<=T; i++) cin >> C[i];
	cin >> N;
	vector<vector<pi>> aux(N + 2);
	for(int i=1; i<=N+1; i++){
		aux[0].emplace_back(i, 0);
	}
	for(int i=2; i<=N+1; i++){
		aux[i].emplace_back(1, 0);
	}
	for(int i=2; i<=N+1; i++){
		cin >> a[i].first >> a[i].second;
		int q; cin >> q;
		while(q--){
			int x, y; cin >> x >> y;
			aux[i].emplace_back(x + 2, y);
		}
	}
	N += 2;
	for(int i=0; i<N; i++){
		for(auto &j : aux[i]){
			int p = j.first;
			int q = j.second;
			int k = (int)ceil(hypot(a[i].first - a[p].first, a[i].second - a[p].second) - 1e-9);
	//		printf("%d %d %d %d\n", i, p, k, k * C[q]);;
			gph[i].push_back({p, k, k * C[q]});
			gph[p].push_back({i, k, k * C[q]});
		}
	}
	solve();
}
