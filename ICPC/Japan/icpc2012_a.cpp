#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 3005;

int main(){
	int tc; 
	cin >> tc; 
	while(tc--){
		int n, m;
		cin >> n >> m;
		int cnt = 0;
		for(int i=-200; i<=200; i++){
			for(int j=-200; j<=200; j++){
				if(i == 0 && j == 0) continue;
				int m2n2 = i * i + j * j;
				int mpnq = i * n + j * m;
				int mqnp = abs(i * m - j * n);
				if(mqnp % m2n2 == 0 && mpnq % m2n2 == 0) cnt++;
			}
		}
		puts(cnt == 8 ? "P" : "C");
	}
}
