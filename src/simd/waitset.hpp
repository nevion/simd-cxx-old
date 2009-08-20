#ifndef AC_SIMD_WAITSET_HPP_
#define AC_SIMD_WAITSET_HPP_

// -- BOOST Include
#include <boost/noncopyable.hpp>

// -- SIMD Include
#include <simd/condition.hpp>


namespace simd {
	class ExecutableWaitSet;
}

/**
 * The <code>ExecutableWaitSet</code> can be used in
 * alternative to <code>DDS::WaitSet</code> to leverage
 * the automatic dispatching provided by <code>ExecutableCondition</code>.
 *
 * @author Angelo Corsaro <mailto:angelo.corsaro@gmail.com>
 */
class simd::ExecutableWaitSet : public ::boost::noncopyable {
public:
	typedef ::simd::ExecutableConditionVector::iterator iterator;

public:
	/**
	 * Creates a new <code>ExecutableWaitSet</code> which has not
	 * condition attached to it.
	 */
	ExecutableWaitSet();

	/**
	 * Creates a new <code>ExecutableWaitSet</code> and attaches the
	 * condition passed to the ctor.
	 *
	 * @param cond the condition to be attached to this wait-set.
	 */
	ExecutableWaitSet(const ::simd::ExecutableConditionRef& cond);

	/**
	 * Destroys this and unregisters all the conditions that are
	 * still attached.
	 */
	~ExecutableWaitSet();

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
	::simd::ExecutableConditionVector wait(const DDS::Duration_t& timeout);

	/**
	 * Waits for one of the attached condition to trigger.
	 *
	 * @return a vector containing the triggered conditions
	 */
	::simd::ExecutableConditionVector wait();

	ExecutableWaitSet& operator +=(const ::simd::ExecutableConditionRef& cond);
	ExecutableWaitSet& operator -=(const ::simd::ExecutableConditionRef& cond);

	DDS::ReturnCode_t attach(const ::simd::ExecutableConditionRef& cond);
	DDS::ReturnCode_t detach(const ::simd::ExecutableConditionRef& cond);

	iterator begin();
	iterator end();

private:
	::DDS::WaitSet waitset_;
	::simd::ExecutableConditionVector cond_vec_;
};


#endif /* AC_SIMD_WAITSET_HPP_ */
