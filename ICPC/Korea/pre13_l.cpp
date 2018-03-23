#include <cstdio>

int p[1005], in[1005];

void recs(int s1, int e1, int s2, int e2){
    for (int i=s2; i<e2; i++) {
        if(p[s1] == in[i]){
            int nulbby = (i - s2 + 1);
            recs(s1+1,s1 + nulbby, s2, i);
            recs(s1 + nulbby, e1, i+1, e2);
            printf("%d ",p[s1]);
            return;
        }
    }
}
void calc(){
    int n;
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&p[i]);
    }
    for (int i=0; i<n; i++) {
        scanf("%d",&in[i]);
    }
    recs(0,n,0,n);
    puts("");
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        calc();
    }
}