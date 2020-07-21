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
#include "trigger_impl.h"

namespace gr {
  namespace taller {

    trigger::sptr
    trigger::make(float nivel, int pendiente, int muestras)
    {
      return gnuradio::get_initial_sptr
        (new trigger_impl(nivel, pendiente, muestras));
    }

    /*
     * The private constructor
     */
    trigger_impl::trigger_impl(float nivel, int pendiente, int muestras)
      : gr::block("trigger",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
   
        d_nivel = nivel;
        d_pendiente = pendiente;
        d_muestras = muestras;

        d_ultima_muestra = 0;
        d_buscando = 1;

        d_nout = 0;

    }

    /*
     * Our virtual destructor.
     */
    trigger_impl::~trigger_impl()
    {
    }

    void
    trigger_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
        ninput_items_required[0] = noutput_items;
    }

    int
    trigger_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];


      int out_now = 0;
      for(int i=0; i<noutput_items; i++){
          if(d_buscando)
          {
              d_buscando = !((d_pendiente*d_ultima_muestra<d_pendiente*d_nivel)&&(d_pendiente*d_nivel<d_pendiente*in[i]));
          }

          if(!d_buscando)
          {
              if(d_nout<d_muestras)
              {
                  //out[10*out_now] = in[i];
		  out[out_now] = in[i];
                  d_nout++;
                  out_now++;
              }
              else
              {
                  d_buscando = 1;
                  d_nout = 0;
              }
          }
          d_ultima_muestra = in[i];
      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return out_now;
    }

  } /* namespace taller */
} /* namespace gr */

