#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;

int n;
string s[MAXN];
int dist[MAXN][18];
bool nxt_short[MAXN][18][18];
vector<int> nxt_long[MAXN][18];

struct node{
	int x, y, d;
	bool operator<(const node &n)const{
		return d> n.d;
	}
};

priority_queue<node> pq;

void enq(int x, int y, int d){
	if(dist[x][y] > d){
		dist[x][y] = d;
		pq.push({x, y, d});
	}
}

void dijkstra(){
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			if(s[i].substr(0, sz(s[j])) == s[j]){
				enq(i, sz(s[i]) - sz(s[j]), sz(s[j]));
			}
		}
	}
	while(sz(pq)){
		auto x = pq.top();
		pq.pop();
		if(x.y == 0){
			cout << x.d << endl;
			return;
		}
		for(int i=1; i<=x.y; i++){
			if(nxt_short[x.x][x.y][i]){
				enq(x.x, x.y - i, x.d + i);
			}
		}
		for(auto &k : nxt_long[x.x][x.y]){
			enq(k, sz(s[k]) - x.y, x.y + x.d);
		}
	}
	puts("0");
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> s[i];
	sort(s, s + n, [&](const string &x, const string &y){
		return sz(x) < sz(y);
	});
	for(int i=0; i<n; i++){
		for(int j=1; j<=sz(s[i]); j++){
			string x = s[i].substr(sz(s[i]) - j, j);
			for(int k=0; k<n; k++){
				if(sz(s[k]) <= sz(x) && x.substr(0, sz(s[k])) == s[k]){
					nxt_short[i][j][sz(s[k])] = 1;
				}
				if(sz(s[k]) > sz(x) && s[k].substr(0, sz(x)) == x){
					nxt_long[i][j].push_back(k);
				}
			}
		}
	}
	memset(dist, 0x3f, sizeof(dist));
	dijkstra();
}

