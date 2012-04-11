//
//  ofxOnsetDetection.h
//
//  Created by Akira Hayasaka on 3/30/12.
//  Copyright (c) 2012 ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆ﾟ･:,｡ﾟ･:,｡★ﾟ･:,｡ﾟ･:,｡☆. All rights reserved.
//

#ifndef example_ofxOnsetDetection_h
#define example_ofxOnsetDetection_h

#include "ofMain.h"
#include "onsetsds.h"

/*
 http://onsetsds.sourceforge.net/
 */


/**
 * Types of incoming FFT data format. OnsetsDS needs to know where the FFT
 * data comes from in order to interpret it correctly.
 */
enum ofx_onsetsds_fft_types {
	OFX_ODS_FFT_SC3_COMPLEX,    ///< SuperCollider, cartesian co-ords ("SCComplexBuf") [dc, nyq, real[1], imag[1], real[2], imag[2]...] - NB it's more efficient to provide polar data from SC
	OFX_ODS_FFT_SC3_POLAR,      ///< SuperCollider, polar co-ords ("SCPolarBuf") [dc, nyq, mag[1], phase[1], mag[2], phase[2]...]
	OFX_ODS_FFT_FFTW3_HC,       ///< FFTW <a href="http://www.fftw.org/fftw3_doc/The-Halfcomplex_002dformat-DFT.html">"halfcomplex"</a> format - [dc, real[1], real[2] ... nyq, imag[nyq-1] ... imag[1]]
	OFX_ODS_FFT_FFTW3_R2C       ///< FFTW regular format, typically produced using <a href="http://www.fftw.org/fftw3_doc/One_002dDimensional-DFTs-of-Real-Data.html#One_002dDimensional-DFTs-of-Real-Data">real-to-complex</a> transform
};

/**
 * Types of onset detection function
 */
enum ofx_onsetsds_odf_types {
	OFX_ODS_ODF_POWER,    ///< Power
	OFX_ODS_ODF_MAGSUM,   ///< Sum of magnitudes
	OFX_ODS_ODF_COMPLEX,  ///< Complex-domain deviation
	OFX_ODS_ODF_RCOMPLEX, ///< Complex-domain deviation, rectified (only increases counted)
	OFX_ODS_ODF_PHASE,    ///< Phase deviation
	OFX_ODS_ODF_WPHASE,   ///< Weighted phase deviation
	OFX_ODS_ODF_MKL       ///< Modified Kullback-Liebler deviation
};


class ofxOnsetDetection 
{
public:
    void setup(int odftype = OFX_ODS_ODF_COMPLEX, int fftformat = OFX_ODS_FFT_FFTW3_HC, 
               int fftsize = 1024, int medspan = 11, int sampleRate = 44100)
    {       
        float* odsdata = (float*) malloc( onsetsds_memneeded(odftype, fftsize, medspan) );
        onsetsds_init(&ods, odsdata, fftformat, odftype, fftsize, medspan, sampleRate);
    }
    
    bool isOnsetting(float * fftArray)
    {
        return onsetsds_process(&ods, fftArray);
    }
    
private:
    OnsetsDS        ods;    
};

#endif
