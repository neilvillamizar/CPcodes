//Treap Data Structure
//Neil Villamizar


// version for implicit treaps

void merge (pnode & t, pnode l, pnode r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_sz (t);
}

void split (pnode t, pnode & l, pnode & r, int key, int add = 0) {
    if (!t)
        return void( l = r = 0 );
    int cur_key = add + sz(t->l); //implicit key
    if (key <= cur_key)
        split (t->l, l, t->l, key, add),  r = t;
    else
        split (t->r, t->r, r, key, add + 1 + sz(t->l)),  l = t;
    upd_sz (t);
}


///////////////////////////////


// Insert element:
// Suppose we need to insert an element at position pos. 
// We divide the treap into two parts, which correspond to arrays [0..pos-1] and [pos..sz].
// to do this we call split (T, T1, T2, pos). Then we can combine tree T1 with the new vertex by calling merge (T1, T1, new_item).
// Finally, we combine trees T1 and T2 back into T by calling merge (T, T1, T2).

void insert(pnode &t, pnode it){}