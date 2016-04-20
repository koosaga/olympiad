#include <cstdio>
#include <algorithm>
using namespace std;
 
int n,m;
char str[1005][1005], s2[3][3];
 
int match(int i, int j){
    if(i < 0 || j < 0) return 0;
    if(i == n-1 || j == m-1) return 0;
    return str[i][j] == s2[0][0] && str[i][j+1] == s2[0][1] && str[i+1][j] == s2[1][0] && str[i+1][j+1] == s2[1][1];
}
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<n; i++) {
        scanf("%s",str[i]);
    }
    scanf("%s %s",s2[0],s2[1]);
    int ret = 0;
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<m-1; j++) {
            if(match(i,j)) ret++;
        }
    }
    int dmax = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            int cmatch = 0, jmatch = 0, omatch = 0, imatch = 0;
            for (int k=-1; k<=0; k++) {
                for (int l=-1; l<=0; l++) {
                    cmatch += match(i+k,j+l);
                }
            }
            int ori = str[i][j];
            str[i][j] = 'J';
            for (int k=-1; k<=0; k++) {
                for (int l=-1; l<=0; l++) {
                    jmatch += match(i+k,j+l);
                }
            }
            str[i][j] = 'O';
            for (int k=-1; k<=0; k++) {
                for (int l=-1; l<=0; l++) {
                    omatch += match(i+k,j+l);
                }
            }
            str[i][j] = 'I';
            for (int k=-1; k<=0; k++) {
                for (int l=-1; l<=0; l++) {
                    imatch += match(i+k,j+l);
                }
            }
            dmax = max(dmax,max(imatch - cmatch,max(omatch - cmatch,jmatch-cmatch)));
            str[i][j] = ori;
        }
    }
    printf("%d",dmax + ret);
}