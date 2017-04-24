#ifndef BINOMIAL_H_INCLUDED
#define BINOMIAL_H_INCLUDED



int no = 0;
long long binomial(int n, int k){
    long long ans =1;
    if (k>n-k) k=n-k;
    for (int i =0; i<k; i++){
         ans = ans*(n-i);
         ans = ans/(i+1);
    }
    return ans;
}




#endif // BINOMIAL_H_INCLUDED
