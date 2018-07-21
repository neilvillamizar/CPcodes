ll BIT[MAXN];
void BIT_upd(int p, ll val){
	p++;
	for(; p <= N; p += p & -p)
		BIT[p] += val;
}
ll BIT_sum(int p){
	ll ret = 0;
	p++;
	for(; p; p -= p & -p)
		ret += BIT[p];
	return ret;
}

ll BIT[MAXR][MAXC];
void BIT_upd(int r , int c , ll val){
	r++; c++;
	for(; r <= R; r += (r & -r)){
		for(int cc = c; cc <= C; cc += (cc & -cc)){
			BIT[r][cc] += val;
		}
	}
}
ll BIT_sum(int r,int c){
	ll sum= 0; r++; c++;
	for(; r; r -= r & -r){
		for(int cc = c;cc; cc -= cc & -cc){
			sum += BIT[r][cc];
		}
	}
	return sum;
}
