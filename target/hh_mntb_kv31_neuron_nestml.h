
/**
 *  hh_mntb_kv31_neuron_nestml.h
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
#ifndef HH_MNTB_KV31_NEURON_NESTML
#define HH_MNTB_KV31_NEURON_NESTML

#ifndef HAVE_LIBLTDL
#error "NEST was compiled without support for dynamic loading. Please install libltdl and recompile NEST."
#endif

// C++ includes:
#include <cmath>

#include "config.h"

#ifndef HAVE_GSL
#error "The GSL library is required for the Runge-Kutta solver."
#endif

// External includes:
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>

// Includes from nestkernel:
#include "structural_plasticity_node.h"
#include "connection.h"
#include "dict_util.h"
#include "event.h"
#include "nest_types.h"
#include "ring_buffer.h"
#include "universal_data_logger.h"

// Includes from sli:
#include "dictdatum.h"

// uncomment the next line to enable printing of detailed debug information
// #define DEBUG

namespace nest
{
namespace hh_mntb_kv31_neuron_nestml_names
{
    const Name _V_m( "V_m" );
    const Name _Act_n( "Act_n" );
    const Name _Inact_p( "Inact_p" );
    const Name _Act_l( "Act_l" );
    const Name _Inact_r( "Inact_r" );
    const Name _Act_m( "Act_m" );
    const Name _Inact_h( "Inact_h" );
    const Name _refr_count( "refr_count" );
    const Name _K_syn_exc__X__exc_spikes( "K_syn_exc__X__exc_spikes" );
    const Name _K_syn_exc__X__exc_spikes__d( "K_syn_exc__X__exc_spikes__d" );
    const Name _K_syn_inh__X__inh_spikes( "K_syn_inh__X__inh_spikes" );
    const Name _K_syn_inh__X__inh_spikes__d( "K_syn_inh__X__inh_spikes__d" );
    const Name _I_Kv3( "I_Kv3" );
    const Name _I_LT( "I_LT" );
    const Name _I_Na( "I_Na" );
    const Name _I_L( "I_L" );
    const Name _C_m( "C_m" );
    const Name _g_Na( "g_Na" );
    const Name _g_LT( "g_LT" );
    const Name _g_Kv3( "g_Kv3" );
    const Name _g_L( "g_L" );
    const Name _E_K( "E_K" );
    const Name _E_Na( "E_Na" );
    const Name _E_L( "E_L" );
    const Name _gamma_Kv3( "gamma_Kv3" );
    const Name _V_spike_th( "V_spike_th" );
    const Name _refr_T( "refr_T" );
    const Name _tau_syn_exc( "tau_syn_exc" );
    const Name _tau_syn_inh( "tau_syn_inh" );
    const Name _I_e( "I_e" );

    const Name gsl_abs_error_tol("gsl_abs_error_tol");
    const Name gsl_rel_error_tol("gsl_rel_error_tol");
}
}



/**
 * Function computing right-hand side of ODE for GSL solver.
 * @note Must be declared here so we can befriend it in class.
 * @note Must have C-linkage for passing to GSL. Internally, it is
 *       a first-class C++ function, but cannot be a member function
 *       because of the C-linkage.
 * @note No point in declaring it inline, since it is called
 *       through a function pointer.
 * @param void* Pointer to model neuron instance.
 *
 * Integrate the variables: 
**/
extern "C" inline int hh_mntb_kv31_neuron_nestml_dynamics( double, const double ode_state[], double f[], void* pnode );

#include "nest_time.h"
  typedef size_t nest_port_t;
  typedef size_t nest_rport_t;

/* BeginDocumentation
  Name: hh_mntb_kv31_neuron_nestml

  Description:

    

  Parameters:
  The following parameters can be set in the status dictionary.
C_m [pF]  0.01 nF
g_Na [nS]  0.5 uS
g_LT [nS]  0.02 uS
g_Kv3 [nS]  0.15 uS (controllo)
g_L [nS]  0.002 uS
refr_T [ms]  solo conteggio degli spike; 2 ms nasconderebbe gli spike a >= 500 Hz


  Dynamic state variables:
Act_n [real]  attivazione I_Kv3 (Kv3.1)
Inact_p [real]  inattivazione parziale I_Kv3
Act_l [real]  attivazione I_LT
Inact_r [real]  inattivazione I_LT
Act_m [real]  attivazione I_Na
Inact_h [real]  inattivazione I_Na
refr_count [integer]  contatore per il rilevamento degli spike


  Sends: nest::SpikeEvent

  Receives: Spike, Current, DataLoggingRequest
*/

// Register the neuron model
void register_hh_mntb_kv31_neuron_nestml( const std::string& name );

class hh_mntb_kv31_neuron_nestml : public nest::StructuralPlasticityNode
{
public:
  /**
   * The constructor is only used to create the model prototype in the model manager.
  **/
  hh_mntb_kv31_neuron_nestml();

