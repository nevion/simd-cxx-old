#ifndef AC_SIMD_DDS_WAITSET_HPP_
#define AC_SIMD_DDS_WAITSET_HPP_

// -- BOOST Include
#include <boost/noncopyable.hpp>

// -- SIMD_DDS Include
#include <dds/condition.hpp>


namespace dds {
	class ActiveWaitSet;
}

/**
 * The <code>ActiveWaitSet</code> can be used in
 * alternative to <code>DDS::WaitSet</code> to leverage
 * the automatic dispatching provided by <code>ActiveCondition</code>.
 *
 * @author Angelo Corsaro <mailto:angelo.corsaro@gmail.com>
 */
class SIMD_EXPORT dds::ActiveWaitSet : public ::boost::noncopyable {
public:
	typedef ::dds::ActiveConditionVector::iterator iterator;

public:
	/**
	 * Creates a new <code>ActiveWaitSet</code> which has not
	 * condition attached to it.
	 */
	ActiveWaitSet();

	/**
	 * Creates a new <code>ActiveWaitSet</code> and attaches the
	 * condition passed to the ctor.
	 *
	 * @param cond the condition to be attached to this wait-set.
	 */
	ActiveWaitSet(const ::dds::ActiveCondition& cond);

	/**
	 * Destroys this and unregisters all the conditions that are
	 * still attached.
	 */
	~ActiveWaitSet();

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
	 * @return a vector containing the triggered conditions
	 *
	 */
	::dds::ActiveConditionVector wait(const DDS::Duration_t& timeout);

	/**
	 * Waits for one of the attached conditions to trigger.
	 *
	 * @return a vector containing the triggered conditions
	 */
	::dds::ActiveConditionVector wait();

	/**
	 * Waits for at least one of the attached conditions to  trigger and then
	 * dispatches the events.
	 *
	 */
	void dispatch();

	/**
	 * Waits for at least one of the attached conditions to  trigger and then
	 * dispatches the events, or, times out and unblocks.
	 *
	 */
	void dispatch(const ::DDS::Duration_t& timeout);

	ActiveWaitSet& operator +=(const ::dds::ActiveCondition& cond);
	ActiveWaitSet& operator -=(const ::dds::ActiveCondition& cond);

	DDS::ReturnCode_t attach(const ::dds::ActiveCondition& cond);
	DDS::ReturnCode_t detach(const ::dds::ActiveCondition& cond);

	iterator begin();
	iterator end();

private:
	::DDS::WaitSet waitset_;
	::dds::ActiveConditionVector cond_vec_;
};


#endif /* AC_SIMD_DDS_WAITSET_HPP_ */
