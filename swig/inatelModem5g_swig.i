/* -*- c++ -*- */

#define INATELMODEM5G_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "inatelModem5g_swig_doc.i"

%{
#include "inatelModem5g/qam_demod_cc.h"
#include "inatelModem5g/qam_demod_param_cc.h"
%}


%include "inatelModem5g/qam_demod_cc.h"
GR_SWIG_BLOCK_MAGIC2(inatelModem5g, qam_demod_cc);

%include "inatelModem5g/qam_demod_param_cc.h"
GR_SWIG_BLOCK_MAGIC2(inatelModem5g, qam_demod_param_cc);
