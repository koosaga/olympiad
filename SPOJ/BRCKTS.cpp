// Ivan Carvalho
// Solution to https://www.spoj.com/problems/BRCKTS/
#include <cstdio>
#include <algorithm>
#define MAXN 30010
using namespace std;
typedef struct no{
	int p1,p2;
}no;
no join(no A,no B){
	no temp;
	temp.p1 = max(A.p1 - B.p2,0) + B.p1;
	temp.p2 = A.p2 + max(B.p2 - A.p1,0);
	return temp;
}
no arvore[4*MAXN];
char vetor[MAXN];
void build(int pos,int left,int right){
	if(left == right){
		if(vetor[left] == '('){
			arvore[pos].p1 = 1;
			arvore[pos].p2 = 0;
		}
		else{
			arvore[pos].p1 = 0;
			arvore[pos].p2 = 1;
		}
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = join(arvore[2*pos],arvore[2*pos+1]);
}
void update(int pos,int left,int right,int x){
	if(left == right){
		swap(arvore[pos].p1,arvore[pos].p2);
		return;
	}
	int mid = (left+right)/2;
	if(x<=mid){
		update(2*pos,left,mid,x);
	}
	else{
		update(2*pos+1,mid+1,right,x);
	}
	arvore[pos] = join(arvore[2*pos],arvore[2*pos+1]);
}
int main(){
	int n,q,teste=0;
	while(scanf("%d",&n) != EOF){
		printf("Test %d:\n",++teste);
		for(int i = 1;i<=n;i++){
			scanf(" %c",&vetor[i]);
		}
		build(1,1,n);
		scanf("%d",&q);
		while(q--){
			int x;
			scanf("%d",&x);
			if(x == 0){
				if(arvore[1].p1 == 0 && arvore[1].p2 == 0) printf("YES\n");
				else printf("NO\n");
			}
			else update(1,1,n,x);
		}
	}
	return 0;
}