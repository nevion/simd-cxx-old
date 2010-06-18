#include <algorithm>
#include <dds/config.hpp>
#include <dds/waitset.hpp>


dds::WaitSet::WaitSet() { }

dds::WaitSet::WaitSet(const Condition& cond) {
	this->attach(cond);
}

dds::WaitSet::~WaitSet() {
	for (unsigned int i = 0; i < cond_vec_.size(); ++i) {
		waitset_.detach_condition(cond_vec_[i]->get_dds_condition());
	}
}

dds::ReturnCode_t
dds::WaitSet::attach(const dds::Condition& cond) {
	cond_vec_.push_back(cond);
	return waitset_.attach_condition(cond->get_dds_condition());
}

dds::ReturnCode_t
dds::WaitSet::detach(const dds::Condition& cond) {
  cond_vec_.erase(std::remove(cond_vec_.begin(), cond_vec_.end(), cond), 
		  cond_vec_.end());
  return waitset_.detach_condition(cond->get_dds_condition());
}


dds::WaitSet&
dds::WaitSet::operator+=(const ::dds::Condition& cond) {
	this->attach(cond);
	return *this;
}


dds::WaitSet&
dds::WaitSet::operator-=(const dds::Condition& cond) {
	this->detach(cond);
	return *this;
}

dds::WaitSet::iterator
dds::WaitSet::begin() {
	return cond_vec_.begin();
}

dds::WaitSet::iterator
dds::WaitSet::end() {
	return cond_vec_.end();
}

dds::ConditionVector
dds::WaitSet::wait(const dds::Duration_t& timeout) {
	DDS::ConditionSeq cseq;
	waitset_.wait(cseq, timeout);
	ConditionVector ecvec;

	for (unsigned int i = 0; i < cond_vec_.size(); ++i) {
		if (cond_vec_[i]->get_trigger_value())
			ecvec.push_back(cond_vec_[i]);
	}

	return ecvec;
}

void
dds::WaitSet::dispatch(const dds::Duration_t& timeout) {
	DDS::ConditionSeq cseq;
	waitset_.wait(cseq, timeout);
	for (unsigned int i = 0; i < cond_vec_.size(); ++i)
			if (cond_vec_[i]->get_trigger_value())
				cond_vec_[i]->execute();
}

void
dds::WaitSet::dispatch() {
	this->dispatch(DDS::DURATION_INFINITE);
}

dds::ConditionVector
dds::WaitSet::wait() {
	return this->wait(DDS::DURATION_INFINITE);
}
