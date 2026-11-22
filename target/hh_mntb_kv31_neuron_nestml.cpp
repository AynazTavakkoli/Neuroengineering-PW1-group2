
/*
 *  hh_mntb_kv31_neuron_nestml.cpp
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
 *  Generated from NESTML 8.2.0 at time: 2026-11-20 11:26:22.896023
**/

// C++ includes:
#include <limits>

// Includes from libnestutil:
#include "numerics.h"

// Includes from nestkernel:
#include "exceptions.h"
#include "kernel_manager.h"
#include "nest_impl.h"
#include "universal_data_logger_impl.h"

// Includes from sli:
#include "dict.h"
#include "dictutils.h"
#include "doubledatum.h"
#include "integerdatum.h"
#include "lockptrdatum.h"

#include "hh_mntb_kv31_neuron_nestml.h"

// uncomment the next line to enable printing of detailed debug information
// #define DEBUG
void
register_hh_mntb_kv31_neuron_nestml( const std::string& name )
{
  nest::register_node_model< hh_mntb_kv31_neuron_nestml >( name );
}

// ---------------------------------------------------------------------------
//   Recordables map
// ---------------------------------------------------------------------------
nest::RecordablesMap<hh_mntb_kv31_neuron_nestml> hh_mntb_kv31_neuron_nestml::recordablesMap_;
namespace nest
{

  // Override the create() method with one call to RecordablesMap::insert_()
  // for each quantity to be recorded.
template <> void RecordablesMap<hh_mntb_kv31_neuron_nestml>::create()
  {
    // add state variables to recordables map
   insert_(hh_mntb_kv31_neuron_nestml_names::_V_m, &hh_mntb_kv31_neuron_nestml::get_V_m);
   insert_(hh_mntb_kv31_neuron_nestml_names::_Act_n, &hh_mntb_kv31_neuron_nestml::get_Act_n);
   insert_(hh_mntb_kv31_neuron_nestml_names::_Inact_p, &hh_mntb_kv31_neuron_nestml::get_Inact_p);
   insert_(hh_mntb_kv31_neuron_nestml_names::_Act_l, &hh_mntb_kv31_neuron_nestml::get_Act_l);
   insert_(hh_mntb_kv31_neuron_nestml_names::_Inact_r, &hh_mntb_kv31_neuron_nestml::get_Inact_r);
   insert_(hh_mntb_kv31_neuron_nestml_names::_Act_m, &hh_mntb_kv31_neuron_nestml::get_Act_m);
   insert_(hh_mntb_kv31_neuron_nestml_names::_Inact_h, &hh_mntb_kv31_neuron_nestml::get_Inact_h);
   insert_(hh_mntb_kv31_neuron_nestml_names::_K_syn_exc__X__exc_spikes, &hh_mntb_kv31_neuron_nestml::get_K_syn_exc__X__exc_spikes);
   insert_(hh_mntb_kv31_neuron_nestml_names::_K_syn_exc__X__exc_spikes__d, &hh_mntb_kv31_neuron_nestml::get_K_syn_exc__X__exc_spikes__d);
   insert_(hh_mntb_kv31_neuron_nestml_names::_K_syn_inh__X__inh_spikes, &hh_mntb_kv31_neuron_nestml::get_K_syn_inh__X__inh_spikes);
   insert_(hh_mntb_kv31_neuron_nestml_names::_K_syn_inh__X__inh_spikes__d, &hh_mntb_kv31_neuron_nestml::get_K_syn_inh__X__inh_spikes__d);
    // add recordable inline expressions to recordables map
	insert_(hh_mntb_kv31_neuron_nestml_names::_I_Kv3, &hh_mntb_kv31_neuron_nestml::get_I_Kv3);
	insert_(hh_mntb_kv31_neuron_nestml_names::_I_LT, &hh_mntb_kv31_neuron_nestml::get_I_LT);
	insert_(hh_mntb_kv31_neuron_nestml_names::_I_Na, &hh_mntb_kv31_neuron_nestml::get_I_Na);
	insert_(hh_mntb_kv31_neuron_nestml_names::_I_L, &hh_mntb_kv31_neuron_nestml::get_I_L);

    // Add vector variables  
  }
}
std::vector< std::tuple< int, int > > hh_mntb_kv31_neuron_nestml::rport_to_nestml_buffer_idx =
{
  
  { hh_mntb_kv31_neuron_nestml::EXC_SPIKES, hh_mntb_kv31_neuron_nestml::INH_SPIKES },
};

