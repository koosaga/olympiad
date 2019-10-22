#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

lint arr[4][MAXN][MAXN];

lint bino(int x, int y){
	lint ret = 1;
	for(int i=0; i<y; i++){
		ret *= x - i;
		ret /= i + 1;
	}
	return ret;
}

int main(){
	int t; cin >> t;
	while(t--){
		int n; scanf("%d",&n);
		memset(arr, 0, sizeof(arr));
		for(int i=0; i<n; i++){
			int sx, sy, ex, ey;
			scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
			ex++; ey++;
			for(int j=0; j<2; j++){
				for(int k=0; k<2; k++){
					arr[2*j+k][sx+j][sy+k]++;
					arr[2*j+k][sx+j][ey]--;
					arr[2*j+k][ex][sy+k]--;
					arr[2*j+k][ex][ey]++;
				}
			}
		}
		for(int i=0; i<4; i++){
			for(int j=1; j<MAXN; j++){
				for(int k=1; k<MAXN; k++){
					arr[i][j][k] += arr[i][j-1][k] + arr[i][j][k-1] - arr[i][j-1][k-1];
				}
			}
			for(int j=0; j<MAXN; j++){
				for(int k=0; k<MAXN; k++){
					arr[i][j][k] = bino(arr[i][j][k], 3);
				}
			}
		}
		lint ret = 0;
		for(int i=1; i<MAXN; i++){
			for(int j=1; j<MAXN; j++){
				ret += arr[0][i][j] - arr[1][i][j] - arr[2][i][j] + arr[3][i][j];
			}
		}
		cout << ret << endl;
	}
}
