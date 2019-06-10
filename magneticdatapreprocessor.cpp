#include "magneticdatapreprocessor.h"
#include "Eigen/Dense"

#define NUMBER_OF_HISTORY 200
MagneticDataPreprocessor::MagneticDataPreprocessor(int n)
{
    _numberOfSensor = n;
    _data = new double [3*_numberOfSensor];
    for(int i = 0; i < 3*_numberOfSensor; i++) _data[i] = 0;
    _calibrateData = new double [3*_numberOfSensor];
    for(int i = 0; i < 3*_numberOfSensor; i++) _calibrateData[i] = 0;
    _outputData = new double [3*_numberOfSensor];
    for(int i = 0; i < 3*_numberOfSensor; i++) _outputData[i] = 0;
    _updatedData = new unsigned char [((_numberOfSensor-1)/8+1)];
    _selectedData = new unsigned char [((_numberOfSensor-1)/8+1)];
    for(int i = 0; i < (_numberOfSensor-1)/8+1; i++)
    {
        _updatedData[i] = 0;
        _selectedData[i] = 0;
    }
    _history = new double* [NUMBER_OF_HISTORY];
    for(int i = 0; i < NUMBER_OF_HISTORY; i++)
    {
        _history[i] = new double [3*_numberOfSensor];
        for(int j = 0; j < 3*_numberOfSensor; j++) _history[i][j] = 0;
    }
    _historyIndex = 0;
    _U = new double [n*3*3];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                if(j==k) _U[i*9+j*3+k] = 1;
                else _U[i*9+j*3+k] = 0;
    _c = new double [n*3];
    for(int i = 0; i < 3*n; i++) _c[i] = 0;
    _rotation = new double [n*3*3];
}

bool MagneticDataPreprocessor::input(double inputData[], int index)
{
    if(index >= _numberOfSensor) return false;
    ////////////////////////////////////
    for(int i = 0; i < 3; i++)
    {
        _data[3*index+i] = inputData[i]-_c[i*_numberOfSensor+index];
    }
    for(int i = 0; i < 3; i++)
    {
        double sum = 0;
        for(int j = 0; j < 3; j++)
            sum += _U[index*9+3*i+j]*inputData[j];
        _data[3*index+i] = sum;
    }
    /////////////////////////////////////
    if(_selectedDataNumber < 6) return false;
    _updatedData[index/8] |= 1<<(index%8);
    for(int i = 0; i < _numberOfSensor/8; i++)
    {
        if(_updatedData[i] != _selectedData[i])
            return false;
    }
    _historyIndex++;
    _historyIndex%=NUMBER_OF_HISTORY;
    for(int i = 0; i < _numberOfSensor*3; i++)
    {
        double historyMean = 0;
        for(int j = 0; j < NUMBER_OF_HISTORY; j++)
        {
            historyMean += _history[j][i];
        }
        historyMean /= double(NUMBER_OF_HISTORY);
        _outputData[i] = _data[i];// - historyMean;
        _history[_historyIndex][i] = _data[i];
    }
    return true;
}

double *MagneticDataPreprocessor::data() const
{
    for(int i = 0; i < _numberOfSensor/8; i++)
    {
        _updatedData[i] = 0;
    }
    return _outputData;
}

void MagneticDataPreprocessor::setUAndC(double *U, double *c)
{
    for(int i = 0; i < _numberOfSensor*3*3; i++) _U[i] = U[i];
    for(int i = 0; i < _numberOfSensor*3; i++) _c[i] = c[i];
}

void MagneticDataPreprocessor::setRotation(double *rotation)
{
    for(int i = 0; i < _numberOfSensor*3*3; i++) _rotation[i] = rotation[i];
}

void MagneticDataPreprocessor::setSelectedData(unsigned char *selectedData)
{
    _selectedDataNumber = 0;
    for(int i = 0; i < _numberOfSensor/8; i++)
    {
        _selectedData[i] = selectedData[i];
        for(int j = 0; j < 8; j++)
        {
            _selectedDataNumber += (_selectedData[i] >> j) % 2;
        }
    }
}

unsigned char MagneticDataPreprocessor::getUpdatedData(int i)
{
    if(i < (_numberOfSensor-1)/8+1)
        return _updatedData[i];
    return _updatedData[0];
}

MagneticDataPreprocessor::~MagneticDataPreprocessor()
{
    for(int i = 0; i < NUMBER_OF_HISTORY; i++) delete [] _history[i];
    delete [] _history;
    delete [] _data;
    delete [] _calibrateData;
    delete [] _outputData;
    delete [] _selectedData;
    delete [] _updatedData;
    delete [] _U;
    delete [] _c;
    delete [] _rotation;
}
