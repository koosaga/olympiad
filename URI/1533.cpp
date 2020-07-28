// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1533
#include <cstdio>
#include <vector>
#include <algorithm>
#define MP make_pair
#define PB push_back
using namespace std;
typedef pair<int,int> ii;
int main(){
	int n;
	while(scanf("%d",&n) && n){
		vector<ii> vetor;
		for(int i=1;i<=n;i++){
			int davez;
			scanf("%d",&davez);
			vetor.push_back(MP(davez,i));
		}
		sort(vetor.begin(),vetor.end());
		printf("%d\n",vetor[n-2].second);
	}
	return 0;
}
