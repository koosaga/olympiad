#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
 
vector<int> pos;
 
int n,a[100005];
 
int main(){
    long long res = 0;
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
        pos.push_back(a[i]*10);
    }
    sort(pos.begin(),pos.end());
    for (int i=0; i<n; i++) {
        res += (int)(lower_bound(pos.begin(),pos.end(),10*a[i]) - lower_bound(pos.begin(),pos.end(),9*a[i]));
    }
    long long cont = 0;
    for (int i=0; i<n; i++) {
        if(i && pos[i-1] != pos[i]) res += cont * (cont - 1) / 2, cont = 0;
        cont++;
    }
    res += cont * (cont - 1) / 2;
    printf("%lld",res);
}