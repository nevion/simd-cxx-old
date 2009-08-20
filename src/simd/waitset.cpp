#include <algorithm>
#include <simd/config.hpp>
#include <simd/waitset.hpp>


simd::ExecutableWaitSet::ExecutableWaitSet() { }

simd::ExecutableWaitSet::ExecutableWaitSet(const ExecutableConditionRef& cond) {
	this->attach(cond);
}

simd::ExecutableWaitSet::~ExecutableWaitSet() {
	for (unsigned int i = 0; i < cond_vec_.size(); ++i) {
		waitset_.detach_condition(cond_vec_[i]->get_dds_condition());
	}
}

DDS::ReturnCode_t
simd::ExecutableWaitSet::attach(const simd::ExecutableConditionRef& cond) {
	cond_vec_.push_back(cond);
	return waitset_.attach_condition(cond->get_dds_condition());
}

DDS::ReturnCode_t
simd::ExecutableWaitSet::detach(const simd::ExecutableConditionRef& cond) {
	std::remove(cond_vec_.begin(), cond_vec_.end(), cond);
	return waitset_.detach_condition(cond->get_dds_condition());
}


simd::ExecutableWaitSet&
simd::ExecutableWaitSet::operator+=(const ::simd::ExecutableConditionRef& cond) {
	this->attach(cond);
	return *this;
}


simd::ExecutableWaitSet&
simd::ExecutableWaitSet::operator-=(const simd::ExecutableConditionRef& cond) {
	this->detach(cond);
	return *this;
}

simd::ExecutableWaitSet::iterator
simd::ExecutableWaitSet::begin() {
	return cond_vec_.begin();
}

simd::ExecutableWaitSet::iterator
simd::ExecutableWaitSet::end() {
	return cond_vec_.end();
}

simd::ExecutableConditionVector
simd::ExecutableWaitSet::wait(const DDS::Duration_t& timeout) {
	DDS::ConditionSeq cseq;
	waitset_.wait(cseq, timeout);
	ExecutableConditionVector ecvec;

	for (unsigned int i = 0; i < cseq.length(); ++i) {
		ExecutableCondition* ec = dynamic_cast<ExecutableCondition*>(cseq[i].in());
		ecvec.push_back(boost::shared_ptr<ExecutableCondition>(ec));
	}

	return ecvec;
}

simd::ExecutableConditionVector
simd::ExecutableWaitSet::wait() {
	return this->wait(DDS::DURATION_INFINITE);
}
