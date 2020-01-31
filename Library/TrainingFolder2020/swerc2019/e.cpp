#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int MAXB = 320;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m;
vector<int> inp[MAXN];
vector<int> ans[MAXN];
bitset<MAXB> bs[3][MAXB];

bitset<MAXB> basis[MAXB];
int sum[MAXB];

void upload(bitset<MAXB> bs, int k){
	for(int i=0; i<m; i++){
		if(bs[i]){
			if(basis[i][i]){
				bs ^= basis[i];
				k ^= sum[i];
			}
			else{
				basis[i] = bs;
				sum[i] = k;
				return;
			}
		}
	}
	if(k){
		puts("IMPOSSIBLE");
		exit(0);
	}
}

vector<int> gauss(){
	vector<int> dap(m);
	for(int i=m-1; i>=0; i--){
		if(basis[i][i]){
			dap[i] = sum[i];
			for(int j=0; j<i; j++){
				if(basis[j][i]) sum[j] ^= sum[i];
			}
		}
	}
	return dap;
}

void solve(){
	for(int i=0; i<m; i++){
		bs[0][i].set(i);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			bs[(i + 1) % 3][j] = 0;
			if(i != 0){
				bs[(i + 1) % 3][j] = bs[(i + 2) % 3][j];
			}
			for(int k=-1; k<=1; k++){
				if(j + k < 0 || j + k >= m) continue;
				bs[(i + 1) % 3][j] ^= bs[i % 3][j + k];
			}
			if(inp[i][j])bs[(i + 1) % 3][j].flip(m);
		}
	}
	for(int i=0; i<m; i++){
		auto msk = bs[n % 3][i];
		int cnst = msk.test(m);
		if(cnst) msk.flip(m);
		upload(msk, cnst);
	}
	for(int i=0; i<n; i++){
		ans[i].resize(m);
	}
	ans[0] = gauss();
	auto ok = [&](int x, int y){
		return x >= 0 && x < n && y >= 0 && y < m;
	};
	for(int i=1; i<n; i++){
		for(int j=0; j<m; j++){
			ans[i][j] = inp[i-1][j];
			if(ok(i - 1, j - 1)) ans[i][j] ^= ans[i - 1][j - 1];
			if(ok(i - 1, j - 0)) ans[i][j] ^= ans[i - 1][j - 0];
			if(ok(i - 1, j + 1)) ans[i][j] ^= ans[i - 1][j + 1];
			if(ok(i - 2, j - 0)) ans[i][j] ^= ans[i - 2][j - 0];
		}
	}
}


char buf[6];

int main(){
	cin >> n >> m;
	vector<int> foo(n*m);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%s", buf);
			if(*buf == 'B') foo[i*m+j] = 1;
			else foo[i*m+j] = 0;
		}
	}
	if(n < m){
		for(int i=0; i<m; i++){
			inp[i].resize(n);
			for(int j=0; j<n; j++){
				inp[i][j] = foo[i+j*m];
			}
		}
		swap(n, m);
		solve();
		swap(n, m);
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				printf(ans[j][i] ? "P " : "A ");
			}
			puts("");
		}
	}
	else{
		for(int i=0; i<n; i++){
			inp[i].resize(m);
			for(int j=0; j<m; j++){
				inp[i][j] = foo[i * m + j];
			}
		}
		solve();
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				printf(ans[i][j] ? "P " : "A ");
			}
			puts("");
		}
	}

}