  /**
   * The copy constructor is used to create model copies and instances of the model.
   * @node The copy constructor needs to initialize the parameters and the state.
   *       Initialization of buffers and interal variables is deferred to
   *       @c init_buffers_() and @c pre_run_hook() (or calibrate() in NEST 3.3 and older).
  **/
  hh_mntb_kv31_neuron_nestml(const hh_mntb_kv31_neuron_nestml &);

  /**
   * Destructor.
  **/
  ~hh_mntb_kv31_neuron_nestml() override;

  // -------------------------------------------------------------------------
  //   Import sets of overloaded virtual functions.
  //   See: Technical Issues / Virtual Functions: Overriding, Overloading,
  //        and Hiding
  // -------------------------------------------------------------------------

  using nest::Node::handles_test_event;
  using nest::Node::handle;

  /**
   * Used to validate that we can send nest::SpikeEvent to desired target:port.
  **/
  nest_port_t send_test_event(nest::Node& target, nest_rport_t receptor_type, nest::synindex, bool) override;


  // -------------------------------------------------------------------------
  //   Functions handling incoming events.
  //   We tell nest that we can handle incoming events of various types by
  //   defining handle() for the given event.
  // -------------------------------------------------------------------------


  void handle(nest::SpikeEvent &) override;        //! accept spikes
  void handle(nest::CurrentEvent &) override;      //! accept input current

  void handle(nest::DataLoggingRequest &) override;//! allow recording with multimeter
  nest_port_t handles_test_event(nest::SpikeEvent&, nest_port_t) override;
  nest_port_t handles_test_event(nest::CurrentEvent&, nest_port_t) override;
  nest_port_t handles_test_event(nest::DataLoggingRequest&, nest_port_t) override;

  // -------------------------------------------------------------------------
  //   Functions for getting/setting parameters and state values.
  // -------------------------------------------------------------------------

  void get_status(DictionaryDatum &) const override;
  void set_status(const DictionaryDatum &) override;


  // -------------------------------------------------------------------------
  //   Getters/setters for state block
  // -------------------------------------------------------------------------

  inline double get_V_m() const
  {
    return S_.ode_state[State_::V_m];
  }

  inline void set_V_m(const double __v)
  {
    S_.ode_state[State_::V_m] = __v;
  }

  inline double get_Act_n() const
  {
    return S_.ode_state[State_::Act_n];
  }

  inline void set_Act_n(const double __v)
  {
    S_.ode_state[State_::Act_n] = __v;
  }

  inline double get_Inact_p() const
  {
    return S_.ode_state[State_::Inact_p];
  }

  inline void set_Inact_p(const double __v)
  {
    S_.ode_state[State_::Inact_p] = __v;
  }

  inline double get_Act_l() const
  {
    return S_.ode_state[State_::Act_l];
  }

  inline void set_Act_l(const double __v)
  {
    S_.ode_state[State_::Act_l] = __v;
  }

  inline double get_Inact_r() const
  {
    return S_.ode_state[State_::Inact_r];
  }

  inline void set_Inact_r(const double __v)
  {
    S_.ode_state[State_::Inact_r] = __v;
  }

  inline double get_Act_m() const
  {
    return S_.ode_state[State_::Act_m];
  }

  inline void set_Act_m(const double __v)
  {
    S_.ode_state[State_::Act_m] = __v;
  }

  inline double get_Inact_h() const
  {
    return S_.ode_state[State_::Inact_h];
  }

  inline void set_Inact_h(const double __v)
  {
    S_.ode_state[State_::Inact_h] = __v;
  }

  inline long get_refr_count() const
  {
    return S_.refr_count;
  }

  inline void set_refr_count(const long __v)
  {
    S_.refr_count = __v;
  }

  inline double get_K_syn_exc__X__exc_spikes() const
  {
    return S_.ode_state[State_::K_syn_exc__X__exc_spikes];
  }

  inline void set_K_syn_exc__X__exc_spikes(const double __v)
  {
    S_.ode_state[State_::K_syn_exc__X__exc_spikes] = __v;
  }

  inline double get_K_syn_exc__X__exc_spikes__d() const
  {
    return S_.ode_state[State_::K_syn_exc__X__exc_spikes__d];
  }

  inline void set_K_syn_exc__X__exc_spikes__d(const double __v)
  {
    S_.ode_state[State_::K_syn_exc__X__exc_spikes__d] = __v;
  }

  inline double get_K_syn_inh__X__inh_spikes() const
  {
    return S_.ode_state[State_::K_syn_inh__X__inh_spikes];
  }

  inline void set_K_syn_inh__X__inh_spikes(const double __v)
  {
    S_.ode_state[State_::K_syn_inh__X__inh_spikes] = __v;
  }

  inline double get_K_syn_inh__X__inh_spikes__d() const
  {
    return S_.ode_state[State_::K_syn_inh__X__inh_spikes__d];
  }

