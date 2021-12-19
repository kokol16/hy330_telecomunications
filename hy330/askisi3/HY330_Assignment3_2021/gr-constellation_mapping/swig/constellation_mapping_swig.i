/* -*- c++ -*- */

#define CONSTELLATION_MAPPING_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "constellation_mapping_swig_doc.i"

%{
#include "constellation_mapping/constellation_mapping.h"
%}

%include "constellation_mapping/constellation_mapping.h"
GR_SWIG_BLOCK_MAGIC2(constellation_mapping, constellation_mapping);
