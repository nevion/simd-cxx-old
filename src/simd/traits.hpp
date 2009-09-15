#ifndef AC_SIMD_TRAITS_HPP
#define AC_SIMD_TRAITS_HPP

namespace simd {  
  template <typename Topic>
  struct topic_type_support { };

  template <typename Topic>
  struct topic_data_writer { };
  
  template <typename Topic>
  struct topic_data_reader { };

  template <typename Topic>
  struct topic_data_seq { };

  // -- Handle/Body Traits classes
   template <typename E>
   struct handle_body_type { };

   template <typename E>
   struct handle_body_ptr { };

   template <typename E>
   struct handle_body_ref { };
}

#define REGISTER_TOPIC_TRAITS(TOPIC) \
namespace simd { \
  template<> struct topic_type_support<TOPIC> { \
    typedef TOPIC##TypeSupport type; \
  }; \
 \
  template<> struct topic_data_writer<TOPIC> { \
    typedef TOPIC##DataWriter type;		       \
  }; \
  \
  template<> struct topic_data_reader<TOPIC> { \
    typedef TOPIC##DataReader type; \
  }; \
  template<> struct topic_data_seq<TOPIC> { \
    typedef TOPIC##Seq type; \
  }; \
}  

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


#endif /* AC_SIMD_TRAITS_HPP */
