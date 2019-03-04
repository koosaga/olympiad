#include <bits/stdc++.h>
using namespace std;
const int MAXN = 16;

int n;
char str[MAXN + 2];
bool vis[MAXN + 2][1<<MAXN];
bool ans[MAXN + 2][1<<MAXN];

bool f(int msk, int pos){
	if(pos == 0) return msk == 0;
	if(vis[pos][msk]) return ans[pos][msk];
	vis[pos][msk] = 1;
	int flow = (1 << pos) - 1;
	for(int i=0; i<n; i++){
		if(f(msk ^ flow, pos - 1)) return ans[pos][msk] = 1;
		flow <<= 1;
		flow &= (1<<n) - 1;
	}
	return ans[pos][msk] = f(msk, pos - 1);
}

int main(){
	cin >> str;
	n = strlen(str);
	int msk = 0;
	for(int i=0; i<n; i++){
		if(str[i] == '0') msk |= (1<<i);
	}
	int dap = n;
	for(int i=0; i<n; i++){
		if(f(msk, i)){
			dap = i;
			break;
		}
	}
	cout << dap << endl;
}
