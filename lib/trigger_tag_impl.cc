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
#include "trigger_tag_impl.h"

namespace gr {
  namespace taller {

    trigger_tag::sptr
    trigger_tag::make(float nivel, int pendiente)
    {
      return gnuradio::get_initial_sptr
        (new trigger_tag_impl(nivel, pendiente));
    }

    /*
     * The private constructor
     */
    trigger_tag_impl::trigger_tag_impl(float nivel, int pendiente)
      : gr::sync_block("trigger_tag",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
        d_nivel = nivel;
        d_pendiente = pendiente;
    
        d_ultima_muestra = 0;

        // le pongo nombre el puerto
        message_port_register_in(pmt::mp("nivel"));
        // le asigno una función que atiende los mensajes que llegan al puerto
        set_msg_handler(pmt::mp("nivel"), boost::bind(&trigger_tag_impl::set_nivel_msg, this, _1));
    }

    void 
    trigger_tag_impl::set_nivel_pendiente(float nivel, int pendiente){
        d_nivel = nivel;
        d_pendiente = pendiente;
    }

    /*
     * Our virtual destructor.
     */
    trigger_tag_impl::~trigger_tag_impl()
    {
    }

    void trigger_tag_impl::set_nivel_msg(pmt::pmt_t msg){

        if(pmt::is_pair(msg)) {
            // saca el primero de la pareja
            pmt::pmt_t key = pmt::car(msg);
            // saca el segundo
            pmt::pmt_t val = pmt::cdr(msg);
            if(pmt::eq(key, pmt::string_to_symbol("nivel"))) {
                if(pmt::is_number(val)) {
                    set_nivel_pendiente(pmt::to_double(val),d_pendiente);
                }
            }
        }
        printf("hola\n");

    }

    int
    trigger_tag_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];


      memcpy(&out[0], &in[0], noutput_items*sizeof(float));
      for(int i=0; i<noutput_items; i++){
          if((d_pendiente*d_ultima_muestra<d_pendiente*d_nivel)&&(d_pendiente*d_nivel<d_pendiente*in[i]))
          {
              //add_item_tag(port number, absolute offset,  key, value)
              add_item_tag(0, nitems_written(0) + i, pmt::mp("trigger"), pmt::PMT_T);
          }
          d_ultima_muestra = in[i];
      }




      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace taller */
} /* namespace gr */

