#ifndef CHRYSALIS_SERIALIZATION_H
#define CHRYSALIS_SERIALIZATION_H

#include <boost/preprocessor.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/unordered_map.hpp>

// --- Helpers ---------------------------------------------------------------------------------------------------------

#define LOAD_FIELD(r, data, field) archive >> field;
#define ACCESS_FIELD(r, data, field) archive & obj.field;
#define ACCESS_MEMBER(r, data, field) archive & this->field;
#define ACCESS_FIELD_PTR(r, data, field) archive & obj->field;
#define DECLARE_FIELD(r, data, field) decltype(obj->field) field;
#define LOAD_BASE(r, data, base) archive & boost::serialization::base_object<base>(obj);
#define FORWARD_MEMBER(r, data, field) std::forward<decltype((obj)->field)>(field)

// --- Friends for constructors ----------------------------------------------------------------------------------------

#define PROVIDE_CONSTRUCTION_ACCESS(Class)                                                                             \
template<class Archive>                                                                                                \
friend void save_construct_data(Archive&, const Class*, const unsigned int);                                           \
template<class Archive>                                                                                                \
friend void load_construct_data(Archive&, Class*, const unsigned int);

#define PROVIDE_SERIALIZATION_ACCESS(Class)                                                                            \
template<class Archive>                                                                                                \
friend void serialize(Archive& archive, Class& project, const unsigned int version);                                   \
template<class Archive>                                                                                                \
friend void save_construct_data(Archive&, const Class*, const unsigned int);                                           \
template<class Archive>                                                                                                \
friend void load_construct_data(Archive&, Class*, const unsigned int);

#define PROVIDE_SERIALIZATION_ACCESS_T(Class)                                                                          \
template<class Archive, typename Type>                                                                                 \
friend void serialize(Archive& archive, Class<Type>& project, const unsigned int version);                             \
template<class Archive, typename Type>                                                                                 \
friend void save_construct_data(Archive&, const Class<Type>*, const unsigned int);                                     \
template<class Archive, typename Type>                                                                                 \
friend void load_construct_data(Archive&, Class<Type>*, const unsigned int);

#define PROVIDE_DEFAULT_SERIALIZATION_ACCESS(Class) explicit Class() = default;

// --- Intrusive serialization -----------------------------------------------------------------------------------------

#define SERIALIZE_BASE_T(Class, ...)                                                                                   \
template <class Archive, typename T>                                                                                   \
void serialize_base(Archive& archive, Class<T>& obj) {                                                                 \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_SEQ_FOR_EACH(LOAD_BASE, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                         \
  )                                                                                                                    \
}

#define SERIALIZED                                                                                                     \
friend boost::serialization::access;                                                                                   \
template<class Archive>                                                                                                \
static void serialize(Archive&, const unsigned int) {}

#define SERIALIZE(...)                                                                                                 \
friend boost::serialization::access;                                                                                   \
template<class Archive>                                                                                                \
void serialize(Archive& archive, const unsigned int) {                                                                 \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_SEQ_FOR_EACH(ACCESS_MEMBER, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                     \
  )                                                                                                                    \
}

#define SERIALIZE_DERIVED_FROM(Base, ...)                                                                              \
friend boost::serialization::access;                                                                                   \
template<class Archive>                                                                                                \
void serialize(Archive& archive, const unsigned int) {                                                                 \
  archive & boost::serialization::base_object<Base>(*this);                                                            \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_LIST_FOR_EACH(ACCESS_MEMBER, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))                                   \
  )                                                                                                                    \
}

// --- Constructors ----------------------------------------------------------------------------------------------------

#define SERIALIZATION_CONSTRUCTOR(Class, ...)                                                                          \
template<class Archive>                                                                                                \
void save_construct_data(Archive& archive, const Class* obj, const unsigned int) {                                     \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_LIST_FOR_EACH(ACCESS_FIELD_PTR, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))                                \
  )                                                                                                                    \
}                                                                                                                      \
template<class Archive>                                                                                                \
void load_construct_data(Archive& archive, Class* obj, const unsigned int) {                                           \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_LIST_FOR_EACH(DECLARE_FIELD, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))                                   \
    BOOST_PP_LIST_FOR_EACH(LOAD_FIELD, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))                                      \
  )                                                                                                                    \
  ::new(obj) Class(                                                                                                    \
      BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(FORWARD_MEMBER, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))              \
  );                                                                                                                   \
}

#define SERIALIZATION_CONSTRUCTOR_T(Class, ...)                                                                        \
template<class Archive, typename T>                                                                                    \
void save_construct_data(Archive& archive, const Class<T>* obj, const unsigned int) {                                  \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_LIST_FOR_EACH(ACCESS_FIELD_PTR, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))                                \
  )                                                                                                                    \
}                                                                                                                      \
template<class Archive, typename T>                                                                                    \
void load_construct_data(Archive& archive, Class<T>* obj, const unsigned int) {                                        \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_LIST_FOR_EACH(DECLARE_FIELD, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))                                   \
    BOOST_PP_LIST_FOR_EACH(LOAD_FIELD, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))                                      \
  )                                                                                                                    \
  ::new(obj) Class<T>(__VA_ARGS__);                                                                                    \
}

// --- Specify members to serialize and use same members in constructor ------------------------------------------------

#define SERIALIZE_CONSTRUCTION(Class, ...)                                                                             \
template<class Archive>                                                                                                \
void serialize(Archive& archive, Class& obj, const unsigned int version) {}                                            \
SERIALIZATION_CONSTRUCTOR(Class, __VA_ARGS__)

#define SERIALIZE_DERIVED_CONSTRUCTION(Class, Base, ...)                                                               \
template<class Archive>                                                                                                \
void serialize(Archive& archive, Class& obj, const unsigned int version) {                                             \
  archive & boost::serialization::base_object<Base>(obj);                                                              \
}                                                                                                                      \
SERIALIZATION_CONSTRUCTOR(Class, __VA_ARGS__)

#define SERIALIZE_DERIVED_CONSTRUCTION_T(Class, Base, ...)                                                             \
template<class Archive, typename T>                                                                                    \
void serialize(Archive& archive, Class<T>& obj, const unsigned int version) {                                          \
  archive & boost::serialization::base_object<Base<T>>(obj);                                                           \
}                                                                                                                      \
SERIALIZATION_CONSTRUCTOR_T(Class, __VA_ARGS__)

#endif //CHRYSALIS_SERIALIZATION_H