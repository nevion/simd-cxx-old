#include <algorithm>
#include <dds/config.hpp>
#include <dds/waitset.hpp>


dds::ActiveWaitSet::ActiveWaitSet() { }

dds::ActiveWaitSet::ActiveWaitSet(const ActiveCondition& cond) {
	this->attach(cond);
}

dds::ActiveWaitSet::~ActiveWaitSet() {
	for (unsigned int i = 0; i < cond_vec_.size(); ++i) {
		waitset_.detach_condition(cond_vec_[i]->get_dds_condition());
	}
}

DDS::ReturnCode_t
dds::ActiveWaitSet::attach(const dds::ActiveCondition& cond) {
	cond_vec_.push_back(cond);
	return waitset_.attach_condition(cond->get_dds_condition());
}

DDS::ReturnCode_t
dds::ActiveWaitSet::detach(const dds::ActiveCondition& cond) {
	std::remove(cond_vec_.begin(), cond_vec_.end(), cond);
	return waitset_.detach_condition(cond->get_dds_condition());
}


dds::ActiveWaitSet&
dds::ActiveWaitSet::operator+=(const ::dds::ActiveCondition& cond) {
	this->attach(cond);
	return *this;
}


dds::ActiveWaitSet&
dds::ActiveWaitSet::operator-=(const dds::ActiveCondition& cond) {
	this->detach(cond);
	return *this;
}

dds::ActiveWaitSet::iterator
dds::ActiveWaitSet::begin() {
	return cond_vec_.begin();
}

dds::ActiveWaitSet::iterator
dds::ActiveWaitSet::end() {
	return cond_vec_.end();
}

dds::ActiveConditionVector
dds::ActiveWaitSet::wait(const DDS::Duration_t& timeout) {
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
dds::ActiveWaitSet::dispatch(const DDS::Duration_t& timeout) {
	DDS::ConditionSeq cseq;
	waitset_.wait(cseq, timeout);
	for (unsigned int i = 0; i < cond_vec_.size(); ++i)
			if (cond_vec_[i]->get_trigger_value())
				cond_vec_[i]->execute();
}

void
dds::ActiveWaitSet::dispatch() {
	this->dispatch(DDS::DURATION_INFINITE);
}

dds::ActiveConditionVector
dds::ActiveWaitSet::wait() {
	return this->wait(DDS::DURATION_INFINITE);
}
