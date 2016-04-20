#include <cstdio>
#include <algorithm>
 
struct data{int pos,type,lv;}a[200005];
int cmp(data a,data b){return a.pos<b.pos;}
int cmp2(data a,data b){return a.lv<b.lv;}
 
int n,m,min,max,sp,r;
 
int count(int s, int e){
    std::sort(a+s,a+e+1,cmp);
    int r=0;
    for (int i=s; i<e; i+=2) {
        r+=a[i+1].pos-a[i].pos;
    }
    if(s%2==e%2){
        int rm=r;
        for (int i=e; i-2>=s; i-=2) {
            r+=a[i].pos-a[i-1].pos-(a[i-1].pos-a[i-2].pos);
            if(rm>r) rm=r;
        }
        r=rm;
    }
    return r;
}
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<n+m; i++) {
        scanf("%d",&a[i].pos);
        if(i>=n) a[i].type=1;
    }
    std::sort(a,a+n+m,cmp);
    for (int i=1; i<n+m; i++) {
        a[i].lv=a[i-1].lv;
        if(a[i].type==a[i-1].type){
            if(a[i].type) a[i].lv++;
            else a[i].lv--;
        }
    }
    std::sort(a,a+n+m,cmp2);
    for (int i=0; i<n+m; i++) {
        if(min<a[i].lv) min=a[i].lv;
        if(max>a[i].lv) max=a[i].lv;
    }
    for (int i=1; i<n+m; i++) {
        if(a[i].lv!=a[i-1].lv){
            r+=count(sp,i-1);
            sp=i;
        }
    }
    r+=count(sp,n+m-1);
    printf("%d",r);
}