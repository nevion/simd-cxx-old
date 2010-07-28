#ifndef AC_SIMD_DDS_CONTENT_FILTERED_TOPIC_IMPL_HPP
#define AC_SIMD_DDS_CONTENT_FILTERED_TOPIC_IMPL_HPP

#include <vector>

#include <dds/topic.hpp>
#include <dds/peer/runtime_impl.hpp>

namespace dds {
  namespace peer {
    template <typename T>
    class ContentFilteredTopicImpl;
  }
}

template <typename T>
class dds::peer::ContentFilteredTopicImpl {
public:
  /**
   * Creates a <code>ContentFilteredTopicImpl</code>.
   *
   * @param t the related topic
   * @param filter the SQL92 filter expression
   * @param params
   */
  ContentFilteredTopicImpl(const std::string& name,
                           const dds::Topic<T>& t,
                           const std::string& filter,
                           const std::vector<std::string>& params)

    : name_(name),
      topic_(t),
      filter_(filter),
      params_(params),
      dp_(dds::peer::RuntimeImpl::instance().get_participant())
  {
    DDS::StringSeq paramSeq;  
    paramSeq.length(params_.size() + 1);
    for (unsigned int i = 0; i < params_.size(); ++i) {
      paramSeq[i] = DDS::string_dup(params_[i].c_str());
    }
    // As per the OpenSplice DDS docs there seems to be the need for n+1 args.
    // thus we fill the (n+1)th within SimD.
    paramSeq[params_.size()] = DDS::string_dup("");
    
    cft_ = 
      dp_->create_contentfilteredtopic(name_.c_str(),
				       topic_->get_dds_topic(),
				       filter_.c_str(),
				       paramSeq);

    dds::Assert::postcondition(cft_ != 0,
                               "Unable to create ContentFilteredTopic",
                                __FILE__); 
  }

  ~ContentFilteredTopicImpl() {
    dp_->delete_contentfilteredtopic(cft_);
  }

 /**
   * Return the SQL92 expression used to filter the topic data
   *
   * @return a <code>std::string</code> representing the SQL92 expression.
   */
  std::string
  get_filter_expression() const {
    return filter_;
  }

  /**
   * Return the arguments used for the filtering expression.
   *
   * @return a <code>std::vector<std::string></code> containing the filter arguments.
   */
  std::vector<std::string>
  get_expression_parameters() const {
    return params_;
  }

  /**
   * Set the filter expression paramenters.
   *
   * @param params the filter expression parameters
   */
  void
  set_expression_parameters(const std::vector<std::string>& params) {
    params_ = params;
    DDS::StringSeq paramSeq;
    paramSeq.length(params_.size());
    for (unsigned int i = 0; i < params_.size(); ++i)
      paramSeq[i] = DDS::string_dup(params_[i].c_str());
    cft_->set_expression_parameters(paramSeq);
  }

  /**
   * Return the related topic.
   *
   * @return the related topic.
   */
  dds::Topic<T>
  get_related_topic() const {
    return topic_;
  }
  ///////////////////////////////////////////////////////////////////////////
  // -- Methods inherited from Topic Description
  virtual std::string
  get_name() const {
    return name_;
  }
  
  virtual std::string
  get_type_name() const {
    return cft_->get_type_name();
  }
  
  virtual dds::DomainParticipant
  get_participant() const {
    return dp_;
  }

public:
  TopicQos get_qos() const {
    return topic_.get_qos();
  }
  
  DDS::ReturnCode_t set_qos(const TopicQos& qos) {
    return topic_.set_qos(qos);
  }
  
public:
  /**
   * Give access to the handle of the DDS topic used to implement
   * this SimD topic. This method is not exposed to the public API and only
   * used by peer classes.
   *
   * @return the DDS <code>ContentFilteredTopic</code>
   */
  DDS::ContentFilteredTopic*
  get_dds_topic() const {
    return cft_;
  }
  
private:
  std::string name_;
  dds::Topic<T> topic_;
  std::string filter_;
  std::vector<std::string> params_;
  DDS::ContentFilteredTopic* cft_;
  dds::DomainParticipant dp_;
};

#endif /* AC_SIMD_DDS_CONTENT_FILTERED_TOPIC_IMPL_HPP */
