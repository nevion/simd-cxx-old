#ifndef AC_SIMD_CONDITION_HPP
#define	AC_SIMD_CONDITION_HPP

// C++ STD Include
#include <vector>

// -- BOOST Include
#include <boost/shared_ptr.hpp>

// -- DDS Includes
#include <dds_dcps.h>
#include <ccpp_dds_dcps.h>

// -- SIMD Includes
#include <simd/config.hpp>

namespace simd {

class ActiveWaitSet;

/**
* The <code>ActiveCondition</code> class allows provides a generic interface for
* all those class that want to provide a command like behviour. This command
* interfance is implemented by the <b>SIMD</b> classes providing the
* condition behaviour. The key advantage of using this command-based approach
* to condition is that the dispatching can be performed directly and without
* requiring downcast and other unsafe operations.
*
* @author Angelo Corsaro <mailto:angelo.corsaro@gmail.com>
* @version 1.0
*/

class ActiveConditionImpl {
public:
        virtual ~ActiveConditionImpl();
public:
        virtual void execute() = 0;
        virtual DDS::Boolean get_trigger_value () = 0;

protected:
        friend class ::simd::ActiveWaitSet;
        virtual DDS::Condition* get_dds_condition() = 0;
};

class ActiveCondition : public ::boost::shared_ptr<ActiveConditionImpl> {
protected:
      ActiveCondition(ActiveConditionImpl* aci);
public:
		virtual ~ActiveCondition();
};

class RDCondition : public ::boost::shared_ptr< ::DDS::ReadCondition >
{
public:
	/*
	explicit RDCondition(::DDS::ReadCondition* rc) {
		this->reset(rc);
	}
*/
	template <typename D> RDCondition(::DDS::ReadCondition* rc, D d) {
		this->reset(rc, d);
	}
	virtual ~RDCondition() { }
};

template <typename ARG, typename FUNCTOR>
class ActiveRDConditionImpl :
public virtual ActiveConditionImpl,
public virtual DDS::ReadCondition
{
public:

	ActiveRDConditionImpl(::simd::RDCondition rcond,
			const ARG& arg,
			const FUNCTOR& f)
	:  rcond_(rcond),
	arg_(arg),
	f_(f) { }

	virtual ~ActiveRDConditionImpl() { }
public:
	virtual DDS::SampleStateMask
	get_sample_state_mask() {
		return rcond_->get_sample_state_mask();
	}

	virtual DDS::ViewStateMask
	get_view_state_mask() {
		return rcond_->get_view_state_mask();
	}

	virtual DDS::InstanceStateMask
	get_instance_state_mask() {
		return rcond_->get_instance_state_mask();
	}

	virtual DDS::DataReader_ptr
	get_datareader() {
		return rcond_->get_datareader();
	}

public:
	virtual void
	execute() {
		f_(arg_);
	}

	virtual DDS::Boolean
	get_trigger_value() {
		return rcond_->get_trigger_value();
	}

protected:
	friend class ActiveWaitSet;
	DDS::Condition*
	get_dds_condition() {
		return rcond_.get();
	}

protected:
	::simd::RDCondition rcond_;
	ARG arg_;
	FUNCTOR f_;
};

// public ::boost::shared_ptr< ActiveReadConditionImpl<ARG, FUNCTOR> > {
template <typename ARG, typename FUNCTOR>
class ActiveRDCondition : public ActiveCondition {
public:
	ActiveRDCondition(RDCondition rcond, const ARG& arg, const FUNCTOR& f)
		: ActiveCondition(new ::simd::ActiveRDConditionImpl<ARG, FUNCTOR>(rcond, arg, f))
	{ }

	virtual ~ActiveRDCondition() { }
};

// -- Type definitions

typedef ::std::vector <ActiveCondition> ActiveConditionVector;

}


#endif	/* AC_SIMD_CONDITION_HPP */

