#include <cstdio>

char s[2005][2005];
int J[2005][2005],O[2005][2005],I[2005][2005];
int n,m;

int f(int a, int b, int c, int d){
    return J[b][d]-J[a-1][d]-J[b][c-1]+J[a-1][c-1];
}
int main(){
    int a,b,c,d,k;
    scanf("%d %d %d",&n,&m,&k);
    for (int i=1; i<=n; i++) {
        scanf("%s",s[i]);
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            J[i][j] = J[i][j-1]+J[i-1][j]-J[i-1][j-1];
            O[i][j] = O[i][j-1]+O[i-1][j]-O[i-1][j-1];
            I[i][j] = I[i][j-1]+I[i-1][j]-I[i-1][j-1];
            if(s[i][j-1] == 'J') J[i][j]++;
            if(s[i][j-1] == 'O') O[i][j]++;
            if(s[i][j-1] == 'I') I[i][j]++;
        }
    }
    for (int i=0; i<k; i++) {
        scanf("%d %d %d %d",&a,&c,&b,&d);
        printf("%d %d %d\n",J[b][d]-J[a-1][d]-J[b][c-1]+J[a-1][c-1],O[b][d]-O[a-1][d]-O[b][c-1]+O[a-1][c-1],I[b][d]-I[a-1][d]-I[b][c-1]+I[a-1][c-1]);
    }
}