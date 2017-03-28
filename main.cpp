#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Project.h"
using namespace std;

int main()
{
    ifstream data("data.csv"); // creates input stream object 'data'
    string line, s0i, s1i;
    vector<double> s0, s1;

    while (getline(data, line)){ //processes 'data' line by line - stores each line in 'line'
        stringstream lineStream(line); // creates stringstream obj 'lineStream' with contents of 'line'
        getline(lineStream,s0i,',' ); // separates 'line' into 's0i' and 's1i'
        getline(lineStream,s1i,',' );
        cout <<"s0i:" << s0i << ", s1i:" << s1i << endl; // do processing of 'line' in 'data' here

        //do i want to figure out how to put s0i, s1i in a vector before processing? probably.
        s0.push_back(stod(s0i);

    }

}
