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

#ifndef INCLUDED_CS330PROJECT_FRAME_SYNC_H
#define INCLUDED_CS330PROJECT_FRAME_SYNC_H

#include <cs330project/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace cs330project {

/*!
 * \brief This block searches for a valid preamble. Using then the
 * synchronization word it extracts the received frame.
 *
 * The based on the frame length field it extracts the rest of the payload.
 *
 * The block produces a PMT pair message, compliant with the pair messages
 * GNU Radio uses, containing only the payload of the
 * frame (without preamble, sync word, length field)
 * \ingroup cs330project
 *
 */
class CS330PROJECT_API frame_sync : virtual public gr::sync_block {
public:
    typedef boost::shared_ptr<frame_sync> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of cs330project::frame_sync.
     *
     * To avoid accidental use of raw pointers, cs330project::frame_sync's
     * constructor is in a private implementation
     * class. cs330project::frame_sync::make is the public interface for
     * creating new instances.
     */
    static sptr make(uint8_t preamble, uint8_t preamble_len,
                     const std::vector<uint8_t> &sync_word,
                     int mod);
};

} // namespace cs330project
} // namespace gr

#endif /* INCLUDED_CS330PROJECT_FRAME_SYNC_H */
