#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Project.h"
using namespace std;

double stod(string s) {                 // std:stod doesn't work!!
    double d;
    stringstream ss(s); //turn the string into a stream
    ss >> d;            //convert
    return d;
}

double getTime(){
    double _t=0;
    while (_t<=0){
        cout << "Enter (positive) time step, in years: " << endl;
        cin >> _t;
    }
    return _t;
}



int main()
{
    cout.precision(10);                 // ensures cout outputs nicely

    ifstream data("data.csv");          // creates input stream object 'data' [if i make it fstream, it clears it after reading]
    string line, s0i, s1i;
    vector<double> s0, s1;

    while (getline(data, line)){        // stores each column in data in vectors s0,s1
                                        // processes 'data' line by line - stores each line in 'line'
        stringstream lineStream(line);  // creates stringstream obj 'lineStream' with contents of 'line'

        getline(lineStream,s0i,',' );   // separates 'line' into 's0i' and 's1i'
        double ds0i = stod(s0i);        // converts to double
        s0.push_back(ds0i);             // pushes onto end of s0

        getline(lineStream,s1i);        // same as above three lines
        double ds1i = stod(s1i);
        s1.push_back(ds1i);
    }

    double t = getTime();



    //create a real badass function for mean of a vector

    vector<double> r0, r1;                  // r0[i-1] will store r0,i; log returns
    for (int i=0; i<s0.size()-1; i++){      // would it be more efficient than push_back to initialise to s0.size()-1 and assign directly?
        r0.push_back(log(s0[i+1]/s0[i]));
    }
    for (int i=0; i<s1.size()-1; i++){
        r1.push_back(log(s1[i+1]/s1[i]));
    }
    int m = r0.size();                      // m = #datapoints - 1
    double r0bar = 0, r1bar =0;
    for (int i=0;i<m;i++){
        r0bar+=r0[i];
    }
    for (int i=0;i<m;i++){
        r1bar+=r1[i];
    }

    r0bar = r0bar/m;
    r1bar = r1bar/m;

    double sv0=0,sv1=0;                     //sample variances - will save square root till calculating sigma0/1
    for (int i=0;i<m;i++){
        sv0 += (r0[i])*(r0[i]);
    }
    sv0=sv0/(m-1);
    sv0-=(m/(m-1))*r0bar*r0bar;

    for (int i=0;i<m;i++){
        sv1 += (r1[i])*(r1[i]);
    }
    sv1=sv1/(m-1);
    sv1-=(m/(m-1))*r1bar*r1bar;

    double scv=0;                           //sample covariance
    for (int i=0;i<m;i++){
        scv += r0[i]*r1[i];
    }
    scv = scv/(m-1);
    scv -= (m/(m-1))*r0bar*r1bar;

    double historicalVolatility0 = sqrt(sv0/t);
    double historicalVolatility1 = sqrt(sv1/t);
    double historicalCorrelation = scv / (t*historicalVolatility0*historicalVolatility1);

    // cause cout for vectors is borked damnit
    cout <<"(  s0     ,    s1   )" << endl;
    for (int i=0;i<s0.size();i++) cout << "(" << s0[i] << ", " << s1[i] << ")" << endl;
    cout <<"(  r0     ,   r1   )" << endl;
    for (int i=0;i<r0.size();i++) cout << "(" << r0[i] << ", " << r1[i] << ")" << endl;
    cout << sv0 << ", " << sv1 << endl;
    cout << scv << endl;
    cout << historicalVolatility0 << endl;
    cout << historicalVolatility1 << endl;
    cout << historicalCorrelation << endl;
}
