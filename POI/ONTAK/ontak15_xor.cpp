#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m;
lint a[500005], x;
int imp[500005], tmp[500005];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%lld",&a[i]);
		x ^= a[i];
	}
	lint ret = 0;
	for(int i=59; i>=0; i--){
		if((x >> i) & 1){
			ret ^= (1ll << i);
		}
		else{
			lint cur = 0;
			for(int j=0; j<n; j++){
				cur ^= a[j];
				tmp[j] = ((cur >> i) & 1);
			}
			int cnt = 1;
			for(int j=0; j<n-1; j++){
				if(!imp[j] && !tmp[j]) cnt++;
			}
			if(cnt < m){
				ret ^= (1ll << i);
				continue;
			}
			else{
				for(int j=0; j<n-1; j++){
					imp[j] |= tmp[j];
				}
			}
		}
	}
	cout << ret;
}
