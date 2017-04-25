#ifndef PROJECTIO_H_INCLUDED
#define PROJECTIO_H_INCLUDED

/** this file is for I/O stuff used throughout the project */

///converts string to decimal
inline double stod(string _s) {            // std::stod doesn't work!!
    double _d;
    stringstream _ss(_s);
    _ss >> _d;
    return _d;
}

/// has user input a positive time in years
inline double getTime(){
    double _t=0;
    while (_t<=0){
        cout << "Enter (positive) time step, in years: " << endl;
        cin >> _t;
        cout << endl;
    }
    return _t;
}
//overloaded version to allow internal parameter setting, for testing
inline double getTime(double _t){
    cout << _t << endl;
    while (_t<=0){
        cout << "Time step should be positive." << endl;
    }
    return _t;
}

/// has user enter an ordered pair of current stock prices
inline vector<double> getStock(){
    vector<double> _stock(2);
    cout << "Please provide positive values for current stock prices." << endl;
    cout << "Current stock price of S0:" << endl;
    cin  >> _stock[0];
    cout << "Current stock price of S1:" << endl;
    cin  >> _stock[1];
    while (_stock[0]<=0||_stock[1]<=0){
        cout << "Current stock prices must be positive decimal values." << endl;
        cout << "Please provide positive values for initial stock prices." << endl;
        cout << "Current stock price of S0:" << endl;
        cin  >> _stock[0];
        cout << "Current stock price of S1:" << endl;
        cin  >> _stock[1];
    }
    return _stock;
}
//overloaded version to allow internal parameter setting, for testing
inline vector<double> getStock(double _price){
    while (_price<=0){cout<< "Current stock prices must be positive decimal values." << endl;}
    vector<double> _stock(2,_price);
    cout << _stock << endl;
    return _stock;
}

/// has user enter a non-negative interest rate
inline double getRate(){
    double _rate;
    cout << "Please enter non-negative interest rate (as decimal value):" << endl;
    cin  >> _rate;
    while(_rate <0){
        cout << "Interest Rate must be a non-negative decimal value." << endl;
        cout << "Please enter non-negative interest rate (as decimal value):" << endl;
        cin  >> _rate;
    }
    return _rate;
}
//overloaded version to allow internal parameter setting, for testing
inline double getRate(double _rate){

    cout << _rate << endl;
    while(_rate <0){
        cout << "Interest Rate must be a non-negative decimal value." << endl;
    }
    return _rate;
}



#endif // PROJECTIO_H_INCLUDED