  inline void set_K_syn_inh__X__inh_spikes__d(const double __v)
  {
    S_.ode_state[State_::K_syn_inh__X__inh_spikes__d] = __v;
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for parameters
  // -------------------------------------------------------------------------

  inline double get_C_m() const
  {
    return P_.C_m;
  }

  inline void set_C_m(const double __v)
  {
    P_.C_m = __v;
  }

  inline double get_g_Na() const
  {
    return P_.g_Na;
  }

  inline void set_g_Na(const double __v)
  {
    P_.g_Na = __v;
  }

  inline double get_g_LT() const
  {
    return P_.g_LT;
  }

  inline void set_g_LT(const double __v)
  {
    P_.g_LT = __v;
  }

  inline double get_g_Kv3() const
  {
    return P_.g_Kv3;
  }

  inline void set_g_Kv3(const double __v)
  {
    P_.g_Kv3 = __v;
  }

  inline double get_g_L() const
  {
    return P_.g_L;
  }

  inline void set_g_L(const double __v)
  {
    P_.g_L = __v;
  }

  inline double get_E_K() const
  {
    return P_.E_K;
  }

  inline void set_E_K(const double __v)
  {
    P_.E_K = __v;
  }

  inline double get_E_Na() const
  {
    return P_.E_Na;
  }

  inline void set_E_Na(const double __v)
  {
    P_.E_Na = __v;
  }

  inline double get_E_L() const
  {
    return P_.E_L;
  }

  inline void set_E_L(const double __v)
  {
    P_.E_L = __v;
  }

  inline double get_gamma_Kv3() const
  {
    return P_.gamma_Kv3;
  }

  inline void set_gamma_Kv3(const double __v)
  {
    P_.gamma_Kv3 = __v;
  }

  inline double get_V_spike_th() const
  {
    return P_.V_spike_th;
  }

  inline void set_V_spike_th(const double __v)
  {
    P_.V_spike_th = __v;
  }

  inline double get_refr_T() const
  {
    return P_.refr_T;
  }

  inline void set_refr_T(const double __v)
  {
    P_.refr_T = __v;
  }

  inline double get_tau_syn_exc() const
  {
    return P_.tau_syn_exc;
  }

  inline void set_tau_syn_exc(const double __v)
  {
    P_.tau_syn_exc = __v;
  }

  inline double get_tau_syn_inh() const
  {
    return P_.tau_syn_inh;
  }

  inline void set_tau_syn_inh(const double __v)
  {
    P_.tau_syn_inh = __v;
  }

  inline double get_I_e() const
  {
    return P_.I_e;
  }

  inline void set_I_e(const double __v)
  {
    P_.I_e = __v;
  }


  // -------------------------------------------------------------------------
  //   Getters/setters for internals
  // -------------------------------------------------------------------------

  inline long get_refr_counts() const
  {
    return V_.refr_counts;
  }

  inline void set_refr_counts(const long __v)
  {
    V_.refr_counts = __v;
  }
  inline double get___h() const
  {
    return V_.__h;
  }

  inline void set___h(const double __v)
  {
    V_.__h = __v;
  }
  inline double get___P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes() const
  {
    return V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes;
  }

  inline void set___P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes(const double __v)
  {
    V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes = __v;
  }
  inline double get___P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes__d() const
  {
    return V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes__d;
  }

  inline void set___P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes__d(const double __v)
  {
    V_.__P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes__d = __v;
  }
  inline double get___P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes() const
  {
    return V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes;
  }

  inline void set___P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes(const double __v)
  {
    V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes = __v;
  }
  inline double get___P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes__d() const
  {
    return V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes__d;
  }

  inline void set___P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes__d(const double __v)
  {
    V_.__P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes__d = __v;
  }
  inline double get___P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes() const
  {
    return V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes;
  }

  inline void set___P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes(const double __v)
  {
    V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes = __v;
  }
  inline double get___P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes__d() const
  {
    return V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes__d;
  }

  inline void set___P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes__d(const double __v)
  {
    V_.__P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes__d = __v;
  }
  inline double get___P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes() const
  {
    return V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes;
  }

  inline void set___P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes(const double __v)
  {
    V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes = __v;
  }
  inline double get___P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes__d() const
  {
    return V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes__d;
  }

  inline void set___P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes__d(const double __v)
  {
    V_.__P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes__d = __v;
  }


  // -------------------------------------------------------------------------
  //   Methods corresponding to event handlers
  // -------------------------------------------------------------------------

  

  // -------------------------------------------------------------------------
  //   Initialization functions
  // -------------------------------------------------------------------------
  void calibrate_time( const nest::TimeConverter& tc ) override;

protected:

private:
  void recompute_internal_variables(bool exclude_timestep=false);

private:

  static const nest_port_t MIN_SPIKE_RECEPTOR = 0;
  static const nest_port_t PORT_NOT_AVAILABLE = -1;

  enum SynapseTypes
  {
    EXC_SPIKES = 0,
    INH_SPIKES = 1,
    MAX_SPIKE_RECEPTOR = 2
  };

  enum ContinuousInput
  {
    I_STIM = 0,
    NUM_CONTINUOUS_INPUT_PORTS = 1
  };

  static const size_t NUM_SPIKE_RECEPTORS = MAX_SPIKE_RECEPTOR - MIN_SPIKE_RECEPTOR;

static std::vector< std::tuple< int, int > > rport_to_nestml_buffer_idx;

  /**
   * Reset state of neuron.
  **/

  void init_state_internal_();

  /**
   * Reset internal buffers of neuron.
  **/
  void init_buffers_() override;

  /**
   * Initialize auxiliary quantities, leave parameters and state untouched.
  **/
  void pre_run_hook() override;

  /**
   * Take neuron through given time interval
  **/
  void update(nest::Time const &, const long, const long) override;

  // The next two classes need to be friends to access the State_ class/member
  friend class nest::RecordablesMap<hh_mntb_kv31_neuron_nestml>;
  friend class nest::UniversalDataLogger<hh_mntb_kv31_neuron_nestml>;

  /**
   * Free parameters of the neuron.
   *


   *
   * These are the parameters that can be set by the user through @c `node.set()`.
   * They are initialized from the model prototype when the node is created.
   * Parameters do not change during calls to @c update() and are not reset by
   * @c ResetNetwork.
   *
   * @note Parameters_ need neither copy constructor nor @c operator=(), since
   *       all its members are copied properly by the default copy constructor
   *       and assignment operator. Important:
   *       - If Parameters_ contained @c Time members, you need to define the
   *         assignment operator to recalibrate all members of type @c Time . You
   *         may also want to define the assignment operator.
   *       - If Parameters_ contained members that cannot copy themselves, such
   *         as C-style arrays, you need to define the copy constructor and
   *         assignment operator to copy those members.
  **/
  struct Parameters_
  {    
    //!  0.01 nF
    double C_m;
    //!  0.5 uS
    double g_Na;
    //!  0.02 uS
    double g_LT;
    //!  0.15 uS (controllo)
    double g_Kv3;
    //!  0.002 uS
    double g_L;
    double E_K;
    double E_Na;
    double E_L;
    double gamma_Kv3;
    double V_spike_th;
    //!  solo conteggio degli spike; 2 ms nasconderebbe gli spike a >= 500 Hz
    double refr_T;
    double tau_syn_exc;
    double tau_syn_inh;
    double I_e;

    double __gsl_abs_error_tol;
    double __gsl_rel_error_tol;

    /**
     * Initialize parameters to their default values.
    **/
    Parameters_();
  };

  /**
   * Dynamic state of the neuron.
   *
   *
   *
   * These are the state variables that are advanced in time by calls to
   * @c update(). In many models, some or all of them can be set by the user
   * through @c `node.set()`. The state variables are initialized from the model
   * prototype when the node is created. State variables are reset by @c ResetNetwork.
   *
   * @note State_ need neither copy constructor nor @c operator=(), since
   *       all its members are copied properly by the default copy constructor
   *       and assignment operator. Important:
   *       - If State_ contained @c Time members, you need to define the
   *         assignment operator to recalibrate all members of type @c Time . You
   *         may also want to define the assignment operator.
   *       - If State_ contained members that cannot copy themselves, such
   *         as C-style arrays, you need to define the copy constructor and
   *         assignment operator to copy those members.
  **/
  struct State_
  {

    // non-ODE state variables
//!  contatore per il rilevamento degli spike
long refr_count;
    //! Symbolic indices to the elements of the state vector y
    enum StateVecElems
    {
      Act_n,
      Inact_p,
      Act_l,
      Inact_r,
      Act_m,
      Inact_h,
      V_m,
      K_syn_exc__X__exc_spikes,
      K_syn_exc__X__exc_spikes__d,
      K_syn_inh__X__inh_spikes,
      K_syn_inh__X__inh_spikes__d,
      // moved state variables from synapse (numeric)
      // moved state variables from synapse (analytic)
      // final entry to easily get the vector size
      STATE_VEC_SIZE
    };

    //! state vector, must be C-array for GSL solver
    double ode_state[STATE_VEC_SIZE];

    State_();
  };

  struct DelayedVariables_
  {
  };

  /**
   * Internal variables of the neuron.
   *
   *
   *
   * These variables must be initialized by @c pre_run_hook (or calibrate in NEST 3.3 and older), which is called before
   * the first call to @c update() upon each call to @c Simulate.
   * @node Variables_ needs neither constructor, copy constructor or assignment operator,
   *       since it is initialized by @c pre_run_hook() (or calibrate() in NEST 3.3 and older). If Variables_ has members that
   *       cannot destroy themselves, Variables_ will need a destructor.
  **/
  struct Variables_
  {
    long refr_counts;
    double __h;
    double __P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes;
    double __P__K_syn_exc__X__exc_spikes__K_syn_exc__X__exc_spikes__d;
    double __P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes;
    double __P__K_syn_exc__X__exc_spikes__d__K_syn_exc__X__exc_spikes__d;
    double __P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes;
    double __P__K_syn_inh__X__inh_spikes__K_syn_inh__X__inh_spikes__d;
    double __P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes;
    double __P__K_syn_inh__X__inh_spikes__d__K_syn_inh__X__inh_spikes__d;
  };

  /**
   * Buffers of the neuron.
   * Usually buffers for incoming spikes and data logged for analog recorders.
   * Buffers must be initialized by @c init_buffers_(), which is called before
   * @c pre_run_hook() (or calibrate() in NEST 3.3 and older) on the first call to @c Simulate after the start of NEST,
   * ResetKernel or ResetNetwork.
   * @node Buffers_ needs neither constructor, copy constructor or assignment operator,
   *       since it is initialized by @c init_nodes_(). If Buffers_ has members that
   *       cannot destroy themselves, Buffers_ will need a destructor.
  **/
  struct Buffers_
  {
    Buffers_(hh_mntb_kv31_neuron_nestml &);
    Buffers_(const Buffers_ &, hh_mntb_kv31_neuron_nestml &);

    /**
     * Logger for all analog data
    **/
    nest::UniversalDataLogger<hh_mntb_kv31_neuron_nestml> logger_;

    // -----------------------------------------------------------------------
    //   Spike buffers and sums of incoming spikes/currents per timestep
    // -----------------------------------------------------------------------    



    /**
     * Buffer containing the incoming spikes
    **/
    inline std::vector< nest::RingBuffer >& get_spike_inputs_()
    {
        return spike_inputs_;
    }
    std::vector< nest::RingBuffer > spike_inputs_;

    /**
     * Buffer containing the sum of all the incoming spikes
    **/
    inline std::vector< double >& get_spike_inputs_grid_sum_()
    {
        return spike_inputs_grid_sum_;
    }
    std::vector< double > spike_inputs_grid_sum_;

    /**
     * Buffer containing a flag whether incoming spikes have been received on a given port
    **/
    inline std::vector< nest::RingBuffer >& get_spike_input_received_()
    {
        return spike_input_received_;
    }
    std::vector< nest::RingBuffer > spike_input_received_;

    /**
     * Buffer containing a flag whether incoming spikes have been received on a given port
    **/
    inline std::vector< double >& get_spike_input_received_grid_sum_()
    {
        return spike_input_received_grid_sum_;
    }
    std::vector< double > spike_input_received_grid_sum_;

    // -----------------------------------------------------------------------
    //   Continuous-input buffers
    // -----------------------------------------------------------------------

    




    /**
     * Buffer containing the incoming continuous input
    **/
    inline std::vector< nest::RingBuffer >& get_continuous_inputs_()
    {
        return continuous_inputs_;
    }
    std::vector< nest::RingBuffer > continuous_inputs_;

    /**
     * Buffer containing the sum of all the continuous inputs
    **/
    inline std::vector< double >& get_continuous_inputs_grid_sum_()
    {
        return continuous_inputs_grid_sum_;
    }
    std::vector< double > continuous_inputs_grid_sum_;

    // -----------------------------------------------------------------------
    //   GSL ODE solver data structures
    // -----------------------------------------------------------------------

    gsl_odeiv_step* __s;    //!< stepping function
    gsl_odeiv_control* __c; //!< adaptive stepsize control function
    gsl_odeiv_evolve* __e;  //!< evolution function
    gsl_odeiv_system __sys; //!< struct describing system

    // __integration_step should be reset with the neuron on ResetNetwork,
    // but remain unchanged during calibration. Since it is initialized with
    // step_, and the resolution cannot change after nodes have been created,
    // it is safe to place both here.
    double __step;             //!< step size in ms
    double __integration_step; //!< current integration time step, updated by GSL
  };

  // -------------------------------------------------------------------------
  //   Getters/setters for inline expressions
  // -------------------------------------------------------------------------

  inline double get_I_syn_exc() const
  {
    return S_.ode_state[State_::K_syn_exc__X__exc_spikes] * 1;
  }

  inline double get_I_syn_inh() const
  {
    return S_.ode_state[State_::K_syn_inh__X__inh_spikes] * 1;
  }

  inline double get_I_Kv3() const
  {
    return P_.g_Kv3 * pow(S_.ode_state[State_::Act_n], 3) * ((1 - P_.gamma_Kv3) + P_.gamma_Kv3 * S_.ode_state[State_::Inact_p]) * (S_.ode_state[State_::V_m] - P_.E_K);
  }

  inline double get_I_LT() const
  {
    return P_.g_LT * S_.ode_state[State_::Act_l] * S_.ode_state[State_::Inact_r] * (S_.ode_state[State_::V_m] - P_.E_K);
  }

  inline double get_I_Na() const
  {
    return P_.g_Na * pow(S_.ode_state[State_::Act_m], 3) * S_.ode_state[State_::Inact_h] * (S_.ode_state[State_::V_m] - P_.E_Na);
  }

  inline double get_I_L() const
  {
    return P_.g_L * (S_.ode_state[State_::V_m] - P_.E_L);
  }

  inline double get_alpha_n() const
  {
    return 0.2719 * std::exp(0.04 * S_.ode_state[State_::V_m] / (1));
  }

  inline double get_beta_n() const
  {
    return 0.1974;
  }

  inline double get_alpha_p() const
  {
    return 0.00713 * std::exp((-0.1942) * S_.ode_state[State_::V_m] / (1));
  }

  inline double get_beta_p() const
  {
    return 0.0935 * std::exp(0.0058 * S_.ode_state[State_::V_m] / (1));
  }

  inline double get_alpha_l() const
  {
    return 1.2 * std::exp(0.03512 * S_.ode_state[State_::V_m] / (1));
  }

  inline double get_beta_l() const
  {
    return 0.2248 * std::exp((-0.0319) * S_.ode_state[State_::V_m] / (1));
  }

  inline double get_alpha_r() const
  {
    return 0.0438 * std::exp((-0.0053) * S_.ode_state[State_::V_m] / (1));
  }

  inline double get_beta_r() const
  {
    return 0.0562 * std::exp((-0.0047) * S_.ode_state[State_::V_m] / (1));
  }

  inline double get_alpha_m() const
  {
    return 76.4 * std::exp(0.037 * S_.ode_state[State_::V_m] / (1));
  }

  inline double get_beta_m() const
  {
    return 6.93 * std::exp((-0.043) * S_.ode_state[State_::V_m] / (1));
  }

  inline double get_alpha_h() const
  {
    return 0.000533 * std::exp((-0.0909) * S_.ode_state[State_::V_m] / (1));
  }

  inline double get_beta_h() const
  {
    return 7.87 * std::exp(0.0691 * S_.ode_state[State_::V_m] / (1));
  }



  // -------------------------------------------------------------------------
  //   Getters/setters for input buffers
  // -------------------------------------------------------------------------  




  /**
   * Buffer containing the incoming spikes
  **/
  inline std::vector< nest::RingBuffer >& get_spike_inputs_()
  {
      return B_.get_spike_inputs_();
  }

  /**
   * Buffer containing the sum of all the incoming spikes
  **/
  inline std::vector< double >& get_spike_inputs_grid_sum_()
  {
      return B_.get_spike_inputs_grid_sum_();
  }

  /**
   * Buffer containing a flag whether incoming spikes have been received on a given port
  **/
  inline std::vector< nest::RingBuffer >& get_spike_input_received_()
  {
      return B_.get_spike_input_received_();
  }

  /**
   * Buffer containing a flag whether incoming spikes have been received on a given port
  **/
  inline std::vector< double >& get_spike_input_received_grid_sum_()
  {
      return B_.get_spike_input_received_grid_sum_();
  }




  /**
   * Buffer containing the incoming continuous input
  **/
  inline std::vector< nest::RingBuffer >& get_continuous_inputs_()
  {
      return B_.get_continuous_inputs_();
  }

  /**
   * Buffer containing the sum of all the continuous inputs
  **/
  inline std::vector< double >& get_continuous_inputs_grid_sum_()
  {
      return B_.get_continuous_inputs_grid_sum_();
  }

  // -------------------------------------------------------------------------
  //   Member variables of neuron model.
  //   Each model neuron should have precisely the following four data members,
  //   which are one instance each of the parameters, state, buffers and variables
  //   structures. Experience indicates that the state and variables member should
  //   be next to each other to achieve good efficiency (caching).
  //   Note: Devices require one additional data member, an instance of the
  //   ``Device`` child class they belong to.
  // -------------------------------------------------------------------------


  Parameters_       P_;        //!< Free parameters.
  State_            S_;        //!< Dynamic state.
  DelayedVariables_ DV_;       //!< Delayed state variables.
  Variables_        V_;        //!< Internal Variables
  Buffers_          B_;        //!< Buffers.

  //! Mapping of recordables names to access functions
  static nest::RecordablesMap<hh_mntb_kv31_neuron_nestml> recordablesMap_;
  friend int hh_mntb_kv31_neuron_nestml_dynamics( double, const double ode_state[], double f[], void* pnode );

}; /* neuron hh_mntb_kv31_neuron_nestml */

inline nest_port_t hh_mntb_kv31_neuron_nestml::send_test_event(nest::Node& target, nest_rport_t receptor_type, nest::synindex, bool)
{
  // You should usually not change the code in this function.
  // It confirms that the target of connection @c c accepts @c nest::SpikeEvent on
  // the given @c receptor_type.
  nest::SpikeEvent e;
  e.set_sender(*this);
  return target.handles_test_event(e, receptor_type);
}

inline nest_port_t hh_mntb_kv31_neuron_nestml::handles_test_event(nest::SpikeEvent&, nest_port_t receptor_type)
{
    // You should usually not change the code in this function.
    // It confirms to the connection management system that we are able
    // to handle @c SpikeEvent on port 0. You need to extend the function
    // if you want to differentiate between input ports.
    if (receptor_type != 0)
    {
      throw nest::UnknownReceptorType(receptor_type, get_name());
    }
    return 0;
}

inline nest_port_t hh_mntb_kv31_neuron_nestml::handles_test_event(nest::CurrentEvent&, nest_port_t receptor_type)
{
  // You should usually not change the code in this function.
  // It confirms to the connection management system that we are able
  // to handle @c CurrentEvent on port 0. You need to extend the function
  // if you want to differentiate between input ports.
  if (receptor_type >= NUM_CONTINUOUS_INPUT_PORTS)
  {
    throw nest::UnknownReceptorType(receptor_type, get_name());
  }
  return receptor_type;
}

inline nest_port_t hh_mntb_kv31_neuron_nestml::handles_test_event(nest::DataLoggingRequest& dlr, nest_port_t receptor_type)
{
  // You should usually not change the code in this function.
  // It confirms to the connection management system that we are able
  // to handle @c DataLoggingRequest on port 0.
  // The function also tells the built-in UniversalDataLogger that this node
  // is recorded from and that it thus needs to collect data during simulation.
  if (receptor_type != 0)
  {
    throw nest::UnknownReceptorType(receptor_type, get_name());
  }

  return B_.logger_.connect_logging_device(dlr, recordablesMap_);
}

inline void hh_mntb_kv31_neuron_nestml::get_status(DictionaryDatum &__d) const
{
  // parameters
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_C_m, get_C_m());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_g_Na, get_g_Na());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_g_LT, get_g_LT());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_g_Kv3, get_g_Kv3());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_g_L, get_g_L());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_E_K, get_E_K());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_E_Na, get_E_Na());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_E_L, get_E_L());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_gamma_Kv3, get_gamma_Kv3());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_V_spike_th, get_V_spike_th());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_refr_T, get_refr_T());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_tau_syn_exc, get_tau_syn_exc());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_tau_syn_inh, get_tau_syn_inh());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_I_e, get_I_e());

  // initial values for state variables in ODE or kernel
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_V_m, get_V_m());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Act_n, get_Act_n());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Inact_p, get_Inact_p());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Act_l, get_Act_l());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Inact_r, get_Inact_r());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Act_m, get_Act_m());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Inact_h, get_Inact_h());
  def< long >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_refr_count, get_refr_count());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_K_syn_exc__X__exc_spikes, get_K_syn_exc__X__exc_spikes());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_K_syn_exc__X__exc_spikes__d, get_K_syn_exc__X__exc_spikes__d());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_K_syn_inh__X__inh_spikes, get_K_syn_inh__X__inh_spikes());
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::_K_syn_inh__X__inh_spikes__d, get_K_syn_inh__X__inh_spikes__d());

  StructuralPlasticityNode::get_status( __d );

  (*__d)[nest::names::recordables] = recordablesMap_.get_list();
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::gsl_abs_error_tol, P_.__gsl_abs_error_tol);
  if ( P_.__gsl_abs_error_tol <= 0. ){
    throw nest::BadProperty( "The gsl_abs_error_tol must be strictly positive." );
  }
  def< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::gsl_rel_error_tol, P_.__gsl_rel_error_tol);
  if ( P_.__gsl_rel_error_tol < 0. ){
    throw nest::BadProperty( "The gsl_rel_error_tol must be zero or positive." );
  }
}

