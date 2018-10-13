//usar de 0  a n-1
ll BIT[MAXN];
ll sumBIT(int p){
    ll ret=0;
    p++;
    for(; p>0; p-=(p&-p)) 
        ret+=BIT[p];
    return ret;
}
void updBIT(int p, ll val){
    p++;
    for(; p<MAXN; p+=(p&-p))   //MOSCA con el limite MAXN (debe ser al menos n+1)
        BIT[p]+=val;
}
