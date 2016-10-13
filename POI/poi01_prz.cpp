#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

int n;
pi a[50005];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
	}
	sort(a,a+n);
	int st = a[0].first, ed = a[0].second;
	for(int i=1; i<n; i++){
		if(ed < a[i].first){
			printf("%d %d\n",st,ed);
			st = a[i].first;
			ed = a[i].second;
		}
		st = min(st, a[i].first);
		ed = max(ed, a[i].second);
	}
	printf("%d %d\n",st, ed);
}