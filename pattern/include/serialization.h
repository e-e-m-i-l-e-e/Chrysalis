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

// --- Friends (Optional) ----------------------------------------------------------------------------------------------
#define PROVIDE_SERIALIZATION_ACCESS(Class)                                                                            \
template<class Archive>                                                                                                \
friend void serialize(Archive& archive, Class& project, const unsigned int version);                                   \
template<class Archive>                                                                                                \
friend void save_construct_data(Archive&, const Class*, const unsigned int);                                           \
template<class Archive>                                                                                                \
friend void load_construct_data(Archive&, Class*, const unsigned int);

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
    ::new(obj) Class(__VA_ARGS__);                                                                                     \
}

// --- Specify members to serialize ------------------------------------------------------------------------------------
#define SERIALIZE_MEMBERS(Class, ...)                                                                                  \
template<class Archive>                                                                                                \
void serialize(Archive& archive, Class& obj, const unsigned int version) {                                             \
    BOOST_PP_SEQ_FOR_EACH(ACCESS_FIELD, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                      \
}

// --- Specify members to serialize and use default constructor --------------------------------------------------------
#define DEFAULT_SERIALIZE_MEMBERS(Class, ...)                                                                          \
SERIALIZE_MEMBERS(Class, __VA_ARGS__)                                                                                  \
SERIALIZATION_CONSTRUCTOR(Class)

// --- Specify members to serialize and use same members in constructor ------------------------------------------------
#define SIMPLE_SERIALIZE_MEMBERS(Class, ...)                                                                           \
SERIALIZE_MEMBERS(Class, __VA_ARGS__)                                                                                  \
SERIALIZATION_CONSTRUCTOR(Class, __VA_ARGS__)

#endif //CHRYSALIS_SERIALIZATION_H