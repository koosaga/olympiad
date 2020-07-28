// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1008
#include <iostream>
 
using namespace std;
 
int main() {
    int a,b;
    double c;
    scanf("%d",&a);
    scanf("%d",&b);
    scanf("%lf",&c);
    printf("NUMBER = %d\nSALARY = U$ %.2lf\n",a,b*c);
    return 0;
}
