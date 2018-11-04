#include <bits/stdc++.h>
using namespace std;

int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int m, n;

int main(){
	cin >> m >> n;
	int px = 0, py = 0;
	int d = 0;
	while(n--){
		string w;
		int x;
		cin >> w >> x;
		if(w == "MOVE"){
			px += x * dx[d];
			py += x * dy[d];
			if(max(px, py) > m || min(px, py) < 0){
				cout << -1;
				return 0;
			}
		}
		else{
			if(x == 0){
				d = (d+1) % 4;
			}
			else{
				d = (d+3) % 4;
			}
		}
	}
	cout << px << " " << py;
}

