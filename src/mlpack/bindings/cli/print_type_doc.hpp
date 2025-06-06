/**
 * @file bindings/cli/print_type_doc.hpp
 * @author Ryan Curtin
 *
 * Print documentation for a given type, detailing what the type actually is to
 * the user.
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_BINDINGS_CLI_PRINT_TYPE_DOC_HPP
#define MLPACK_BINDINGS_CLI_PRINT_TYPE_DOC_HPP

#include <mlpack/core/util/is_std_vector.hpp>

namespace mlpack {
namespace bindings {
namespace cli {

/**
 * Return a string representing the command-line type of an option.
 */
template<typename T>
std::string PrintTypeDoc(
    util::ParamData& data,
    const std::enable_if_t<!arma::is_arma_type<T>::value>* = 0,
    const std::enable_if_t<!util::IsStdVector<T>::value>* = 0,
    const std::enable_if_t<!data::HasSerialize<T>::value>* = 0,
    const std::enable_if_t<!std::is_same_v<T,
        std::tuple<data::DatasetInfo, arma::mat>>>* = 0);

/**
 * Return a string representing the command-line type of a vector.
 */
template<typename T>
std::string PrintTypeDoc(
    util::ParamData& data,
    const std::enable_if_t<util::IsStdVector<T>::value>* = 0);

/**
 * Return a string representing the command-line type of a matrix option.
 */
template<typename T>
std::string PrintTypeDoc(
    util::ParamData& data,
    const std::enable_if_t<arma::is_arma_type<T>::value>* = 0);

/**
 * Return a string representing the command-line type of a matrix tuple option.
 */
template<typename T>
std::string PrintTypeDoc(
    util::ParamData& data,
    const std::enable_if_t<std::is_same_v<T,
        std::tuple<data::DatasetInfo, arma::mat>>>* = 0);

/**
 * Return a string representing the command-line type of a model.
 */
template<typename T>
std::string PrintTypeDoc(
    util::ParamData& data,
    const std::enable_if_t<!arma::is_arma_type<T>::value>* = 0,
    const std::enable_if_t<data::HasSerialize<T>::value>* = 0);

/**
 * Print the command-line type of an option into a string.
 */
template<typename T>
void PrintTypeDoc(util::ParamData& data,
                  const void* /* input */,
                  void* output)
{
  *((std::string*) output) = PrintTypeDoc<std::remove_pointer_t<T>>(data);
}

} // namespace cli
} // namespace bindings
} // namespace mlpack

#include "print_type_doc_impl.hpp"

#endif
