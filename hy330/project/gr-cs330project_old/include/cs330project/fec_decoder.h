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

#ifndef INCLUDED_CS330PROJECT_FEC_DECODER_H
#define INCLUDED_CS330PROJECT_FEC_DECODER_H

#include <cs330project/api.h>
#include <gnuradio/block.h>

namespace gr {
namespace cs330project {

/*!
 * \brief Decodes a received message with one of the available FEC algorithms
 * The FEC types are:
 *  0: No FEC
 *  1: Hamming triple repetition
 *  2: Golay (12, 24)
 * \ingroup cs330project
 *
 */
class CS330PROJECT_API fec_decoder : virtual public gr::block {
public:
    typedef boost::shared_ptr<fec_decoder> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of cs330project::fec_encoder.
     *
     * To avoid accidental use of raw pointers, cs330project::fec_encoder's
     * constructor is in a private implementation
     * class. cs330project::fec_encoder::make is the public interface for
     * creating new instances.
     */
    static sptr make(int type = 0);
};

} // namespace cs330project
} // namespace gr

#endif /* INCLUDED_CS330PROJECT_FEC_DECODER_H */
