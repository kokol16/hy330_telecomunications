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
#include "deinterleaver_impl.h"

namespace gr {
namespace cs330project {

deinterleaver::sptr
deinterleaver::make(size_t block_size)
{
    return gnuradio::get_initial_sptr
           (new deinterleaver_impl(block_size));
}


/*
 * The private constructor
 */
deinterleaver_impl::deinterleaver_impl(size_t block_size)
    : gr::block("deinterleaver",
                gr::io_signature::make(0, 0, 0),
                gr::io_signature::make(0, 0, 0))
{
    message_port_register_in(pmt::mp("pdu_in"));
    message_port_register_out(pmt::mp("pdu_out"));

    /* Register the message handler. For every message received in the input
     * message port it will be called automatically.
     */
    set_msg_handler(pmt::mp("pdu_in"),
    [this](pmt::pmt_t msg) {
        this->deinterleaver_impl::deinterleave(msg);
    });
}

/*
 * Our virtual destructor.
 */
deinterleaver_impl::~deinterleaver_impl()
{
}

void
deinterleaver_impl::deinterleave(pmt::pmt_t m)
{
    /* TODO: Add your code here */

    /*
     * FIXME: This just copies the input to the output. Even you do not
     * implement the deinterleaver, it will forward the input message to the next
     * block and everything should work fine
     */
    message_port_pub(pmt::mp("pdu_out"), m);
}


} /* namespace cs330project */
} /* namespace gr */
