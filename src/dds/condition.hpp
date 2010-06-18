#ifndef AC_SIMD_DDS_CONDITION_HPP
#define	AC_SIMD_DDS_CONDITION_HPP

// C++ STD Include
#include <vector>

// -- BOOST Include
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

// -- DDS Includes
#include <dds_dcps.h>
#include <ccpp_dds_dcps.h>

// -- SIMD_DDS Includes
#include <dds/config.hpp>
#include <dds/peer/condition_impl.hpp>

namespace dds {

  class SIMD_API WaitSet;
  class SIMD_API Condition;
  // namespace peer {
  //   class SIMD_API ConditionImpl;
  //   class SIMD_API ReadConditionImpl;
  //   class SIMD_API QueryConditionImpl;
  // }
  /**
   * The <code>Condition</code> class allows provides a generic
   * interface for all those class that want to provide a command like
   * behviour. This command interfance is implemented by the
   * <b>SIMD_DDS</b> classes providing the condition behaviour. The
   * key advantage of using this command-based approach to condition
   * is that the dispatching can be performed directly and without
   * requiring downcast and other unsafe operations.
   *
   * @author Angelo Corsaro <mailto:angelo.corsaro@gmail.com>
   * @version 1.0
   */
  /////////////////////////////////////////////////////////////////////////////
  class SIMD_API Condition {
  public:
    Condition(dds::peer::ConditionImpl* ac);
    virtual ~Condition();

  public:
    bool
    operator==(const Condition& other);

    inline dds::peer::ConditionImpl*
    operator->() { return cond_.get(); }

    inline const dds::peer::ConditionImpl*
    operator->() const { return cond_.get(); }

  protected:
    template <typename CT2, typename CT1> friend CT2 downcast(CT1&);
    template <typename CT2, typename CT1> bool can_downcast(CT1& orig);
    ::boost::shared_ptr<dds::peer::ConditionImpl> cond_;
  };

  DEFINE_HANDLE_BODY_TRAITS(Condition, dds::peer::ConditionImpl)
    
  class SIMD_API ReadCondition: public Condition {
  public:
    ReadCondition(dds::peer::ReadConditionImpl* arci);
    virtual ~ReadCondition();

  public:
    bool
    operator==(const ReadCondition& other);

    inline dds::peer::ReadConditionImpl*
    operator->() { return pcond_; }

    inline const dds::peer::ReadConditionImpl*
    operator->() const { return pcond_; }

  protected:
    // Notice that reference counting is
    // maintained by the parent class.
    template <typename CT2, typename CT1> friend CT2 downcast(CT1&);
    template <typename CT2, typename CT1> bool can_downcast(CT1& orig);
    ReadCondition();
    dds::peer::ReadConditionImpl* pcond_;
  };

  DEFINE_HANDLE_BODY_TRAITS(ReadCondition, dds::peer::ReadConditionImpl)

  class SIMD_API QueryCondition: public ReadCondition {
  protected:
    QueryCondition(dds::peer::QueryConditionImpl* qcond);
    virtual ~QueryCondition();

  public:
    bool
    operator==(const ReadCondition& other);

    inline dds::peer::QueryConditionImpl*
    operator->() { return pcond_; }

    inline const dds::peer::QueryConditionImpl*
    operator->() const { return pcond_; }

  protected:
    // Refcount maintained by the root class.
    template <typename CT2, typename CT1> friend CT2 downcast(CT1&);
    template <typename CT2, typename CT1> bool can_downcast(CT1& orig);
    QueryCondition();
    dds::peer::QueryConditionImpl* pcond_;
  };

  DEFINE_HANDLE_BODY_TRAITS(QueryCondition, dds::peer::QueryConditionImpl)


  // -- Type definitions

  typedef ::std::vector<Condition> ConditionVector;


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

  template<typename ARG, typename FUNCTOR>
  class TReadCondition: public ReadCondition {
  public:
    TReadCondition(boost::shared_ptr<DDS::ReadCondition> rcond,
		   const ARG& arg, const FUNCTOR& f) :
      ReadCondition(new ::dds::peer::TReadConditionImpl<ARG, FUNCTOR>(rcond, arg, f)) {
      }
      
      virtual ~TReadCondition() {
      }
      
    public:
    inline dds::peer::ReadConditionImpl*
      operator->() { return pcond_; }
    
    inline const dds::peer::ReadConditionImpl*
    operator->() const { return pcond_; }
  };

}
#include <dds/peer/condition_impl.hpp>

#endif	/* AC_SIMD_DDS_CONDITION_HPP */

