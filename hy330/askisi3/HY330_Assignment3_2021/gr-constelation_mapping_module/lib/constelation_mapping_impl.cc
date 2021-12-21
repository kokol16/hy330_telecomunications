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

#define QPSK_NORMALIZATION 1 / 1.4142135623
#define QAM_16_NORMALIZATION 1 / 3.1622776601683795
#include <gnuradio/io_signature.h>
#include "constelation_mapping_impl.h"
#include <string>
#include <iostream>

namespace gr
{
  namespace constelation_mapping_module
  {

    constelation_mapping::sptr
    constelation_mapping::make(int _k)
    {
      return gnuradio::get_initial_sptr(new constelation_mapping_impl(_k));
    }

    /*
     * The private constructor
     */
    constelation_mapping_impl::constelation_mapping_impl(int _k)
        : gr::sync_block("constelation_mapping",
                         gr::io_signature::make(1, 1, sizeof(unsigned char)),
                         gr::io_signature::make(1, 1, sizeof(gr_complex))),
          k(_k)
    {
    }

    /*
     * Our virtual destructor.
     */
    constelation_mapping_impl::~constelation_mapping_impl()
    {
    }

    int
    constelation_mapping_impl::work(int noutput_items,
                                    gr_vector_const_void_star &input_items,
                                    gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *)input_items[0];
      gr_complex *out = (gr_complex *)output_items[0];

      /*for (int i=0; i<4; i++)
      {
          out[i].imag(i+i+1);
          out[i].real(-i+i-1);
      }*/
      gr_complex qpsk[4];
      qpsk[0].imag(-1);
      qpsk[0].real(-1);
      qpsk[1].imag(1);
      qpsk[1].real(-1);
      qpsk[2].imag(-1);
      qpsk[2].real(1);
      qpsk[3].imag(1);
      qpsk[3].real(1);
      gr_complex bpsk[2];
      bpsk[0].imag(0);
      bpsk[0].real(-1);
      bpsk[1].imag(0);
      bpsk[1].real(1);

      gr_complex qam_16[16] = {{-3, -3}, {-3, -1}, {-3, 3}, {-3, 1}, {-1, -3}, {-1, -1}, {-1, 3}, {-1, 1}, {3, -3}, {3, -1}, {3, 3}, {3, 1}, {1, -3}, {1, -1}, {1, 3}, {1, 1}};

      normalize_qpsk(qpsk, 4);
      normalize_qam_16(qam_16, 16);

      if (k == 1)
      {

        std::string str = "";
        int prev = 0;
        int index = 0;
        for (int i = 0; i < noutput_items; ++i)
        {
          str = std::to_string(in[i]);
          int demic_number = 0;
          demic_number = std::stoi(str, 0, 2);
          out[i].imag(bpsk[demic_number].imag());
          out[i].real(bpsk[demic_number].real());
          //std::cout << out[i / 2].real() << out[i / 2].imag() << std::endl;
        }
      }
      else if (k == 2)
      {
        std::string str = "";
        int prev = 0;
        int index = 0;
        for (int i = 0; i < noutput_items; i = i + 2)
        {
          str = std::to_string(in[i]);
          str += std::to_string(in[i + 1]);
          int demic_number = 0;
          demic_number = std::stoi(str, 0, 2);
          out[i / 2].imag(qpsk[demic_number].imag());
          out[i / 2].real(qpsk[demic_number].real());
          //std::cout << out[i / 2].real() << out[i / 2].imag() << std::endl;
        }
      }
      else if (k == 4)
      {
        std::string str = "";
        int prev = 0;
        int index = 0;
        for (int i = 0; i < noutput_items; i = i + 4)
        {
          str = std::to_string(in[i]);
          str += std::to_string(in[i + 1]);
          str += std::to_string(in[i + 2]);
          str += std::to_string(in[i + 3]);
          int demic_number = 0;
          demic_number = std::stoi(str, 0, 2);
          out[i / 4].imag(qam_16[demic_number].imag());
          out[i / 4].real(qam_16[demic_number].real());
          //std::cout << out[i / 2].real() << out[i / 2].imag() << std::endl;
        }
      }
      else
      {
        fprintf(stderr, "invlid k bits\n");
        return -1;
      }

      /*
        if (in[i] == 0)
        {

          out[i].imag(0);
          out[i].real(-1);
        }
        else
        {

          out[i].imag(0);
          out[i].real(1);
        }*/

      // Tell runtime system how many output items we produced.
      return noutput_items / k;
    }
    void constelation_mapping_impl::normalize_qpsk(gr_complex *qpsk, int size)
    {
      for (int i = 0; i < size; ++i)
      {
        qpsk[i].imag(qpsk[i].imag() * QPSK_NORMALIZATION);
        qpsk[i].real(qpsk[i].real() * QPSK_NORMALIZATION);
      }
    }
    void constelation_mapping_impl::normalize_qam_16(gr_complex *qpsk, int size)
    {
      for (int i = 0; i < size; ++i)
      {
        qpsk[i].imag(qpsk[i].imag() * QAM_16_NORMALIZATION);
        qpsk[i].real(qpsk[i].real() * QAM_16_NORMALIZATION);
      }
    }

  } /* namespace constelation_mapping_module */
} /* namespace gr */
