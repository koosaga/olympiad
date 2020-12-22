#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 3000005;

bool chk[MAXN];

pi find_protocol(vector<int> &decks, int n){
	int sum = 0;
	for(auto &i : decks){
		chk[i] = 1;
		sum += i;
		sum %= (2*n+1);
	}
	pi ans(-1, -1);
	auto Do = [&](int x, int y){
		x += sum; y += sum;
		x %= 2*n+1; y %= 2*n+1;
		if(chk[x] && chk[y]) ans = pi(x, y);
	};
	// You can independently verify, that those graph
	// * have different difference for all edges (directed)
	// * have max. independent set < n
	// so, for any set of n vertices, you can always find edges
	// which you can return, with sum encoded
	if(n % 2 == 0){
		for(int i = 1; i < n; i++){
			Do(2*n+1-i, i);
		}
		Do(0, 2*n);
		Do(0, 1);
		Do(n, 2);
		Do(n, 2*n-1);
		Do(4, n+1);
		Do(2*n-3, n+1);
	}
	else{
		for(int i = 1; i < n; i++){
			Do(i, 2*n+1-i);
		}
		Do(0, 2*n);
		Do(0, 1);
		Do(n, 2);
		Do(n, 2*n-1);
		Do(4, n+1);
		Do(2*n-3, n+1);
	}
	for(auto &i : decks) chk[i] = 0;
	return ans;
}

int solve(int x, int y, int n){
	int offset = -1;
	auto Do = [&](int X, int Y){
		if((x + Y) % (2*n+1) == (X + y) % (2*n+1)){
			offset = x - X + 2*n+1;
			offset %= 2*n+1;
		}
	};

	if(n % 2 == 0){
		for(int i = 1; i < n; i++){
			Do(2*n+1-i, i);
		}
		Do(0, 2*n);
		Do(0, 1);
		Do(n, 2);
		Do(n, 2*n-1);
		Do(4, n+1);
		Do(2*n-3, n+1);
	}
	else{
		for(int i = 1; i < n; i++){
			Do(i, 2*n+1-i);
		}
		Do(0, 2*n);
		Do(0, 1);
		Do(n, 2);
		Do(n, 2*n-1);
		Do(4, n+1);
		Do(2*n-3, n+1);
	}

	assert(offset != -1); return offset;
}

int main(){
	int T; scanf("%d",&T);
	int R; scanf("%d",&R);
	while(T--){
		if(R <= 2){
			int n; scanf("%d",&n);
			vector<int> decks(n);
			for(auto &i : decks) scanf("%d",&i);
			pi ret = find_protocol(decks, n);
			printf("%d %d\n", ret.first, ret.second);
		}
		else{
			int sum = 0;
			int n; scanf("%d",&n);
			for(int i=0; i<2; i++){
				int x, y; scanf("%d %d",&x,&y);
				sum += solve(x, y, n);
			}
			sum = 4*n+2-sum;
			printf("%d\n", sum % (2*n+1));
		}
		fflush(stdout);
	}
}

