#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

double score[7][3] = {
    {9.23076, 26.7, 1.835},
    {1.84523, 75, 1.348},
    {56.0211, 1.5, 1.05},
    {4.99087, 42.5, 1.81},
    {0.188807, 210, 1.41},
    {15.9803, 3.8, 1.04},
    {0.11193, 254, 1.88}
};

double solve(int p, double x){
    return score[p][0] * pow(fabs(score[p][1] - x), score[p][2]);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int ret = 0;
        for(int i=0; i<7; i++){
            int x;
            scanf("%d",&x);
            ret += (int)solve(i, x);
        }
        printf("%d\n",ret);
    }
}