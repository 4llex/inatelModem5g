/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
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
#include "qam_demod_param_cc_impl.h"
#include "qam_demod.h"

namespace gr {
  namespace inatelModem5g {

    qam_demod_param_cc::sptr
    qam_demod_param_cc::make(std::vector<gr_complex> constelation, std::vector<int> map, std::vector<float> noisevar)
    {
      return gnuradio::get_initial_sptr
        (new qam_demod_param_cc_impl(constelation, map, noisevar));
    }

    /*
     * The private constructor
     */
    qam_demod_param_cc_impl::qam_demod_param_cc_impl(std::vector<gr_complex> constelation, std::vector<int> map, std::vector<float> noisevar)
      : gr::sync_block("qam_demod_param_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
        d_const(constelation),
        d_map(map),
        d_noisevar(noisevar)
    {}

    /*
     * Our virtual destructor.
     */
    qam_demod_param_cc_impl::~qam_demod_param_cc_impl()
    {
    }

    int
    qam_demod_param_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];


      // Do <+signal processing+>
      std::vector<gr_complex> received_signals(noutput_items);
      std::vector<gr_complex> qam_symbols(noutput_items);

      #pragma simd
      for (int i=0; i<noutput_items; i++){
        received_signals[i] = *(in+i);
      }

      qam_symbols = qamllr(received_signals, d_const, d_map, d_noisevar);

      #pragma simd
      for (int i=0; i<noutput_items; i++){
        *(out+i) = qam_symbols[i];
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace inatelModem5g */
} /* namespace gr */

