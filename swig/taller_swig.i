/* -*- c++ -*- */

#define TALLER_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "taller_swig_doc.i"

%{
#include "taller/interleaver.h"
#include "taller/deinterleaver.h"
#include "taller/potencia.h"
#include "taller/trigger.h"
#include "taller/trigger_tag.h"
#include "taller/align_tag.h"
%}


%include "taller/interleaver.h"
GR_SWIG_BLOCK_MAGIC2(taller, interleaver);
%include "taller/deinterleaver.h"
GR_SWIG_BLOCK_MAGIC2(taller, deinterleaver);
%include "taller/potencia.h"
GR_SWIG_BLOCK_MAGIC2(taller, potencia);
%include "taller/trigger.h"
GR_SWIG_BLOCK_MAGIC2(taller, trigger);
%include "taller/trigger_tag.h"
GR_SWIG_BLOCK_MAGIC2(taller, trigger_tag);
%include "taller/align_tag.h"
GR_SWIG_BLOCK_MAGIC2(taller, align_tag);
