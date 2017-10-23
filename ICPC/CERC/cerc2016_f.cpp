#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, a[100005], b[100005];
int ca[100005], cb[100005];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		ca[a[i]] = 1;
	}
	for(int i=1; i<=n; i++){
		scanf("%d",&b[i]);
		cb[b[i]] = 1;
	}
	int totedg = n - count(b+1, b+n+1, 0);
	int prvedg = n - count(a+1, a+n+1, 0);
	int edg = 0;
	for(int i=1; i<=n; i++){
		if(!ca[i] && !cb[i]){
			for(int j=i; a[j] > 0 && a[j] == b[j]; j=a[j]){
				edg++;
			}
		}
	}
	cout << totedg + prvedg - 2 * edg;
}
