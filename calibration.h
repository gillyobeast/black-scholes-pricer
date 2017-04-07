#ifndef CALIBRATION_H_INCLUDED
#define CALIBRATION_H_INCLUDED

double stod(string _s) {                // std:stod doesn't work!!
    double _d;
    stringstream _ss(_s);               //turn the string into a stream
    _ss >> _d;                          //convert
    return _d;
}

double getTime(){
    double _t=0;
    while (_t<=0){
        cout << "Enter (positive) time step, in years: " << endl;
        cin >> _t;
    }
    return _t;
}

double vecMean(vector<double> _vec){
    double _sum = 0;
    int _m=_vec.size();
    for (int i=0;i<_m;i++){
        _sum += _vec[i];
    }
    return _sum/_m;
}

double sampleVar(vector<double> _vec){
    double _sum = 0;
    double _mean = vecMean(_vec);
    int _m=_vec.size();
    for (int i=0;i<_m;i++){
        _sum += _vec[i]*_vec[i];
    }
    return _sum/(_m-1) - (_m*_mean*_mean)/(_m-1);
}

double sampleCovar(vector<double> _vec1, vector<double> _vec2){
    if (!(_vec1.size()==_vec2.size())) throw "Covariance requires equal sample sizes. Vectors not of the same lenth";
    int _m=_vec1.size();
    double _sum = 0;
    for (int i = 0;i<_m;i++){
       _sum+= _vec1[i]*_vec2[i];
    }
    return _sum/(_m-1) - (_m*vecMean(_vec1)*vecMean(_vec2))/(_m-1);
}
#endif // CALIBRATION_H_INCLUDED
