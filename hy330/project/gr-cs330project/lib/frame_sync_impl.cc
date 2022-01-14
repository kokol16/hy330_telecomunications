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

#include <string>
#include <gnuradio/io_signature.h>
#include "frame_sync_impl.h"

namespace gr
{
    namespace cs330project
    {

        void print_in(uint8_t bit)
        {
            if (bit == 1)
            {
                std::cout << "01";
            }
            else if (bit == 0)
            {
                std::cout << "00";
            }
            else if (bit == 2)
            {
                std::cout << "10";
            }
            else if (bit == 3)
            {
                std::cout << "11";
            }
        }
        frame_sync::sptr
        frame_sync::make(uint8_t preamble, uint8_t preamble_len,
                         const std::vector<uint8_t> &sync_word,
                         int mod)
        {
            return gnuradio::get_initial_sptr(new frame_sync_impl(preamble, preamble_len, sync_word, mod));
        }

        bool get_k_bit_least_significat_from_byte(uint8_t byte, int k_bit)
        {
            return ((byte >> k_bit) & 1);
        }
        void print_bit(uint8_t bit)
        {
            if (bit == 0)
            {
                std::cout << "0";
            }
            else
            {
                std::cout << "1";
            }
        }
        int frame_sync_impl::find_index_of_point(int index)
        {
            for (int i = 0; i < 4; ++i)
            {
                if (gray_code_qpsk[i] == index)
                {
                    return i;
                }
            }
            return 0;
        }
        /*
 * The private constructor
 */
        frame_sync_impl::frame_sync_impl(uint8_t preamble, uint8_t preamble_len,
                                         const std::vector<uint8_t> &sync_word,
                                         int mod)
            : gr::sync_block("frame_sync",
                             gr::io_signature::make(1, 1, sizeof(uint8_t)),
                             gr::io_signature::make(0, 0, 0)),

              d_mod((mod_t)mod),
              sync_word(sync_word), preamble(preamble), preamble_len(preamble_len), reg_preamble(preamble_len * 8), reg_sync_word(sync_word.size() * 8), reg_sync_word_inverse(sync_word.size() * 8), reg_frame_length(8 * 2), frame_length_index(0), reg_input(preamble_len * 8), reg_input_sync_word(sync_word.size() * 8), reg_input_frame_length(2 * 8), reg_sync_word_perm_00_11(sync_word.size() * 8), reg_sync_word_perm_00_10(sync_word.size() * 8), reg_sync_word_perm_00_01(sync_word.size() * 8)
        {
            gray_code_qpsk[0] = 0;
            gray_code_qpsk[1] = 1;
            gray_code_qpsk[2] = 3;
            gray_code_qpsk[3] = 2;

            bpsk_rotation = NORMAL;
            qpsk_rotation = _00_00;
            bits_seen_so_far = 0;
            count_frames = 0;
            payload_length = 0;
            sync_fsm[0] = &frame_sync_impl::find_preamble_sequence;
            sync_fsm[1] = &frame_sync_impl::find_sync_word;
            sync_fsm[2] = &frame_sync_impl::extract_frame_length;
            int index = 0;
            for (int i = 0; i < preamble_len; ++i)
            {
                for (int j = 7; j >= 0; --j)
                {

                    this->reg_preamble[index++] = get_k_bit_least_significat_from_byte(preamble, j);
                }
            }
            index = 0;
            for (int i = 0; i < sync_word.size(); ++i)
            {
                for (int j = 7; j >= 0; --j)
                {

                    this->reg_sync_word[index++] = get_k_bit_least_significat_from_byte(sync_word[i], j);
                }
            }

            for (int i = 0; i < reg_sync_word_inverse.size(); ++i)
                this->reg_sync_word_inverse[i] = (!reg_sync_word[i]);

            index = 0;
            size_t index2 = 0, index3 = 0;
            uint8_t bit1, bit2, _index, byte;
            for (int i = 0; i < sync_word.size(); ++i)
            {
                for (int j = 7; j >= 0; j = j - 2)
                {
                    //print_bit(get_k_bit_least_significat_from_byte(sync_word[i], j))
                    this->reg_sync_word_perm_00_11[index++] = !get_k_bit_least_significat_from_byte(sync_word[i], j);
                    this->reg_sync_word_perm_00_11[index++] = !get_k_bit_least_significat_from_byte(sync_word[i], j - 1);

                    //00 -> 01
                    bit1 = get_k_bit_least_significat_from_byte(sync_word[i], j);
                    bit2 = get_k_bit_least_significat_from_byte(sync_word[i], j - 1);
                    _index = bit1 * 2 + bit2 * 1;
                    _index = find_index_of_point(_index);
                    byte = gray_code_qpsk[(_index + 1) % 4];
                    this->reg_sync_word_perm_00_01[index2++] = get_k_bit_least_significat_from_byte(byte, 1);
                    this->reg_sync_word_perm_00_01[index2++] = get_k_bit_least_significat_from_byte(byte, 0);

                    //00 -> 10
                    // std::cout << "byte is ";
                    // print_in((_index + 3) % 4);
                    //  std::cout << "\n";
                    byte = gray_code_qpsk[(_index + 3) % 4];
                    // std::cout << "byte im puting: ";
                    // print_in(byte);
                    // std::cout << "\n";
                    this->reg_sync_word_perm_00_10[index3++] = get_k_bit_least_significat_from_byte(byte, 1);
                    this->reg_sync_word_perm_00_10[index3++] = get_k_bit_least_significat_from_byte(byte, 0);
                }
            }

            std::cout << "sync word in bits: " << reg_sync_word << std::endl;
            std::cout << "sync word with inversed bits: " << reg_sync_word_inverse << std::endl;
            std::cout << "sync word with 00 to 11 : " << reg_sync_word_perm_00_11 << std::endl;
            std::cout << "sync word with 00 01 : " << reg_sync_word_perm_00_01 << std::endl;
            std::cout << "sync word with 00 10 bits: " << reg_sync_word_perm_00_10 << std::endl;

            message_port_register_out(pmt::mp("pdu"));
        }

