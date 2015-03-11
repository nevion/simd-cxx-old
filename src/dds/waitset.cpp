#include <algorithm>
#include <dds/config.hpp>
#include <dds/waitset.hpp>

DEFINE_EXCEPTION(dds, InterruptedException)

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

::dds::ConditionVector 
dds::WaitSet::triggered_conditions() {
  ConditionVector ecvec;
  
  for (unsigned int i = 0; i < cond_vec_.size(); ++i) {
    if (cond_vec_[i]->get_trigger_value())
      ecvec.push_back(cond_vec_[i]);
  }
  return ecvec;
}

void 
dds::WaitSet::wait (DDS::ConditionSeq& seq) {
  int rc = waitset_.wait(seq, DDS::DURATION_INFINITE);
  if (rc == DDS::RETCODE_ALREADY_DELETED)
    throw dds::InterruptedException("Wait Interrupted by External Signal",
				    __FILE__, rc);
}

void
dds::WaitSet::wait(const dds::Duration_t& timeout) {
  DDS::ConditionSeq cseq;
  int rc = waitset_.wait(cseq, timeout);
  if (rc == DDS::RETCODE_ALREADY_DELETED)
    throw dds::InterruptedException("Wait Interrupted by External Signal",
				    __FILE__, rc);
}

void
dds::WaitSet::dispatch(const dds::Duration_t& timeout) {
	DDS::ConditionSeq cseq;
	int rc = waitset_.wait(cseq, timeout);
	if (rc == DDS::RETCODE_ALREADY_DELETED)
	  throw dds::InterruptedException("Wait Interrupted by External Signal",
					  __FILE__, rc);
	
	for (unsigned int i = 0; i < cond_vec_.size(); ++i)
	  if (cond_vec_[i]->get_trigger_value())
	    cond_vec_[i]->execute();
}

void
dds::WaitSet::dispatch() {
	this->dispatch(DDS::DURATION_INFINITE);
}

void
dds::WaitSet::wait() {
  this->wait(DDS::DURATION_INFINITE);
}

#if defined(WIN32)
HANDLE
#elif defined(_POSIX_C_SOURCE)
int
#endif
dds::WaitSet::get_os_waitable_handle(){
    return waitset_.get_os_waitable_handle();
}

uint64_t dds::WaitSet::clear_os_waitable_handle_events(){
    return waitset_.clear_os_waitable_handle_events();
}
