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
#include "fec_decoder_impl.h"

namespace gr {
namespace cs330project {

fec_decoder::sptr
fec_decoder::make(int type)
{
    return gnuradio::get_initial_sptr
           (new fec_decoder_impl(type));
}


/*
 * The private constructor
 */
fec_decoder_impl::fec_decoder_impl(int type)
    : gr::block("fec_encoder",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0)),
      d_type(type)
{
    message_port_register_in(pmt::mp("pdu_in"));
    message_port_register_out(pmt::mp("pdu_out"));

    /* Register the message handler. For every message received in the input
     * message port it will be called automatically.
     */
    set_msg_handler(pmt::mp("pdu_in"),
    [this](pmt::pmt_t msg) {
        this->fec_decoder_impl::decode(msg);
    });
}

/*
 * Our virtual destructor.
 */
fec_decoder_impl::~fec_decoder_impl()
{
}

void
fec_decoder_impl::decode(pmt::pmt_t m)
{
    switch (d_type) {
    /* No FEC just copy the input message to the output */
    case 0:
        message_port_pub(pmt::mp("pdu_out"), m);
        return;
    case 1:
        /* Do Hamming encoding */
        return;
    case 2:
        /* Do Golay encoding */
        return;
    default:
        throw std::runtime_error("fec_decoder: Invalid FEC");
        return;
    }
}

} /* namespace cs330project */
} /* namespace gr */
