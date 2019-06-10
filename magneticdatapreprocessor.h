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
    void setSelectedData(unsigned char *selectedData);

    unsigned char getUpdatedData(int i);
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
    unsigned char *_selectedData;
    int _selectedDataNumber;
    double *_U;
    double *_c;
    double *_rotation;
};

#endif // MAGNETICSTRUCTDATA_H
