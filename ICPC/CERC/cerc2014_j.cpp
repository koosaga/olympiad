#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
char str[12][12];
bool chk[12][12];
int empt[12][12];
 
int bktk(int x, int y){
	int ret = 0;
	empt[x][y]++;
	for(int i=-1; i<=1; i+=2){
		for(int j=-1; j<=1; j+=2){
			if(x + 2*i < 0 || x + 2*i >= 10 || y +2*j < 0 || y + 2*j >= 10){
				continue;
			}
			if(str[x+i][y+j] == 'B' && empt[x+2*i][y+2*j] && !chk[x+i][y+j]){
				chk[x+i][y+j] = 1;
				ret = max(ret, bktk(x+2*i, y+2*j) + 1);
				chk[x+i][y+j] = 0;
			}
		}
	}
	empt[x][y]--;
	return ret;
}
 
int solve(){
	int ret = 0;
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			empt[i][j] = 0;
			if(str[i][j] == '.' || str[i][j] == '#'){
				empt[i][j] = 1;
			}
		}
	}
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			if(str[i][j] == 'W'){
				ret = max(ret, bktk(i, j));
			}
		}
	}
	return ret;
}
 
int main(){
	int t;
	cin >> t;
	while(t--){
		for(int i=0; i<10; i++){
			cin >> str[i];
		}
		cout << solve() << endl;
	}
}