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

#ifndef INCLUDED_CS330PROJECT_FRAMER_IMPL_H
#define INCLUDED_CS330PROJECT_FRAMER_IMPL_H

#include <cs330project/framer.h>

namespace gr
{
    namespace cs330project
    {

        class framer_impl : public framer
        {
        private:
            void
            construct(pmt::pmt_t m);
            std::vector<uint8_t> payload;
            uint8_t preamble;
            size_t preamble_len;
            std::vector<uint8_t> sync_word;

        public:
            framer_impl(uint8_t preamble, size_t preamble_len,
                        const std::vector<uint8_t> &sync_word);
            ~framer_impl();
        };

    } // namespace cs330project
} // namespace gr

#endif /* INCLUDED_CS330PROJECT_FRAMER_IMPL_H */
