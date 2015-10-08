#ifndef FFTREAL_WRAPPER_H
#define FFTREAL_WRAPPER_H

#include <QtCore/QtGlobal>

class FFTRealWrapperPrivate;

#define FFT_LENGTH_POWER_OF_TWO 12

class FFTRealWrapper
{
public:
    FFTRealWrapper();
    ~FFTRealWrapper();

    typedef float DataType;
    void calculateFFT(DataType in[], const DataType out[]);

private:
    FFTRealWrapperPrivate*  m_private;
};

#endif
