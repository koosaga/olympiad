#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int rev[1000005], sfx[1000005];
char str[1000005];
int n;

void solve(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&sfx[i]);
		sfx[i]--;
		rev[sfx[i]] = i;
	}
	memset(str, 0, sizeof(str));
	rev[n] = -1;
	str[sfx[0]] = 'a';
	for(int i=1; i<n; i++){
		int p1 = sfx[i-1] + 1;
		int p2 = sfx[i] + 1;
		if(rev[p1] < rev[p2]){
			str[sfx[i]] = str[sfx[i-1]];
		}
		else{
			str[sfx[i]] = str[sfx[i-1]] + 1;
			if(str[sfx[i]] > 'z'){
				puts("-1");
				return;
			}
		}
	}
	cout << str << endl;
}

int main(){
	int t;
	scanf("%d",&t);
	for(int i=1; i<=t; i++){
	//	printf("Case #%d: ", i);
		solve();
	}
}
