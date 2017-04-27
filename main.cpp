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

    cout.precision(10);                     // ensures cout outputs doubles to a reasonable accuracy
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
    string line, s0i, s1i; // s0i is stock 0 at time i, &c
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







    cout << "Please enter an expiry date for the option." << endl;
int expiry = getTime(10);

    MinCall min_call; min_call.set_K(100);
    MaxCall max_call; max_call.set_K(100);
    SpreadCall spread_call; min_call.set_K(100);
    Payoff* chosen_payoff;


    int payoff_choice=2;
    while (payoff_choice < 1 || payoff_choice > 3){
        cout << "Please choose an option payoff:" << endl;
        cout << "   1. Spread call." << endl;
        cout << "   2. Min call." << endl;
        cout << "   3. Max call." << endl;
        cin  >> payoff_choice;
    }
    if (payoff_choice == 1){
        chosen_payoff = &spread_call;
        cout << "Pricing with 'spread call' payoff function." << endl;
    } else if (payoff_choice == 2){
        chosen_payoff = &min_call;
        cout << "Pricing with 'min call' payoff function." << endl;
    } else if (payoff_choice == 3){
        chosen_payoff = &max_call;
        cout << "Pricing with 'max call' payoff function." << endl;
    }

vector<double> strikes = getStrike(100,200);

    cout << "Calculating European option prices. Please wait." << endl;
    string euro_filename = "Eprices.csv";
    ofstream Eprices(euro_filename.c_str());
    for (int j=1; j <= 5; j++){ // for loop preparing column headings
        Eprices << ",N=" << 100*j;
    } Eprices << endl;
    // for loop writing to ith row of table
    for (double i = 0; i <= 10; i++){
        double strike = (i/10) * strikes[1] + (1-i/10) * strikes[0];
        min_call.set_K(strike);     // this is necessary because Payoff has no get_K() member.
        max_call.set_K(strike);     // could otherwise have used '&chosen_payoff->set_K(strike);'
        spread_call.set_K(strike);
        Eprices << "K=" << strike;
        //for loop writing to jth column of table
        for (double j = 1; j <= 5; j++){
            CorrBinModel binModel(model,expiry/(100*j));
            Eprices << "," << PriceEuropean(binModel, *chosen_payoff, 100*j);
            cout << ".";
        }
        Eprices << endl;
        cout << endl;
    }
    Eprices.close();
    cout << "Done. European option prices can be found in '" << euro_filename << "'" << endl << endl;


    cout << "Calculating American option prices. Please wait." << endl;
    string amer_filename = "Aprices.csv";
    ofstream Aprices(amer_filename.c_str());
    for (int j=1; j <= 5; j++){ // for loop preparing column headings
        Aprices << ",N=" << 100*j;
    } Aprices << endl;
    // for loop writing to ith row of table
    for (double i = 0; i <= 10; i++){
        double strike = (i/10) * strikes[1] + (1-i/10) * strikes[0];
        min_call.set_K(strike);
        max_call.set_K(strike);
        spread_call.set_K(strike);
        Aprices << "K=" << strike;
        //for loop writing to jth column of table
        for (double j = 1; j <= 5; j++){
            CorrBinModel binModel(model,expiry/(100*j));
            Aprices << "," << PriceAmerican(binModel, *chosen_payoff, 100*j);
            cout << ".";

        }
        Aprices << endl;
        cout << endl;
    }
    Aprices.close();
    cout << "Done. American option prices can be found in '" << amer_filename << "'" << endl << endl;




}
