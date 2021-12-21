/* -*- c++ -*- */
/*
 * Copyright 2021 gkokol.
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

#ifndef INCLUDED_CONSTELATION_MAPPING_MODULE_CONSTELATION_MAPPING_IMPL_H
#define INCLUDED_CONSTELATION_MAPPING_MODULE_CONSTELATION_MAPPING_IMPL_H

#include <constelation_mapping_module/constelation_mapping.h>

namespace gr
{
  namespace constelation_mapping_module
  {

    class constelation_mapping_impl : public constelation_mapping
    {
    private:
      int k;
      // Nothing to declare in this block.

    public:
      constelation_mapping_impl(int _k);
      ~constelation_mapping_impl();

      // Where all the action really happens
      int work(
          int noutput_items,
          gr_vector_const_void_star &input_items,
          gr_vector_void_star &output_items);
      void normalize_qpsk(gr_complex *qpsk, int size);
      void normalize_qam_16(gr_complex *qpsk, int size);

    };

  } // namespace constelation_mapping_module
} // namespace gr

#endif /* INCLUDED_CONSTELATION_MAPPING_MODULE_CONSTELATION_MAPPING_IMPL_H */
