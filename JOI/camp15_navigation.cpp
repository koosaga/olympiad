#include "navigation_lib.h"
#include <vector>
using namespace std;
 
vector<int> graph[100005];
bool my_flag[100005];
 
void dfs(int x, int pa){
    Flag(x,my_flag[x]);
    for (auto &i : graph[x]){
        if(i == pa) continue;
        if(i < x) my_flag[i] = my_flag[x];
        else my_flag[i] = my_flag[x] ^ 1;
        dfs(i,x);
    }
}
 
void Anna(int K, int N, int T, int A[], int B[]){
    for (int i=0; i<N-1; i++) {
        graph[A[i]].push_back(B[i]);
        graph[B[i]].push_back(A[i]);
    }
    dfs(T,-1);
}
 
void Bruno(int K, int S, int F, int L, int P[], int Q[]){
    for (int i=0; i<L; i++) {
        if(P[i] < S){
            if(Q[i] != F){
                Answer(P[i]);
            }
        }
        else{
            if(Q[i] == F){
                Answer(P[i]);
            }
        }
    }
    Answer(S);
}