///////////////////////////
//
// Splay
//
///////////////////////////
namespace Splay {
  struct node {
    LL val;
    node *parent, *left, *right;
    node() {}
    node(LL val, node *parent): val(val), parent(parent), left(NULL), right(NULL) {}
  };
  struct Allocator {
    node a[5000000];
    int ptr;
    Allocator() { ptr=0; }
    void clear() { ptr=0; }
    node *allocate(node x) {
      ptr++; a[ptr]=x; return &a[ptr];
    }
  } pool;
  
  node *root=NULL;
  
  void tl(node *x) {
    node *y=x->parent; x->parent=y->parent;
    if (y->parent) 
     if (y==y->parent->left)y->parent->left=x;
     else y->parent->right=x;
    y->right=x->left; 
    if (x->left) x->left->parent=y;
    x->left=y; y->parent=x; 
  }
  void tr(node *x) {
    node *y=x->parent; x->parent=y->parent;
    if (y->parent) 
     if (y==y->parent->left)y->parent->left=x;
     else y->parent->right=x;
    y->left=x->right; 
    if (x->right) x->right->parent=y;
    x->right=y; y->parent=x; 
  }
  void splay(node *x, node *y) {
    while (x->parent!=y)
      if (x->parent->parent==y)
        if (x==x->parent->left) tr(x); 
        else tl(x);
      else if (x->parent==x->parent->parent->left)
          if (x==x->parent->left)
            tr(x->parent), tr(x);
          else  tl(x), tr(x);
      else if (x==x->parent->right)
            tl(x->parent), tl(x);
      else  tr(x), tl(x);
    if (!y) root=x;
  }
}  
