#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 55, MAXC = 2;

vector<pi> vec[105];
int n, piv;
__int128 dp[105][55][55];

struct node{
	int x, y, z;
	__int128 val;
	bool operator<(const node &n)const{
		return val > n.val;
	}
};

void solve(){
	priority_queue<node> pq;
	for(int i=0; i<=n; i++){
		for(int j=0; j<=piv; j++){
			for(int k=0; k<=piv; k++){
				if(dp[i][j][k] < 1e19) pq.push({i, j, k, dp[i][j][k]});
			}
		}
	}
	while(sz(pq)){
		auto x = pq.top(); pq.pop();
		if(dp[x.x][x.y][x.z] != x.val) continue;
		for(int i=0; i<=n; i++){
			for(auto &j : vec[i]){
				if(j.first == x.x){
					for(int l=0; l<=piv; l++){
						if(dp[j.first][x.y][x.z] + dp[j.second][x.z][l] < dp[i][x.y][l]){
							dp[i][x.y][l] = dp[j.first][x.y][x.z] + dp[j.second][x.z][l];
							pq.push({i, x.y, l, dp[i][x.y][l]});
						}
					}
				}
				if(j.second == x.x){
					for(int l=0; l<=piv; l++){
						if(dp[j.first][l][x.y] + dp[j.second][x.y][x.z] < dp[i][l][x.z]){
							dp[i][l][x.z] = dp[j.first][l][x.y] + dp[j.second][x.y][x.z];
							pq.push({i, l, x.z, dp[i][l][x.z]});
						}
					}
				}
			}
		}
	}
}

int trie[MAXN][MAXC], fail[MAXN], term[MAXN];

void init(vector<string> &v){
	memset(trie, 0, sizeof(trie));
	memset(fail, 0, sizeof(fail));
	memset(term, 0, sizeof(term));
	piv = 0;
	for(auto &i : v){
		int p = 0;
		for(auto &j : i){
			if(!trie[p][j]) trie[p][j] = ++piv;
			p = trie[p][j];
		}
		term[p] = 1;
	}
	queue<int> que;
	for(int i=0; i<MAXC; i++){
		if(trie[0][i]) que.push(trie[0][i]);
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(int i=0; i<MAXC; i++){
			if(trie[x][i]){
				int p = fail[x];
				while(p && !trie[p][i]) p = fail[p];
				p = trie[p][i];
				fail[trie[x][i]] = p;
				if(term[p]) term[trie[x][i]] = 1;
				que.push(trie[x][i]);
			}
		}
	}
}

int main(){
	int x, y;
	cin >> n >> x >> y;
	int fn = n;
	while(x--){
		int v, l; 
		scanf("%d %d",&v,&l);
		v++;
		vector<int> seq(l);
		for(auto &j : seq) scanf("%d",&j), j++;
		int prv = seq[0];
		for(int i=1; i<l; i++){
			n++;
			vec[n].emplace_back(prv, seq[i]);
			prv = n;
		}
		vec[v].emplace_back(prv, 0);
	}
	vector<string> ac;
	while(y--){
		int n; scanf("%d",&n);
		string s;
		s.resize(n);
		for(int i=0; i<n; i++){
			scanf("%d",&x);
			s[i] = x;
		}
		ac.push_back(s);
	}
	init(ac);
	memset(dp, 0x3f, sizeof(dp));
	for(int i=0; i<=piv; i++){
		for(int j=0; j<2; j++){
			int cur = i;
			while(cur && !trie[cur][j]) cur = fail[cur];
			cur = trie[cur][j];
			if(term[i]) cur = i;
			dp[j+1][i][cur] = 1;
		}
		dp[0][i][i] = 0;;
	}
	solve();
	for(int i=3; i<=fn; i++){
		__int128 ret = 1e30;
		for(int j=0; j<=piv; j++){
			if(term[j] == 0) ret = min(ret, dp[i][0][j]);
		}
		if(ret < (((__int128)1) << 63)){
			printf("NO %lld\n", (long long) ret);
		}
		else puts("YES");
	}
}
