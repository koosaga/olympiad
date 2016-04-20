#include <cstdio>
#include <algorithm>
#define AVG (s+e)/2
 
int search(int a[],int v,int err,int s, int e){
    if(a[AVG]<=v+err && a[AVG]>=v-err) return 1;
    if(s==e) return 0;
    if(a[AVG]>v+err) return search(a,v,err,s,AVG);
    if(a[AVG]<v-err) return search(a,v,err,AVG+1,e);
    return search(a,v,err,AVG+1,e)+search(a,v,err,s,AVG);
}
int main(){
    int m,n,l;
    scanf("%d %d %d",&m,&n,&l);
    int a[m],x,y,r=0;
    for (int i=0; i<m; i++) {
        scanf("%d",&a[i]);
    }
    std::sort(a,a+m);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x,&y);
        if(search(a,x,l-y,0,m-1)) r++;
    }
    printf("%d",r);
}