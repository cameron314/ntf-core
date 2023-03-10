// Copyright 2020-2023 Bloomberg Finance L.P.
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <ntsa_endpoint.h>

#include <bsls_ident.h>
BSLS_IDENT_RCSID(ntsa_endpoint_cpp, "$Id$ $CSID$")

#include <bslim_printer.h>
#include <bsl_sstream.h>

namespace BloombergLP {
namespace ntsa {

namespace {

void throwEndpointInvalidFormat(const bslstl::StringRef& text)
{
    bsl::stringstream ss;
    ss << "Failed to parse address: the text '" << text << "' is invalid";

    NTSCFG_THROW(ss.str());
}

}  // close unnamed namespace

Endpoint::Endpoint(const bslstl::StringRef& text)
: d_type(ntsa::EndpointType::e_UNDEFINED)
{
    if (!this->parse(text)) {
        throwEndpointInvalidFormat(text);
    }
}

Endpoint& Endpoint::operator=(const bslstl::StringRef& text)
{
    this->reset();

    if (text.empty()) {
        return *this;
    }

    bool valid;

    valid = this->makeIp().parse(text);
    if (valid) {
        return *this;
    }

    this->makeLocal().setValue(text);

    return *this;
}

bool Endpoint::parse(const bslstl::StringRef& text)
{
    this->reset();

    if (text.empty()) {
        return true;
    }

    bool valid;

    valid = this->makeIp().parse(text);
    if (valid) {
        return true;
    }

    this->makeLocal().setValue(text);

    return true;
}

bsl::string Endpoint::text() const
{
    switch (d_type) {
    case ntsa::EndpointType::e_IP:
        return d_ip.object().text();
    case ntsa::EndpointType::e_LOCAL:
        if (d_local.object().isUnnamed()) {
            return "(unnamed)";
        }
        else {
            return d_local.object().value();
        }
    default:
        return "";
    }
}

ntsa::Transport::Value Endpoint::transport(
    ntsa::TransportMode::Value mode) const
{
    ntsa::Transport::Value result = ntsa::Transport::e_UNDEFINED;

    if (d_type == ntsa::EndpointType::e_IP) {
        if (d_ip.object().host().isV4()) {
            if (mode == ntsa::TransportMode::e_DATAGRAM) {
                result = ntsa::Transport::e_UDP_IPV4_DATAGRAM;
            }
            else if (mode == ntsa::TransportMode::e_STREAM) {
                result = ntsa::Transport::e_TCP_IPV4_STREAM;
            }
        }
        else if (d_ip.object().host().isV6()) {
            if (mode == ntsa::TransportMode::e_DATAGRAM) {
                result = ntsa::Transport::e_UDP_IPV6_DATAGRAM;
            }
            else if (mode == ntsa::TransportMode::e_STREAM) {
                result = ntsa::Transport::e_TCP_IPV6_STREAM;
            }
        }
    }
    else if (d_type == ntsa::EndpointType::e_LOCAL) {
        if (mode == ntsa::TransportMode::e_DATAGRAM) {
            result = ntsa::Transport::e_LOCAL_DATAGRAM;
        }
        else if (mode == ntsa::TransportMode::e_STREAM) {
            result = ntsa::Transport::e_LOCAL_STREAM;
        }
    }

    return result;
}

bool Endpoint::isExplicit() const
{
    if (d_type == ntsa::EndpointType::e_UNDEFINED) {
        return false;
    }
    else if (d_type == ntsa::EndpointType::e_IP) {
        if (d_ip.object().port() == 0) {
            if (d_ip.object().host().isUndefined()) {
                return false;
            }
            else if (d_ip.object().host().isV4()) {
                if (d_ip.object().host().v4().isAny()) {
                    return false;
                }
            }
            else if (d_ip.object().host().isV6()) {
                if (d_ip.object().host().v6().isAny()) {
                    return false;
                }
            }
        }
    }
    else if (d_type == ntsa::EndpointType::e_LOCAL) {
        if (d_local.object().isUnnamed()) {
            return false;
        }
    }

    return true;
}

bool Endpoint::isImplicit() const
{
    return !this->isExplicit();
}

bool Endpoint::equals(const Endpoint& other) const
{
    if (d_type != other.d_type) {
        return false;
    }

    switch (d_type) {
    case ntsa::EndpointType::e_IP:
        return d_ip.object().equals(other.d_ip.object());
    case ntsa::EndpointType::e_LOCAL:
        return d_local.object().equals(other.d_local.object());
    default:
        return true;
    }
}

bool Endpoint::less(const Endpoint& other) const
{
    if (d_type != other.d_type) {
        return false;
    }

    switch (d_type) {
    case ntsa::EndpointType::e_IP:
        return d_ip.object().less(other.d_ip.object());
    case ntsa::EndpointType::e_LOCAL:
        return d_local.object().less(other.d_local.object());
    default:
        return true;
    }
}

bsl::ostream& Endpoint::print(bsl::ostream& stream,
                              int           level,
                              int           spacesPerLevel) const
{
    switch (d_type) {
    case ntsa::EndpointType::e_IP:
        d_ip.object().print(stream, level, spacesPerLevel);
        break;
    case ntsa::EndpointType::e_LOCAL:
        d_local.object().print(stream, level, spacesPerLevel);
        break;
    default:
        BSLS_ASSERT(d_type == ntsa::EndpointType::e_UNDEFINED);
        stream << "UNDEFINED";
        break;
    }

    return stream;
}

}  // close package namespace
}  // close enterprise namespace
