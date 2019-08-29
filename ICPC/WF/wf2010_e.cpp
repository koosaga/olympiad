// TL on live archive

#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define dec fuck
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int mod = 10007;

int n, m;
char str[22][12];

struct state{
	vector<int> deg; // degree should remain 2
	vector<int> disj; // disjoint set
	int ULocc; // avoid forbidden pattern
	bool operator<(const state &s)const{
		if(ULocc != s.ULocc) return ULocc < s.ULocc;
		if(deg != s.deg) return deg < s.deg;
		return disj < s.disj;
	}
	void uni(int p, int q){
		p = disj[p]; q = disj[q];
		if(p && q){
			for(auto &i : disj){
				if(i == max(p, q)) i = min(p, q);
			}
		}
	}
	void compress(){
		int ord[15] = {}, piv = 0;
		for(auto &i : disj){
			if(i && !ord[i]) ord[i] = ++piv;
			i = ord[i];
		}
	}
};

int mp[22][100005];
bool nxt[22][100005];

map<state, int> numb[10];
int piv;

int f(int x, int y, state s){
	if(x == n){
		for(int i=0; i<m; i++) if(s.disj[i] > 1) return -1e9;
		for(int i=0; i<m; i++) if(s.deg[i] != (i == m-1)) return -1e9;
		return 0;
	}
	if(y == m){
		state ns = s;
		ns.ULocc = 0;
		return f(x + 1, 0, ns);
	}
	int cv = count(s.deg.begin(), s.deg.end(), 2);
	if(cv > 1) return -1e9;
	if(cv == 1 && (y == 0 || s.deg[y - 1] != 2)) return -1e9;
	if(numb[y].find(s) == numb[y].end()){
		numb[y][s] = piv++;
	}
	int idx = numb[y][s];
	if(~mp[x][idx]) return mp[x][idx];
	int ret = -1e9;
	// TODO: when lose simple cycle
	if(str[x][y] != '#' && !(s.ULocc && (y > 0 && s.disj[y - 1] == 0) && (s.disj[y] == 0))){
		state new_state = s;
		int myDeg = 2;
		bool fuck = 0;
		if(new_state.disj[y]){
			new_state.deg[y]--, myDeg--;
			if(new_state.deg[y] < 0) fuck = 1;
		}
		if(y && new_state.disj[y-1]){
			new_state.deg[y - 1]--, myDeg--;
			if(new_state.deg[y - 1] < 0) fuck = 1;
		}
		if(new_state.deg[y] != 0) fuck = 1;
		if(!fuck){
			new_state.ULocc = new_state.disj[y] > 0;
			if(new_state.disj[y] == 0) new_state.disj[y] = 12;
			if(y) new_state.uni(y, y - 1);
			new_state.compress();
			new_state.deg[y] = myDeg;
			ret = f(x, y + 1, new_state) + 1;
		}
	}
	if(!(!s.ULocc && (y > 0 && s.disj[y - 1] > 0) && s.disj[y] > 0)){
		state new_state = s;
		if(new_state.deg[y] == 0){
			new_state.ULocc = new_state.disj[y] > 0;
			bool fuck = 0;
			if(new_state.disj[y] && count(new_state.disj.begin(), new_state.disj.end(), new_state.disj[y]) == 1){
				fuck = 1;
			}
			if(!fuck){
				new_state.disj[y] = 0;
				new_state.deg[y] = 0;
				new_state.compress();
				int up = f(x, y + 1, new_state);
				if(ret < up){
					ret = up;
					nxt[x][idx] = 1;
				}
			}
		}
	}
	return mp[x][idx] = ret;
}

void g(int x, int y, state s){
	if(x == n) return;
	if(y == m){
		state ns = s;
		ns.ULocc = 0;
		g(x + 1, 0, ns);
		return;
	}
	bool flag = nxt[x][numb[y][s]];
	if(!flag){
		str[x][y] = 'C';
		state new_state = s;
		int myDeg = 2;
		if(new_state.disj[y]) new_state.deg[y]--, myDeg--;
		if(y && new_state.disj[y-1]) new_state.deg[y - 1]--, myDeg--;
		if(new_state.deg[y] == 0){
			new_state.ULocc = new_state.disj[y] > 0;
			if(new_state.disj[y] == 0) new_state.disj[y] = 12;
			if(y) new_state.uni(y, y - 1);
			new_state.compress();
			new_state.deg[y] = myDeg;
			g(x, y + 1, new_state);
		}
	}
	else{
		state new_state = s;
		if(new_state.deg[y] == 0){
			new_state.ULocc = new_state.disj[y] > 0;
			bool fuck = 0;
			if(new_state.disj[y] && count(new_state.disj.begin(), new_state.disj.end(), new_state.disj[y]) == 1){
				fuck = 1;

			}
			if(!fuck){
				new_state.disj[y] = 0;
				new_state.deg[y] = 0;
				new_state.compress();
				g(x, y + 1, new_state);
			}
		}
	}
}

void solve(){
	piv = 0;
	for(int i=0; i<10; i++) numb[i].clear();
	memset(mp, -1, sizeof(mp));
	memset(nxt, 0, sizeof(nxt));
	state st;
	st.ULocc = 0;
	st.disj.resize(m);
	st.deg.resize(m);
	st.deg[0] = 1;
	st.disj[0] = 1;
	f(0, 0, st);
	g(0, 0, st);
	for(int i=0; i<n; i++) cout << str[i] << endl;
	assert(piv <= 100000);

}

int main(){
	int tc = 0;
	while(true){
		tc++;
		scanf("%d %d",&n,&m);
		if(n + m == 0) break;
		for(int i=0; i<n; i++) cin >> str[i];
		printf("Case %d:\n", tc);
		solve();
		puts("");
	}
}


