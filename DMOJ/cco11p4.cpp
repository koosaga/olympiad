// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco11p4
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
typedef pair<int,int> ii;
set<ii> cjt2,cjt1;
int davez,N;
int main(){
	scanf("%d",&N);
	scanf("%d",&davez);
	cjt2.insert(ii(davez,1));
	for(int i = 2;i<=N;i++){
		scanf("%d",&davez);
		ii agora = ii(davez,i);
		if(!cjt2.empty()){
			auto it = cjt2.lower_bound(agora);
			if(it != cjt2.begin()){
				it = prev(it);
				ii copia = *it;
				cjt2.erase(it);
				cjt2.insert(agora);
				cjt1.insert(copia);
				continue;
			}
		}
		if(!cjt1.empty()){
			auto it = cjt1.lower_bound(agora);
			if(it != cjt1.begin()){
				it = prev(it);
				ii copia = *it;
				cjt1.erase(it);
				cjt2.insert(agora);
				continue;
			}
		}
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	return 0;
}