/* -*- c++ -*- */

#define CS330PROJECT_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "cs330project_swig_doc.i"

%{
#include "cs330project/interleaver.h"
#include "cs330project/deinterleaver.h"
#include "cs330project/fec_encoder.h"
#include "cs330project/fec_decoder.h"
#include "cs330project/frame_sync.h"
#include "cs330project/framer.h"
%}

%include "cs330project/interleaver.h"
GR_SWIG_BLOCK_MAGIC2(cs330project, interleaver);
%include "cs330project/deinterleaver.h"
GR_SWIG_BLOCK_MAGIC2(cs330project, deinterleaver);
%include "cs330project/fec_encoder.h"
GR_SWIG_BLOCK_MAGIC2(cs330project, fec_encoder);
%include "cs330project/fec_decoder.h"
GR_SWIG_BLOCK_MAGIC2(cs330project, fec_decoder);
%include "cs330project/frame_sync.h"
GR_SWIG_BLOCK_MAGIC2(cs330project, frame_sync);
%include "cs330project/framer.h"
GR_SWIG_BLOCK_MAGIC2(cs330project, framer);
