#ifndef PAYOFF_H_INCLUDED
#define PAYOFF_H_INCLUDED

/** this file is for option payoff function subclasses */

class spreadCall: public Payoff{ //todo: move to a 'payoff.h' header
public:
    double Value(vector<double> S){
        if(S[0]-S[1]-K>0) return S[0]-S[1]-K;
        else return 0;
    }
    void set_K(double _K){K=_K;}
private:
    double K; // strike price
};

class minCall: public Payoff{
public:
    double Value(vector<double> S){
        double S_min = S[0];
        if(S[0]>S[1]) S_min = S[1];
        if(S_min-K>0) return S_min-K;
        else return 0;
    }
    void set_K(double _K){K=_K;}
private:
    double K; // strike price
};

class maxCall: public Payoff{
public:
    double Value(vector<double> S){
        double S_max = S[0];
        if(S[0]<S[1]) S_max = S[1];
        if(S_max-K>0) return S_max-K;
        else return 0;
    }
    void set_K(double _K){K=_K;}
private:
    double K; // strike price
};


#endif // PAYOFF_H_INCLUDED
