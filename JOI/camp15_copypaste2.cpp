#include <cstdio>

int k, m;
char str[200005];
int n;
int s[200005], e[200005], x[200005];
int dep[205];

int main(){
    scanf("%d %d %s",&k,&m,str+1);
    scanf("%d",&n);
    for (int i=n-1; i>=0; i--) {
        scanf("%d %d %d",&s[i],&e[i],&x[i]);
        s[i]++;
        x[i]++;
    }
    for (int i=1; i<=k; i++) {
        dep[i] = i;
    }
    for (int i=0; i<n; i++) {
        int ndep[205] = {};
        for (int j=1; j<=k; j++) {
            if(dep[j] > x[i] + e[i] - s[i]){
                ndep[j] = dep[j] - e[i] + s[i] - 1;
            }
            else if(dep[j] <= x[i] + e[i] - s[i] && dep[j] >= x[i]){
                ndep[j] = dep[j] - x[i] + s[i];
            }
            else{
                ndep[j] = dep[j];
            }
        }
        for (int j=1; j<=k; j++) {
            dep[j] = ndep[j];
            //    printf("%d ",dep[j]);
        }
        //puts("");
    }
    for (int i=1; i<=k; i++) {
        putchar(str[dep[i]]);
    }
}