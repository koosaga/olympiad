#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 300005;

int n, chk[1123455];

string s[MAXN];
char buf[669];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%s", buf);
		if(strlen(buf) > 8) continue;
		int x; sscanf(buf, "%d", &x);
		if(x >= 0 && x < 1010101) chk[x] = 1;
	}
	for(int i=0; ;i++){
		if(!chk[i]){
			cout << i << endl;
			return 0;
		}
	}
}
