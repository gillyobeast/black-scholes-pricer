#ifndef PROJECTIO_H_INCLUDED
#define PROJECTIO_H_INCLUDED

/** this file is for I/O stuff used throughout the project */

inline double stod(string _s) {            // std::stod doesn't work!! converts string to decimal
    double _d;
    stringstream _ss(_s);
    _ss >> _d;
    return _d;
}




inline double getTime(){                   // has user input a positive time in years
    double _t=0;
    while (_t<=0){
        cout << "Enter (positive) time step, in years: " << endl;
        cin >> _t;
        cout << endl;
    }
    return _t;
}

inline vector<double> getStock(){          // has user enter an ordered pair of current stock prices
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

inline double getRate(){                   // has user enter a non-negative interest rate
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



#endif // PROJECTIO_H_INCLUDED
