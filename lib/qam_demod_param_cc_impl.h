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
#pragma once
#ifndef INCLUDED_INATELMODEM5G_QAM_DEMOD_PARAM_CC_IMPL_H
#define INCLUDED_INATELMODEM5G_QAM_DEMOD_PARAM_CC_IMPL_H

#include <inatelModem5g/qam_demod_param_cc.h>

namespace gr {
  namespace inatelModem5g {

    class qam_demod_param_cc_impl : public qam_demod_param_cc
    {
     private:
      // Nothing to declare in this block.
      std::vector<gr_complex> d_const;
      std::vector<int> d_map;
      std::vector<float> d_noisevar;

     public:
      qam_demod_param_cc_impl(std::vector<gr_complex> constelation, std::vector<int> map, std::vector<float> noisevar);
      ~qam_demod_param_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace inatelModem5g
} // namespace gr

#endif /* INCLUDED_INATELMODEM5G_QAM_DEMOD_PARAM_CC_IMPL_H */

