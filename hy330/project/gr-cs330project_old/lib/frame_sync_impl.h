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

#ifndef INCLUDED_CS330PROJECT_FRAME_SYNC_IMPL_H
#define INCLUDED_CS330PROJECT_FRAME_SYNC_IMPL_H

#include <cs330project/frame_sync.h>
#include <cs330project/shift_reg.h>

namespace gr
{
    namespace cs330project
    {

        class frame_sync_impl : public frame_sync
        {
        private:
            void extra_qpsk_bytes_to_vector(uint8_t byte, std::vector<uint8_t> &reg);
            void extra_qpsk_bytes(uint8_t byte, shift_reg &reg);
            void extra_qpsk_bytesV2(uint8_t byte, shift_reg &reg);

            typedef enum
            {
                BPSK = 0,
                QPSK
            } mod_t;
            typedef enum
            {
                NORMAL = 0,
                INVERSE
            } bpsk_rotation_t;

            typedef enum
            {
                _00_00 = 0,
                _00_11,
                _00_01,
                _00_10

            } qpsk_rotation_t;

            qpsk_rotation_t qpsk_rotation;

            bpsk_rotation_t bpsk_rotation;
            shift_reg reg_preamble;
            shift_reg reg_sync_word;
            shift_reg reg_sync_word_inverse;

            shift_reg reg_sync_word_perm_00_11;
            shift_reg reg_sync_word_perm_00_10;
            shift_reg reg_sync_word_perm_00_01;

            shift_reg reg_frame_length;
            int frame_length_index;
            size_t count_frames;
            int payload_length;
            size_t bits_seen_so_far;

            shift_reg reg_input;
            shift_reg reg_input_sync_word;
            shift_reg reg_input_frame_length;
            std::vector<uint8_t> payload_in_bits;
            std::vector<uint8_t> payload_in_bytes;

            //  shift_reg reg_payload;

            const mod_t d_mod;

        public:
            uint8_t preamble;
            size_t preamble_len;
            std::vector<uint8_t> sync_word;
            typedef enum
            {
                PREAMBLE = 0,
                SYNCWORD,
                FRAME_LENGTH,
                EXTRACT_PAYLOAD,
                SEND_PAYLOAD

            } sync_fsm_t;
            sync_fsm_t action = PREAMBLE;

            sync_fsm_t (frame_sync_impl::*sync_fsm[3])(shift_reg);
            sync_fsm_t find_preamble_sequence(shift_reg);
            sync_fsm_t find_sync_word(shift_reg);
            sync_fsm_t extract_frame_length(shift_reg);
            //   sync_fsm_t extract_payload(shift_reg);

            frame_sync_impl(uint8_t preamble, uint8_t preamble_len,
                            const std::vector<uint8_t> &sync_word,
                            int mod);
            ~frame_sync_impl();

            // Where all the action really happens
            int work(
                int noutput_items,
                gr_vector_const_void_star &input_items,
                gr_vector_void_star &output_items);
        };

    } // namespace cs330project
} // namespace gr

#endif /* INCLUDED_CS330PROJECT_FRAME_SYNC_IMPL_H */
