#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

char a[1005][1005];
char b[1005][1005];
int n1, m1, n2, m2;

bool ok(int x, int y){
	return x >= 0 && x < n1 && y >= 0 && y < m1 && a[x][y] == 'x';
}

bool solve(){
	scanf("%d %d %d %d",&n1,&m1,&n2,&m2);
	for(int i=0; i<n1; i++) scanf("%s",a[i]);
	vector<pi> pos;
	for(int i=0; i<n2; i++){
		scanf("%s",b[i]);
		for(int j=0; j<m2; j++){
			if(b[i][j] == 'x') pos.push_back(pi(i, j));
		}
	}
	for(int i=1; i<pos.size(); i++){
		pos[i].first -= pos[0].first;
		pos[i].second -= pos[0].second;
	}
	pos[0] = pi(0, 0);
	for(int i=0; i<n1; i++){
		for(int j=0; j<m1; j++){
			if(a[i][j] == 'x'){
				for(auto &k : pos){
					if(!ok(i + k.first, j + k.second)){
						return false;
					}
					a[i + k.first][j + k.second] = '.';
				}
			}
		}
	}
	return true;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		puts(solve() ? "TAK" : "NIE");
	}
}
