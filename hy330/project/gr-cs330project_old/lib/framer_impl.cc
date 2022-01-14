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
#include "framer_impl.h"

namespace gr
{
    namespace cs330project
    {

        framer::sptr
        framer::make(uint8_t preamble, size_t preamble_len,
                     const std::vector<uint8_t> &sync_word)
        {
            return gnuradio::get_initial_sptr(
                new framer_impl(preamble, preamble_len, sync_word));
        }

        /*
 * The private constructor
 */
        framer_impl::framer_impl(uint8_t preamble, size_t preamble_len,
                                 const std::vector<uint8_t> &sync_word) : gr::block("framer", gr::io_signature::make(0, 0, 0),
                                                                                    gr::io_signature::make(0, 0, 0)),
                                                                          sync_word(sync_word), preamble(preamble), preamble_len(preamble_len)
        {
            message_port_register_in(pmt::mp("pdu"));
            message_port_register_out(pmt::mp("frame"));

            /*
     * Register the message handler. For every message received in the input
     * message port it will be called automatically.
     */
            set_msg_handler(pmt::mp("pdu"),
                            [this](pmt::pmt_t msg)
                            {
                                this->framer_impl::construct(msg);
                            });
        }

        unsigned char extract_byte(unsigned int x, size_t n)
        {
            n %= sizeof(x);

            return x >> CHAR_BIT * n & 0xFF;
        }
        void
        framer_impl::construct(pmt::pmt_t m)
        {
            /* Extract the bytes of the PDU. GNU Radio handles PDUs in pairs.
     * The first element of the pair contains metadata associated with  the
     * PDU, whereas the second element of the pair is a pmt with a u8 vector
     * containing the raw bytes. Below there is an example how to get the
     * PDU raw pointer and the length of the frame in bytes that points to
     */
            pmt::pmt_t meta(pmt::car(m));
            pmt::pmt_t bytes(pmt::cdr(m));
            /* Access the raw bytes of the PDU */
            size_t pdu_len;
            const uint8_t *bytes_in = pmt::u8vector_elements(bytes, pdu_len);
            //add reamble

            for (int i = 0; i < preamble_len; ++i)
            {
                payload.push_back(preamble);
            }

            for (int i = 0; i < sync_word.size(); ++i)
            {

                payload.push_back(sync_word[i]);
            }

            //add payload length
            uint8_t tmp[2];
            tmp[0] = extract_byte(pdu_len, 1);
            tmp[1] = extract_byte(pdu_len, 0);

            std::cout << "packet that was sent has payload length: " << pdu_len << std::endl;

            //  tmp[0]= (uint16_t)pdu_len;
            // tmp[1]= (uint16_t)pdu_len >> 8;
            //  uint16_t lala = (uint16_t)pdu_len;
            // uint8_t b1 = ((uint16_t)lala >> 0) & 0xFF;
            //  uint8_t b2 = ((uint16_t)lala >> 8) & 0xFF;

            payload.push_back(tmp[0]);
            payload.push_back(tmp[1]);

            //add payload
            for (int i = 0; i < pdu_len; ++i)
            {
                payload.push_back(bytes_in[i]);
            }
            pmt::pmt_t payload_t = pmt::init_u8vector(payload.size(), payload);

            message_port_pub(pmt::mp("frame"), pmt::cons(pmt::PMT_NIL, payload_t));
            payload.clear();
        }

        /*
 * Our virtual destructor.
 */
        framer_impl::~framer_impl()
        {
        }

    } /* namespace cs330project */
} /* namespace gr */

/*
//meta = pmt::make_dict();
            pmt::pmt_t preamble_dict = pmt::make_dict();

            pmt::pmt_t key = pmt::intern("preamble_dict");
            std::vector<uint8_t> preambles;

            meta = pmt::dict_add(meta, key, pmt::init_u8vector(preamble_len, preambles));
            pmt::pmt_t sync_word_dict = pmt::make_dict();
            //pmt::print(pmt::dict_values(preamble_dict));
            key = pmt::intern("sync_word_dict");
            meta = pmt::dict_add(meta, key, pmt::init_u8vector(sync_word.size(), sync_word));*/

/*
            pmt::pmt_t p1 = pmt::intern("pdu_len");
            pmt::pmt_t p2 = pmt::from_uint64(pdu_len);
            meta = pmt::dict_add(meta, p1, p2);
            p1 = pmt::intern("pdu_len");
            p2 = pmt::from_uint64(pdu_len);
            std::vector<uint8_t> vec;
            for (uint8_t obj : sync_word)
            {
                vec.push_back(obj);
                std::cout << "metadata: " << (unsigned char)obj << std::endl;
            }*/

// const uint8_t *meta_data = pmt::u8vector_elements(meta, meta_len);
//pmt::print((sync_word));