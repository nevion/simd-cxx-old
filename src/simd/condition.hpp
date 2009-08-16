#ifndef AC_SIMD_CONDITION_HPP
#define	AC_SIMD_CONDITION_HPP

// -- BOOST Include
#include <boost/shared_ptr.hpp>

// -- DDS Includes
#include <dds_dcps.h>
#include <ccpp_dds_dcps.h>
#include <ccpp_Condition_impl.h>

// -- SIMD Includes
#include <simd/config.hpp>

namespace simd {

   /**
    * The <code>ExecCondition</code> class allows provides a generic interface for
    * all those class that want to provide a command like behviour. This command
    * interfance is implemented by the <b>SIMD</b> classes providing the
    * condition behaviour. The key advantage of using this command-based approach
    * to condition is that the dispatching can be performed directly and without
    * requiring downcast and other unsafe operations.
    *
    * @author Angelo Corsaro <mailto:angelo.corsaro@gmail.com>
    * @version 1.0
    */
   class ExecCondition {
   public:
      virtual ~ExecCondition();
   public:
      virtual void execute() = 0;
      virtual DDS::Boolean get_trigger_value () = 0;
   };

   template <typename ARG, typename FUNCTOR>
   class ReadConditionCommand : public virtual ExecCondition,
                                public virtual DDS::ReadCondition
   {
   public:

      ReadConditionCommand(boost::shared_ptr<DDS::ReadCondition> rcond,
                           const ARG& arg,
                           const FUNCTOR& f)
      :  rcond_(rcond),
         arg_(arg),
         f_(f) { }

      virtual ~ReadConditionCommand() {
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
      boost::shared_ptr<DDS::ReadCondition> rcond_;
      ARG arg_;
      FUNCTOR f_;
   };
}


#endif	/* AC_SIMD_CONDITION_HPP */

