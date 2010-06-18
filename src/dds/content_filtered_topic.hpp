#ifndef AC_SIMD_DDS_CONTENT_FILTERED_TOPIC_HPP
#define AC_SIMD_DDS_CONTENT_FILTERED_TOPIC_HPP

#include <dds/config.hpp>
#include <dds/topic.hpp>
#include <dds/topic_description.hpp>
#include <dds/peer/content_filtered_topic_impl.hpp>

namespace dds {
  template <typename T>
  class ContentFilteredTopic;
/*
  namespace peer {
    template <typename T>
    class ContentFilteredTopicImpl;
  }*/
}

/**
 * This class implements the DDS <code>ContentFilteredTopic</code>
 * which allows application to express constraints on the subscribed data
 * by means of SQL92 expressions.
 *
 * @author Angelo Corsaro <angelo.corsaro@gmail.com>
 */
template <typename T>
class dds::ContentFilteredTopic : public dds::TopicDescription {
public:
  /**
   * Creates a void <code>ContentFilteredTopic</code>
   */
  ContentFilteredTopic() {}
  /**
   * Creates a <code>ContentFilteredTopic</code>.
   *
   * @param name the topic name
   * @param t the related topic
   * @param filter the SQL92 filter expression
   * @param params
   */
  ContentFilteredTopic(const std::string& name,
                       const dds::Topic<T>& t,
		       const std::string& filter,
		       const std::vector<std::string>& params)

  : pimpl_(new dds::peer::ContentFilteredTopicImpl<T>(name, t, filter, params))
  { }

  /**
   * Destroys this <code>ContentFilteredTopic</code> references and as a result
   * decrements the reference count of the underlying implementation. If the
   * reference count drops to zero the underlying implementation object is collected.s
   */
  virtual ~ContentFilteredTopic() { }
  
public:
  /**
   * Return the SQL92 expression used to filter the topic data
   *
   * @return a <code>std::string</code> representing the SQL92 expression.
   */
  std::string 
  get_filter_expression() const {
    return pimpl_->get_filter_expression();
  }

  /**
   * Return the arguments used for the filtering expression.
   *
   * @return a <code>std::vector<std::string></code> containing the
   * filter arguments.
   */
  std::vector<std::string>
  get_expression_parameters() const {
    return pimpl_->get_expression_parameters();
  }

  /**
   * Set the filter expression paramenters.
   *
   * @param params the filter expression parameters
   */
  void
  set_expression_parameters(const std::vector<std::string>& params) {
    pimpl_->set_expression_parameters(params);
  }

  /**
   * Return the related topic.
   *
   * @return the related topic.
   */
  dds::Topic<T> 
  get_related_topic() const {
    return pimpl_->get_related_topic();
  }
  ///////////////////////////////////////////////////////////////////////////
  // -- Methods inherited from Topic Description
  virtual std::string
  get_name() const {
    return pimpl_->get_name();
  }
  
  virtual std::string
  get_type_name() const {
    return pimpl_->get_type_name();
  }

  virtual dds::DomainParticipant
  get_participant() const {
    return pimpl_->get_participant();
  }
  ///////////////////////////////////////////////////////////////////////////

  TopicQos
  get_qos() const
  {
    return pimpl_->get_qos();
  }


  dds::ReturnCode_t
  set_qos(const TopicQos& qos)
  {
    return pimpl_->set_qos(qos);
  }

public:
  boost::shared_ptr<dds::peer::ContentFilteredTopicImpl<T> >
  operator->() {
    return pimpl_;
  }
private:
  boost::shared_ptr<dds::peer::ContentFilteredTopicImpl<T> > pimpl_;
};
#endif /* AC_SIMD_DDS_CONTENT_FILTERED_TOPIC_HPP */
