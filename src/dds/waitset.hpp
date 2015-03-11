#ifndef AC_SIMD_DDS_WAITSET_HPP_
#define AC_SIMD_DDS_WAITSET_HPP_

// -- BOOST Include
#include <boost/noncopyable.hpp>

// -- SIMD_DDS Include
#include <dds/types.hpp>
#include <dds/condition.hpp>



namespace dds {
  class WaitSet;
  DECLARE_EXCEPTION(InterruptedException)
}

/**
 * The <code>WaitSet</code> can be used in
 * alternative to <code>DDS::WaitSet</code> to leverage
 * the automatic dispatching provided by <code>Condition</code>.
 *
 * @author Angelo Corsaro <mailto:angelo.corsaro@gmail.com>
 */
class SIMD_API dds::WaitSet : public ::boost::noncopyable {
 public:
  typedef ::dds::ConditionVector::iterator iterator;

 public:
  /**
   * Creates a new <code>WaitSet</code> which has not
   * condition attached to it.
   */
  WaitSet();

  /**
   * Creates a new <code>WaitSet</code> and attaches the
   * condition passed to the ctor.
   *
   * @param cond the condition to be attached to this wait-set.
   */
  WaitSet(const ::dds::Condition& cond);

  /**
   * Destroys this and unregisters all the conditions that are
   * still attached.
   */
  ~WaitSet();

 public:
  /**
   * Waits for one of the attached condition to trigger or
   * for a timeout to expire. The attached conditions that
   * have been notified before the expiration of the timeout
   * are returned by the call.
   *
   * @param timeout the maximum amount of time for which the wait
   * should block while waiting for a condition to be triggered.
   *
   *
   */
	
  void wait(const dds::Duration_t& timeout);

  /**
   * Waits for one of the attached conditions to trigger.
   *
   * @return a vector containing the triggered conditions
   */
  void wait();

  void wait (DDS::ConditionSeq& seq);

  /**
   * @return a vector containing the triggered conditions
   */
  ::dds::ConditionVector triggered_conditions();

  /**
   * Waits for at least one of the attached conditions to
   * trigger and then dispatches the events.
   *
   */
  void dispatch();

  /**
   * Waits for at least one of the attached conditions to  trigger and then
   * dispatches the events, or, times out and unblocks.
   *
   */
  void dispatch(const ::dds::Duration_t& timeout);

  WaitSet& operator +=(const ::dds::Condition& cond);
  WaitSet& operator -=(const ::dds::Condition& cond);

  dds::ReturnCode_t attach(const ::dds::Condition& cond);
  dds::ReturnCode_t detach(const ::dds::Condition& cond);
#if defined(WIN32)
  HANDLE
#elif defined(_POSIX_C_SOURCE)
  int
#endif
  get_os_waitable_handle();
  uint64_t clear_os_waitable_handle_events();

  iterator begin();
  iterator end();

 private:
  ::DDS::WaitSet waitset_;
  ::dds::ConditionVector cond_vec_;
};


#endif /* AC_SIMD_DDS_WAITSET_HPP_ */
