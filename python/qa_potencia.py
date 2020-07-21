#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2020 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import taller_swig as taller

import numpy as np

class qa_potencia (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # set up fg

        for exponente in [0.1, 1, 2, 3, 5]:
            exponente = 2
            src_data = range(1000)
            src = blocks.vector_source_f(src_data, False, 1)
            dst = blocks.vector_sink_f(1)

            potencia = taller.potencia(exponente)

            self.tb.connect(src,potencia,dst)

            self.tb.run ()
            # check data

            actual_result = dst.data()

            expected_result = np.power(src_data,exponente)

            self.assertFloatTuplesAlmostEqual(expected_result, actual_result)


if __name__ == '__main__':
    gr_unittest.run(qa_potencia, "qa_potencia.xml")
