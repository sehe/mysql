//
// Copyright (c) 2019-2021 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MYSQL_DETAIL_NETWORK_ALGORITHMS_CLOSE_STATEMENT_HPP
#define BOOST_MYSQL_DETAIL_NETWORK_ALGORITHMS_CLOSE_STATEMENT_HPP

#include "boost/mysql/detail/network_algorithms/common.hpp"

namespace boost {
namespace mysql {
namespace detail {

template <class Stream>
void close_statement(
    channel<Stream>& chan,
    std::uint32_t statement_id,
    error_code& code,
    error_info& info
);

template <class Stream, class CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void(error_code))
async_close_statement(
    channel<Stream>& chan,
    std::uint32_t statement_id,
    CompletionToken&& token,
    error_info& info
);

} // detail
} // mysql
} // boost

#include "boost/mysql/detail/network_algorithms/impl/close_statement.hpp"

#endif /* INCLUDE_BOOST_MYSQL_DETAIL_NETWORK_ALGORITHMS_CLOSE_STATEMENT_HPP_ */
