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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "constellation_mapping_impl.h"

namespace gr
{
  namespace constellation_mapping
  {

    constellation_mapping::sptr
    constellation_mapping::make()
    {
      return gnuradio::get_initial_sptr(new constellation_mapping_impl('1'));
    }

    /*
     * The private constructor
     */
    constellation_mapping_impl::constellation_mapping_impl(unsigned char _k)
        : gr::sync_block("constellation_mapping",
                         gr::io_signature::make(1, 1, sizeof(unsigned char)),
                         gr::io_signature::make(1, 1, sizeof(gr_complex))),
          k(_k)
    {
    }

    /*
     * Our virtual destructor.
     */
    constellation_mapping_impl::~constellation_mapping_impl()
    {
    }

    int
    constellation_mapping_impl::work(int noutput_items,
                                     gr_vector_const_void_star &input_items,
                                     gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *)input_items[0];
      gr_complex *out = (gr_complex *)output_items[0];
      
      for (int i=0; i<4; i++)
      {
          out[i].imag(i+i+1);
          out[i].real(-i+i-1);
      }
      for (int i = 0; i < noutput_items; ++i)
      {

        if (in[i] == 0)
        {

          out[i].imag(0);
          out[i].real(-1);
        }
        else
        {

          out[i].imag(0);
          out[i].real(1);
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace constellation_mapping */
} /* namespace gr */
