// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ZQUERY/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50010;
const int BUCKET = 230;
int vetor[MAXN],N,Q,primeira[2*MAXN],precalc[BUCKET][BUCKET],divisao[MAXN];
vector<int> pilhas[2*MAXN];
void build(int id){
	for(int i = 0;i<2*MAXN;i++) primeira[i] = N;
	int resp = 0;
	if(id == 0){
		primeira[MAXN] = -1;
	}
	else{
		primeira[vetor[id*BUCKET - 1]] = id*BUCKET - 1; 
	}
	for(int i = id*BUCKET;i<N;i++){
		int val = vetor[i];
		primeira[val] = min(primeira[val],i);
		resp = max(resp,i - primeira[val]);
		precalc[id][divisao[i]] = resp;
	}
}
int main(){
	scanf("%d %d",&N,&Q);
	for(int i = 0;i<N;i++){
		scanf("%d",&vetor[i]);
		divisao[i] = i/BUCKET;
	}
	for(int i = 1;i<N;i++) vetor[i] += vetor[i-1];
	for(int i = 0;i<N;i++) vetor[i] += MAXN;
	pilhas[MAXN].push_back(-1);
	for(int i = 0;i<N;i++) pilhas[vetor[i]].push_back(i);
	int tot_baldes = (N-1)/BUCKET;
	for(int i = 0;i<=tot_baldes;i++) build(i);
	while(Q--){
		int l,r;
		scanf("%d %d",&l,&r);
		l--;r--;
		int l_bucket = divisao[l],r_bucket = divisao[r];
		if(l_bucket == r_bucket){
			int resp = 0;
			for(int i = l;i<=r;i++){
				int val = vetor[i];
				int pos = *lower_bound(pilhas[val].begin(),pilhas[val].end(),l-1);
				resp = max(resp,i - pos);
			}
			printf("%d\n",resp);
		}
		else{
			int resp = precalc[l_bucket+1][r_bucket-1];
			for(int i = r_bucket*BUCKET;i<=r;i++){
				int val = vetor[i];
				int pos = *lower_bound(pilhas[val].begin(),pilhas[val].end(),l-1);
				resp = max(resp,i - pos);
			}
			for(int i = max(0,l-1);i<(l_bucket+1)*BUCKET;i++){
				int val = vetor[i];
				int pos = *prev(upper_bound(pilhas[val].begin(),pilhas[val].end(),r));
				resp = max(resp,pos - i);
			}
			if(l == 0){
				int val = MAXN;
				int pos = *prev(upper_bound(pilhas[val].begin(),pilhas[val].end(),r));
				resp = max(resp,pos + 1);
			}
			printf("%d\n",resp);
		}
	}
	return 0;
} 