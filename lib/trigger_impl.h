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

#ifndef INCLUDED_TALLER_TRIGGER_IMPL_H
#define INCLUDED_TALLER_TRIGGER_IMPL_H

#include <taller/trigger.h>

namespace gr {
  namespace taller {

    class trigger_impl : public trigger
    {
     private:
         
         // el nivel donde va a saltar el trigger
         float d_nivel; 
         // una pendiente positiva o negativa (1 o -1)
         int d_pendiente;
         // cuantas muestras va a sacar cuando detecte el trigger
         int d_muestras; 

         // ultima muestra que vi
         float d_ultima_muestra;

         // si estoy sacando muestras o estoy buscando el trigger
         bool d_buscando;

         // cuantas muestras ya genere con este trigger
         int d_nout;


     public:
      trigger_impl(float nivel, int pendiente, int muestras);
      ~trigger_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace taller
} // namespace gr

#endif /* INCLUDED_TALLER_TRIGGER_IMPL_H */

