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

#include <iostream>
#include <gnuradio/io_signature.h>
#include <bits/stdc++.h>
#include "qam_demod_cc_impl.h"
#include "qam_demod.h"

using namespace std;

namespace gr {
  namespace inatelModem5g {

    qam_demod_cc::sptr
    qam_demod_cc::make()
    {
      return gnuradio::get_initial_sptr
        (new qam_demod_cc_impl());
    }

    /*
     * The private constructor
     */
    qam_demod_cc_impl::qam_demod_cc_impl()
      : gr::sync_block("qam_demod_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {}

    /*
     * Our virtual destructor.
     */
    qam_demod_cc_impl::~qam_demod_cc_impl()
    {
    }

    int
    qam_demod_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

      vector<int> map = {3,2,1,0};
      vector<float> noisevar = {0.1}; 
      vector<complex<float> > constel = {{-1,+1},{-1,-1},{+1,+1},{+1,-1}};
     

      // Do <+signal processing+>
      //vector<complex<float>> signal_received = {{-3,5}, {2,-1}, {-5,6}, {7,-8}, {6,8}, {1,2}};
      vector<complex<float>> signal_received(noutput_items);
      vector<complex<float>> qam_simbols(noutput_items);
      #pragma simd
      for (int i=0; i<noutput_items; i++){
          signal_received[i] = *(in+i);
      }
      
      // ********** wheberth  hints
      // size_t sz = map.size()
      // gr_complex *d = map.data();

      // d[0..sz-1]

      // vector<gr_complex> map256 (256) = {0};

     
      qam_simbols = qamllr(signal_received, constel, map, noisevar);

      #pragma simd
      memcpy(out, qam_simbols.data(), sizeof(gr_complex)*qam_simbols.size());

      // for (int i =0; i< qam_simbols.size(); i++){
      //   cout << qam_simbols[i];
      // }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace inatelModem5g */
} /* namespace gr */

