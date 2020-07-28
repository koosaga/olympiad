// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1013
#include <iostream>
 
using namespace std;
 
int main() {
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    if (a>=b && a>=c) printf("%d eh o maior\n",a);
    else if (b>=a && b>=c) printf("%d eh o maior\n",b);
    else printf("%d eh o maior\n",c);
    return 0;
}
