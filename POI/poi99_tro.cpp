#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

char s[10005];

vector<int> gph[10005];
int piv;

int make(int x, int p){
	if(s[x] == '0') return x+1;
	if(s[x] == '1'){
		gph[p].push_back(++piv);
		return make(x+1, piv);
	}
	if(s[x] == '2'){
		gph[p].push_back(++piv);
		int w = make(x+1, piv);
		gph[p].push_back(++piv);
		return make(w, piv);
	}
	assert(0);
}

int dp[10005][3][2];

int main(){
	cin >> s;
	make(0, 0);
	for(int i=piv; i>=0; i--){
		dp[i][0][0] = dp[i][0][1] = 1;
		if(gph[i].size() == 1){
			for(int j=0; j<3; j++){
				vector<int> no;
				int mx = -1, mn = 1e9;
				for(int k=0; k<3; k++){
					if(j == k) continue;
					no.push_back(k);
				}
				for(auto &k : no){
					mx = max(mx, dp[gph[i][0]][k][0]);
					mn = min(mn, dp[gph[i][0]][k][1]);
				}
				dp[i][j][0] += mx;
				dp[i][j][1] += mn;
			}
		}
		else if(gph[i].size() == 2){
			for(int j=0; j<3; j++){
				vector<int> no;
				for(int k=0; k<3; k++){
					if(j == k) continue;
					no.push_back(k);
				}
				dp[i][j][0] += max(dp[gph[i][0]][no[0]][0] + dp[gph[i][1]][no[1]][0], 
									dp[gph[i][1]][no[0]][0] + dp[gph[i][0]][no[1]][0]);
				dp[i][j][1] += min(dp[gph[i][0]][no[0]][1] + dp[gph[i][1]][no[1]][1],
									dp[gph[i][1]][no[0]][1] + dp[gph[i][0]][no[1]][1]);
			}
		}
	}
	int mx = -1, mn = 1e9;
	for(int i=0; i<3; i++){
		mx = max(dp[0][i][0], mx);
		mn = min(dp[0][i][1], mn);
	}
	printf("%d %d\n", mx, mn);
}
