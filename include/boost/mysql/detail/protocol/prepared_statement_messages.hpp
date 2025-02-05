//
// Copyright (c) 2019-2021 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MYSQL_DETAIL_PROTOCOL_PREPARED_STATEMENT_MESSAGES_HPP
#define BOOST_MYSQL_DETAIL_PROTOCOL_PREPARED_STATEMENT_MESSAGES_HPP

#include "boost/mysql/detail/protocol/serialization.hpp"
#include "boost/mysql/detail/protocol/constants.hpp"
#include "boost/mysql/value.hpp"

namespace boost {
namespace mysql {
namespace detail {

// prepare
struct com_stmt_prepare_packet
{
    string_eof statement;

    static constexpr std::uint8_t command_id = 0x16;

    template <class Self, class Callable>
    static void apply(Self& self, Callable&& cb)
    {
        std::forward<Callable>(cb)(
            self.statement
        );
    }
};

// response
struct com_stmt_prepare_ok_packet
{
    // std::uint8_t status: must be 0
    std::uint32_t statement_id;
    std::uint16_t num_columns;
    std::uint16_t num_params;
    // std::uint8_t reserved_1: must be 0
    std::uint16_t warning_count;
    // std::uint8_t metadata_follows when CLIENT_OPTIONAL_RESULTSET_METADATA: not implemented

    template <class Self, class Callable>
    static void apply(Self& self, Callable&& cb)
    {
        std::forward<Callable>(cb)(
            self.statement_id,
            self.num_columns,
            self.num_params,
            self.warning_count
        );
    }
};

template <>
struct serialization_traits<com_stmt_prepare_ok_packet, serialization_tag::struct_with_fields> :
    noop_serialize<com_stmt_prepare_ok_packet>
{
    static inline errc deserialize_(deserialization_context& ctx,
            com_stmt_prepare_ok_packet& output) noexcept;
};

// execute
template <class ValueForwardIterator>
struct com_stmt_execute_packet
{
    std::uint32_t statement_id;
    std::uint8_t flags;
    std::uint32_t iteration_count;
    // if num_params > 0: NULL bitmap
    std::uint8_t new_params_bind_flag;
    ValueForwardIterator params_begin;
    ValueForwardIterator params_end;

    static constexpr std::uint8_t command_id = 0x17;

    template <class Self, class Callable>
    static void apply(Self& self, Callable&& cb)
    {
        std::forward<Callable>(cb)(
            self.statement_id,
            self.flags,
            self.iteration_count,
            self.new_params_bind_flag
        );
    }
};

template <class ValueForwardIterator>
struct serialization_traits<
    com_stmt_execute_packet<ValueForwardIterator>,
    serialization_tag::struct_with_fields
> : noop_deserialize<com_stmt_execute_packet<ValueForwardIterator>>
{
    static inline std::size_t get_size_(const serialization_context& ctx,
            const com_stmt_execute_packet<ValueForwardIterator>& value) noexcept;
    static inline void serialize_(serialization_context& ctx,
            const com_stmt_execute_packet<ValueForwardIterator>& input) noexcept;
};

struct com_stmt_execute_param_meta_packet
{
    protocol_field_type type;
    std::uint8_t unsigned_flag;

    template <class Self, class Callable>
    static void apply(Self& self, Callable&& cb)
    {
        std::forward<Callable>(cb)(
            self.type,
            self.unsigned_flag
        );
    }
};

// close
struct com_stmt_close_packet
{
    std::uint32_t statement_id;

    static constexpr std::uint8_t command_id = 0x19;

    template <class Self, class Callable>
    static void apply(Self& self, Callable&& cb)
    {
        std::forward<Callable>(cb)(
            self.statement_id
        );
    }
};


} // detail
} // mysql
} // boost

#include "boost/mysql/detail/protocol/impl/prepared_statement_messages.hpp"

#endif /* INCLUDE_BOOST_MYSQL_DETAIL_PROTOCOL_PREPARED_STATEMENT_MESSAGES_HPP_ */
