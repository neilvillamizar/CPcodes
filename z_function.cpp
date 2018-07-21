#include <iostream>
#include <vector>
using namespace std;
#define ms(obj,val) memset(obj,val,sizeof(obj))
#define ms2(obj,val,sz) memset(obj,val,sizeof(obj[0])*sz)
#define FOR(i,f,t) for(int i=f;i<(int)t;i++)

typedef vector<int> vi;


// Z[i] LCP between str[i] and str[0]
vi z_func(string str) {
	int N = str.length();
	vi Z(N);
	Z[0]=N;
	int L=0,R=0;
	FOR(i,1,N) {
		if(i>=R) {
			L=R=i;
			while(R<N && str[R]==str[R-i]) R++;
			Z[i]=R-L;
		} else {
			int k=i-L;
			if(Z[k]<R-i) Z[i]=Z[k];
			else {
				L=i;
				while(R<N && str[R]==str[R-i]) R++;
				Z[i]=R-L;
			}
		}
	}
	return Z;
}


vi z_function(string s){
	int l = 0, r = 0, n = s.length();
	vi z(n, 0);
	z[0] = n;
	FOR(i, 1, n){
		if(i <= r) z[i]=min(z[i-l], r-i+1);
		while(z[i]+i<n && s[z[i]+i]==s[z[i]]) z[i]++;
		if(r < i+z[i]-1)
			l = i, r = i+z[i]-1;
	}
	return z;
}

int main(){}

