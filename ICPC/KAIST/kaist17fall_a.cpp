#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 +7;

int n;
char str[205][205];
vector<pi> ans;

void Do(int x, int y, int stp){
	if(!stp){
		if(str[x][y] == 'D') return;
		assert(str[x][y] == 'L');
		if(str[x-1][y] == 'L'){
			str[x-1][y] = 'U';
			str[x][y] = 'D';
			str[x-1][y+1] = 'U';
			str[x][y+1] = 'D';
			ans.push_back(pi(x-1, y));
			return;
		}
		else{
			Do(x-1, y+1, stp);
			str[x-2][y] = 'L';
			str[x-2][y+1] = 'R';
			str[x-1][y] = 'L';
			str[x-1][y+1] = 'R';
			ans.push_back(pi(x-2, y));
			str[x-1][y] = 'U';
			str[x][y] = 'D';
			str[x-1][y+1] = 'U';
			str[x][y+1] = 'D';
			ans.push_back(pi(x-1, y));
			return;
		}
	}
	assert(0);
}

int main(){
	cin >> n;
	for(int i=0; i<2*n; i++) cin >> str[i];
	for(int i=0; i<2*n; i++){
		int dis;
		if(i >= n) dis = 2 * n - 1 - (i - n);
		else dis = 2 * n - 1 - (n - 1 - i);
		for(int j=dis; j >= 0 &&str[j][i] != '.'; j-=2){
			Do(j, i, 0);
		}
	}
	cout << ans.size() << endl;
	for(auto &i : ans) printf("%d %d\n", i.first + 1, i.second + 1);
}
