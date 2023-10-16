#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 250005;
using pi = pair<int, int>;

int chk[MAXN];

int main(){
	int n, m; scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		chk[e] = 1;
	}
	cout << "1\n" << (int)(find(chk+1,chk+n+1,0)-chk) << endl;
}
