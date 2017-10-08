#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int p, a, b, c, d, n;

double price(int k){
    return p * (sin(a * k + b) + cos(c * k + d) + 2);
}
int main(){
    scanf("%d %d %d %d %d %d",&p,&a,&b,&c,&d,&n);
    double cmax = 0, ret = 0;
    for(int i=1; i<n; i++){
        cmax = max(cmax, price(i));
        ret = max(ret, cmax - price(i+1));
    }
    printf("%f",ret);
}