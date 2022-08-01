#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 300;
using word = bitset<MAXN>;

word get_solution(vector<word> bs, int n){
	vector<word> ind(n), trk(n);
	for(int i = 0; i < n; i++){
		word ins = bs[i];
		word rws = 0; rws.set(i);
		bool ok = 0;
		for(int j = 0; j < n; j++){
			if(ins[j]){
				if(!ind[j][j]){
					ind[j] = ins;
					trk[j] = rws;
					ok = 1;
					break;
				}
				else{
					ins ^= ind[j];
					rws ^= trk[j];
				}
			}
		}
		if(!ok){
			return rws;
		}
	}
	return 0;
}

vector<word> find_two_cycles(vector<word> bs, int n){
	vector<word> ind(n - 2), trk(n - 2);
	vector<word> cyc;
	for(int i = 0; i < n; i++){
		word ins = bs[i];
		word rws = 0; rws.set(i);
		bool ok = 0;
		for(int j = 0; j < n - 2; j++){
			if(ins[j]){
				if(!ind[j][j]){
					ind[j] = ins;
					trk[j] = rws;
					ok = 1;
					break;
				}
				else{
					ins ^= ind[j];
					rws ^= trk[j];
				}
			}
		}
		if(!ok){
			cyc.push_back(rws);
		}
	}
	if(sz(cyc) != 2) return vector<word>();
	vector<word> ret;
	ret.push_back(cyc[0]);
	ret.push_back(cyc[1]);
	ret.push_back(cyc[0] ^ cyc[1]);
	return ret;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int tc; cin >> tc;
	while(tc--){
		int n; cin >> n;
		vector<word> bs(n);
		for(int i = 0; i < n; i++){
			string s; cin >> s;
			for(int j = 0; j < n; j++){
				if(s[j] == '1') bs[i][j] = 1;
			}
		}
		word sol = get_solution(bs, n);
		if(sol.count() == 0){
			cout << "NO\n";
			continue;
		}
		for(int i = 0; i < n; i++){
			if(sol[i]){
				swap(bs[0], bs[i]);
				bool fuck = sol[0];
				sol[0] = sol[i];
				sol[i] = fuck;
				break;
			}
		}
		vector<int> t(n);
		for(int i = 0; i < n; i++){
			if(sol[i]){
				for(int j = 0; j < n; j++){
					if(bs[i][j]) t[j]++;
				}
			}
		}
		word T = 0;
		for(int i = 0; i < n; i++){
			assert(t[i] % 2 == 0);
			if(t[i] % 4 == 2) T.set(i);
		}
		auto nw = bs;
		nw[0] = T;
		bool ans = (get_solution(nw, n).count() == 0);
		for(int i = 1; i < n; i++){
			if(sol[i]){
				vector<word> col(n);
				for(int j = 1; j < n; j++){
					if(j == i) continue;
					for(int k = 0; k < n; k++){
						col[k][j - 1 - (j > i)] = bs[j][k];
					}
				}
				vector<word> cyc = find_two_cycles(col, n);
				if(sz(cyc) == 0) continue;
				for(int x = 0; x < n; x++){
					if(!bs[i][x]) continue;
					for(int y = x + 1; y < n; y++){
						if(!bs[i][y]) continue;
						bool indep = true;
						for(auto &z : cyc){
							if(!z[x] && !z[y]) indep = false;
						}
						if(indep) ans ^= 1;
					}
				}
			}
		}
		cout << (ans ? "NO" : "YES") << "\n";
	}
}