        /*
 * Our virtual destructor.
 */
        frame_sync_impl::~frame_sync_impl()
        {
        }

        frame_sync_impl::sync_fsm_t frame_sync_impl::find_sync_word(shift_reg input)
        {
            //std::cout << "looking for sync word..." << std::endl;

            shift_reg reg = reg_sync_word ^ input;
            //count how many same bits they have
            if (reg.count() == 0)
            {
                std::cout << "found sync word !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << input << std::endl;
                //  std::cout << "found sync word" << input << std::endl;

                return FRAME_LENGTH;
            }
            if (d_mod == BPSK)
            {

                if ((reg_sync_word_inverse ^ input).count() == 0)
                {
                    std::cout << "found sync word inversed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << input << std::endl;
                    bpsk_rotation = INVERSE;
                    return FRAME_LENGTH;
                }
            }

            if (d_mod == QPSK)
            {
                if (bits_seen_so_far == 64 * 8 + 8 * 2)
                {
                    std::cout << input << std::endl;
                }
                if ((reg_sync_word_perm_00_11 ^ input).count() == 0)
                {
                    std::cout << "found sync word _00_11 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << input << std::endl;
                    qpsk_rotation = _00_11;
                    return FRAME_LENGTH;
                }
                else if ((reg_sync_word_perm_00_01 ^ input).count() == 0)
                {
                    std::cout << "found sync word _00_01!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << input << std::endl;
                    qpsk_rotation = _00_01;

                    return FRAME_LENGTH;
                }
                else if ((reg_sync_word_perm_00_10 ^ input).count() == 0)
                {
                    std::cout << "found sync word _00_10!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << input << std::endl;
                    qpsk_rotation = _00_10;

                    return FRAME_LENGTH;
                }
            }
            /*
            if(bits_seen_so_far>=preamble_len*8+ sync_word.size()*8){
                bits_seen_so_far=0;
                std::cout<<" didn't find sync word after preamble len + word size bits" << std::endl;
                return PREAMBLE;
            }*/

            return SYNCWORD;
        }

