#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int dx[4] = {2, 2, 1, 1};
const int dy[4] = {-1, 1, -2, 2};

using pi = pair<int, int>;

// It takes at most several minutes to get a sufficiently long uncrossed knight tour for m <= 6.
// It takes about 3 hours to get the 7 x 130 uncrossed knight tour.
// It takes about 6 hours to get the 8 x 23 uncrossed knight tour. 

int n, m;

struct segment{
	int x, y, k; 
	bool operator<(const segment &s)const{
		return make_tuple(x, y, k) < make_tuple(s.x, s.y, s.k);
	}
};

int ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

bool prec[21][21][4][4];

bool segment_intersect(segment x, segment y){
	if(abs(x.x - y.x) > 10 || abs(x.y - y.y) > 10) return 0;
	return prec[y.x - x.x + 10][y.y - x.y + 10][x.k][y.k];
}

int get(int x, int y){ return (x ) * m + (y); }

struct state{
	vector<segment> v;
	// two rows of this
	vector<int> disj;
	vector<int> deg;
	int compCount;
	int adv;
	state(){
		compCount = adv = 0;
		for(int i=0; i<18; i++){
			disj.push_back(i + 1);
			deg.push_back(0);
		}
	}
	vector<int> context_information(int x, int y){
		vector<int> ret;
		ret.push_back(adv);
		ret.push_back(compCount);
		for(int i=0; i<sz(disj); i++){
			assert(disj[i]);
			if(deg[i] == 0) ret.push_back(0);
			if(deg[i] == 1) ret.push_back(disj[i]);
			if(deg[i] == 2) ret.push_back(-disj[i]);
		}
		for(auto &l : v){
			ret.push_back(l.x);
			ret.push_back(l.y);
			ret.push_back(l.k);
		}
		return ret;
	}
	void doUni(int x, int y){
		int l = disj[x];
		int r = disj[y];
		if(l != r) compCount--;
		for(auto &i : disj){
			if(i == max(l, r)) i = min(l, r);
		}
	}
	bool push_back_segment(int x, int y, int k){
		segment nseg = {x, y, k};
		for(auto &i : v){
			if(segment_intersect(i, nseg)) return 0;
		}
		int nxt = get(dx[k], dy[k]);
		if(deg[0] >= 2) return 0;
		if(deg[nxt] >= 2) return 0;
		adv = max(adv, x + dx[k]);
		if(deg[0] == 0) compCount++;
		if(deg[nxt] == 0) compCount++;
		if(k <= 1) v.push_back(nseg);
		else if(k == 3){
			bool good = 0;
			for(auto &j : v){
				if(j.k == 3){
					good = 1;
					j.x = x;
					j.y = y;
					break;
				}
			}
			if(!good) v.push_back(nseg);
		}
		sort(v.begin(), v.end());
		deg[0]++;
		deg[nxt]++;
		doUni(0, nxt);
		return 1;
	}
	void debug(){
		for(auto &i : v){
			printf("(%d,%d) - (%d,%d)\n", i.x, i.y, i.x + dx[i.k], i.y + dy[i.k]);
		}
		puts("");
	}
	bool shift(int x, int y){
		bool pdeg = deg[0] > 0;
		deg[0] = 0;
		rotate(deg.begin(), deg.begin() + 1, deg.end());
		{
			int foo = sz(disj) + 1;
			disj.push_back(foo);
		}
		int new_start = -1;
		for(int i=1; i<sz(disj); i++){
			if(disj[i] == 1){
				new_start = i;
				break;
			}
		}
		for(int i=1; i<sz(disj); i++){
			if(disj[i] == 1){
				disj[i] = new_start + 1;
			}
			disj[i]--;
		}
		if(pdeg && compCount != 1 && new_start == -1){
			return 1;
		}
		disj.erase(disj.begin());
		vector<segment> nxt;
		for(auto &i : v){
			if(pi(i.x + dx[i.k], i.y + dy[i.k]) >= pi(x + 1, y - 1)){
				nxt.push_back(i);
			}
		}
		v = nxt;
		return 0;
	}
};

int main(){
	for(int i=0; i<=20; i++){
		for(int j=0; j<=20; j++){
			for(int xk=0; xk<=3; xk++){
				for(int yk=0; yk<=3; yk++){
					pi p1 = pi(10, 10);
					pi p2 = pi(10 + dx[xk], 10 + dy[xk]);
					pi p3 = pi(i, j);
					pi p4 = pi(i + dx[yk], j + dy[yk]);
					prec[i][j][xk][yk] = ccw(p1, p2, p3) * ccw(p1, p2, p4) < 0 &&
						ccw(p3, p4, p1) * ccw(p3, p4, p2) < 0;
				}
			}
		}
	}
	cin >> m;
		vector<int> dap;
		vector<pair<state, int>> dp;
		state st; dp.emplace_back(st, 0);
		for(int x = 1; ; x++){
			for(int y = 1; y <= m; y++){
				vector<pair<state, int>> nxt;
				for(auto &j : dp){
					if(!j.first.shift(x, y)) nxt.push_back(j);
				}
				sort(nxt.begin(), nxt.end(), [&](pair<state, int> &a, pair<state, int> &b){
					auto vect1 = a.first.context_information(x, y);
					auto vect2 = b.first.context_information(x, y);
					if(vect1 != vect2) return vect1 < vect2;
					return a.second > b.second;
				});
				dp.clear();
				for(auto &i : nxt){
					if(sz(dp) && dp.back().first.context_information(x, y) == i.first.context_information(x, y)){
						continue;
					}
					dp.push_back(i);
				}
				nxt.clear();
				for(auto &j : dp){
					auto ok = [&](int x, int y){
						return y > 0 && y <= m;
					};
					if(j.first.deg[0] == 0){
						auto nstate = j.first;
						nxt.emplace_back(nstate, j.second);
						for(int a=0; a<4; a++){
							for(int b=a+1; b<4; b++){
								if(ok(x + dx[a], y + dy[a]) && ok(x + dx[b], y + dy[b])){
									auto nstate = j.first;
									bool good = 1;
									if(!nstate.push_back_segment(x, y, a)) good = 0;
									if(!nstate.push_back_segment(x, y, b)) good = 0;
									if(good){
										nxt.emplace_back(nstate, j.second + 1);
									}
								}
							}
						}
					}
					if(j.first.deg[0] == 1){
						for(int i=0; i<4; i++){
							if(ok(x + dx[i], y + dy[i])){
								auto nstate = j.first;
								bool good = 1;
								if(!nstate.push_back_segment(x, y, i)) good = 0;
								if(good){
									nxt.emplace_back(nstate, j.second + 1);
								}
							}
						}
					}
					if(j.first.deg[0] == 2){
						auto nstate = j.first;
						nxt.emplace_back(nstate, j.second + 1);
					}
				}
				dp= nxt;
			}
			int ret = 0;
			vector<pair<state, int>> nxt;
			for(auto &i : dp){
				if(i.first.compCount == 1 && i.first.adv <= x){
					ret = max(ret, i.second);
				}
				else{
					nxt.push_back(i);
				}
			}
			dp = nxt;
			cout << ret << ",";
			fflush(stdout);
		}
		cout << endl;
}
