#include <cstdio>
#include <cmath>
#include <stack>
#include <algorithm>
using namespace std;
typedef long double lfloat;

int n, x[200005], l[200005];
lfloat r[200005];
stack<int> s;

long double col(int i, int j){
    return 0.25 * (x[i] - x[j]) * (x[i] - x[j]) / r[i];
}

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x[i],&l[i]);
        r[i] = l[i];
        while (!s.empty()) {
            r[i] = min(r[i],col(s.top(),i));
            if(r[s.top()] < r[i]){
                s.pop();
            }
            else break;
        }
        s.push(i);
        printf("%.3Lf\n",r[i]);
    }
}