#ifndef BINOMIAL_H_INCLUDED
#define BINOMIAL_H_INCLUDED

long long binomial(int n, int k){
    if (k>n) return  -1;
    long long _out=1;
    for (int l=1;l<k+1;l++){
        _out = _out * ((k-n+l)/l);
    }
} // todo: fix!

#endif // BINOMIAL_H_INCLUDED
