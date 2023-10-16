#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;

stack<int> s;

int n,a[300005];

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    int res = 0;
    for (int i=0; i<n; i++) {
        while(!s.empty() && a[s.top()] > a[i]){
            int q = s.top(), w = 0;
            s.pop();
            if(s.empty()) w = i;
            else w = i - 1 - s.top();
            res = max(res,min(w, a[q]));
        }
        s.push(i);
    }
    while (!s.empty()){
        int q = s.top(), w = 0;
        s.pop();
        if(s.empty()) w = n;
        else w = n - 1 - s.top();
        res = max(res,min(w, a[q]));
    }
    printf("%d\n", res);
}
