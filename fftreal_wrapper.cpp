#include "fftreal_wrapper.h"

#if defined Q_CC_MSVC
#    pragma warning(disable:4100)
#elif defined Q_CC_GNU
#    pragma GCC diagnostic ignored "-Wunused-parameter"
#elif defined Q_CC_MWERKS
#    pragma warning off (10182)
#endif

#include "ffft/FFTRealFixLen.h"

using namespace ffft;

class FFTRealWrapperPrivate {
public:
    FFTRealFixLen<FFT_LENGTH_POWER_OF_TWO> m_fft;
};


FFTRealWrapper::FFTRealWrapper()
    :   m_private(new FFTRealWrapperPrivate)
{

}

FFTRealWrapper::~FFTRealWrapper()
{
    delete m_private;
}

void FFTRealWrapper::calculateFFT(DataType in[], const DataType out[])
{
    m_private->m_fft.do_fft(in, out);
}
