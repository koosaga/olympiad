//qwerasdfzxcl
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

void ans(int x, int y){
    printf("%d:%d\n", x, y);
}

int main(){
    int n, x, y;
    scanf("%d %d %d", &n, &x, &y);
    if (n==1){
        if (x==y) printf("1\n");
        else printf("0\n");
        ans(x, y);
        return 0;
    }
    if (x+y < n){
        printf("%d\n", n - x - y);
        for (int i=1;i<=n-x-y;i++) ans(0, 0);
        n -= n - x - y;
    }
    else{
        printf("0\n");
    }

    while(n>2){
        if (x>1) {
            ans(1, 0); --x;
        }
        else{
            assert(y>1);
            ans(0, 1); --y;
        }
        --n;
    }

    if (n==2){
        if (x==0){
            ans(0, 1); --y;
        }
        else if (y==0){
            ans(1, 0); --x;
        }
        else{
            ans(x, 0); x = 0;
        }
        --n;
    }

    if (n==1){
        if (x==0){
            ans(0, y);
        }
        else{
            ans(x, 0);
        }
    }
    return 0;
}
