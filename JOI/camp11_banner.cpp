#include <cstdio>
typedef long long lint;

int w, h, a[405][405];
int cnt[405][405][8];
lint ans;

int main(){
    scanf("%d %d",&w,&h);
    for (int i=0; i<w; i++) {
        for (int j=0; j<h; j++) {
            scanf("%d",&a[i][j]);
        }
    }
    for (int i=0; i<w; i++) {
        for (int j=0; j<h; j++) {
            for (int k=j+1; k<h; k++) {
                for (int l=1; l<7; l++) {
                    if(((1 << a[i][j]) | (1 << a[i][k]) | l) != 7){
                        continue;
                    }
                    ans += cnt[j][k][l];
                }
            }
        }
        for (int j=0; j<h; j++) {
            for (int k=j+1; k<h; k++) {
                cnt[j][k][(1<<a[i][j])|(1<<a[i][k])]++;
            }
        }
    }
    printf("%lld\n",ans);
}