// ---------------------------------------------------------------------------
//   Default constructors defining default parameters and state
//   Note: the implementation is empty. The initialization is of variables
//   is a part of hh_mntb_kv31_neuron_nestml's constructor.
// ---------------------------------------------------------------------------

hh_mntb_kv31_neuron_nestml::Parameters_::Parameters_()
{
}

hh_mntb_kv31_neuron_nestml::State_::State_()
{
}

// ---------------------------------------------------------------------------
//   Parameter and state extractions and manipulation functions
// ---------------------------------------------------------------------------

hh_mntb_kv31_neuron_nestml::Buffers_::Buffers_(hh_mntb_kv31_neuron_nestml &n):
  logger_(n)
  , spike_inputs_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_inputs_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , continuous_inputs_( std::vector< nest::RingBuffer >( NUM_CONTINUOUS_INPUT_PORTS ) )
  , continuous_inputs_grid_sum_( std::vector< double >( NUM_CONTINUOUS_INPUT_PORTS ) )
  , __s( nullptr ), __c( nullptr ), __e( nullptr )
{
  // Initialization of the remaining members is deferred to init_buffers_().
}

hh_mntb_kv31_neuron_nestml::Buffers_::Buffers_(const Buffers_ &, hh_mntb_kv31_neuron_nestml &n):
  logger_(n)
  , spike_inputs_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_inputs_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_( std::vector< nest::RingBuffer >( NUM_SPIKE_RECEPTORS ) )
  , spike_input_received_grid_sum_( std::vector< double >( NUM_SPIKE_RECEPTORS ) )
  , continuous_inputs_( std::vector< nest::RingBuffer >( NUM_CONTINUOUS_INPUT_PORTS ) )
  , continuous_inputs_grid_sum_( std::vector< double >( NUM_CONTINUOUS_INPUT_PORTS ) )
  , __s( nullptr ), __c( nullptr ), __e( nullptr )
{
  // Initialization of the remaining members is deferred to init_buffers_().
}

// ---------------------------------------------------------------------------
//   Default constructor for node
// ---------------------------------------------------------------------------

hh_mntb_kv31_neuron_nestml::hh_mntb_kv31_neuron_nestml():StructuralPlasticityNode(), P_(), S_(), B_(*this)
{
  init_state_internal_();
  recordablesMap_.create();
  pre_run_hook();
}

// ---------------------------------------------------------------------------
//   Copy constructor for node
// ---------------------------------------------------------------------------

hh_mntb_kv31_neuron_nestml::hh_mntb_kv31_neuron_nestml(const hh_mntb_kv31_neuron_nestml& __n):
  StructuralPlasticityNode(), P_(__n.P_), S_(__n.S_), B_(__n.B_, *this)
{
  // copy parameter struct P_
  P_.C_m = __n.P_.C_m;
  P_.g_Na = __n.P_.g_Na;
  P_.g_LT = __n.P_.g_LT;
  P_.g_Kv3 = __n.P_.g_Kv3;
  P_.g_L = __n.P_.g_L;
  P_.E_K = __n.P_.E_K;
  P_.E_Na = __n.P_.E_Na;
  P_.E_L = __n.P_.E_L;
  P_.gamma_Kv3 = __n.P_.gamma_Kv3;
  P_.V_spike_th = __n.P_.V_spike_th;
  P_.refr_T = __n.P_.refr_T;
  P_.tau_syn_exc = __n.P_.tau_syn_exc;
  P_.tau_syn_inh = __n.P_.tau_syn_inh;
  P_.I_e = __n.P_.I_e;

  // copy state struct S_
  S_.ode_state[State_::V_m] = __n.S_.ode_state[State_::V_m];
  S_.ode_state[State_::Act_n] = __n.S_.ode_state[State_::Act_n];
  S_.ode_state[State_::Inact_p] = __n.S_.ode_state[State_::Inact_p];
  S_.ode_state[State_::Act_l] = __n.S_.ode_state[State_::Act_l];
  S_.ode_state[State_::Inact_r] = __n.S_.ode_state[State_::Inact_r];
  S_.ode_state[State_::Act_m] = __n.S_.ode_state[State_::Act_m];
  S_.ode_state[State_::Inact_h] = __n.S_.ode_state[State_::Inact_h];
  S_.refr_count = __n.S_.refr_count;
  S_.ode_state[State_::K_syn_exc__X__exc_spikes] = __n.S_.ode_state[State_::K_syn_exc__X__exc_spikes];
  S_.ode_state[State_::K_syn_exc__X__exc_spikes__d] = __n.S_.ode_state[State_::K_syn_exc__X__exc_spikes__d];
  S_.ode_state[State_::K_syn_inh__X__inh_spikes] = __n.S_.ode_state[State_::K_syn_inh__X__inh_spikes];
  S_.ode_state[State_::K_syn_inh__X__inh_spikes__d] = __n.S_.ode_state[State_::K_syn_inh__X__inh_spikes__d];

  // copy internals V_
  V_.refr_counts = __n.V_.refr_counts;
  V_.__h = __n.V_.__h;
  V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes = __n.V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes;
  V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes__d = __n.V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes__d;
  V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes = __n.V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes;
  V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes__d = __n.V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes__d;
  V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes = __n.V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes;
  V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes__d = __n.V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes__d;
  V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes = __n.V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes;
  V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes__d = __n.V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes__d;
}

