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
#include "interleaver_impl.h"

namespace gr {
  namespace taller {

    interleaver::sptr
    interleaver::make(const std::vector<int>& orden)
    {
      return gnuradio::get_initial_sptr
        (new interleaver_impl(orden));
    }

    /*
     * The private constructor
     */
    interleaver_impl::interleaver_impl(const std::vector<int>& orden)
      : gr::sync_block("interleaver",
              gr::io_signature::make(1, 1, orden.size()*sizeof(gr_complex)),
              gr::io_signature::make(1, 1, orden.size()*sizeof(gr_complex)))
    {
        d_orden = orden;
        d_length = orden.size();
    }

    /*
     * Our virtual destructor.
     */
    interleaver_impl::~interleaver_impl()
    {
    }

    int
    interleaver_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];


      for(int i=0; i<noutput_items; i++){

          for (int carrier = 0; carrier<d_length; carrier++){
              out[i*d_length+carrier] = in[i*d_length + d_orden[carrier]];
          }

      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace taller */
} /* namespace gr */

