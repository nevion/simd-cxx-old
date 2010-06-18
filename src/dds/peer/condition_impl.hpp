#ifndef AC_SIMD_DDS_CONDITION_IMPL_HPP
#define AC_SIMD_DDS_CONDITION_IMPL_HPP

#include <dds/config.hpp>

namespace dds {
  class SIMD_API WaitSet;
  class SIMD_API Condition;

  namespace peer {

    class SIMD_API ConditionImpl {
    public:
      virtual ~ConditionImpl();
    public:
      virtual void execute() = 0;
      virtual DDS::Boolean get_trigger_value() = 0;

    protected:
      friend class ::dds::WaitSet;
      friend class ::dds::Condition;
      virtual DDS::Condition* get_dds_condition() const = 0;
    };

    ///////////////////////////////////////////////////////////////////////////
  class SIMD_API ReadConditionImpl: public ConditionImpl {
  public:
    virtual ~ReadConditionImpl();
  public:
    virtual DDS::SampleStateMask get_sample_state_mask() = 0;
    virtual DDS::ViewStateMask get_view_state_mask() = 0;
    virtual DDS::InstanceStateMask get_instance_state_mask() = 0;
  };


/////////////////////////////////////////////////////////////////////////////
    class SIMD_API QueryConditionImpl: public ReadConditionImpl {
  public:
    virtual ~QueryConditionImpl();

  public:
    virtual std::string get_query_expression() = 0;
    virtual std::string get_query_parameters() = 0;
    virtual void set_query_parameters(const std::string& params) = 0;
  };


    ///////////////////////////////////////////////////////////////////////////
    //@TODO: Instead of inheriting the DDS::ReadCondition this should be
    // inheriting the proper actual class implementing the ReadCondition
    // behaviour. Otherwise, it won't be possible to pass instances of
    // this class to the legacy waitset.  The caveat here is that the
    // class implementing the ReadCondition is implementation dependent,
    // thus one potential approach is to add it as an extra template
    // parameter that will be bound by for each specific DDS
    // implementation.
    template<typename ARG, typename FUNCTOR>
    class TReadConditionImpl: public ReadConditionImpl {
    public:
      // @TODO: Make this ctor protected and add ReadCondition/DataReader as
      // friend classes
      TReadConditionImpl(::boost::shared_ptr<DDS::ReadCondition> rcond,
			 const ARG& arg, const FUNCTOR& f) :
	rcond_(rcond), arg_(arg), f_(f) {
      }
    public:
      virtual ~TReadConditionImpl() {
      }

    public:
      virtual DDS::SampleStateMask get_sample_state_mask() {
	return rcond_->get_sample_state_mask();
      }

      virtual DDS::ViewStateMask get_view_state_mask() {
	return rcond_->get_view_state_mask();
      }

      virtual DDS::InstanceStateMask get_instance_state_mask() {
	return rcond_->get_instance_state_mask();
      }

      virtual DDS::DataReader_ptr get_datareader() {
	return rcond_->get_datareader();
      }

    public:
      virtual void execute() {
	f_(arg_);
      }

      virtual DDS::Boolean get_trigger_value() {
	return rcond_->get_trigger_value();
      }

    protected:
      friend class WaitSet;
      DDS::Condition*
      get_dds_condition() const {
	return rcond_.get();
      }

    protected:
      ::boost::shared_ptr<DDS::ReadCondition> rcond_;
      ARG arg_;
      FUNCTOR f_;
    };
  }}
#endif /* AC_SIMD_DDS_CONDITION_IMPL_HPP */