// ---------------------------------------------------------------------------
//   Destructor for node
// ---------------------------------------------------------------------------

hh_mntb_kv31_neuron_nestml::~hh_mntb_kv31_neuron_nestml()
{
  // GSL structs may not have been allocated, so we need to protect destruction

  if (B_.__s)
  {
    gsl_odeiv_step_free( B_.__s );
  }

  if (B_.__c)
  {
    gsl_odeiv_control_free( B_.__c );
  }

  if (B_.__e)
  {
    gsl_odeiv_evolve_free( B_.__e );
  }
}

// ---------------------------------------------------------------------------
//   Node initialization functions
// ---------------------------------------------------------------------------
void hh_mntb_kv31_neuron_nestml::calibrate_time( const nest::TimeConverter& tc )
{
  LOG( nest::M_WARNING,
    "hh_mntb_kv31_neuron_nestml",
    "Simulation resolution has changed. Internal state and parameters of the model have been reset!" );

  init_state_internal_();
}
void hh_mntb_kv31_neuron_nestml::init_state_internal_()
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] hh_mntb_kv31_neuron_nestml::init_state_internal_()" << std::endl;
#endif

  const double __timestep = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the timestep() function
  // by default, integrate all variables with a conservative tolerance, in the sense that we err on the side of integrating very precisely at the expense of extra computation
  P_.__gsl_abs_error_tol = 1e-6;
  P_.__gsl_rel_error_tol = 1e-6;
  // initial values for parameters
  P_.C_m = 10; // as pF
  P_.g_Na = 500; // as nS
  P_.g_LT = 20; // as nS
  P_.g_Kv3 = 150; // as nS
  P_.g_L = 2; // as nS
  P_.E_K = (-80); // as mV
  P_.E_Na = 50; // as mV
  P_.E_L = (-63); // as mV
  P_.gamma_Kv3 = 0.2; // as real
  P_.V_spike_th = (-10); // as mV
  P_.refr_T = 0.5; // as ms
  P_.tau_syn_exc = 0.2; // as ms
  P_.tau_syn_inh = 2.0; // as ms
  P_.I_e = 0; // as pA

  V_.__h = nest::Time::get_resolution().get_ms();
  recompute_internal_variables();
  // initial values for state variables
  S_.ode_state[State_::V_m] = (-64.5); // as mV
  S_.ode_state[State_::Act_n] = 0.0945; // as real
  S_.ode_state[State_::Inact_p] = 1.0; // as real
  S_.ode_state[State_::Act_l] = 0.0661; // as real
  S_.ode_state[State_::Inact_r] = 0.4475; // as real
  S_.ode_state[State_::Act_m] = 0.0595; // as real
  S_.ode_state[State_::Inact_h] = 0.6728; // as real
  S_.refr_count = 0; // as integer
  S_.ode_state[State_::K_syn_exc__X__exc_spikes] = 0; // as real
  S_.ode_state[State_::K_syn_exc__X__exc_spikes__d] = 0; // as 1 / s
  S_.ode_state[State_::K_syn_inh__X__inh_spikes] = 0; // as real
  S_.ode_state[State_::K_syn_inh__X__inh_spikes__d] = 0; // as 1 / s
}

