/* -*- c++ -*- */
/* 
 * Copyright 2020 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "potencia_impl.h"

#include <math.h>
#include <volk/volk.h>

namespace gr {
  namespace taller {

    potencia::sptr
    potencia::make(float exponente)
    {
      return gnuradio::get_initial_sptr
        (new potencia_impl(exponente));
    }

    /*
     * The private constructor
     */
    potencia_impl::potencia_impl(float exponente)
      : gr::sync_block("potencia",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
       
       // alineacion para poder usar VOLK 
        const int alignment_multiple = volk_get_alignment() / sizeof(float);
        set_alignment(std::max(1,alignment_multiple));

        d_exp = exponente;
    }

    /*
     * Our virtual destructor.
     */
    potencia_impl::~potencia_impl()
    {
    }

    int
    potencia_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      //for (int i=0; i<noutput_items; i++){
      //  out[i] = pow(in[i],d_exp);
      //}

      //printf("noutput_items: %i\n", noutput_items);
      volk_32f_s32f_power_32f(&out[0], &in[0], d_exp, noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace taller */
} /* namespace gr */

