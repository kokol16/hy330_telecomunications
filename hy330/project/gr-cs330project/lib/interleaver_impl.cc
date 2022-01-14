/* -*- c++ -*- */
/*
 * gr-cs330project: Useful blocks for SDR and GNU Radio learning
 *
 *  Copyright (C) 2019, 2020 Manolis Surligas <surligas@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "interleaver_impl.h"

namespace gr
{
    namespace cs330project
    {

        interleaver::sptr
        interleaver::make(size_t block_size)
        {
            return gnuradio::get_initial_sptr(new interleaver_impl(block_size));
        }

        /*
 * The private constructor
 */
        interleaver_impl::interleaver_impl(size_t block_size)
            : gr::block("interleaver",
                        gr::io_signature::make(0, 0, 0),
                        gr::io_signature::make(0, 0, 0))
        {
            this->block_size = block_size;
            //[k][k]
            this->interleaver_array = new uint8_t *[block_size];
            for (int i = 0; i < block_size; ++i)
            {
                this->interleaver_array[i] = new uint8_t[block_size];
            }
            message_port_register_in(pmt::mp("pdu_in"));
            message_port_register_out(pmt::mp("pdu_out"));

            /* Register the message handler. For every message received in the input
     * message port it will be called automatically.
     */
            set_msg_handler(pmt::mp("pdu_in"),
                            [this](pmt::pmt_t msg)
                            {
                                this->interleaver_impl::interleave(msg);
                            });
        }

        /*
 * Our virtual destructor.
 */
        interleaver_impl::~interleaver_impl()
        {
            // free dynamically allocated memory
            for (int i = 0; i < block_size; ++i)
            {
                delete[] this->interleaver_array[i];
            }
            delete[] this->interleaver_array;
        }

        void
        interleaver_impl::interleave(pmt::pmt_t m)
        {
            pmt::pmt_t bytes(pmt::cdr(m));

            pmt::pmt_t payload;
            /* Access the raw bytes of the PDU */
            size_t pdu_len;
            const uint8_t *bytes_in = pmt::u8vector_elements(bytes, pdu_len);
            //bytes to bits
            int col=0;
            for (int i = 0; i < pdu_len; ++i)
            {
                col=0;
                for (int j = 7; j >= 0; --j)
                {
                    uint8_t bit = (bytes_in[i] >> j) & 1;
                    interleaver_array[i][col++]=bit;
                }
            }
           // for(i=0; )

            message_port_pub(pmt::mp("pdu_out"), m);
            //memset(array, 0, sizeof(array[0][0]) * m * n);
        }

    } /* namespace cs330project */
} /* namespace gr */
