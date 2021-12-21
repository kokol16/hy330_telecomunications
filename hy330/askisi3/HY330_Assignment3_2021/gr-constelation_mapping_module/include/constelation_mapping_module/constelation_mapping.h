/* -*- c++ -*- */
/*
 * Copyright 2021 gkokol.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_CONSTELATION_MAPPING_MODULE_CONSTELATION_MAPPING_H
#define INCLUDED_CONSTELATION_MAPPING_MODULE_CONSTELATION_MAPPING_H

#include <constelation_mapping_module/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace constelation_mapping_module {

    /*!
     * \brief <+description of block+>
     * \ingroup constelation_mapping_module
     *
     */
    class CONSTELATION_MAPPING_MODULE_API constelation_mapping : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<constelation_mapping> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of constelation_mapping_module::constelation_mapping.
       *
       * To avoid accidental use of raw pointers, constelation_mapping_module::constelation_mapping's
       * constructor is in a private implementation
       * class. constelation_mapping_module::constelation_mapping::make is the public interface for
       * creating new instances.
       */
      static sptr make(int _k);
    };

  } // namespace constelation_mapping_module
} // namespace gr

#endif /* INCLUDED_CONSTELATION_MAPPING_MODULE_CONSTELATION_MAPPING_H */

