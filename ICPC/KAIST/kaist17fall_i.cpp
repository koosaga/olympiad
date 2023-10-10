#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 1000005;

// http://www.imomath.com/index.php?options=785

int n, a[MAXN];

int main(){
    scanf("%d",&n);
    if(n <= 3){
        puts("NIE");
        return 0;
    }
    for(int i=0; i<n; i++) scanf("%d",&a[i]);
    rotate(a, min_element(a, a+n), a+n);
    int x = a[1], y = a[n-1];
    if(x + y < n){
        puts("TAK");
        return 0;
    }
    for(int i=2; i<n-1; i++){
        if(a[i-1] + x < n){
            if(a[i] != a[i-1] + x){
                puts("TAK");
                return 0;
            }
        }
        else if(a[i-1] >= y){
            if(a[i] != a[i-1] - y){
                puts("TAK");
                return 0;
            }
        }
        else if(a[i] != a[i-1] + x - y){
            puts("TAK");
            return 0;
        }
    }
    puts("NIE");
}
