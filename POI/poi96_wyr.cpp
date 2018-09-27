#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 5005;

struct node{
	int x, y, d;
	bool operator<(const node &n)const{
		return d > n.d;
	}
};

int n;
int trie[MAXN][26], piv, term[MAXN];
int dist[MAXN][MAXN];
string s, t;

int main(){
	scanf("%d %*d",&n);
	cin >> s;
	scanf("%*d"); 
	cin >> t;
	for(int i=0; i<n; i++){
		scanf("%*d");
		string x; cin >> x;
		int p = 0;
		for(auto &j : x){
			if(!trie[p][j - 'a']){
				trie[p][j - 'a'] = ++piv;
			}
			p = trie[p][j - 'a'];
		}
		term[p] = 1;
	}
	if(s.size() > t.size()) swap(s, t);
	if(t.substr(0, s.size()) != s){
		puts("NIE");
		return 0;
	}
	vector<int> v(piv + 1, 1e9);
	v[0] = 0;
	for(int i=s.size(); i<t.size(); i++){
		vector<int> w(piv + 1, 1e9);
		for(int j=0; j<v.size(); j++){
			if(trie[j][t[i] - 'a']){
				w[trie[j][t[i] - 'a']] = min(w[trie[j][t[i] - 'a']], v[j]);
			}
			if(term[trie[j][t[i] - 'a']]){
				w[0] = min(w[0], v[j] + 1);
			}
		}
		v = w;
	}
	priority_queue<node> pq;
	memset(dist, 0x3f, sizeof(dist));
	for(int i=0; i<=piv; i++){
		pq.push({i, 0, v[i]});
		dist[i][0] = v[i];
	}
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		auto enq = [&](int x, int y, int d){
			if(dist[x][y] > d){
				dist[x][y] = d;
				pq.push({x, y, d});
			}
		};
		for(int i=0; i<26; i++){
			if(trie[x.x][i] && trie[x.y][i]){
				int l = trie[x.x][i];
				int r = trie[x.y][i];
				enq(l, r, x.d);
				if(term[l]) enq(0, r, x.d + 1);
				if(term[r]) enq(l, 0, x.d + 1);
				if(term[l] && term[r]) enq(0, 0, x.d + 2);
			}
		}
	}
	if(dist[0][0] > 1e8) cout << "NIE";
	else cout << dist[0][0] << endl;
}
