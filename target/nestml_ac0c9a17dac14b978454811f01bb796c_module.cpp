
/*
*  nestml_ac0c9a17dac14b978454811f01bb796c_module.cpp
*
*  This file is part of NEST.
*
*  Copyright (C) 2004 The NEST Initiative
*
*  NEST is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 2 of the License, or
*  (at your option) any later version.
*
*  NEST is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
*
*  Generated from NESTML 8.2.0 at time: 2026-11-20 10:26:26.077217
*/

// Include from NEST
#include "nest_extension_interface.h"

// include headers with your own stuff


#include "hh_mntb_kv31_neuron_nestml.h"



class nestml_ac0c9a17dac14b978454811f01bb796c_module : public nest::NESTExtensionInterface
{
  public:
    nestml_ac0c9a17dac14b978454811f01bb796c_module() {}
    ~nestml_ac0c9a17dac14b978454811f01bb796c_module() {}

    void initialize() override;
};

nestml_ac0c9a17dac14b978454811f01bb796c_module nestml_ac0c9a17dac14b978454811f01bb796c_module_LTX_module;

void nestml_ac0c9a17dac14b978454811f01bb796c_module::initialize()
{
    // register neurons
    register_hh_mntb_kv31_neuron_nestml("hh_mntb_kv31_neuron_nestml");
}
