struct SEG{
    int l, r, val; //etc, etc.
    //represents segment [l,r) !!!!!!
};

int A[MAXN];
SEG ST[4*MAXN];

SEG merge(SEG L, SEG R){
    //Can do anything you need here
    return {L.l, R.r, max(L.val,R.val)};
}

void build(int l, int r, int id){
    if(l == r-1) {ST[id] = {l, r, A[l]}; return;}
    build(l, (l+r)/2, id<<1);
    build((l+r)/2, r, id<<1|1);
    ST[id] = merge(ST[id<<1], ST[id<<1|1]);
}

SEG query(int l, int r, int id){
    int cl = ST[id].l, cr = ST[id].r;
    int m = (cl + cr)/2;
    if(cl == l && cr == r) return ST[id];
    if(r <= m) return query(l, r, id<<1);
    if(l >= m) return query(l, r, id<<1|1);
    return merge(query(l, m, id<<1), query(m, r, id<<1|1));
}

void upd(int p, int val, int id){
    int l = ST[id].l, r = ST[id].r, m = (l+r)/2;
    if(l == r-1) {ST[id] = {l, r, val}; return;}
    if(p < m) upd(p, val, id<<1);
    else upd(p, val, id<<1|1);
    ST[id] = merge(ST[id<<1], ST[id<<1|1]);
}