/* -*- c++ -*- */
/*
 * gr-satnogs: SatNOGS GNU Radio Out-Of-Tree Module
 *
 *  Copyright (C) 2018, Libre Space Foundation <http://librespacefoundation.org/>
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

#ifndef INCLUDED_SATNOGS_SHIFT_REG_H
#define INCLUDED_SATNOGS_SHIFT_REG_H

#include <cs330project/api.h>
#include <deque>
#include <ostream>

namespace gr
{
    namespace cs330project
    {

        /*!
 * \brief Implements a bit shift register
 *
 */
        class CS330PROJECT_API shift_reg
        {
        public:
            shift_reg(size_t len);
       //     shift_reg();

            ~shift_reg();

            void
            reset();

            void
            set();

            size_t
            len() const;

            size_t
            size() const;

            size_t
            count();

            shift_reg
            operator|(const shift_reg &rhs);

            shift_reg
            operator&(const shift_reg &rhs);

            shift_reg
            operator^(const shift_reg &rhs);

            shift_reg &
            operator>>=(bool bit);

            bool &
            operator[](size_t pos);

            bool
            operator[](size_t pos) const;

            shift_reg &
            operator<<=(bool bit);

            void
            push_front(bool bit);

            void
            push_back(bool bit);

            bool
            front();

            bool
            back();

            friend std::ostream &
            operator<<(std::ostream &os, const shift_reg &reg);

        private:
            const size_t d_len;
            std::deque<bool> d_reg;
        };

    } // namespace cs330project
} // namespace gr

#endif /* INCLUDED_CS330PROJECT_SHIFT_REG_H */
