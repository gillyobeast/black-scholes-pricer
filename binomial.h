#ifndef BINOMIAL_H_INCLUDED
#define BINOMIAL_H_INCLUDED

/** this file gives a function to calculate the binomial coefficents */


int no = 0;
long long binomial(int n, int k){
    long long ans =1;
    if (k>n-k) k=n-k;          //  optimisation, using the symmetry of the
    for (int i =0; i<k; i++){ //  binomial coefficients: C(n,k)=C(n,n-k)
         ans = ans*(n-i);
         ans = ans/(i+1);
    }
    return ans;
}




#endif // BINOMIAL_H_INCLUDED
