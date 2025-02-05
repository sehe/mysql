//
// Copyright (c) 2019-2021 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MYSQL_DETAIL_PROTOCOL_TEXT_DESERIALIZATION_HPP
#define BOOST_MYSQL_DETAIL_PROTOCOL_TEXT_DESERIALIZATION_HPP

#include "boost/mysql/detail/protocol/serialization.hpp"
#include "boost/mysql/error.hpp"
#include "boost/mysql/value.hpp"
#include "boost/mysql/metadata.hpp"
#include <vector>

namespace boost {
namespace mysql {
namespace detail {

inline errc deserialize_text_value(
    boost::string_view from,
    const field_metadata& meta,
    value& output
);

inline error_code deserialize_text_row(
    deserialization_context& ctx,
    const std::vector<field_metadata>& meta,
    std::vector<value>& output
);

} // detail
} // mysql
} // boost

#include "boost/mysql/detail/protocol/impl/text_deserialization.ipp"

#endif
