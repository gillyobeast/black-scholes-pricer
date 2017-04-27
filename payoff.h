#ifndef PAYOFF_H_INCLUDED
#define PAYOFF_H_INCLUDED

/** this file defines option payoff function subclasses */


class SpreadCall: public Payoff{
public:
    double Value(vector<double> S) const{
        return (S[0]-S[1]>K)?(S[0]-S[1]-K):0;
    }
    void set_K(double _K){K=_K;}
private:
    double K; // strike price
};

class MinCall: public Payoff{
public:
    double Value(vector<double> S) const{
        double S_min = (S[0]<S[1])?S[0]:S[1];
        return (S_min>K)?(S_min-K):0;
    }
    void set_K(double _K){K=_K;}
private:
    double K; // strike price
};

class MaxCall: public Payoff{
public:
    double Value(vector<double> S) const{
        double S_max = (S[0]>S[1])?S[0]:S[1];
        return (S_max>K)?(S_max-K):0;
    }
    void set_K(double _K){K=_K;}
private:
    double K; // strike price
};


#endif // PAYOFF_H_INCLUDED
