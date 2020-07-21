/* -*- c++ -*- */
/* 
 * Copyright 2020 Federico 'Larroca' La Rocca.
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
#include "align_tag_impl.h"

namespace gr {
  namespace taller {

    align_tag::sptr
    align_tag::make(int muestras)
    {
      return gnuradio::get_initial_sptr
        (new align_tag_impl(muestras));
    }

    /*
     * The private constructor
     */
    align_tag_impl::align_tag_impl(int muestras)
      : gr::block("align_tag",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
        d_muestras = muestras;
        set_output_multiple(muestras);

        set_tag_propagation_policy(TPP_DONT);
    }

    /*
     * Our virtual destructor.
     */
    align_tag_impl::~align_tag_impl()
    {
    }

    void
    align_tag_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        ninput_items_required[0] = noutput_items;
    }

    int
    align_tag_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      for(int i=0; i<noutput_items; i=i+d_muestras)
      {

          std::vector<tag_t> tags;
          get_tags_in_window(
                  tags, // Tags will be saved here
                  0, // Port 0
                  i, // Start of range (relative to nitems_read(0))
                  i+d_muestras, // End of relative range
                  pmt::mp("trigger")); // Optional: Only find tags with key "my_tag_key"

          //me fijo si el tag está
          if(tags.size()){
              // me fijo si no estoy alineado con el tag
                if(tags[0].offset-nitems_read(0)){
                   // si no estoy alineado consumo hasta ese punto
                    consume_each(tags[0].offset-nitems_read(0));
                    return 0;
                }
                else
                {
                    memcpy(&out[i],&in[i],d_muestras*sizeof(float));
                    consume_each(d_muestras);
                    return d_muestras;
                }
          }
          else
          {
              //printf("no encontró el tag %lu\n", nitems_read(0));
          }

      }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace taller */
} /* namespace gr */

