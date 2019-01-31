// Nodo del Segment Tree, representa el rango [l,r)
struct STN{
    int val;
    STN *l, *r;
    STN() {l = r = NULL, val = 0;}
};

typedef STN* STNP;
int val(STNP t) { return t?t->val:0; }

STNP roots[MAXN];
int A[MAXN];
int N, M;

// Build Tree
void STB(STNP& root, int l = 0, int r = N){
    if(!root) root = new STN();
    if(l == r-1){ 
        root->val = A[l];
        return;
    }
    int mid = (l+r)/2;
    root->l = new STN();
    root->r = new STN();
    STB(root->l, l, mid);
    STB(root->r, mid, r);
    root->val = val(root->l) + val(root->r);
}

// Upgrade Tree (curr es la raiz asociada al update)
void STU(STNP& last, STNP& curr, int p, int delt, int l = 0, int r = N){
    if(!curr) curr = new STN();
    if(l == r-1){
        curr->val = last->val + delt;
        return;
    }
    int mid = (l+r)/2;
    if(p<mid){
        curr->r = last->r;
        curr->l = new STN();
        STU(last->l, curr->l, p, delt, l, mid);
    }
    else{
        curr->l = last->l;
        curr->r = new STN();
        STU(last->r, curr->r, p, delt, mid, r);
    }
    curr->val = val(curr->l) + val(curr->r);
}

//Query
int STQ(STNP root, int l, int r, int cl = 0, int cr = N){
    if(l == cl && r == cr) return root->val;
    int mid = (cl + cr)>>1;
    if(r <= m) return STQ(root->l, l, r, cl, mid);
    if(l >= m) return STQ(root->r, l, r, mid, cr);
    return STQ(root->l, l, mid, cl, mid) + STQ(root->r, mid, r, mid, cr); 
}