inline void hh_mntb_kv31_neuron_nestml::set_status(const DictionaryDatum &__d)
{
  // parameters
  double tmp_C_m = get_C_m();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_C_m, tmp_C_m, this);
  double tmp_g_Na = get_g_Na();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_g_Na, tmp_g_Na, this);
  double tmp_g_LT = get_g_LT();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_g_LT, tmp_g_LT, this);
  double tmp_g_Kv3 = get_g_Kv3();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_g_Kv3, tmp_g_Kv3, this);
  double tmp_g_L = get_g_L();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_g_L, tmp_g_L, this);
  double tmp_E_K = get_E_K();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_E_K, tmp_E_K, this);
  double tmp_E_Na = get_E_Na();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_E_Na, tmp_E_Na, this);
  double tmp_E_L = get_E_L();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_E_L, tmp_E_L, this);
  double tmp_gamma_Kv3 = get_gamma_Kv3();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_gamma_Kv3, tmp_gamma_Kv3, this);
  double tmp_V_spike_th = get_V_spike_th();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_V_spike_th, tmp_V_spike_th, this);
  double tmp_refr_T = get_refr_T();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_refr_T, tmp_refr_T, this);
  double tmp_tau_syn_exc = get_tau_syn_exc();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_tau_syn_exc, tmp_tau_syn_exc, this);
  double tmp_tau_syn_inh = get_tau_syn_inh();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_tau_syn_inh, tmp_tau_syn_inh, this);
  double tmp_I_e = get_I_e();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_I_e, tmp_I_e, this);

  // initial values for state variables in ODE or kernel
  double tmp_V_m = get_V_m();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_V_m, tmp_V_m, this);
  double tmp_Act_n = get_Act_n();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Act_n, tmp_Act_n, this);
  double tmp_Inact_p = get_Inact_p();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Inact_p, tmp_Inact_p, this);
  double tmp_Act_l = get_Act_l();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Act_l, tmp_Act_l, this);
  double tmp_Inact_r = get_Inact_r();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Inact_r, tmp_Inact_r, this);
  double tmp_Act_m = get_Act_m();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Act_m, tmp_Act_m, this);
  double tmp_Inact_h = get_Inact_h();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_Inact_h, tmp_Inact_h, this);
  long tmp_refr_count = get_refr_count();
  nest::updateValueParam<long>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_refr_count, tmp_refr_count, this);
  double tmp_K_syn_exc__X__exc_spikes = get_K_syn_exc__X__exc_spikes();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_K_syn_exc__X__exc_spikes, tmp_K_syn_exc__X__exc_spikes, this);
  double tmp_K_syn_exc__X__exc_spikes__d = get_K_syn_exc__X__exc_spikes__d();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_K_syn_exc__X__exc_spikes__d, tmp_K_syn_exc__X__exc_spikes__d, this);
  double tmp_K_syn_inh__X__inh_spikes = get_K_syn_inh__X__inh_spikes();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_K_syn_inh__X__inh_spikes, tmp_K_syn_inh__X__inh_spikes, this);
  double tmp_K_syn_inh__X__inh_spikes__d = get_K_syn_inh__X__inh_spikes__d();
  nest::updateValueParam<double>(__d, nest::hh_mntb_kv31_neuron_nestml_names::_K_syn_inh__X__inh_spikes__d, tmp_K_syn_inh__X__inh_spikes__d, this);

  // We now know that (ptmp, stmp) are consistent. We do not
  // write them back to (P_, S_) before we are also sure that
  // the properties to be set in the parent class are internally
  // consistent.
  StructuralPlasticityNode::set_status(__d);

  // if we get here, temporaries contain consistent set of properties
  set_C_m(tmp_C_m);
  set_g_Na(tmp_g_Na);
  set_g_LT(tmp_g_LT);
  set_g_Kv3(tmp_g_Kv3);
  set_g_L(tmp_g_L);
  set_E_K(tmp_E_K);
  set_E_Na(tmp_E_Na);
  set_E_L(tmp_E_L);
  set_gamma_Kv3(tmp_gamma_Kv3);
  set_V_spike_th(tmp_V_spike_th);
  set_refr_T(tmp_refr_T);
  set_tau_syn_exc(tmp_tau_syn_exc);
  set_tau_syn_inh(tmp_tau_syn_inh);
  set_I_e(tmp_I_e);
  set_V_m(tmp_V_m);
  set_Act_n(tmp_Act_n);
  set_Inact_p(tmp_Inact_p);
  set_Act_l(tmp_Act_l);
  set_Inact_r(tmp_Inact_r);
  set_Act_m(tmp_Act_m);
  set_Inact_h(tmp_Inact_h);
  set_refr_count(tmp_refr_count);
  set_K_syn_exc__X__exc_spikes(tmp_K_syn_exc__X__exc_spikes);
  set_K_syn_exc__X__exc_spikes__d(tmp_K_syn_exc__X__exc_spikes__d);
  set_K_syn_inh__X__inh_spikes(tmp_K_syn_inh__X__inh_spikes);
  set_K_syn_inh__X__inh_spikes__d(tmp_K_syn_inh__X__inh_spikes__d);




  updateValue< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::gsl_abs_error_tol, P_.__gsl_abs_error_tol);
  if ( P_.__gsl_abs_error_tol <= 0. )
  {
    throw nest::BadProperty( "The gsl_abs_error_tol must be strictly positive." );
  }
  updateValue< double >(__d, nest::hh_mntb_kv31_neuron_nestml_names::gsl_rel_error_tol, P_.__gsl_rel_error_tol);
  if ( P_.__gsl_rel_error_tol < 0. )
  {
    throw nest::BadProperty( "The gsl_rel_error_tol must be zero or positive." );
  }

  // recompute internal variables in case they are dependent on parameters or state that might have been updated in this call to set_status()
  recompute_internal_variables();
};



#endif /* #ifndef HH_MNTB_KV31_NEURON_NESTML */
