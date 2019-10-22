#include <bits/stdc++.h>
using namespace std;

int k;
char str[2100000];
int sj[2100000], so[2100000], si[2100000];

int solve(int s){
    int pt = s, ret = 0;
    for (int i=k-1; i>=0; i--) {
        int add = (1 << (2*i));
        ret += sj[pt + add - 1] - sj[pt - 1];
        pt += add;
        ret += so[pt + add - 1] - so[pt - 1];
        pt += add;
        ret += si[pt + add - 1] - si[pt - 1];
        pt += add;
    }
    return ret + 1;
}

int main(){
    scanf("%d %s",&k,str+1);
    memcpy(str+(1<<(2*k))+1,str+1,(1<<2*k));
    for (int i=1; i<=2 * (1<<(2*k)); i++) {
        sj[i] = sj[i-1] + (str[i] == 'J');
        so[i] = so[i-1] + (str[i] == 'O');
        si[i] = si[i-1] + (str[i] == 'I');
    }
    int ret = 0;
    for (int i=1; i<=(1<<2*k); i++) {
        ret = max(ret,solve(i));
    }
    printf("%d\n",(1<<2*k) - ret);
}