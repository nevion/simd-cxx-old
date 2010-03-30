#ifndef AC_SIMD_DDS_SIGNALS_HPP_
#define AC_SIMD_DDS_SIGNALS_HPP_

// -- BOOST Includes
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <boost/signals2/signal.hpp>

#define DECLARE_DDS_SIGNAL(SIGNAL, SIGNATURE, ID)			\
  struct SIGNAL {							\
    enum { value = ID };						\
    template <typename T> struct traits {				\
      typedef boost::function<SIGNATURE>            function_type;	\
      typedef boost::signals2::signal<SIGNATURE>    signal_type;	\
      typedef typename signal_type::slot_type       slot_type;		\
    };									\
  };								


namespace dds {
  
  template <typename T> class DataReader;

  // -- Data Reader Signals
  DECLARE_DDS_SIGNAL(on_data_available,             void (DataReader<T>&), 0)
  DECLARE_DDS_SIGNAL(on_requested_incompatible_qos, void (DataReader<T>&,  const DDS::RequestedIncompatibleQosStatus&), 1)
  DECLARE_DDS_SIGNAL(on_liveliness_changed,         void  (DataReader<T>&, const DDS::LivelinessChangedStatus&), 2)
  DECLARE_DDS_SIGNAL(on_requested_deadline_missed,  void (DataReader<T>&,  const DDS::RequestedDeadlineMissedStatus&), 3)
  DECLARE_DDS_SIGNAL(on_sample_rejected,            void (DataReader<T>&,  const DDS::SampleRejectedStatus&), 4)
  DECLARE_DDS_SIGNAL(on_subscription_matched,       void (DataReader<T>&,  const DDS::SubscriptionMatchedStatus&), 5)
  DECLARE_DDS_SIGNAL(on_sample_lost,                void (DataReader<T>&,  const DDS::SampleLostStatus&), 6)
}
#endif /* AC_SIMD_DDS_SIGNALS_HPP_ */
