#ifndef PROJECTIO_H_INCLUDED
#define PROJECTIO_H_INCLUDED

/** this file contains I/O stuff used throughout the project */


/* //attempt at ifstreamToVector(). gives an ios_base.h error. FeelsBadMan
vector<vector<double> > ifstreamToVector(ifstream _input){
    string _line, _col0, _col1;
    vector<vector<double> > _output(2);
    while (getline(_input, _line)){

        stringstream _lineStream(_line);

        getline(_lineStream,_col0,',' );
        _output[0].push_back(stod(_col0));

        getline(_lineStream,_col1);
        _output[1].push_back(stod(_col1));
    }
}
*/

/**
    Takes a string object and returns a double object.
    @param _string string object to be converted
    @return double object with value found in string object
*/
inline double stod(string _string) {
    double _double;
    stringstream _stringstream(_string);
    _stringstream >> _double;
    return _double;
}

/**
    Gets a positive time in years.
    @return time, will only be positive
*/
inline double getTime(){
    double _time = 0;
    while (_time <= 0){
        cout << "Enter (positive) time, in years: " << endl;
        cin  >> _time;
    }
    return _time;
}
//overloaded version to allow internal parameter setting, for testing
inline double getTime(double _time){
    cout << _time << endl;
    while (_time <= 0){
        cout << "Time should be positive." << endl;
    }
    return _time;
}

/**
    Gets a pair of positive stock prices step in years.
    @return vector of positive stock price, will only be positive
*/
inline vector<double> getStock(){
    vector<double> _stock(2);
    cout << "Please provide positive values for current stock prices." << endl;
    cout << "Stock price of S0:" << endl;
    cin  >> _stock[0];
    cout << "Stock price of S1:" << endl;
    cin  >> _stock[1];
    while (_stock[0] <= 0 || _stock[1] <= 0){
        cout << "Stock prices must be positive decimal values." << endl;
        cout << "Please provide positive values for current stock prices." << endl;
        cout << "Stock price of S0:" << endl;
        cin  >> _stock[0];
        cout << "Stock price of S1:" << endl;
        cin  >> _stock[1];
    }
    return _stock;
}
//overloaded version to allow internal parameter setting, for testing
inline vector<double> getStock(double _price){
    while (_price<=0){cout<< "Stock prices must be positive decimal values." << endl; exit(0);}
    vector<double> _stock(2,_price);
    cout << _stock << endl;
    return _stock;
}

/**
    Gets a non-negative interest rate.
    @return interest rate, will only be non-negative
*/
inline double getRate(){
    double _rate;
    cout << "Please enter non-negative interest rate (as decimal value):" << endl;
    cin  >> _rate;
    while(_rate < 0){
        cout << "Interest Rate must be a non-negative decimal value." << endl;
        cout << "Please enter non-negative interest rate (as decimal value):" << endl;
        cin  >> _rate;
    }
    return _rate;
}
//overloaded version to allow internal parameter setting, for testing
inline double getRate(double _rate){

    cout << _rate << endl;
    while (_rate < 0){
        cout << "Interest Rate must be a non-negative decimal value." << endl;
    }
    return _rate;
}

/**
    Gets an increasing pair of strike prices.
    @return pair of stock prices, [0]<[1]
*/
vector<double> getStrike(){
    vector <double> _strike(2);
    cout << "Minimum strike price:" << endl;
    cin  >> _strike[0];
    cout << "Maximum strike price:" << endl;
    cin  >> _strike[1];
    while (_strike[0] >= _strike[1]){
        cout << "Strike prices must be increasing." << endl;
        cout << "Minimum strike price:" << endl;
        cin  >> _strike[0];
        cout << "Maximum strike price:" << endl;
        cin  >> _strike[1];
    }
    return _strike;
}
//overloaded version to allow internal parameter setting, for testing
vector<double> getStrike(double _price0, double _price1){
    while (_price0 >= _price1){cout << "Strike prices must be increasing." << endl; exit(0);}
    vector<double> _strike;
    _strike.push_back(_price0);
    _strike.push_back(_price1);
    cout << _strike << endl;
    return _strike;
}

#endif // PROJECTIO_H_INCLUDED
