#ifndef CHRYSALIS_SERIALIZATION_H
#define CHRYSALIS_SERIALIZATION_H

#include <boost/preprocessor.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/unordered_map.hpp>

// --- Forward declarations --------------------------------------------------------------------------------------------
#define SERIALIZABLE(Class)                                                                                            \
Class;                                                                                                                 \
template<class Archive>                                                                                                \
void serialize(Archive&, Class&, const unsigned int);                                                                  \
template<class Archive>                                                                                                \
void load_construct_data(Archive&, Class*, const unsigned int);                                                        \
template<class Archive>                                                                                                \
void save_construct_data(Archive&, const Class*, const unsigned int);                                                  \
class Class

#define SERIALIZABLE_T(Class, T)                                                                                       \
Class;                                                                                                                 \
template<class Archive, typename T>                                                                                    \
void serialize(Archive&, Class<T>&, const unsigned int);                                                               \
template<class Archive, typename T>                                                                                    \
void load_construct_data(Archive&, Class<T>*, const unsigned int);                                                     \
template<class Archive, typename T>                                                                                    \
void save_construct_data(Archive&, const Class<T>*, const unsigned int);                                               \
template<typename T>                                                                                                   \
class Class

#define SERIALIZABLE_T_DERIVED_FROM(Class, T, Base)                                                                    \
Class;                                                                                                                 \
template<class Archive, typename T>                                                                                    \
void serialize(Archive&, Class<T>&, const unsigned int);                                                               \
template<class Archive, typename T>                                                                                    \
void load_construct_data(Archive&, Class<T>*, const unsigned int);                                                     \
template<class Archive, typename T>                                                                                    \
void save_construct_data(Archive&, const Class<T>*, const unsigned int);                                               \
template<typename T> requires std::derived_from<T, Base>                                                               \
class Class

// --- Friends (Optional) ----------------------------------------------------------------------------------------------
#define PROVIDE_SERIALIZATION_ACCESS(Class)                                                                            \
template<class Archive>                                                                                                \
friend void serialize(Archive& archive, Class& project, const unsigned int version);                                   \
template<class Archive>                                                                                                \
friend void save_construct_data(Archive&, const Class*, const unsigned int);                                           \
template<class Archive>                                                                                                \
friend void load_construct_data(Archive&, Class*, const unsigned int);

#define PROVIDE_DEFAULT_SERIALIZATION_ACCESS(Class)                                                                    \
PROVIDE_SERIALIZATION_ACCESS(Class)                                                                                    \
explicit Class() = default;

#define PROVIDE_SERIALIZATION_ACCESS_T(Class)                                                                          \
template<class Archive, typename TSerializable>                                                                        \
friend void serialize(Archive& archive, Class<TSerializable>& project, const unsigned int version);                    \
template<class Archive, typename TSerializable>                                                                        \
friend void save_construct_data(Archive&, const Class<TSerializable>*, const unsigned int);                            \
template<class Archive, typename TSerializable>                                                                        \
friend void load_construct_data(Archive&, Class<TSerializable>*, const unsigned int);

// --- Helpers ---------------------------------------------------------------------------------------------------------
#define LOAD_FIELD(r, data, field) archive >> field;
#define ACCESS_FIELD(r, data, field) archive & obj.field;
#define ACCESS_FIELD_PTR(r, data, field) archive & obj->field;
#define DECLARE_FIELD(r, data, field) decltype(obj->field) field;

