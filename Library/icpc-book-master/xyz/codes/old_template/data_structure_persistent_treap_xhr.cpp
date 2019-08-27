///////////////////////////
//
// Persistent Treap
//
///////////////////////////
struct node {
  double key;
  int size;
  node *left, *right;
  node() {}
  node(double key): key(key), size(1), left(NULL), right(NULL) {}
};
struct memoPool {
  int ptr;
  node a[20000000];
  memoPool() { ptr=0; }
  node *allocate(node t) 
  { 
    ptr++; a[ptr]=t; 
    return &a[ptr]; 
  }
} pool;
node *mkcpy(node *t) {
  return pool.allocate(*t);
}

node *update(node *t) {
  t->size=(t->left?t->left->size:0)+
          (t->right?t->right->size:0)+1;
  return t;
}
double ran() {
  static unsigned ranval=1357203341;
  ranval+=(ranval<<2)+1;
  return (ranval&65535)/65536.0;
}
void merge(node *L, node *R, node *&t) {
  if (!L || !R) { t=L?L:R; return; }
  node *ret;
  int lsz=L?L->size:0, rsz=R?R->size:0;
  if (ran()*(lsz+rsz)<lsz)
    ret=mkcpy(L), 
    merge(ret->right,R,ret->right);
  else  ret=mkcpy(R), 
    merge(L,ret->left,ret->left);
  t=update(ret);
}
void split(node*t, node*&L, node*&R,double y){
  if (!t) { L=NULL; R=NULL; return; }
  node *ret=mkcpy(t);
  if (y<ret->key)
    split(ret->left,L,ret->left,y), 
    R=update(ret);
  else  split(ret->right,ret->right,R,y),
    L=update(ret);
}
void insert(node *&t, double key) {
  node *L, *M=pool.allocate(node(key)), *R;
  split(t,L,R,key);
  merge(L,M,t); merge(t,R,t);
}
void erase(node *&t, double which) {
  node *L, *t0, *t1, *R;
  split(t,L,t0,which-eps);
  split(t0,t1,R,which+eps);
  merge(L,R,t);
} 
