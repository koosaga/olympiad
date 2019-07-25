#include<bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;
const int dx[6] = {1, -1, 0, 0, 0, 0};
const int dy[6] = {0, 0, 1, -1, 0, 0};
const int dz[6] = {0, 0, 0, 0, -1, 1};

int a, b, c, n;
vector<tuple<int, int, int>> v;

int main(){
	cin >> a >> b >> c >> n;
	lint ans = 2ll * a * b + 2ll * b * c + 2ll * c * a;
	for(int i=0; i<n; i++){
		int x, y, z; scanf("%d %d %d",&x,&y,&z);
		x++; y++; z++;
		if(x == 1) ans--;
		if(x == a) ans--;
		if(y == 1) ans--;
		if(y == b) ans--;
		if(z == 1) ans--;
		if(z == c) ans--;
		v.emplace_back(x, y, z);
	}
	sort(v.begin(), v.end());
	for(auto [x, y, z] : v){
		for(int j=0; j<6; j++){
			int nx = x + dx[j];
			int ny = y + dy[j];
			int nz = z + dz[j];
			if(1 <= nx && nx <= a && 1 <= ny && ny <= b && 1 <= nz && nz <= c){
				if(!binary_search(v.begin(), v.end(), make_tuple(nx, ny, nz))) ans++;
			}
		}
	}
	cout << ans << endl;
}