void hh_mntb_kv31_neuron_nestml::init_buffers_()
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] hh_mntb_kv31_neuron_nestml::init_buffers_()" << std::endl;
#endif
  // spike input buffers
  get_spike_inputs_().clear();
  get_spike_inputs_grid_sum_().clear();
  get_spike_input_received_().clear();
  get_spike_input_received_grid_sum_().clear();
  get_continuous_inputs_().clear();
  get_continuous_inputs_grid_sum_().clear();


  B_.logger_.reset();



  if ( not B_.__s )
  {
    B_.__s = gsl_odeiv_step_alloc( gsl_odeiv_step_rkf45, State_::STATE_VEC_SIZE );
  }
  else
  {
    gsl_odeiv_step_reset( B_.__s );
  }

  if ( not B_.__c )
  {
    B_.__c = gsl_odeiv_control_y_new( P_.__gsl_abs_error_tol, P_.__gsl_rel_error_tol );
  }
  else
  {
    gsl_odeiv_control_init( B_.__c, P_.__gsl_abs_error_tol, P_.__gsl_rel_error_tol, 1.0, 0.0 );

  }

  if ( not B_.__e )
  {
    B_.__e = gsl_odeiv_evolve_alloc( State_::STATE_VEC_SIZE );
  }
  else
  {
    gsl_odeiv_evolve_reset( B_.__e );
  }

  // B_.__sys.function = hh_mntb_kv31_neuron_nestml_dynamics; // will be set just prior to the call to gsl_odeiv_evolve_apply()
  B_.__sys.jacobian = nullptr;
  B_.__sys.dimension = State_::STATE_VEC_SIZE;
  B_.__sys.params = reinterpret_cast< void* >( this );
  B_.__step = nest::Time::get_resolution().get_ms();
  B_.__integration_step = nest::Time::get_resolution().get_ms();
}

void hh_mntb_kv31_neuron_nestml::recompute_internal_variables(bool exclude_timestep)
{
  const double __timestep = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the timestep() function

  if (exclude_timestep)
  {    
    V_.refr_counts = nest::Time(nest::Time::ms((double) (P_.refr_T))).get_steps(); // as integer
    V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes = 1.0 * V_.__h * std::exp((-V_.__h) / P_.tau_syn_exc) / P_.tau_syn_exc + 1.0 * std::exp((-V_.__h) / P_.tau_syn_exc); // as real
    V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes__d = 1.0 * V_.__h * std::exp((-V_.__h) / P_.tau_syn_exc); // as real
    V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes = (-1.0) * V_.__h * std::exp((-V_.__h) / P_.tau_syn_exc) / pow(P_.tau_syn_exc, 2); // as real
    V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes__d = (-1.0) * V_.__h * std::exp((-V_.__h) / P_.tau_syn_exc) / P_.tau_syn_exc + 1.0 * std::exp((-V_.__h) / P_.tau_syn_exc); // as real
    V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes = 1.0 * V_.__h * std::exp((-V_.__h) / P_.tau_syn_inh) / P_.tau_syn_inh + 1.0 * std::exp((-V_.__h) / P_.tau_syn_inh); // as real
    V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes__d = 1.0 * V_.__h * std::exp((-V_.__h) / P_.tau_syn_inh); // as real
    V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes = (-1.0) * V_.__h * std::exp((-V_.__h) / P_.tau_syn_inh) / pow(P_.tau_syn_inh, 2); // as real
    V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes__d = (-1.0) * V_.__h * std::exp((-V_.__h) / P_.tau_syn_inh) / P_.tau_syn_inh + 1.0 * std::exp((-V_.__h) / P_.tau_syn_inh); // as real
  }
  else {    
    V_.refr_counts = nest::Time(nest::Time::ms((double) (P_.refr_T))).get_steps(); // as integer
    V_.__h = nest::Time::get_resolution().get_ms(); // as ms
    V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes = 1.0 * V_.__h * std::exp((-V_.__h) / P_.tau_syn_exc) / P_.tau_syn_exc + 1.0 * std::exp((-V_.__h) / P_.tau_syn_exc); // as real
    V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes__d = 1.0 * V_.__h * std::exp((-V_.__h) / P_.tau_syn_exc); // as real
    V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes = (-1.0) * V_.__h * std::exp((-V_.__h) / P_.tau_syn_exc) / pow(P_.tau_syn_exc, 2); // as real
    V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes__d = (-1.0) * V_.__h * std::exp((-V_.__h) / P_.tau_syn_exc) / P_.tau_syn_exc + 1.0 * std::exp((-V_.__h) / P_.tau_syn_exc); // as real
    V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes = 1.0 * V_.__h * std::exp((-V_.__h) / P_.tau_syn_inh) / P_.tau_syn_inh + 1.0 * std::exp((-V_.__h) / P_.tau_syn_inh); // as real
    V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes__d = 1.0 * V_.__h * std::exp((-V_.__h) / P_.tau_syn_inh); // as real
    V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes = (-1.0) * V_.__h * std::exp((-V_.__h) / P_.tau_syn_inh) / pow(P_.tau_syn_inh, 2); // as real
    V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes__d = (-1.0) * V_.__h * std::exp((-V_.__h) / P_.tau_syn_inh) / P_.tau_syn_inh + 1.0 * std::exp((-V_.__h) / P_.tau_syn_inh); // as real
  }
}
void hh_mntb_kv31_neuron_nestml::pre_run_hook()
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] hh_mntb_kv31_neuron_nestml::pre_run_hook()" << std::endl;
#endif

  B_.logger_.init();

  // parameters might have changed -- recompute internals
  V_.__h = nest::Time::get_resolution().get_ms();
  recompute_internal_variables();

  // buffers B_
  B_.spike_inputs_.resize(NUM_SPIKE_RECEPTORS);
  B_.spike_inputs_grid_sum_.resize(NUM_SPIKE_RECEPTORS);
  B_.spike_input_received_.resize(NUM_SPIKE_RECEPTORS);
  B_.spike_input_received_grid_sum_.resize(NUM_SPIKE_RECEPTORS);
  B_.continuous_inputs_.resize(NUM_CONTINUOUS_INPUT_PORTS);
  B_.continuous_inputs_grid_sum_.resize(NUM_CONTINUOUS_INPUT_PORTS);

}

