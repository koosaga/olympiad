// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco14p4
#include <cstdio>
#include <vector>
#include <algorithm>
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
vector<ii> guloso;
int main(){
	int n,s,comeca  = 0,resp = 1;
	scanf("%d %d",&n,&s);
	for(int i=1;i<=n;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		if(i == s){
			comeca = a;
			continue;
		}
		if(a >= b) guloso.push_back(MP(b,a - b));
	}
	sort(guloso.begin(),guloso.end());
	for(int i = 0;i<guloso.size();i++){
		if(guloso[i].first > comeca){
			break;
		}
		comeca += guloso[i].second;
		resp++;
	}
	printf("%d\n%d\n",comeca,resp);
	return 0;
}