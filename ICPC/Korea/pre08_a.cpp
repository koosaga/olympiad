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

int main(){
    int t;
    scanf("%d\n",&t);
    while(t--){
        char str[1000] = {};
        fgets(str,1000,stdin);
        int freq[26];
        for(int i=0; i<26; i++){
            freq[i] = count(str, str +1000, i + 'a');
        }
        int maxv = *max_element(freq, freq + 26);
        int cnt = 0;
        for(int i=0; i<26; i++){
            if(freq[i] == maxv) cnt++;
        }
        if(cnt == 1) printf("%c\n",max_element(freq, freq+ 26) - freq + 'a');
        else puts("?");
    }
}