        frame_sync_impl::sync_fsm_t frame_sync_impl::find_preamble_sequence(shift_reg input)
        {
            shift_reg reg = reg_preamble ^ input;
            //count how many same bits they have
            if (reg.count() == preamble_len * 8 / 2)
            {
                //found 50% right bits from the preamble
                //  std::cout << "input with preamble" << input << std::endl;

                std::cout << "found 50% right bits from the preamble" << std::endl;
                return SYNCWORD;
            }
            return PREAMBLE;
        }

        frame_sync_impl::sync_fsm_t frame_sync_impl::extract_frame_length(shift_reg input)
        {
            if (d_mod == BPSK)
            {
                reg_frame_length[frame_length_index++] = input.back();
                if (frame_length_index == 16)
                {
                    std::cout << "payload length is: " << reg_frame_length << std::endl;
                    frame_length_index = 0;
                    return EXTRACT_PAYLOAD;
                }
                else
                {
                    return FRAME_LENGTH;
                }
            }
            else if (d_mod == QPSK)
            {
                reg_frame_length[frame_length_index++] = input[0];
                reg_frame_length[frame_length_index++] = input[1];

                if (frame_length_index == 16)
                {
                    std::cout << "payload length is: " << reg_frame_length << std::endl;
                    frame_length_index = 0;
                    return EXTRACT_PAYLOAD;
                }
                else
                {
                    return FRAME_LENGTH;
                }
            }
            return FRAME_LENGTH;
        }
        void frame_sync_impl::extra_qpsk_bytes_to_vector(uint8_t byte, std::vector<uint8_t> &reg)
        {
            bool b1 = get_k_bit_least_significat_from_byte(byte, 0);
            bool b2 = get_k_bit_least_significat_from_byte(byte, 1);
            uint8_t index, _index;

            index = b1 * 2 + b2 * 1;
            _index = find_index_of_point(index);

            if (qpsk_rotation == _00_01)
            {
                byte = gray_code_qpsk[(_index + 1) % 4];

                reg.push_back(get_k_bit_least_significat_from_byte(byte, 0));
                reg.push_back(get_k_bit_least_significat_from_byte(byte, 1));
            }
            else if (qpsk_rotation == _00_11)
            {
                reg.push_back(!b2);
                reg.push_back(!b1);
            }
            else if (qpsk_rotation == _00_10)
            {
                byte = gray_code_qpsk[(_index + 3) % 4];
                reg.push_back(get_k_bit_least_significat_from_byte(byte, 0));
                reg.push_back(get_k_bit_least_significat_from_byte(byte, 1));
            }
            else
            {
                reg.push_back(b2);
                reg.push_back(b1);
            }

            /*   if (byte == 0)
            {

                reg.push_back(0);
                reg.push_back(0);
            }
            else if (byte == 1)
            {
                reg.push_back(0);
                reg.push_back(1);
            }
            else if (byte == 2)
            {

                reg.push_back(1);
                reg.push_back(0);
            }
            else
            {
                reg.push_back(1);
                reg.push_back(1);
            }*/
        }
        void frame_sync_impl::extra_qpsk_bytes(uint8_t byte, shift_reg &reg)
        {
            bool b1 = get_k_bit_least_significat_from_byte(byte, 0);
            bool b2 = get_k_bit_least_significat_from_byte(byte, 1);
            uint8_t index, _index;

            index = b1 * 2 + b2 * 1;
            _index = find_index_of_point(index);

            if (qpsk_rotation == _00_01)
            {
                byte = gray_code_qpsk[(_index + 1) % 4];
                reg.push_back(get_k_bit_least_significat_from_byte(byte, 0));
                reg.push_back(get_k_bit_least_significat_from_byte(byte, 1));
            }
            else if (qpsk_rotation == _00_11)
            {
                reg.push_back(!b2);
                reg.push_back(!b1);
            }
            else if (qpsk_rotation == _00_10)
            {
                byte = gray_code_qpsk[(_index + 3) % 4];
                reg.push_back(get_k_bit_least_significat_from_byte(byte, 0));
                reg.push_back(get_k_bit_least_significat_from_byte(byte, 1));
            }
            else
            {
                reg.push_back(b2);
                reg.push_back(b1);
            }

            /* 
            if (byte == 0)
            {
                reg.push_back(0);
                reg.push_back(0);
            }
            else if (byte == 1)
            {
                reg.push_back(0);
                reg.push_back(1);
            }
            else if (byte == 2)
            {

                reg.push_back(1);
                reg.push_back(0);
            }
            else
            {
                reg.push_back(1);
                reg.push_back(1);
            }*/
        }
        void frame_sync_impl::extra_qpsk_bytesV2(uint8_t byte, shift_reg &reg)
        {
            bool b1 = get_k_bit_least_significat_from_byte(byte, 0);
            bool b2 = get_k_bit_least_significat_from_byte(byte, 1);
            uint8_t index, _index;
            index = b1 * 2 + b2 * 1;

            _index = find_index_of_point(index);

            if (qpsk_rotation == _00_01)
            {
                byte = gray_code_qpsk[(_index + 1) % 4];

                reg.push_front(get_k_bit_least_significat_from_byte(byte, 1));
                reg.push_front(get_k_bit_least_significat_from_byte(byte, 0));
            }
            else if (qpsk_rotation == _00_11)
            {
                reg.push_front(!b1);
                reg.push_front(!b2);
            }
            else if (qpsk_rotation == _00_10)
            {
                byte = gray_code_qpsk[(index + 3) % 4];

                reg.push_front(get_k_bit_least_significat_from_byte(byte, 1));
                reg.push_front(get_k_bit_least_significat_from_byte(byte, 0));
            }
            else
            {
                reg.push_front(b1);
                reg.push_front(b2);
            }
            /* if (byte == 0)
            {

                reg.push_front(0);
                reg.push_front(0);
            }
            else if (byte == 1)
            {
                reg.push_front(1);
                reg.push_front(0);
            }
            else if (byte == 2)
            {

                reg.push_front(0);
                reg.push_front(1);
            }
            else
            {
                reg.push_front(1);
                reg.push_front(1);
            }*/
        }
        int
        frame_sync_impl::work(int noutput_items,
                              gr_vector_const_void_star &input_items,
                              gr_vector_void_star &output_items)
        {
            const uint8_t *in = (const uint8_t *)input_items[0];

            //2048 size of pdu

            for (int i = 0; i < noutput_items; ++i)
            {

                if (action == PREAMBLE)
                {
                    if (d_mod == BPSK)
                    {
                        ++bits_seen_so_far;
                        reg_input.push_back(in[i]);
                    }
                    else if (d_mod == QPSK)
                    {
                        bits_seen_so_far += 2;

                        extra_qpsk_bytes(in[i], reg_input);
                    }
                    action = (this->*sync_fsm[action])(reg_input);
                }
                else if (action == SYNCWORD)
                {
                    if (d_mod == BPSK)
                    {
                        ++bits_seen_so_far;
                        reg_input_sync_word.push_back(in[i]);
                    }
                    else if (d_mod == QPSK)
                    {
                        bits_seen_so_far += 2;
                        extra_qpsk_bytes(in[i], reg_input_sync_word);
                    }

                    action = (this->*sync_fsm[action])(reg_input_sync_word);
                }
                else if (action == FRAME_LENGTH)
                {
                    if (d_mod == BPSK)
                    {
                        if (bpsk_rotation == INVERSE)
                        {

                            reg_input_frame_length.push_back(!in[i]);
                        }
                        else
                        {
                            reg_input_frame_length.push_back(in[i]);
                        }
                    }
                    else if (d_mod == QPSK)
                    {
                        //  print_in(in[i]);
                        extra_qpsk_bytesV2(in[i], reg_input_frame_length);
                    }

                    action = (this->*sync_fsm[action])(reg_input_frame_length);

                    if (action == EXTRACT_PAYLOAD)
                    {
                        std::string str = "";
                        for (int i = 0; i < reg_frame_length.size(); ++i)
                        {
                            if (reg_frame_length[i] == 1)
                            {
                                str += "1";
                            }
                            else
                            {
                                str += "0";
                            }
                        }
                        payload_length = std::stoi(str, 0, 2);
                        std::cout << "payload recieved length in number: " << payload_length << std::endl;
                    }
                }
                else if (action == EXTRACT_PAYLOAD)
                {
                    if (d_mod == BPSK)
                    {
                        if (bpsk_rotation == INVERSE)
                        {
                            payload_in_bits.push_back(!in[i]);
                        }
                        else
                        {
                            payload_in_bits.push_back(in[i]);
                        }
                    }
                    else if (d_mod == QPSK)
                    {
                        extra_qpsk_bytes_to_vector(in[i], payload_in_bits);
                        ++count_frames;
                    }

                    ++count_frames;
                    if (count_frames == payload_length * 8)
                    {
                        std::cout << "payload payload_in_bits size (bits)... " << payload_in_bits.size() << std::endl;

                        std::cout << "payload extracted (bits)... " << count_frames << std::endl;

                        action = SEND_PAYLOAD;
                    }
                }
                else if (action == SEND_PAYLOAD)
                {
                    std::string str = "";

                    for (int i = 0; i < payload_in_bits.size(); ++i)
                    {
                        if (i != 0 && i % 8 == 0)
                        {
                            uint8_t byte = (uint8_t)std::stoi(str, 0, 2);
                            //  printf("%02hhx ", byte);
                            payload_in_bytes.push_back(byte);
                            // std::cout << "lalalalala" << std::endl;

                            //std::cout << str<<std::endl;

                            str = "";
                        }
                        if (payload_in_bits[i] == 1)
                        {
                            str += "1";
                        }
                        else
                        {
                            str += "0";
                        }
                    }

                    std::cout << "string: " << str << std::endl;
                    uint8_t byte = (uint8_t)std::stoi(str, 0, 2);
                    payload_in_bytes.push_back(byte);

                    std::cout << "payload size (in bytes) to send: " << payload_in_bytes.size() << std::endl;

                    pmt::pmt_t pair = pmt::cons(pmt::PMT_NIL, pmt::init_u8vector(payload_in_bytes.size(), payload_in_bytes));
                    action = PREAMBLE;

                    // std::cout << reg_input << std::endl;
                    //  exit(1);

                    message_port_pub(pmt::mp("pdu"), pair);
                    std::cout << "=====================END OF PACKET===================" << std::endl;

                    //make the clears
                    reg_input_sync_word.reset();
                    reg_input_frame_length.reset();

                    payload_in_bytes.clear();
                    payload_in_bits.clear();

                    count_frames = 0;
                    payload_length = 0;
                    frame_length_index = 0;
                    bits_seen_so_far = 0;
                    str = "";
                }
            }

            return noutput_items;
        }

    } /* namespace cs330project */
} /* namespace gr */

/*

    reg_input.push_front(in[i]);
                if (i == 72)
                {
                    for (int j = 0; j < 16; j++)
                    {
                        if (in[i-8 + j] == 0)
                        {
                            std::cout << "0";
                        }
                        else
                        {
                            std::cout << "1";
                        }
                    }
                }


*/

/* for (int i = 64 * 8; i < 64 * 8 + 16; i++)
            {
                std::cout << reg_input[i] << std::endl;
            }*/

//std::cout << reg_input << std::endl;
/*
            for (int i = 0; i < noutput_items; ++i)
            {
                // action = (this->*sync_fsm[action])(reg_input);
                std::cout << reg_input[i];

                if (i != 0 && i % 8 == 0)
                {

                    std::cout << "\n==================================" << std::endl;
                }
            }*/