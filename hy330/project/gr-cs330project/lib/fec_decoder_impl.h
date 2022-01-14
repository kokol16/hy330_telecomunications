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

#ifndef INCLUDED_CS330PROJECT_FEC_DECODER_IMPL_H
#define INCLUDED_CS330PROJECT_FEC_DECODER_IMPL_H

#include <cs330project/fec_decoder.h>

namespace gr
{
    namespace cs330project
    {

        class fec_decoder_impl : public fec_decoder
        {
        private:
            const int d_type;
            std::vector<uint8_t> input_packet_in_bits;
            std::vector<uint8_t> packet_after_decoding_in_bits;
            std::vector<uint8_t> packet_after_decoding_in_bytes;
            int count_ones;
            int count_zeros;

            void vector_of_bits_to_bytes(std::vector<uint8_t> vector_bits, std::vector<uint8_t> &packet_after_decoding_in_bytes);

            void decode(pmt::pmt_t m);

        public:
            fec_decoder_impl(int type);
            ~fec_decoder_impl();
        };

    } // namespace cs330project
} // namespace gr

#endif /* INCLUDED_CS330PROJECT_FEC_DECODER_IMPL_H */
