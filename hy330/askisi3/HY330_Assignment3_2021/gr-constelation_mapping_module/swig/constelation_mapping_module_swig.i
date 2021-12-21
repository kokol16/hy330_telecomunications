/* -*- c++ -*- */

#define CONSTELATION_MAPPING_MODULE_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "constelation_mapping_module_swig_doc.i"

%{
#include "constelation_mapping_module/constelation_mapping.h"
%}

%include "constelation_mapping_module/constelation_mapping.h"
GR_SWIG_BLOCK_MAGIC2(constelation_mapping_module, constelation_mapping);
