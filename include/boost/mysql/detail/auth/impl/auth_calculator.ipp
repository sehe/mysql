//
// Copyright (c) 2019-2021 Ruben Perez Hidalgo (rubenperez038 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MYSQL_DETAIL_AUTH_IMPL_AUTH_CALCULATOR_IPP
#define BOOST_MYSQL_DETAIL_AUTH_IMPL_AUTH_CALCULATOR_IPP

#include "boost/mysql/detail/auth/mysql_native_password.hpp"
#include "boost/mysql/detail/auth/caching_sha2_password.hpp"
#include "boost/mysql/detail/auxiliar/make_string_view.hpp"

namespace boost {
namespace mysql {
namespace detail {

constexpr authentication_plugin mysql_native_password_plugin {
    make_string_view("mysql_native_password"),
    &mysql_native_password::compute_response
};

constexpr authentication_plugin caching_sha2_password_plugin {
    make_string_view("caching_sha2_password"),
    &caching_sha2_password::compute_response
};

constexpr std::array<const authentication_plugin*, 2> all_authentication_plugins {
    &mysql_native_password_plugin,
    &caching_sha2_password_plugin
};

} // detail
} // mysql
} // boost

inline const boost::mysql::detail::authentication_plugin*
boost::mysql::detail::auth_calculator::find_plugin(
    boost::string_view name
)
{
    auto it = std::find_if(
        all_authentication_plugins.begin(),
        all_authentication_plugins.end(),
        [name](const authentication_plugin* plugin) { return plugin->name == name; }
    );
    return it == std::end(all_authentication_plugins) ? nullptr : *it;
}

inline boost::mysql::error_code
boost::mysql::detail::auth_calculator::calculate(
    boost::string_view plugin_name,
    boost::string_view password,
    boost::string_view challenge,
    bool use_ssl
)
{

    plugin_ = find_plugin(plugin_name);
    if (plugin_)
    {
        // Blank password: we should just return an empty auth string
        if (password.empty())
        {
            response_.clear();
            return error_code();
        }
        else
        {
            return plugin_->calculator(password, challenge, use_ssl, response_);
        }
    }
    else
    {
        return make_error_code(errc::unknown_auth_plugin);
    }
}



#endif /* INCLUDE_BOOST_MYSQL_DETAIL_AUTH_IMPL_AUTH_CALCULATOR_IPP_ */
