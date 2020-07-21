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


#ifndef INCLUDED_TALLER_TRIGGER_H
#define INCLUDED_TALLER_TRIGGER_H

#include <taller/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace taller {

    /*!
     * \brief <+description of block+>
     * \ingroup taller
     *
     */
    class TALLER_API trigger : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<trigger> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of taller::trigger.
       *
       * To avoid accidental use of raw pointers, taller::trigger's
       * constructor is in a private implementation
       * class. taller::trigger::make is the public interface for
       * creating new instances.
       */
      static sptr make(float nivel, int pendiente, int muestras);
    };

  } // namespace taller
} // namespace gr

#endif /* INCLUDED_TALLER_TRIGGER_H */