// ---------------------------------------------------------------------------
//   Update and spike handling functions
// ---------------------------------------------------------------------------

extern "C" inline int hh_mntb_kv31_neuron_nestml_dynamics(double __time, const double ode_state[], double f[], void* pnode)
{
  typedef hh_mntb_kv31_neuron_nestml::State_ State_;
  // get access to node so we can almost work as in a member function
  assert( pnode );
  const hh_mntb_kv31_neuron_nestml& node = *( reinterpret_cast< hh_mntb_kv31_neuron_nestml* >( pnode ) );
  constexpr int I_STIM = hh_mntb_kv31_neuron_nestml::I_STIM;

  // ode_state[] here is---and must be---the state vector supplied by the integrator,
  // not the state vector in the node, node.S_.ode_state[].


  f[State_::Act_n] = (-0.1974) * ode_state[State_::Act_n] + 0.2719 * (1 - ode_state[State_::Act_n]) * std::exp(0.04 * ode_state[State_::V_m]);
  f[State_::Inact_p] = (-0.0935) * ode_state[State_::Inact_p] * std::exp(0.0058 * ode_state[State_::V_m]) + 0.00713 * (1 - ode_state[State_::Inact_p]) * std::exp((-0.1942) * ode_state[State_::V_m]);
  f[State_::Act_l] = (-0.2248) * ode_state[State_::Act_l] * std::exp((-0.0319) * ode_state[State_::V_m]) + 1.2 * (1 - ode_state[State_::Act_l]) * std::exp(0.03512 * ode_state[State_::V_m]);
  f[State_::Inact_r] = (-0.0562) * ode_state[State_::Inact_r] * std::exp((-0.0047) * ode_state[State_::V_m]) + 0.0438 * (1 - ode_state[State_::Inact_r]) * std::exp((-0.0053) * ode_state[State_::V_m]);
  f[State_::Act_m] = (-6.93) * ode_state[State_::Act_m] * std::exp((-0.043) * ode_state[State_::V_m]) + 76.4 * (1 - ode_state[State_::Act_m]) * std::exp(0.037 * ode_state[State_::V_m]);
  f[State_::Inact_h] = (-7.87) * ode_state[State_::Inact_h] * std::exp(0.0691 * ode_state[State_::V_m]) + 0.000533 * (1 - ode_state[State_::Inact_h]) * std::exp((-0.0909) * ode_state[State_::V_m]);
  f[State_::V_m] = ((-ode_state[State_::Act_l]) * ode_state[State_::Inact_r] * node.P_.g_LT * ((-node.P_.E_K) + ode_state[State_::V_m]) - pow(ode_state[State_::Act_m], 3) * ode_state[State_::Inact_h] * node.P_.g_Na * ((-node.P_.E_Na) + ode_state[State_::V_m]) - pow(ode_state[State_::Act_n], 3) * node.P_.g_Kv3 * ((-node.P_.E_K) + ode_state[State_::V_m]) * (ode_state[State_::Inact_p] * node.P_.gamma_Kv3 - node.P_.gamma_Kv3 + 1) + node.P_.I_e + node.B_.continuous_inputs_grid_sum_[I_STIM] + ode_state[State_::K_syn_exc__X__exc_spikes] - ode_state[State_::K_syn_inh__X__inh_spikes] - node.P_.g_L * ((-node.P_.E_L) + ode_state[State_::V_m])) / node.P_.C_m;
  f[State_::K_syn_exc__X__exc_spikes] = 1.0 * ode_state[State_::K_syn_exc__X__exc_spikes__d];
  f[State_::K_syn_exc__X__exc_spikes__d] = (-ode_state[State_::K_syn_exc__X__exc_spikes]) / pow(node.P_.tau_syn_exc, 2) - 2 * ode_state[State_::K_syn_exc__X__exc_spikes__d] / node.P_.tau_syn_exc;
  f[State_::K_syn_inh__X__inh_spikes] = 1.0 * ode_state[State_::K_syn_inh__X__inh_spikes__d];
  f[State_::K_syn_inh__X__inh_spikes__d] = (-ode_state[State_::K_syn_inh__X__inh_spikes]) / pow(node.P_.tau_syn_inh, 2) - 2 * ode_state[State_::K_syn_inh__X__inh_spikes__d] / node.P_.tau_syn_inh;
  return GSL_SUCCESS;
}
void hh_mntb_kv31_neuron_nestml::update(nest::Time const & origin, const long from, const long to)
{
  const double __timestep = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the timestep() function

  for ( long lag = from ; lag < to ; ++lag )
  {


    auto get_t = [origin, lag](){ return nest::Time( nest::Time::step( origin.get_steps() + lag + 1) ).get_ms(); };

#ifdef DEBUG
    std::cout << "[neuron " << this << "] hh_mntb_kv31_neuron_nestml::update: handling post spike at t = " << get_t() << std::endl;
#endif
    /**
     * buffer spikes from spiking input ports
    **/

    for (long i = 0; i < NUM_SPIKE_RECEPTORS; ++i)
    {
      get_spike_inputs_grid_sum_()[i] = get_spike_inputs_()[i].get_value(lag);
      get_spike_input_received_grid_sum_()[i] = get_spike_input_received_()[i].get_value(lag);
    }

    /**
     * subthreshold updates of the convolution variables
     *
     * step 1: regardless of whether and how integrate_odes() will be called, update variables due to convolutions
    **/

    const double K_syn_exc__X__exc_spikes__tmp_ = S_.ode_state[State_::K_syn_exc__X__exc_spikes] * V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes + S_.ode_state[State_::K_syn_exc__X__exc_spikes__d] * V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes__d;
    const double K_syn_exc__X__exc_spikes__d__tmp_ = S_.ode_state[State_::K_syn_exc__X__exc_spikes] * V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes + S_.ode_state[State_::K_syn_exc__X__exc_spikes__d] * V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes__d;
    const double K_syn_inh__X__inh_spikes__tmp_ = S_.ode_state[State_::K_syn_inh__X__inh_spikes] * V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes + S_.ode_state[State_::K_syn_inh__X__inh_spikes__d] * V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes__d;
    const double K_syn_inh__X__inh_spikes__d__tmp_ = S_.ode_state[State_::K_syn_inh__X__inh_spikes] * V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes + S_.ode_state[State_::K_syn_inh__X__inh_spikes__d] * V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes__d;


    /**
     * Begin NESTML generated code for the update block(s)
    **/

  double V_m_old = S_.ode_state[State_::V_m];

  // start rendered code for integrate_odes()

  // analytic solver: integrating state variables (first step): K_syn_exc__X__exc_spikes, K_syn_exc__X__exc_spikes__d, K_syn_inh__X__inh_spikes, K_syn_inh__X__inh_spikes__d
  const double K_syn_exc__X__exc_spikes__tmp = S_.ode_state[State_::K_syn_exc__X__exc_spikes] * V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes + S_.ode_state[State_::K_syn_exc__X__exc_spikes__d] * V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes__d;
  const double K_syn_exc__X__exc_spikes__d__tmp = S_.ode_state[State_::K_syn_exc__X__exc_spikes] * V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes + S_.ode_state[State_::K_syn_exc__X__exc_spikes__d] * V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes__d;
  const double K_syn_inh__X__inh_spikes__tmp = S_.ode_state[State_::K_syn_inh__X__inh_spikes] * V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes + S_.ode_state[State_::K_syn_inh__X__inh_spikes__d] * V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes__d;
  const double K_syn_inh__X__inh_spikes__d__tmp = S_.ode_state[State_::K_syn_inh__X__inh_spikes] * V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes + S_.ode_state[State_::K_syn_inh__X__inh_spikes__d] * V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes__d;


  // numeric solver: integrating state variables: Act_n, Inact_p, Act_l, Inact_r, Act_m, Inact_h, V_m, K_syn_exc__X__exc_spikes, K_syn_exc__X__exc_spikes__d, K_syn_inh__X__inh_spikes, K_syn_inh__X__inh_spikes__d
  double __t = 0;
  B_.__sys.function = hh_mntb_kv31_neuron_nestml_dynamics;
  // numerical integration with adaptive step size control:
  // ------------------------------------------------------
  // gsl_odeiv_evolve_apply performs only a single numerical
  // integration step, starting from t and bounded by step;
  // the while-loop ensures integration over the whole simulation
  // step (0, step] if more than one integration step is needed due
  // to a small integration step size;
  // note that (t+IntegrationStep > step) leads to integration over
  // (t, step] and afterwards setting t to step, but it does not
  // enforce setting IntegrationStep to step-t; this is of advantage
  // for a consistent and efficient integration across subsequent
  // simulation intervals
  while ( __t < B_.__step )
  {

    const int status = gsl_odeiv_evolve_apply(B_.__e,
                                              B_.__c,
                                              B_.__s,
                                              &B_.__sys,              // system of ODE
                                              &__t,                   // from t
                                              B_.__step,              // to t <= step
                                              &B_.__integration_step, // integration step size
                                              S_.ode_state);          // neuronal state

    if ( status != GSL_SUCCESS )
    {
      throw nest::GSLSolverFailure( get_name(), status );
    }
  }
  // analytic solver: integrating state variables (second step): K_syn_exc__X__exc_spikes, K_syn_exc__X__exc_spikes__d, K_syn_inh__X__inh_spikes, K_syn_inh__X__inh_spikes__d
  /* replace analytically solvable variables with precisely integrated values  */
  S_.ode_state[State_::K_syn_exc__X__exc_spikes] = K_syn_exc__X__exc_spikes__tmp;
  S_.ode_state[State_::K_syn_exc__X__exc_spikes__d] = K_syn_exc__X__exc_spikes__d__tmp;
  S_.ode_state[State_::K_syn_inh__X__inh_spikes] = K_syn_inh__X__inh_spikes__tmp;
  S_.ode_state[State_::K_syn_inh__X__inh_spikes__d] = K_syn_inh__X__inh_spikes__d__tmp;
  if (S_.refr_count > 0)
  {  
    S_.refr_count -= 1;
  }
  else if (S_.ode_state[State_::V_m] > P_.V_spike_th && V_m_old > S_.ode_state[State_::V_m])
  {  
    S_.refr_count = V_.refr_counts;

    // begin generated code for emit_spike() function

    #ifdef DEBUG
    std::cout << "Emitting a spike at t = " << nest::Time(nest::Time::step(origin.get_steps() + lag + 1)).get_ms() << "\n";
    #endif
    set_spiketime(nest::Time::step(origin.get_steps() + lag + 1));
    nest::SpikeEvent se;
    nest::kernel().event_delivery_manager.send(*this, se, lag);
    // end generated code for emit_spike() function
  }

    /**
     * Begin NESTML generated code for the onReceive block(s)
    **/


    /**
     * subthreshold updates of the convolution variables
     *
     * step 2: regardless of whether and how integrate_odes() was called, update variables due to convolutions. Set to the updated values at the end of the timestep.
    **/

    S_.ode_state[State_::K_syn_exc__X__exc_spikes] = K_syn_exc__X__exc_spikes__tmp_;
    S_.ode_state[State_::K_syn_exc__X__exc_spikes__d] = K_syn_exc__X__exc_spikes__d__tmp_;
    S_.ode_state[State_::K_syn_inh__X__inh_spikes] = K_syn_inh__X__inh_spikes__tmp_;
    S_.ode_state[State_::K_syn_inh__X__inh_spikes__d] = K_syn_inh__X__inh_spikes__d__tmp_;

    /**
     * spike updates due to convolutions
    **/

    S_.ode_state[State_::K_syn_exc__X__exc_spikes__d] += ((0.001 * B_.spike_inputs_grid_sum_[EXC_SPIKES - MIN_SPIKE_RECEPTOR])) * (numerics::e / P_.tau_syn_exc) / (1 / 1000.0);
    S_.ode_state[State_::K_syn_inh__X__inh_spikes__d] += ((0.001 * B_.spike_inputs_grid_sum_[INH_SPIKES - MIN_SPIKE_RECEPTOR])) * (numerics::e / P_.tau_syn_inh) / (1 / 1000.0);

    /**
     * Begin NESTML generated code for the onCondition block(s)
    **/


    /**
     * handle continuous input ports
    **/
    for (long i = 0; i < NUM_CONTINUOUS_INPUT_PORTS; ++i)
    {
      get_continuous_inputs_grid_sum_()[i] = get_continuous_inputs_()[i].get_value(lag);
    }
    // voltage logging
    B_.logger_.record_data(origin.get_steps() + lag);
  }
}

