#ifndef CALIBRATION_H_INCLUDED
#define CALIBRATION_H_INCLUDED

/** this file contains model calibration funtions */
/* could be renamed 'stats', as all of these are statisticsy things*/


/**
    Calculates log returns of a dataset.
    -- the logarithmic difference between consecutive terms.
    @param _vector dataset to be worked on
    @return the log returns of the dataset
*/
inline vector<vector<double> > logReturns(vector<vector <double> > _vector){
    vector<vector<double> > _out(_vector.size());
    int _m = _vector[0].size();
    for (int j=0; j<_vector.size();j++){
        for (int i=0; i<_m-1; i++){
            _out[j].push_back(log(_vector[j][i+1]/_vector[j][i]));
        }
    }
    return _out;
}
/**
    Calculates the means of a dataset.
    @param _vector dataset to be worked on
    @return vector containing the mean of each 'column' of the dataset
*/
inline vector<double> vecMean(vector<vector<double> > _vector){
    vector<double> _mean(_vector.size(),0);
    int _m = _vector[0].size();
    for (int j=0; j<_vector.size();j++){
        for (int i=0;i<_m;i++){
            _mean[j] += _vector[j][i];
        }
        _mean[j]=_mean[j]/_m;
    }
    return _mean;
}

/**
    Calculates the sample variances of a dataset.
    @param _vector dataset to be worked on
    @return vector containing the sample variance of each 'column' of the dataset
*/
inline vector<double> sampleVar(vector<vector<double> > _vector){
    vector<double> _var(_vector.size(),0);
    vector<double> _mean = vecMean(_vector);
    int _m=_vector[0].size();
    for(int j=0;j<_vector.size();j++){
        for (int i=0;i<_m;i++){
            _var[j] += _vector[j][i]*_vector[j][i];
        }
        _var[j] = _var[j]/(_m-1)+(_m*_mean[j]*_mean[j])/(_m-1);
    }
    return _var;
}

/**
    Calculates the sample covariance of a dataset.
    @param _vector dataset to be worked on
    @return vector containing the sample variance of the dataset
*/
inline double sampleCovar(vector<vector<double> > _vec){
    int _m=_vec[0].size();
    double _sum = 0;
    for (int i = 0;i<_m;i++){
       _sum+= _vec[0][i]*_vec[1][i];
    }
    return _sum/(_m-1) - (_m*vecMean(_vec)[0]*vecMean(_vec)[1])/(_m-1);
}


#endif // CALIBRATION_H_INCLUDED
