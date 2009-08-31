#include <algorithm>
#include <simd/config.hpp>
#include <simd/waitset.hpp>


simd::ActiveWaitSet::ActiveWaitSet() { }

simd::ActiveWaitSet::ActiveWaitSet(const ActiveCondition& cond) {
	this->attach(cond);
}

simd::ActiveWaitSet::~ActiveWaitSet() {
	for (unsigned int i = 0; i < cond_vec_.size(); ++i) {
		waitset_.detach_condition(cond_vec_[i]->get_dds_condition());
	}
}

DDS::ReturnCode_t
simd::ActiveWaitSet::attach(const simd::ActiveCondition& cond) {
	cond_vec_.push_back(cond);
	return waitset_.attach_condition(cond->get_dds_condition());
}

DDS::ReturnCode_t
simd::ActiveWaitSet::detach(const simd::ActiveCondition& cond) {
	std::remove(cond_vec_.begin(), cond_vec_.end(), cond);
	return waitset_.detach_condition(cond->get_dds_condition());
}


simd::ActiveWaitSet&
simd::ActiveWaitSet::operator+=(const ::simd::ActiveCondition& cond) {
	this->attach(cond);
	return *this;
}


simd::ActiveWaitSet&
simd::ActiveWaitSet::operator-=(const simd::ActiveCondition& cond) {
	this->detach(cond);
	return *this;
}

simd::ActiveWaitSet::iterator
simd::ActiveWaitSet::begin() {
	return cond_vec_.begin();
}

simd::ActiveWaitSet::iterator
simd::ActiveWaitSet::end() {
	return cond_vec_.end();
}

simd::ActiveConditionVector
simd::ActiveWaitSet::wait(const DDS::Duration_t& timeout) {
	DDS::ConditionSeq cseq;
	waitset_.wait(cseq, timeout);
	ActiveConditionVector ecvec;

	for (unsigned int i = 0; i < cond_vec_.size(); ++i) {
		if (cond_vec_[i]->get_trigger_value())
			ecvec.push_back(cond_vec_[i]);
	}

	return ecvec;
}

void
simd::ActiveWaitSet::dispatch(const DDS::Duration_t& timeout) {
	DDS::ConditionSeq cseq;
	waitset_.wait(cseq, timeout);
	for (unsigned int i = 0; i < cond_vec_.size(); ++i)
			if (cond_vec_[i]->get_trigger_value())
				cond_vec_[i]->execute();
}

void
simd::ActiveWaitSet::dispatch() {
	this->dispatch(DDS::DURATION_INFINITE);
}

simd::ActiveConditionVector
simd::ActiveWaitSet::wait() {
	return this->wait(DDS::DURATION_INFINITE);
}