// Do not move this function as inline to h-file. It depends on
// universal_data_logger_impl.h being included here.
void hh_mntb_kv31_neuron_nestml::handle(nest::DataLoggingRequest& e)
{
  B_.logger_.handle(e);
}


void hh_mntb_kv31_neuron_nestml::handle(nest::SpikeEvent &e)
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] hh_mntb_kv31_neuron_nestml::handle(SpikeEvent)" << std::endl;
#endif

  assert(e.get_delay_steps() > 0);
  assert( e.get_rport() < B_.spike_inputs_.size() );

  double weight = e.get_weight();
  size_t nestml_buffer_idx = 0;
  if ( weight >= 0.0 )
  {
    nestml_buffer_idx = std::get<0>(rport_to_nestml_buffer_idx[e.get_rport()]);
  }
  else
  {
    nestml_buffer_idx = std::get<1>(rport_to_nestml_buffer_idx[e.get_rport()]);
    if ( nestml_buffer_idx == hh_mntb_kv31_neuron_nestml::PORT_NOT_AVAILABLE )
    {
      nestml_buffer_idx = std::get<0>(rport_to_nestml_buffer_idx[e.get_rport()]);
    }
    weight = -weight;
  }
  B_.spike_inputs_[ nestml_buffer_idx - MIN_SPIKE_RECEPTOR ].add_value(
    e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin() ),
    weight * e.get_multiplicity() );
  B_.spike_input_received_[ nestml_buffer_idx - MIN_SPIKE_RECEPTOR ].add_value(
    e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin() ),
    1. );
}

void hh_mntb_kv31_neuron_nestml::handle(nest::CurrentEvent& e)
{
#ifdef DEBUG
  std::cout << "[neuron " << this << "] hh_mntb_kv31_neuron_nestml::handle(CurrentEvent)" << std::endl;
#endif
  assert(e.get_delay_steps() > 0);
  assert( e.get_rport() < B_.continuous_inputs_.size() );

  const double current = e.get_current();     // we assume that in NEST, this returns a current in pA
  const double weight = e.get_weight();

  B_.continuous_inputs_[e.get_rport()].add_value(
               e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin()),
               weight * current );
}

// -------------------------------------------------------------------------
//   Methods corresponding to event handlers
// -------------------------------------------------------------------------

