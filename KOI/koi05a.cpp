#include <cstdio>
#include <cstring>
 
int n,a[10],k,obj;
int optima[10],v;
 
void print(int* aa){
    int i=0;
    while (aa[i]==0) i++;
    for (; i<10; i++) printf("%d",aa[i]);
}
 
void f(int depth, int cnum[],int visited){
    if(v) return;
    if(depth==9){
        int sum=0;
        for (int i=0; i<5; i++) sum+=(5-i)*cnum[i];
        for (int i=5; i<9; i++) sum-=(i-4)*cnum[i];
        if(sum<0) return;
        if(sum%5) return;
        int i;
        for (i=0; i<=n; i++) {
            if(a[i]==sum/5) break;
        }
        if(i==n+1) return;
        if((visited&(1<<(i-1)))) return;
        cnum[9]=sum/5;
        if(k==obj){
            print(cnum);
            k++;
            v++;
            return;
        }
        memcpy(optima,cnum,40);
        k++;
        return;
    }
    f(depth+1,cnum,visited);
    for (int i=1; i<=n; i++) {
        if(!(visited&(1<<(i-1)))){
            cnum[depth]=a[i];
            f(depth+1,cnum,visited|(1<<(i-1)));
        }
    }
    cnum[depth]=0;
}
int main(){
    int cnum[10]={};
    scanf("%d",&n);
    for (int i=1; i<=n; i++) scanf("%d",&a[i]);
    scanf("%d",&obj);
    f(0,cnum,0);
    if(!v) print(optima);
}