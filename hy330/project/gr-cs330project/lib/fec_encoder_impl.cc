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
#include "fec_encoder_impl.h"

namespace gr
{
    namespace cs330project
    {

        fec_encoder::sptr
        fec_encoder::make(int type)
        {
            return gnuradio::get_initial_sptr(new fec_encoder_impl(type));
        }

        /*
 * The private constructor
 */
        fec_encoder_impl::fec_encoder_impl(int type)
            : gr::block("fec_encoder",
                        gr::io_signature::make(0, 0, 0),
                        gr::io_signature::make(0, 0, 0)),
              d_type(type)
        {
            message_port_register_in(pmt::mp("pdu_in"));
            message_port_register_out(pmt::mp("pdu_out"));

            /*
     * Register the message handler. For every message received in the input
     * message port it will be called automatically.
     */
            set_msg_handler(pmt::mp("pdu_in"),
                            [this](pmt::pmt_t msg)
                            {
                                this->fec_encoder_impl::encode(msg);
                            });
        }

        /*
 * Our virtual destructor.
 */
        fec_encoder_impl::~fec_encoder_impl()
        {
        }
        void fec_encoder_impl::vector_of_bits_to_bytes(std::vector<uint8_t> vector_bits, std::vector<uint8_t> &packet_after_encoding_in_bytes)
        {
            //make vector of bits to bytes
            std::string str = "";
            for (int i = 0; i < vector_bits.size(); ++i)
            {
                if (i != 0 && i % 8 == 0)
                {
                    uint8_t byte = (uint8_t)std::stoi(str, 0, 2);
                    //  printf("%02hhx ", byte);
                    packet_after_encoding_in_bytes.push_back(byte);
                    // std::cout << "lalalalala" << std::endl;

                    //std::cout << str<<std::endl;

                    str = "";
                }
                if (vector_bits[i] == 1)
                {
                    str += "1";
                }
                else
                {
                    str += "0";
                }
            }
            uint8_t byte = (uint8_t)std::stoi(str, 0, 2);
            packet_after_encoding_in_bytes.push_back(byte);
        }
        void
        fec_encoder_impl::encode(pmt::pmt_t m)
        {
            pmt::pmt_t bytes(pmt::cdr(m));

            pmt::pmt_t payload;
            /* Access the raw bytes of the PDU */
            size_t pdu_len;
            const uint8_t *bytes_in = pmt::u8vector_elements(bytes, pdu_len);
           // printf("send %02hhx \n", bytes_in[pdu_len-1]);
            
            switch (d_type)
            {
            /* No FEC just copy the input message to the output */
            case 0:
                message_port_pub(pmt::mp("pdu_out"), m);
                return;
            case 1:
                std::cout << "length before encoding hamming: " << pdu_len << std::endl;

                for (int i = 0; i < pdu_len; ++i)
                {
                    for (int j = 7; j >=0; --j)
                    {
                        uint8_t bit = (bytes_in[i] >> j) & 1;
                        for (int k = 0; k < 3; ++k)
                        {
                            packet_after_encoding.push_back(bit);
                        }
                    }
                }

                vector_of_bits_to_bytes(packet_after_encoding, packet_after_encoding_in_bytes);


                std::cout << "length after encoding  hamming: " << packet_after_encoding_in_bytes.size() << std::endl;
                payload = pmt::init_u8vector(packet_after_encoding_in_bytes.size(), packet_after_encoding_in_bytes);
                message_port_pub(pmt::mp("pdu_out"), pmt::cons(pmt::PMT_NIL, payload));

                packet_after_encoding.clear();
                packet_after_encoding_in_bytes.clear();

                /* Do Hamming encoding */
                return;
            case 2:
                /* Do Golay encoding */
                return;
            default:
                throw std::runtime_error("fec_encoder: Invalid FEC");
                return;
            }
        }

    } /* namespace cs330project */
} /* namespace gr */
