#ifndef MAGNETICSTRUCTDATA_H
#define MAGNETICSTRUCTDATA_H

class MagneticDataPreprocessor
{
public:
    MagneticDataPreprocessor(int n);
    bool input(double inputData[], int index);

    double *data() const;
    void setUAndC(double *U, double *c);

    void setRotation(double *rotation);
    ~MagneticDataPreprocessor();
private:
    MagneticDataPreprocessor& operator=(MagneticDataPreprocessor& mag){}
    int _numberOfSensor;
    double *_data;
    double **_history;
    int _historyIndex;
    double *_calibrateData;
    double *_outputData;
    unsigned char *_updatedData;
    double *_U;
    double *_c;
    double *_rotation;
};

#endif // MAGNETICSTRUCTDATA_H
