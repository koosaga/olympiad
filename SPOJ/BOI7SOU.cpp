// Ivan Carvalho
// Solution to https://www.spoj.com/problems/BOI7SOU/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
deque<ii> jmin,jmax;
vector<int> resposta;
int main(){
	int n,k,c;
	scanf("%d %d %d",&n,&k,&c);
	for(int i = 1;i<k;i++){
		int davez;
		scanf("%d",&davez);
		ii par = ii(davez,i);
		while(!jmin.empty() && jmin.back() > par) jmin.pop_back();
		while(!jmax.empty() && jmax.back() < par) jmax.pop_back();
		jmin.push_back(par);
		jmax.push_back(par);
	}
	for(int i = k;i<=n;i++){
		int davez;
		scanf("%d",&davez);
		ii par = ii(davez,i);
		if(!jmin.empty() && jmin.front().second == i - k) jmin.pop_front();
		if(!jmax.empty() && jmax.front().second == i - k) jmax.pop_front();
		while(!jmin.empty() && jmin.back() > par) jmin.pop_back();
		while(!jmax.empty() && jmax.back() < par) jmax.pop_back();
		jmin.push_back(par);
		jmax.push_back(par);
		if(jmax.front().first - jmin.front().first <= c) resposta.push_back(i - k + 1);
	}
	if(resposta.empty()) printf("NONE\n");
	for(int i : resposta) printf("%d\n",i);
	return 0;
}