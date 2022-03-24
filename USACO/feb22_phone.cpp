#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;

template<typename T>
T gcd(const T &a, const T &b) {
    return b == T(0) ? a : gcd(b, a % b);
}

struct mint {
    int val;
    mint() { val = 0; }
    mint(const lint& v) {
        val = (-mod <= v && v < mod) ? v : v % mod;
        if (val < 0) val += mod;
    }

    friend ostream& operator<<(ostream& os, const mint& a) { return os << a.val; }
    friend bool operator==(const mint& a, const mint& b) { return a.val == b.val; }
    friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
    friend bool operator<(const mint& a, const mint& b) { return a.val < b.val; }

    mint operator-() const { return mint(-val); }
    mint& operator+=(const mint& m) { if ((val += m.val) >= mod) val -= mod; return *this; }
    mint& operator-=(const mint& m) { if ((val -= m.val) < 0) val += mod; return *this; }
    mint& operator*=(const mint& m) { val = (lint)val*m.val%mod; return *this; }
    friend mint ipow(mint a, lint p) {
        mint ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans;
    }
    friend mint inv(const mint& a) { assert(a.val); return ipow(a, mod - 2); }
    mint& operator/=(const mint& m) { return (*this) *= inv(m); }

    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    operator int64_t() const {return val; }
};


string s;
int prec[MAXN][4];

bool shuffle(int l, int r, vector<int> &nstk){
	if(sz(nstk) < r - l) return 0;
	if(l < 0) return 0;
	int ans = 0;
	for(int i = 0; i < r - l; i++){
		ans |= (1 << nstk[sz(nstk) - 1 - i]);
	}
	return prec[l][r - l - 1] == ans;
}

bool chk1[10][10][10];
bool chk2[10][10][10][10];
bool chk3[10][10];

bool pattern2(vector<int> &nstk){
	if(sz(nstk) < 2) return 0;
	int l = nstk[sz(nstk) - 2];
	int r = nstk[sz(nstk) - 1];
	return chk3[l][r];
}

bool pattern4(vector<int> &nstk){
	if(sz(nstk) < 4) return 0;
	return chk2[nstk[0]][nstk[1]][nstk[2]][nstk[3]];
}

int code2[10][10];
int code3[10][10][10];
int idx[16][150];

int code(vector<int> v){
	if(sz(v) == 0) return 0;
	if(sz(v) == 1) return v[0];
	if(sz(v) == 2) return code2[v[0]][v[1]];
	if(sz(v) == 3) return code3[v[0]][v[1]][v[2]];
	return -1;
}

vector<int> reduce(vector<int> v, int msk){
	if(sz(v) > 4) assert(0);
	while(sz(v) && 
		((msk >> sz(v)) % 2 == 0 || code(v) == -1)){
		v.erase(v.begin());
	}
	return v;
}

