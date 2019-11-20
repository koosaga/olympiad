#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 41;
const int MAXS = 7000;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const string dircode = "senw";

int n, m, d, q;
char str[MAXN][MAXN];

struct state{
	int x, y, d;
	bool ok(int x, int y){
		return 0 <= x && x < n && 0 <= y && y < m && str[x][y] == '.';
	}
	void M(){
		if(ok(x + dx[d], y + dy[d])) x += dx[d], y += dy[d];
	}
	void L(){
		d = (d + 1) & 3;
	}
	bool condition(char c){
		if(c == 'b') return !ok(x + dx[d], y + dy[d]);
		else return dircode[d] == c;
	}
	void read(){
		cin >> x >> y;
		string c; cin >> c;
		for(int i=0; i<4; i++){
			if(dircode[i] == c[0]) d = i;
		}
		x--, y--;
	}
	int code(){ 
		return (x * m + y) * 4 + d;
	}
	void write(){
		printf("%d %d %c\n", x+1, y+1, dircode[d]);
	}
};

string prog[26];
state dp[26][MAXS];
bool vis[26][MAXS];
bool in_stk[26][MAXS];

state dfs(string str, state s);

state dfs_prec(int num, state s){
	if(in_stk[num][s.code()]) throw 69;
	if(vis[num][s.code()]) return dp[num][s.code()];
	vis[num][s.code()] = 1;
	in_stk[num][s.code()] = 1;
	dp[num][s.code()] = dfs(prog[num], s);
	in_stk[num][s.code()] = 0;
	return dp[num][s.code()];
}

string seek(string &s, int ptr){
	int cnt = 0;
	string aux;
	for(int i=ptr; i<sz(s); i++){
		if(s[i] == '(') cnt++;
		if(s[i] == ')') cnt--;
		if(i > ptr && cnt >= 1) aux.push_back(s[i]);
		if(cnt == 0) return aux;
	}
	assert(0);
}

state dfs(string str, state s){
	if(sz(str) == 0) return s;
	if(str[0] == 'm'){
		s.M();
		return dfs(str.substr(1, sz(str) - 1), s);
	}
	else if(str[0] == 'l'){
		s.L();
		return dfs(str.substr(1, sz(str) - 1), s);
	}
	else if(str[0] == 'i'){
		string prog1, prog2, prog3;
		int ptr = 2;
		prog1 = seek(str, ptr);
		ptr += sz(prog1) + 2;
		prog2 = seek(str, ptr);
		ptr += sz(prog2) + 2;
		prog3 = str.substr(ptr, sz(str) - ptr);
		if(s.condition(str[1])) return dfs(prog3, dfs(prog1, s));
		else return dfs(prog3, dfs(prog2, s));
	}
	else if(str[0] == 'u'){
		string prog1, prog2, prog3;
		int ptr = 2;
		prog1 = seek(str, ptr);
		ptr += sz(prog1) + 2;
		prog2 = str.substr(ptr, sz(str) - ptr);
		bool vis[MAXS] = {};
		while(!s.condition(str[1]) && !vis[s.code()]){
			vis[s.code()] = 1;
			s = dfs(prog1, s);
		}
		if(vis[s.code()]) throw 69;
		return dfs(prog2, s);
	}
	else if(isupper(str[0])){
		s = dfs_prec(str[0] - 'A', s);
		return dfs(str.substr(1, sz(str) - 1), s);
	}
	else assert(0);
}

int main(){
	cin >> n >> m >> d >> q;
	for(int i=0; i<n; i++) cin >> str[i];
	for(int i=0; i<d; i++){
		string x; cin >> x;
		prog[x[0] - 'A'] = x.substr(2, sz(x) - 2);
	}
	while(q--){
		memset(vis, 0, sizeof(vis));
		memset(in_stk, 0, sizeof(in_stk));
		state st;
		st.read();
		string s; cin >> s;
		try{
			dfs(s, st).write();
		}catch(int e){
			puts("inf");
		}
	}
}
