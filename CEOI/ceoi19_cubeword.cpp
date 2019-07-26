#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int mod = 998244353;
const int N = 62;
using lint = long long;
using pi = pair<int, int>;

int sgn(char c){
	if(islower(c)) return c - 'a';
	if(isupper(c)) return c - 'A' + 26;
	return c - '0' + 52;
}

int cnt[62][62], prec[62][62][62];
int v[12][62][62];

lint solve(int l){
	memcpy(cnt, v[l], sizeof(cnt));
	memset(prec, 0, sizeof(prec));
	for(int i=0; i<N; i++){
		for(int j=0; j<=i; j++){
			for(int k=0; k<N; k++){
				for(int l=0; l<N; l++){
					prec[i][j][k] += cnt[i][l] * (1ll * cnt[j][l] * cnt[k][l] % mod) % mod;
					if(prec[i][j][k] >= mod) prec[i][j][k] -= mod;
				}
			}
		}
	}
	lint ret = 0;
	for(int i=0; i<N; i++){
		for(int j=0; j<=i; j++){
			for(int k=0; k<N; k++){
				for(int l=0; l<=k; l++){
					lint fuck = (1ll * prec[i][j][k] * prec[i][j][l] % mod) * (1ll * prec[k][l][i] * prec[k][l][j] % mod) % mod;
					if(i != j) fuck <<= 1;
					if(k != l) fuck <<= 1;
					ret += fuck;
				}
			}
		}
	}
	return ret % mod;
}

vector<string> vec[11];
char buf[22];

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%s", buf);
		string s = buf;
		int l = s.size();
		vec[l].push_back(s);
		string t = s; reverse(t.begin(), t.end());
		vec[l].push_back(t);
	}
	lint ret = 0;
	for(int i=3; i<=10; i++){
		sort(vec[i].begin(), vec[i].end());
		vec[i].resize(unique(vec[i].begin(), vec[i].end()) - vec[i].begin());
		for(auto &j : vec[i]){
			int st = sgn(j[0]), ed = sgn(j.back());
			v[i][st][ed]++;
		}
	}
	for(int i=3; i<=10; i++){
		ret += solve(i);
	}
	cout << ret % mod << endl;
}
