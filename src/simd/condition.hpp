#ifndef AC_SIMD_CONDITION_HPP
#define	AC_SIMD_CONDITION_HPP

// C++ STD Include
#include <vector>

// -- BOOST Include
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

// -- DDS Includes
#include <dds_dcps.h>
#include <ccpp_dds_dcps.h>

// -- SIMD Includes
#include <simd/config.hpp>

#define DEFINE_HANDLE_BODY_TRAITS(H, B)		\
  template<> struct handle_body_ptr<H> {	\
    typedef B* type;				\
  };						\
  template<> struct handle_body_type<H> {	\
    typedef B type;				\
  };						\
  template<> struct handle_body_ref<H> {	\
    typedef B& ref;				\
  };


namespace simd {

  class ActiveWaitSet;
  class ActiveCondition;

  // -- Handle/Body Traits classes
  template <typename E> struct handle_body_type { };
  template <typename E> struct handle_body_ptr { };
  template <typename E> struct handle_body_ref { };


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
  /////////////////////////////////////////////////////////////////////////////
  class ActiveConditionImpl {
  public:
    virtual ~ActiveConditionImpl();
  public:
    virtual void execute() = 0;
    virtual DDS::Boolean get_trigger_value() = 0;

  protected:
    friend class ::simd::ActiveWaitSet;
    friend class ::simd::ActiveCondition;
    virtual DDS::Condition* get_dds_condition() const = 0;
  };

  class ActiveCondition {
  public:
    ActiveCondition(ActiveConditionImpl* ac);
    virtual ~ActiveCondition();

  public:
    bool
    operator==(const ActiveCondition& other);

    inline ActiveConditionImpl*
    operator->() { return cond_.get(); }

    inline const ActiveConditionImpl*
    operator->() const { return cond_.get(); }

  protected:
    template <typename CT2, typename CT1> friend CT2 downcast(CT1&);
    template <typename CT2, typename CT1> bool can_downcast(CT1& orig);
      ::boost::shared_ptr<ActiveConditionImpl> cond_;

  };

  DEFINE_HANDLE_BODY_TRAITS(ActiveCondition, ActiveConditionImpl)

  /////////////////////////////////////////////////////////////////////////////
  class ActiveReadConditionImpl: public ActiveConditionImpl {
  public:
    virtual ~ActiveReadConditionImpl();
  public:
    virtual DDS::SampleStateMask get_sample_state_mask() = 0;
    virtual DDS::ViewStateMask get_view_state_mask() = 0;
    virtual DDS::InstanceStateMask get_instance_state_mask() = 0;
  };

  class ActiveReadCondition: public ActiveCondition {
  public:
    ActiveReadCondition(ActiveReadConditionImpl* arci);
    virtual ~ActiveReadCondition();

  public:
    bool
    operator==(const ActiveReadCondition& other);

    inline ActiveReadConditionImpl*
    operator->() { return pcond_; }

    inline const ActiveReadConditionImpl*
    operator->() const { return pcond_; }

  protected:
    // Notice that reference counting is
    // maintained by the parent class.
    template <typename CT2, typename CT1> friend CT2 downcast(CT1&);
    template <typename CT2, typename CT1> bool can_downcast(CT1& orig);
    ActiveReadCondition();
    ActiveReadConditionImpl* pcond_;
  };

  DEFINE_HANDLE_BODY_TRAITS(ActiveReadCondition, ActiveReadConditionImpl)

  /////////////////////////////////////////////////////////////////////////////
  class ActiveQueryConditionImpl: public ActiveReadConditionImpl {
  public:
    virtual ~ActiveQueryConditionImpl();

  public:
    virtual std::string get_query_expression() = 0;
    virtual std::string get_query_parameters() = 0;
    virtual void set_querly_parameters(const std::string& params) = 0;
  };

  class ActiveQueryCondition: public ActiveReadCondition {
  protected:
    ActiveQueryCondition(ActiveQueryConditionImpl* qcond);
    virtual ~ActiveQueryCondition();

