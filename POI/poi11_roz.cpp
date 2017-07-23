#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 1000005;

int n;
char str[MAXN];

int main(){
	cin >> n >> (str + 1);
	int ans = 0;
	for(int i='a'; i<='z'; i++){
		int cnt[26] = {};
		for(int j=1; j<=n; j++){
			if(str[j] == i){
				int aux[26] = {};
				for(int k=j+1; k<=n && str[k] != i; k++){
					aux[str[k] - 'a']++;
				}
				for(int j=0; j<26; j++){
					if(j + 'a' == i) continue;
					ans = max(ans, cnt[j] + aux[j] - 1);
				}
			}
			cnt[str[j] - 'a']++;
			if(str[j] == i) for(int j=0; j<26; j++) cnt[j] = max(cnt[j] - 1, 0);
		}
	}
	cout << ans;
}
