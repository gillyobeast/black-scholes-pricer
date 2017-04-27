#ifndef BINOMIAL_H_INCLUDED
#define BINOMIAL_H_INCLUDED

/** this file gives a function to calculate the binomial coefficents */


/**
    Computes a binomial coefficient.
    @param n the overall number of things to choose from
    @param k the number of things to choose
    @return the number of ways of choosing k things from a set of n things
*/
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