vector<int> cands[MAXN];
int addValue[1557][10];
int conValue[1557][10];
mint cur[1175], nxt[1175];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
	vector<pair<int, vector<int>>> rev;
	{
		vector<vector<int>> pats = {
			{1, 2, 4, 5},
			{2, 3, 5, 6},
			{4, 5, 7, 8},
			{5, 6, 8, 9}
		};
		for(auto &x : pats){
			do{
				chk2[x[0]][x[1]][x[2]][x[3]] = 1;
				chk1[x[0]][x[1]][x[2]] = 1;
				chk1[x[0]][x[1]][x[3]] = 1;
				chk1[x[0]][x[2]][x[3]] = 1;
				chk1[x[1]][x[2]][x[3]] = 1;
			}while(next_permutation(all(x)));
		}
		chk3[1][2] = chk3[2][3] = chk3[4][5] = chk3[5][6] = chk3[7][8] = chk3[8][9] = 1;
		for(int i = 4; i <= 9; i++) chk3[i-3][i] = 1;
		for(int i = 1; i <= 9; i++){
			for(int j = 1; j < i; j++){
				chk3[i][j] = chk3[j][i];
			}
		}
		memset(code2, -1, sizeof(code2));
		memset(code3, -1, sizeof(code3));
		int piv = 10;
		for(int i = 1; i <= 9; i++){
			for(int j = 1; j <= 9; j++){
				if(i != j){
					int px = (i - 1) / 3;
					int py = (i - 1) % 3;
					int qx = (j - 1) / 3;
					int qy = (j - 1) % 3;
					if(abs(qy - py) <= 1 && abs(px - qx) <= 1) 
						code2[i][j] = piv++;
				}
			}
		}
		for(int i = 1; i <= 9; i++){
			for(int j = 1; j <= 9; j++){
				for(int k = 1; k <= 9; k++){
					if(chk1[i][j][k]) code3[i][j][k] = piv++;
				}
			}
		}
		memset(idx, -1, sizeof(idx));
		for(int i = 0; i < 16; i++){
			if(i == 0) continue;
			vector<int> v;
			rev.emplace_back(i, v);
			for(int j = 1; j <= 9; j++){
				v.push_back(j);
				if(sz(reduce(v, i)) == sz(v)) rev.emplace_back(i, v);
				for(int k = 1; k <= 9; k++){
					v.push_back(k);
					if(sz(reduce(v, i)) == sz(v)) rev.emplace_back(i, v);
					for(int l = 1; l <= 9; l++){
						v.push_back(l);
						if(sz(reduce(v, i)) == sz(v)) rev.emplace_back(i, v);
						v.pop_back();
					}
					v.pop_back();
				}
				v.pop_back();
			}
		}
		for(int i = 0; i < sz(rev); i++){
			idx[rev[i].first][code(rev[i].second)] = i;
		}
	}
	// prep Reduce
	{
		for(int i = 0; i < sz(rev); i++){
			int msk = rev[i].first;
			vector<int> stk = rev[i].second;
			for(int j = 1; j <= 9; j++){
				vector<int> nstk = stk;
				nstk.push_back(j);
				int nmsk = (msk << 1) & 15;
				addValue[i][j] = idx[nmsk + 1][code(reduce(nstk, nmsk + 1))];
				conValue[i][j] = idx[nmsk][code(reduce(nstk, nmsk))];
			}
		}
	}
	while(n--){
	//	s.resize(100000);
	//	for(int i = 0; i < 100000; i++) s[i] = (rand() % 2 ? '5' : (rand() % 9 + '1'));
		cin >> s;
		for(int i = 0; i < sz(s); i++){
			cands[i].clear();
			cands[i].push_back(s[i] - '0');
			vector<int> v;
			for(int j = i - 1; j >= i - 3; j--){
				if(j < 0) break;
				v.push_back(s[j + 1] - '0');
				if(code(v) != -1) cands[i].push_back(s[j] - '0');
			}
			v.clear();
			for(int j = i + 1; j <= i + 3; j++){
				if(j == sz(s)) break;
				v.push_back(s[j - 1] - '0');
				if(code(v) != -1) cands[i].push_back(s[j] - '0');
			}
			sort(all(cands[i]));
			cands[i].resize(unique(all(cands[i])) - cands[i].begin());
			int msk = 0;
			for(int j = 0; j < 4 && i + j < sz(s); j++){
				msk |= (1<<(s[i+j] - '0'));
				prec[i][j] = msk;
			}
		}
		mint ret = 0;
		memset(cur, 0, sizeof(cur));
		cur[0] = 1;
		for(int x = 0; x <= sz(s); x++){
			for(int ii = 0; ii < sz(rev); ii++){
				if(!cur[ii]) continue;
				int msk = rev[ii].first;
				if(x == sz(s)){
					if(msk & 1) ret += cur[ii];
					continue;
				}
				vector<int> nstk = rev[ii].second;
				for(auto &i : cands[x]){
					int nmsk = (msk << 1) & 15;
					if((msk & 1) && s[x] == i + '0'){
						int pos = addValue[ii][i];
						nxt[pos] += cur[ii];
						continue;
					}
					nstk.push_back(i);
					if((msk & 2) && pattern2(nstk) && shuffle(x - 1, x + 1, nstk)){
						int pos = addValue[ii][i];
						nxt[pos] += cur[ii];
					}
					else if((msk & 8) && pattern4(nstk) && shuffle(x - 3, x + 1, nstk)){
						int pos = addValue[ii][i];
						nxt[pos] += cur[ii];
					}
					else if(nmsk){
						int pos = conValue[ii][i];
						nxt[pos] += cur[ii];
					}
					nstk.pop_back();
				}
			}
			swap(cur, nxt);
			memset(nxt, 0, sizeof(nxt));
		}
		cout << ret << "\n";
	}
}
