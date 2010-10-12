#ifndef AC_SIMD_DDS_READER_HPP
#define AC_SIMD_DDS_READER_HPP

#include <dds/types.hpp>
#include <dds/condition.hpp>


namespace dds {

  template<typename T>
  class DataInstanceReader;

  template<typename T>
  class DataReader;

}
#include <dds/peer/reader_impl.hpp>

template <typename T>
class dds::DataReader {
public:
public:            
  typedef typename dds::peer::DataReaderImpl<T>::DR   DR;
  typedef typename dds::peer::DataReaderImpl<T>::TSeq TSeq;

public:
  DataReader() { }

  DataReader(const Topic<T>& topic) 
  {
    pimpl_.reset(new dds::peer::DataReaderImpl<T>(topic));
    pimpl_->set_datareader(this);
  }

  DataReader(const Topic<T>& topic, 
	     const DataReaderQos& qos) 
  {
    pimpl_.reset(new dds::peer::DataReaderImpl<T>(topic, qos));
    pimpl_->set_datareader(this);
  }

  DataReader(const ContentFilteredTopic<T>& topic) {
    pimpl_.reset(new dds::peer::DataReaderImpl<T>(topic));
    pimpl_->set_datareader(this);
  }

  DataReader(const ContentFilteredTopic<T>& topic,
             const DataReaderQos& qos) {
    pimpl_.reset(new dds::peer::DataReaderImpl<T>(topic, qos));
    pimpl_->set_datareader(this);
  }
  
  ~DataReader() { }

public:

  /**
   * Reads all new samples from any view state and alive instances. Notice
   * that this call is intended to loan the <code>samples</code> as
   * well as the <conde>infos</code> containers, thus will require a
   * return_loan.
   */
  inline dds::ReturnCode_t 
  read(TSeq& samples, 
       dds::SampleInfoSeq& infos) 
  {
    return pimpl_->read(samples, infos);
  }

  /**
   * Takes all new samples from any view state and alive instances. Notice
   * that this call is intended to loan the <code>samples</code> as
   * well as the <conde>infos</code> containers, thus will require a
   * return_loan.
   */
  inline dds::ReturnCode_t 
  take(TSeq& samples, 
       dds::SampleInfoSeq& infos) 
  {
    return pimpl_->take(samples, infos);
  }

  /**
   * Reads at most <code>max_samples</code> samples that have not been
   * read yet from all vies and alive instances.
   */
  dds::ReturnCode_t 
  read(TSeq& samples, 
       long max_samples) 
  {
    return pimpl_->read(samples, max_samples);
  }

  /**
   * Takes at most <code>max_samples</code> samples that have not been
   * read yet from all vies and alive instances.
   */
  dds::ReturnCode_t 
  take(TSeq& samples, 
       long max_samples) 
  {
    return pimpl_->take(samples, max_samples);
  }

  /**
   * Most generic <code>read</code> exposing all the knobs provided by
   * the OMG DDS API.
   */
  dds::ReturnCode_t 
  read(TSeq& samples, 
       dds::SampleInfoSeq& infos,
       long max_samples, 
       dds::SampleStateMask samples_state,
       dds::ViewStateMask views_state,
       dds::InstanceStateMask instances_state) 
  {
    return pimpl_->read(samples, 
			infos, 
			max_samples, 
			samples_state, 
			views_state, 
			instances_state);
  }

  /**
   * Most generic <code>take</code> exposing all the knobs provided by
   * the OMG DDS API.
   */
  dds::ReturnCode_t 
  take(TSeq& samples, 
       dds::SampleInfoSeq& infos,
       long max_samples, 
       dds::SampleStateMask samples_state,
       dds::ViewStateMask views_state,
       dds::InstanceStateMask instances_state) 
  {
    return pimpl_->take(samples, 
			infos, 
			max_samples, 
			samples_state, 
			views_state, 
			instances_state);
  }

  dds::ReturnCode_t 
  return_loan(TSeq& samples, 
	      dds::SampleInfoSeq& infos) 
  {
    return pimpl_->return_loan(samples, infos);
  }
  ////////////////////////////////////////////////////////////////////////////
  // -- ForwardIterator read/take
  template <typename DataForwardIterator, typename InfoForwardIterator> 
  uint32_t
  read(DataForwardIterator data_begin, 
       InfoForwardIterator info_begin,
       uint32_t max_samples, 
       dds::SampleStateMask samples_state,
       dds::ViewStateMask views_state,
       dds::InstanceStateMask instances_state) {
    return pimpl_->read(data_begin, info_begin, max_samples,
			samples_state, views_state, instances_state);
  }

  template <typename DataForwardIterator, typename InfoForwardIterator> 
  uint32_t
  read(DataForwardIterator data_begin, 
       InfoForwardIterator info_begin,
       uint32_t max_samples) {
    return pimpl_->read(data_begin, info_begin, max_samples);
  }

  //--------------------------------------------------------------------------
  template <typename DataForwardIterator, typename InfoForwardIterator> 
  uint32_t
  take(DataForwardIterator data_begin, 
       InfoForwardIterator info_begin,
       uint32_t max_samples) {
    return pimpl_->take(data_begin, info_begin, max_samples);
  }

