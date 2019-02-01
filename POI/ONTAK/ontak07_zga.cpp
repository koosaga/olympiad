#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct disj{
	int pa[400005];
	void init(int n){
		for(int i=0; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	void uni(int x, int y){
		pa[find(x)]= find(y);
		find(x);
	}
}disj;

vector<int> v;
int s[100005], e[100005], x[100005];
int n;

int main(){
	scanf("%d",&n);
	for (int i=0; i<n; i++) {
		scanf("%d %d %d",&s[i],&e[i],&x[i]);
		v.push_back(s[i]-1);
		v.push_back(e[i]);
		s[i]--;
	}
	sort(v.begin(),v.end());
	v.resize(unique(v.begin(),v.end()) - v.begin());
	int t = (int)v.size();
	disj.init(2*t);
	for (int i=0; i<n; i++) {
		s[i] = (int)(lower_bound(v.begin(),v.end(),s[i]) - v.begin());
		e[i] = (int)(lower_bound(v.begin(),v.end(),e[i]) - v.begin());
		if(x[i]){
			disj.uni(s[i] + t,e[i]);
			disj.uni(e[i] + t,s[i]);
		}
		else{
			disj.uni(s[i],e[i]);
			disj.uni(s[i] + t,e[i] + t);
		}
		if(disj.find(s[i]) == disj.find(t + s[i]) || disj.find(e[i]) == disj.find(t + e[i])){
			printf("%d",i);
			return 0;
		}
	}
	printf("%d",n);
}