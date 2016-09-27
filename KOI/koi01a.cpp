#include <cstdio>
#include <map>
using namespace std;
 
int t,n,m;
int a[1005], b[1005];
map<int,int> mp;
 
int main(){
	scanf("%d",&t);
	scanf("%d",&n);
	for (int i=0; i<n; i++) {
		scanf("%d",&a[i]);
	}
	scanf("%d",&m);
	for (int i=0; i<m; i++) {
		scanf("%d",&b[i]);
	}
	for (int i=0; i<n; i++) {
		int r = 0;
		for (int j=i; j<n; j++) {
			r += a[j];
			mp[r]++;
		}
	}
	long long res = 0;
	for (int i=0; i<m; i++) {
		int r = 0;
		for (int j=i; j<m; j++) {
			r += b[j];
			if(mp.find(t - r) != mp.end()){
				res += mp[t-r];
			}
		}
	}
	printf("%lld",res);
}