  public:
    bool
    operator==(const ActiveReadCondition& other);

    inline ActiveQueryConditionImpl*
    operator->() { return pcond_; }

    inline const ActiveQueryConditionImpl*
    operator->() const { return pcond_; }

  protected:
    // Refcount maintained by the root class.
    template <typename CT2, typename CT1> friend CT2 downcast(CT1&);
    template <typename CT2, typename CT1> bool can_downcast(CT1& orig);
    ActiveQueryCondition();
    ActiveQueryConditionImpl* pcond_;
  };

  DEFINE_HANDLE_BODY_TRAITS(ActiveQueryCondition, ActiveQueryConditionImpl)

  /////////////////////////////////////////////////////////////////////////////
  //@TODO: Instead of inheriting the DDS::ReadCondition this should be inheriting
  // the proper actual class implementing the ReadCondition behaviour. Otherwise,
  // it won't be possible to pass instances of this class to the legacy waitset.
  // The caveat here is that the class implementing the ReadCondition is implementation
  // dependent, thus one potential approach is to add it as an extra template parameter that
  // will be bound by for each specific DDS implementation.
  template<typename ARG, typename FUNCTOR>
  class iActiveReadConditionImpl: public ActiveReadConditionImpl {
  public:
    // @TODO: Make this ctor protected and add ActiveReadCondition/DataReader as
    // friend classes
    iActiveReadConditionImpl(::boost::shared_ptr<DDS::ReadCondition> rcond,
			     const ARG& arg, const FUNCTOR& f) :
      rcond_(rcond), arg_(arg), f_(f) {
    }
  public:
    virtual ~iActiveReadConditionImpl() {
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
    friend class ActiveWaitSet;
    DDS::Condition*
    get_dds_condition() const {
      return rcond_.get();
    }

  protected:
    ::boost::shared_ptr<DDS::ReadCondition> rcond_;
    ARG arg_;
    FUNCTOR f_;
  };

  template<typename ARG, typename FUNCTOR>
  class iActiveReadCondition: public ActiveReadCondition {
  public:
    iActiveReadCondition(boost::shared_ptr<DDS::ReadCondition> rcond,
			 const ARG& arg, const FUNCTOR& f) :
      ActiveReadCondition(new ::simd::iActiveReadConditionImpl<ARG, FUNCTOR>(
									     rcond, arg, f)) {
    }

    virtual ~iActiveReadCondition() {
    }

  public:
    inline ActiveReadConditionImpl*
    operator->() { return pcond_; }

    inline const ActiveReadConditionImpl*
    operator->() const { return pcond_; }
  };

  // -- Type definitions

  typedef ::std::vector<ActiveCondition> ActiveConditionVector;


  // @TODO: This is a quick and dirty hack which should be implemented
  // in a  more general manner and w/o breaking encapsulation.
  // For the time being it suffice since the only class that ever require
  // downcast are Conditions.
  template <typename CT2, typename CT1> CT2 downcast(CT1& orig) {
    typename handle_body_ptr<CT1>::type b1 = orig.operator->();
    typename handle_body_ptr<CT2>::type b2 =
      dynamic_cast<typename handle_body_ptr<CT2>::type>(b1);
    CT2* pct2 = 0;
    if (b2 != 0) {
      pct2 = new CT2();
      pct2->cond_ = orig.cond_;
      pct2->pcond_ = b2;
    }
    Assert::postcondition(pct2 != 0, "downcast_condition: Attempted invalid conversion", __FILE__);
    return *pct2;
  }

  template <typename CT2, typename CT1> bool can_downcast(CT1& orig) {
    typename handle_body_ptr<CT1>::type b1 = orig.operator->();
    typename handle_body_ptr<CT2>::type b2 =
      dynamic_cast<typename handle_body_ptr<CT2>::type>(b1);
    return b2 != 0;
  }

}
#endif	/* AC_SIMD_CONDITION_HPP */

