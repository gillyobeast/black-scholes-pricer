#include <iostream>         // console in/out library
#include <string>           // does the string stuff
#include <sstream>          // does the stringstream stuff
#include <fstream>          // file in/out library
#include <stdlib.h>         // adds 'exit()'
#include "Project.h"        // compulsory header file
#include "projectIO.h"      // i/o stuff, used throughout
#include "calibration.h"    // model calibration functions
#include "payoff.h"         // payoff functions
#include "pricer.h"         // PriceEuropean()

using namespace std;


int main()
{

    cout.precision(10);                       // ensures cout outputs doubles to a reasonable accuracy
    /** INTRODUCTION TO PROGRAM */
    cout << "Welcome to the two-dimensional Black-Scholes model option pricer!" << endl;
    cout << "It prices options!" << endl << endl;

    cout << "Before it can price options, the model must be calibrated using historical stock data." << endl;

    /** MODEL CALIBRATION */
    ifstream data("data.csv");               // creates input stream object 'data'
    cout << "Opening historical stock data." << endl;
    if (data.fail()) {
        cout << "Error opening file. Closing program." << endl;
        exit(1);
    }
    cout << "Success opening file. Calibrating model." << endl;
    cout << "Please specify the time interval for the historical data." << endl;
    double t = getTime(0.25);

//    vector<vector<double> > S = ifstreamToVector(data);
    vector<vector<double> > S(2);
    string line, s0i, s1i;
    while (getline(data, line)){    //does the job of ifstreamToVector() as i can't get a definition of it to work outside of main.
        stringstream lineStream(line);
        getline(lineStream,s0i, ',');
        S[0].push_back(stod(s0i));
        getline(lineStream,s1i);
        S[1].push_back(stod(s1i));
    }

    vector<vector<double> > R=logReturns(S);     // R stores log returns
    vector<double> sampleVariance = sampleVar(R);
    double sampleCovariance = sampleCovar(R);
    vector<double> historicalVolatility;
    for (int i = 0; i < 2; i++) historicalVolatility.push_back(sqrt(sampleVariance[i]/t));
    double historicalCorrelation = sampleCovariance / (t*historicalVolatility[0]*historicalVolatility[1]);

    cout << "Two-dimensional Black-Scholes model calibrated." << endl;
    cout << "Calibration values:" << endl;
    cout << "   Historical Volatility of S0:  "  << historicalVolatility[0] << endl
         << "                            S1:  "  << historicalVolatility[1] << endl;
    cout << "   Historical Correlation:       "  << historicalCorrelation   << endl << endl;

//    int menu=-1;
//    cout << "Please enter an option:" << endl;
//    cout << "1. Recalibrate model." << endl;
//    cout << "0. Exit program." << endl;
//        cin  >> menu;
//    switch(menu){
//        case 1:{
//            break;}
//        case 0:{
//            break;}
//        default:{
//            cout << "Please enter an option:" << endl;
//            cout << "1. Calibrate model." << endl;
//            cout << "0. Exit program." << endl;
//            cin >> menu;}
//    }






    double rate = getRate(0.05);
    vector<double> stockCurrent = getStock(100);



                //creates bs model with calibrated parameters and user entered data.
    BSModel2 model(stockCurrent, rate, historicalVolatility, historicalCorrelation);
    while (model.IsWellDefined()==0){                   // validation
        cout << "Please enter valid data." << endl;
        return 1;
    }






    /*ofstream Eprices("Eprices.csv"), Aprices("Aprices.csv");*/
    //save writing to these till i get the next bit right.
    //note: change 'cout' to 'Eprices' or 'Aprices' as needed.
    cout << "Please enter an expiry date for the option." << endl;
    int expiry = getTime(10);

                    //creates corr bin model with calibrated bs model and user entered time step.


    // there is a clever way of making it do the option that the user enters.
    // i can't think what it would be.
    //vector<Payoff*> options = (SpreadCall, MinCall, MaxCall);

    int payoff_choice=-1;
    while (payoff_choice < 1 || payoff_choice > 3){
        cout << "Please choose an option payoff:" << endl;
        cout << "   1. Spread call." << endl;
        cout << "   2. Min call." << endl;
        cout << "   3. Max call." << endl;
        cin  >> payoff_choice;
    }
    cout << "Please enter a minimum strike price:" << endl;
    double strike_min;
    cin  >> strike_min;
    cout << "Please enter a maximum strike price:" << endl;
    double strike_max;
    cin  >> strike_max;
    cout << "Thank you. Calculating European option prices." << endl;
    if (payoff_choice = 1){

        CorrBinModel binModel(model,expiry/(100));

    }




}
