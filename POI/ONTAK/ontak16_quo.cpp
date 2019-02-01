#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

lint k;
int n;
char str[1000005];

int main(){
	scanf("%lld %d %s",&k,&n,str);
	int cnt = 0;
	for(int i=n-1; i>=0; i--){
		if(str[i] == 'P'){
			cnt++;
		}
		else{
			if(cnt == 0){
				if(str[i] == 'L'){
					if(k % 2 == 1){
						puts("0");
						return 0;
					}
					k /= 2;
				}
				else{
					if(k % 2 == 0 || k == 1){
						puts("0");
						return 0;
					}
					k /= 2;
				}
			}
			else cnt--;
		}
	}
	int ans = 1;
	for(int i=0; i<cnt; i++) ans = (ans * 2) % mod;
	cout << ans;
}
