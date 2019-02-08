
int n;

struct STN{
    STN* l, r;
    int Le,Ri,val;
    //represents segment [L,R] !!!!!!
    STN(int le=0, int ri=n-1, int value=0, STN* X1=NULL, STN* X2=NULL){
    	val=value;
    	Le = le;
    	Ri = ri;
    	l = X1;
    	r = X2;
    }
};

typedef STN*  STNP

//input array
int A[MAXN];
//roots of all versions.
STNP STROOT[MAXN];

STN merge(STN L, STN R){
    //Can do anything you need here
    return {L.l, R.r, L.Le, R.Ri, max(L.val,R.val)};
}


//Construct version 0. O(nlogn).
void STB(STNP v){
	int L = v->Le, R = v->Ri;
	if(L==R){
		v->val = A[L];
		return;
	}
	int mid = (L+R)/2;
	v->l = new STN(L,mid);
	v->r = new STN(mid+1,R);
	STB(v->l);
	STB(v->r);
	v = merge(v->l, v->r);
}


//Upgrade to new version. O(logn).
void STU(STNP prev, STNP cur, int p, int val){
	
	int L = cur->Le, R = cur->Ri;

    if (L == R){ 
        cur->val = val; 
        return; 
    }

    int mid = (L+R) / 2; 
    if (p <= mid){ 
        cur->r = prev->r; 
        cur->l = new STN(L,mid); 
        STU(prev->l,cur->l, p, val); 
    }else{ 
        cur->l = prev->l; 
        cur->r = new STN(mid+1,R); 
        STU(prev->r, cur->r, p, val); 
    } 
  
    cur = merge(cur->l, cur->r);
}

//Do a query in version of root v.
STN STQ(STNP v, int le, int ri){
	int L = v->Le, R = v->Ri;

    if (le == L and R == ri) 
       return v; 
   	int mid = (L+R)/2;
   	if(ri <= mid) return STQ(v->l,le,ri);
   	if(le >= mid) return STQ(v->r,le,ri);

    return merge(STQ(v->l,le,mid),STQ(v->r,mid+1,ri)); 
} 
