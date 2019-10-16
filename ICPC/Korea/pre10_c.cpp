#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

int n, m;
char s1[MAXN], s2[MAXN];

int main(){
	int t; scanf("%d\n",&t);
	while(t--){
		fgets(s1, MAXN, stdin);
		fgets(s2, MAXN, stdin);
		int n = strlen(s1) - 1;
		vector<int> ans;
		int cnt[20] = {};
		for(int i=0; i<n; i++) s1[i] = tolower(s1[i]);
		for(int i=0; s2[i]; i++){
			if(isalpha(s2[i])){
				s2[i] = tolower(s2[i]);
				cnt[0]++;
				for(int j=n-1; j>=0; j--){
					if(s1[j] == s2[i] && cnt[j]){
						cnt[j+1]++;
						cnt[j]--;
					}
				}
				cnt[0] = 0;
				if(cnt[n]){
					cnt[n] = 0;
					ans.push_back(i + 1);
				}
			}
		}
		printf("%d ", sz(ans));
		if(sz(ans) > 3) ans.resize(3);
		for(auto &i : ans) printf("%d ", i);
		puts("");
	}
}
