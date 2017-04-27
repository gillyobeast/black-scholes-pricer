#ifndef PRICER_H_INCLUDED
#define PRICER_H_INCLUDED

/** this file gives the PriceEuropean() function */

/**
    Calculates a fair price for a European style option.
    @param model a correlated binary model
    @param payoff a reference to a subclass of Payoff class
    @param N expiry date of option
    @return the fair price of the European option
*/
inline double PriceEuropean(const CorrBinModel& model, const Payoff& payoff, int N){
    double _sum=0;
    for (int j0=0;j0<=N;j0++)
        for (int j1=0;j1<=N;j1++){
            _sum += model.Prob(N,j0,j1)
                  *payoff.Value(model.S(N,j0,j1));
        }
    return _sum*exp(-model.Get_r()*model.Get_h()*N);
};

#endif // PRICER_H_INCLUDED
