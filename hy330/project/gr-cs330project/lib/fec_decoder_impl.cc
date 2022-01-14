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

namespace gr
{
    namespace cs330project
    {

        fec_decoder::sptr
        fec_decoder::make(int type)
        {
            return gnuradio::get_initial_sptr(new fec_decoder_impl(type));
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
            count_ones = 0;
            count_zeros = 0;

            /* Register the message handler. For every message received in the input
     * message port it will be called automatically.
     */
            set_msg_handler(pmt::mp("pdu_in"),
                            [this](pmt::pmt_t msg)
                            {
                                this->fec_decoder_impl::decode(msg);
                            });
        }

        /*
 * Our virtual destructor.
 */
        fec_decoder_impl::~fec_decoder_impl()
        {
        }
        void fec_decoder_impl::vector_of_bits_to_bytes(std::vector<uint8_t> vector_bits, std::vector<uint8_t> &packet_after_decoding_in_bytes)
        {
            //make vector of bits to bytes
            std::string str = "";
            for (int i = 0; i < vector_bits.size(); ++i)
            {
                if (i != 0 && i % 8 == 0)
                {
                    uint8_t byte = (uint8_t)std::stoi(str, 0, 2);
                    //  printf("%02hhx ", byte);
                    packet_after_decoding_in_bytes.push_back(byte);
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
            packet_after_decoding_in_bytes.push_back(byte);
        }
        void
        fec_decoder_impl::decode(pmt::pmt_t m)
        {
            pmt::pmt_t bytes(pmt::cdr(m));
            pmt::pmt_t payload;

            /* Access the raw bytes of the PDU */
            size_t pdu_len;
            const uint8_t *bytes_in = pmt::u8vector_elements(bytes, pdu_len);
            switch (d_type)
            {
            /* No FEC just copy the input message to the output */
            case 0:
                message_port_pub(pmt::mp("pdu_out"), m);
                return;
            case 1:
                std::cout << "length before decoding hamming: " << pdu_len << std::endl;

                count_ones = 0;
                count_zeros = 0;
              //  printf("got %02hhx \n", bytes_in[pdu_len - 1]);

                for (int i = 0; i < pdu_len; i++)
                {

                    for (int j = 7; j >= 0; --j)
                    {

                        uint8_t bit = (bytes_in[i] >> j) & 1;

                        input_packet_in_bits.push_back(bit);
                    }
                    //  std::cout<<"-------------------"<<std::endl;
                }
               

                //reconstruct the bits
                for (int i = 0; i < input_packet_in_bits.size(); i++)
                {

                    if (i != 0 && i % 3 == 0)
                    {
                        if (count_ones > count_zeros)
                        {
                            packet_after_decoding_in_bits.push_back(1);
                        }
                        else
                        {
                            packet_after_decoding_in_bits.push_back(0);
                        }
                        count_ones = 0;
                        count_zeros = 0;
                    }
                    if (input_packet_in_bits[i] == 1)
                    {
                        ++count_ones;
                    }
                    else
                    {
                        ++count_zeros;
                    }
                }
               /* std::cout << "count ones: " << count_ones << std::endl;
                std::cout << "count zeros: " << count_zeros << std::endl;*/

                if (count_ones > count_zeros)
                {
                    packet_after_decoding_in_bits.push_back(1);
                }
                else
                {
                    packet_after_decoding_in_bits.push_back(0);
                }
                /*std::cout << "got ";
                //expected 11100001  got 10000111
                for (int i = packet_after_decoding_in_bits.size() - 8; i < packet_after_decoding_in_bits.size()   ; ++i)
                {
                    if (packet_after_decoding_in_bits[i])
                    {
                        std::cout << "1";
                    }
                    else
                    {
                        std::cout << "0";
                    }
                }
                std::cout << std::endl;*/

                count_ones = 0;
                count_zeros = 0;
                //make bits to bytes
                vector_of_bits_to_bytes(packet_after_decoding_in_bits, packet_after_decoding_in_bytes);
                std::cout << "length after decoding hamming: " << packet_after_decoding_in_bytes.size() << std::endl;
                payload = pmt::init_u8vector(packet_after_decoding_in_bytes.size(), packet_after_decoding_in_bytes);
                message_port_pub(pmt::mp("pdu_out"), pmt::cons(pmt::PMT_NIL, payload));
                packet_after_decoding_in_bits.clear();
                packet_after_decoding_in_bytes.clear();
                input_packet_in_bits.clear();
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
