// Ivan Carvalho
// Solution to https://www.spoj.com/problems/IITWPC4D/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
const int MAXN = 1e5 + 10;
int vetor[MAXN],arvore[4*MAXN],exibir[MAXN],usado[MAXN],n,TC;
void update(int pos,int left,int right,int x,int val){
	//printf("P %d L %d R %d X %d V %d\n",pos,left,right,x,val);
	if(left == right){
		arvore[pos] += val;
		return;
	}
	int mid = (left + right)/2;
	if(x <= mid){
		arvore[pos] += val;
		update(2*pos,left,mid,x,val);
	}
	else{
		arvore[pos] += val;
		update(2*pos+1,mid+1,right,x,val);
	}
}
int kth(int pos,int left,int right,int count){
	//printf("P %d L %d R %d C %d\n",pos,left,right,count);
	if(left == right){
		return left;
	}
	int mid = (left+right)/2;
	int davez = arvore[2*pos];
	if(count <= davez) return kth(2*pos,left,mid,count);
	return kth(2*pos+1,mid+1,right,count - davez);
}
int query(int pos,int left,int right,int i,int j){
	//printf("P %d L %d R %d I %d J %d\n",pos,left,right,i,j);
	if(left > right || left > j || right < i) return 0;
	if(left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	return query(2*pos,left,mid,i,j) + query(2*pos+1,mid+1,right,i,j);
}
int main(){
	scanf("%d",&TC);
	for(int tc=1;tc<=TC;tc++){
		scanf("%d",&n);
		set<int> conjunto;
		memset(usado,0,sizeof(usado));
		memset(arvore,0,sizeof(arvore));
		for(int i=1;i<=n;i++){
			scanf("%d",&vetor[i]);
			update(1,1,n,i,1);
			conjunto.insert(i);
		}
		int flag = 0;
		for(int i = n;i >= 1;i--){
			int k = i - vetor[i];
			exibir[i] = kth(1,1,n,k);
			update(1,1,n,exibir[i],-1);
			if(conjunto.count(exibir[i])){
				conjunto.erase(exibir[i]);
			}
			else{
				flag = 1;
			}
		}
		if(!conjunto.empty()) flag = 1;
		printf("Test : %d\n",tc);
		for(int i=1;i<=n;i++){
			usado[i] = query(1,1,n,exibir[i]+1,n);
			//printf("%d ",usado[i]);
			if(usado[i] != vetor[i]) flag = 1;
			update(1,1,n,exibir[i],1);
		}
		//printf("\n");
		if(flag){
			printf("-1\n");
			continue;
		}
		for(int i=1;i<=n;i++) printf("%d ",exibir[i]);
		printf("\n");
	}
	return 0;
}