  template <typename DataForwardIterator, typename InfoForwardIterator> 
  uint32_t
  take(DataForwardIterator data_begin, 
       InfoForwardIterator info_begin,
       uint32_t max_samples, 
       dds::SampleStateMask samples_state,
       dds::ViewStateMask views_state,
       dds::InstanceStateMask instances_state) {
    return pimpl_->take(data_begin, info_begin, max_samples,
			samples_state, views_state, instances_state);
  }
  //
  ////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////
  // -- OutputIterator read/take
  template <typename DataOutputIterator, typename InfoOutputIterator> 
  uint32_t
  read(DataOutputIterator data_begin, 
       InfoOutputIterator info_begin,
       dds::SampleStateMask samples_state,
       dds::ViewStateMask views_state,
       dds::InstanceStateMask instances_state) {
    return pimpl_->read(data_begin, info_begin, samples_state, views_state, instances_state);
  }
  
  template <typename DataOutputIterator> 
  uint32_t
  read(DataOutputIterator data_begin) {
    return pimpl_->read(data_begin);
  }
  //--------------------------------------------------------------------------
  template <typename DataOutputIterator, typename InfoOutputIterator> 
  uint32_t
  take(DataOutputIterator data_begin, 
       InfoOutputIterator info_begin,
       dds::SampleStateMask samples_state,
       dds::ViewStateMask views_state,
       dds::InstanceStateMask instances_state) {
    return pimpl_->read(data_begin, info_begin, samples_state, views_state, instances_state);
  }
  
  template <typename DataOutputIterator> 
  uint32_t
  take(DataOutputIterator data_begin) {
    return pimpl_->read(data_begin);
  }
  //
  ////////////////////////////////////////////////////////////////////////////
  
  ////////////////////////////////////////////////////////////////////////////
  // -- Vector read/take
  void read(std::vector<T>& data, 
	    std::vector<dds::SampleInfo>& info,
	    dds::SampleStateMask samples_state,
	    dds::ViewStateMask views_state,
	    dds::InstanceStateMask instances_state) {
    pimpl_->read(data, info, samples_state, views_state, instances_state);
  }
  
  void read(std::vector<T>& data, 
	    std::vector<dds::SampleInfo>& info) {
    pimpl_->read(data, info);
  }

  void read(std::vector<T>& data) {
    pimpl_->read(data);
  }

  void take(std::vector<T>& data, 
	    std::vector<dds::SampleInfo>& info,
	    dds::SampleStateMask samples_state,
	    dds::ViewStateMask views_state,
	    dds::InstanceStateMask instances_state) {
    pimpl_->take(data, info, samples_state, views_state, instances_state);
  }
  
  void take(std::vector<T>& data, 
	    std::vector<dds::SampleInfo>& info) {
    pimpl_->take(data, info);
  }

  void take(std::vector<T>& data) {
    pimpl_->take(data);
  }

public:
  // -- Qos Getter/Setter
  DataReaderQos 
  get_qos() {
    return pimpl_->get_qos();
  }

  dds::ReturnCode_t 
  set_qos(const DataReaderQos& qos) 
  {
    return pimpl_->set_qos(qos);
  }

  Topic<T> 
  get_topic() 
  {
    return pimpl_->get_topic();
  }

  dds::ReturnCode_t 
  wait_for_historical_data(const dds::Duration_t& timeout) 
  {
    return pimpl_->wait_for_historical_data(timeout);
  }

  // -- Condition API
  /**
   * Creates an <code>ReadCondition</code> that waits for new samples to
   * be arriving in order to notify.
   */
  template <typename F>
  ::dds::ReadCondition
  create_readcondition(const F& f)
  {
    return this->create_readcondition(f,
				      DDS::NOT_READ_SAMPLE_STATE,
				      DDS::ANY_VIEW_STATE,
				      DDS::ALIVE_INSTANCE_STATE);
  }
  
  
  template <typename F>
  ::dds::ReadCondition
  create_readcondition(const F& f, 
		       dds::SampleStateMask sample_state, 
		       dds::ViewStateMask view_state, 
		       dds::InstanceStateMask instance_state)
  {
    return pimpl_->create_readcondition(f,sample_state, view_state, instance_state);
  }


  /*
  ::dds::QueryCondition
  create_querycondition(const dds::SampleStateMask&     ssm,
			const dds::ViewStateMask&       vsm,
			const dds::InstanceStateMask&   ism,
			const std::string&              query_expr,
			const std::vector<std::string>& params) {
    return pimpl_->create_querycondition(ssm, vsm, ism, query_expre, params);
  }
  */
public:
  // Signal/Slot API
  
  template <typename Signal> 
  dds::sigcon_t 
  connect(typename Signal::template traits<T>::slot_type slot) {
    return pimpl_->connect<Signal>(slot);
  }
  
protected:
  boost::shared_ptr<dds::peer::DataReaderImpl<T> > pimpl_;
};

#endif /* AC_SIMD_DDS_READER_HPP */
