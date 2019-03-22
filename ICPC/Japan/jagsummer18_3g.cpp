#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 1005;

int n, m;
lint dp[MAXN][MAXN];
lint minCost[MAXN][13][26];
string s;

int main(){
	cin >> m >> s;
	s = "+" + s;
	n = s.size();
	memset(minCost, 0x3f, sizeof(minCost));
	memset(dp, 0x3f, sizeof(dp));
	for(int i=0; i<=n-2; i++){
		for(int j=i+2; j<=n && j<=i+11; j++){
			string sub = s.substr(i, j - i);
			int mandatory = 0;
			if(sub[0] != '+') sub[0] = '+', mandatory++;
			if(sub[1] == '0' || sub[1] == '+') sub[1] = '1', mandatory++;
			for(int i=2; i<sub.size(); i++){
				if(sub[i] == '+'){
					sub[i] = '0';
					mandatory++;
				}
			}
			lint num = 0, pwr = 1;
			for(int i=1; i<sub.size(); i++) num = num * 10 + sub[i] - '0';
			vector<lint> minuses;
			for(int i=sub.size()-1; i>=1; i--){
				if(i != 1){
					minuses.push_back((sub[i] - '0') * pwr);
				}
				else{
					minuses.push_back((sub[i] - '1') * pwr);
				}
				pwr *= 10;
			}
			sort(minuses.rbegin(), minuses.rend());
			minCost[i][j-i][mandatory] = num;
			for(int k=0; k<minuses.size(); k++){
				num -= minuses[k];
				minCost[i][j-i][mandatory + k + 1] = num;
			}
		}
		string sub = s.substr(i, 2);
		int wrong = 0;
		if(sub[0] != '+') wrong++;
		if(sub[1] != '0') wrong++;
		minCost[i][2][wrong] = min(minCost[i][2][wrong], 0ll);
	}
	for(int i=0; i<=n; i++) dp[0][i] = 0;
	for(int i=1; i<=n; i++){
		for(int j=0; j<=i; j++){
			for(int k=2; k<=11 &&k<=i; k++){
				for(int l=0; l<=11&&l<=j; l++){
					dp[i][j] = min(dp[i][j], dp[i-k][j-l] + minCost[i-k][k][l]);
				}
			}
		}
	}
	for(int i=0; i<=n; i++){
		if(dp[n][i] <= m){
			cout << i << endl;
			return 0;
		}
	}
	cout << -1 << endl;
}

