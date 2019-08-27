///////////////////////////
//
// Tarjan (SCC)
//
///////////////////////////
void tarjan(int u, int pre) {
  top++; stack[top]=u; 
  stp++; dfn[u]=low[u]=stp;
  rept(iter,e[u])
  {
    int v=*iter;
    if (v==pre) continue;
    if (!dfn[v]) {
      tarjan(v,u);
      low[u]=min(low[u],low[v]);
    }
    else  low[u]=min(low[u],dfn[v]);
  }
  if (dfn[u]==low[u]) {
    cn++; 
    do { 
      belong[stack[top]]=cn; top--;  
    } while (stack[top+1]!=u);
  }
} 