// --- Specify constructor arguments -----------------------------------------------------------------------------------
#define SERIALIZATION_CONSTRUCTOR(Class, ...)                                                                          \
template<class Archive>                                                                                                \
void save_construct_data(Archive& archive, const Class* obj, const unsigned int) {                                     \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_SEQ_FOR_EACH(ACCESS_FIELD_PTR, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                  \
  )                                                                                                                    \
}                                                                                                                      \
template<class Archive>                                                                                                \
void load_construct_data(Archive& archive, Class* obj, const unsigned int) {                                           \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_SEQ_FOR_EACH(DECLARE_FIELD, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                     \
    BOOST_PP_SEQ_FOR_EACH(LOAD_FIELD, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                        \
  )                                                                                                                    \
  ::new(obj) Class(__VA_ARGS__);                                                                                       \
}

// --- Specify constructor arguments -----------------------------------------------------------------------------------
#define SERIALIZATION_CONSTRUCTOR_T(Class, T, ...)                                                                     \
template<class Archive, typename T>                                                                                    \
void save_construct_data(Archive& archive, const Class<T>* obj, const unsigned int) {                                  \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_SEQ_FOR_EACH(ACCESS_FIELD_PTR, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                  \
  )                                                                                                                    \
}                                                                                                                      \
template<class Archive, typename T>                                                                                    \
void load_construct_data(Archive& archive, Class<T>* obj, const unsigned int) {                                        \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_SEQ_FOR_EACH(DECLARE_FIELD, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                     \
    BOOST_PP_SEQ_FOR_EACH(LOAD_FIELD, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                        \
  )                                                                                                                    \
  ::new(obj) Class<T>(__VA_ARGS__);                                                                                    \
}

// --- Specify members to serialize ------------------------------------------------------------------------------------
#define SERIALIZE_MEMBERS(Class, ...)                                                                                  \
template<class Archive>                                                                                                \
void serialize(Archive& archive, Class& obj, const unsigned int version) {                                             \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_SEQ_FOR_EACH(ACCESS_FIELD, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                      \
  )                                                                                                                    \
}
// --- Specify members to serialize ------------------------------------------------------------------------------------
#define SERIALIZE_MEMBERS_T(Class, T, ...)                                                                             \
template<class Archive, typename T>                                                                                    \
void serialize(Archive& archive, Class<T>& obj, const unsigned int version) {                                          \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_SEQ_FOR_EACH(ACCESS_FIELD, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                      \
  )                                                                                                                    \
}
// --- Specify base class and members to serialize ---------------------------------------------------------------------
#define SERIALIZE_DERIVED_MEMBERS(Class, Base, ...)                                                                    \
template<class Archive>                                                                                                \
void serialize(Archive& archive, Class& obj, const unsigned int version) {                                             \
  archive & boost::serialization::base_object<Base>(obj);                                                              \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_SEQ_FOR_EACH(ACCESS_FIELD, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                      \
  )                                                                                                                    \
}

#define SERIALIZE_DERIVED_MEMBERS_T(Class, T, Base, ...)                                                               \
template<class Archive, typename T>                                                                                    \
void serialize(Archive& archive, Class<T>& obj, const unsigned int version) {                                          \
  archive & boost::serialization::base_object<Base<T>>(obj);                                                           \
  __VA_OPT__(                                                                                                          \
    BOOST_PP_SEQ_FOR_EACH(ACCESS_FIELD, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                      \
  )                                                                                                                    \
}

// --- Specify members to serialize and use default constructor --------------------------------------------------------
#define DEFAULT_SERIALIZE_MEMBERS(Class, ...)                                                                          \
SERIALIZE_MEMBERS(Class, __VA_ARGS__)                                                                                  \
SERIALIZATION_CONSTRUCTOR(Class)

// --- Specify members to serialize and use default constructor for class template -------------------------------------
#define DEFAULT_SERIALIZE_BASE_MEMBERS_T(Class, T, ...)                                                                \
SERIALIZE_MEMBERS_T(Class, T, __VA_ARGS__)

// --- Specify base class, members to serialize and use default constructor --------------------------------------------
#define DEFAULT_SERIALIZE_DERIVED_MEMBERS(Class, Base, ...)                                                            \
SERIALIZE_DERIVED_MEMBERS(Class, Base, __VA_ARGS__)                                                                    \
SERIALIZATION_CONSTRUCTOR(Class)

#define DEFAULT_SERIALIZE_DERIVED_MEMBERS_T(Class, T, Base, ...)                                                       \
SERIALIZE_DERIVED_MEMBERS_T(Class, T, Base, __VA_ARGS__)                                                               \
SERIALIZATION_CONSTRUCTOR_T(Class, T)

// --- Specify members to serialize and use same members in constructor ------------------------------------------------
#define SIMPLE_SERIALIZE_MEMBERS(Class, ...)                                                                           \
SERIALIZE_MEMBERS(Class, __VA_ARGS__)                                                                                  \
SERIALIZATION_CONSTRUCTOR(Class, __VA_ARGS__)

#define SIMPLE_SERIALIZE_MEMBERS_T(Class, T, ...)                                                                      \
SERIALIZE_MEMBERS_T(Class, T, __VA_ARGS__)                                                                             \
SERIALIZATION_CONSTRUCTOR_T(Class, T, __VA_ARGS__)

#define SIMPLE_SERIALIZE_DERIVED_MEMBERS(Class, Base, ...)                                                             \
SERIALIZE_DERIVED_MEMBERS(Class, Base, __VA_ARGS__)                                                                    \
SERIALIZATION_CONSTRUCTOR(Class, __VA_ARGS__)

#define EMPTY_SERIALIZABLE(Class)                                                                                      \
Class;                                                                                                                 \
template<class Archive>                                                                                                \
void serialize(Archive&, Class&, const unsigned int) {}                                                                \
class Class

#endif //CHRYSALIS_SERIALIZATION_H