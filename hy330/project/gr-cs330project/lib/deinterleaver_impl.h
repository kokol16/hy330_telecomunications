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

#ifndef INCLUDED_CS330PROJECT_DEINTERLEAVER_IMPL_H
#define INCLUDED_CS330PROJECT_DEINTERLEAVER_IMPL_H

#include <cs330project/deinterleaver.h>

namespace gr {
namespace cs330project {

class deinterleaver_impl : public deinterleaver {
private:
    void deinterleave(pmt::pmt_t m);

public:
    deinterleaver_impl(size_t block_size);
    ~deinterleaver_impl();

};

} // namespace cs330project
} // namespace gr

#endif /* INCLUDED_CS330PROJECT_DEINTERLEAVER_IMPL_H */
