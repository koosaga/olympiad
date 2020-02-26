#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, k;
int a[MAXN];

int main(){
	cin >> n >> k;
	iota(a, a + n, 1);
	vector<int> pos;
	vector<vector<int>> tot;
	for(int m=n; m!=1; m/=pos.back()){
		if(gcd(m, k) == 1){
			puts("-1");
			exit(0);
		}
		pos.push_back(gcd(m, k));
	}
	int R = n, C = 1;
	for(auto &i : pos){
		map<pi, vector<int>> ans;
		for(int j=0; j<n; j++){
			int px = j / C, py = j % C;
			px /= i, py /= (k / i);
			ans[pi(px, py)].push_back(a[j]);
		}
		int ptr = 0;
		for(auto &i : ans){
			tot.push_back(i.second);
			for(auto &j : i.second){
				a[ptr++] = j;
			}
		}
		R /= i;
		C *= i;
	}
	cout << sz(tot) << endl;
	for(auto &i : tot){
		for(auto &j : i) printf("%d ", j);
		puts("");
	}
}

