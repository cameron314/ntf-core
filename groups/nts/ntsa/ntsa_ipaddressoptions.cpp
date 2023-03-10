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

#include <ntsa_ipaddressoptions.h>

#include <bsls_ident.h>
BSLS_IDENT_RCSID(ntsa_ipaddressoptions_cpp, "$Id$ $CSID$")

#include <bslim_printer.h>

namespace BloombergLP {
namespace ntsa {

bool IpAddressOptions::equals(const IpAddressOptions& other) const
{
    return (d_ipAddressFallback == other.d_ipAddressFallback &&
            d_ipAddressType == other.d_ipAddressType &&
            d_ipAddressSelector == other.d_ipAddressSelector &&
            d_transport == other.d_transport);
}

bool IpAddressOptions::less(const IpAddressOptions& other) const
{
    if (d_ipAddressFallback < other.d_ipAddressFallback) {
        return true;
    }

    if (d_ipAddressFallback > other.d_ipAddressFallback) {
        return false;
    }

    if (d_ipAddressType < other.d_ipAddressType) {
        return true;
    }

    if (d_ipAddressType > other.d_ipAddressType) {
        return false;
    }

    if (d_ipAddressSelector < other.d_ipAddressSelector) {
        return true;
    }

    if (d_ipAddressSelector > other.d_ipAddressSelector) {
        return false;
    }

    return d_transport < other.d_transport;
}

bsl::ostream& IpAddressOptions::print(bsl::ostream& stream,
                                      int           level,
                                      int           spacesPerLevel) const
{
    bslim::Printer printer(&stream, level, spacesPerLevel);
    printer.start();

    if (!d_ipAddressFallback.isNull()) {
        printer.printAttribute("ipAddressFallback", d_ipAddressFallback);
    }

    if (!d_ipAddressType.isNull()) {
        printer.printAttribute("ipAddressType", d_ipAddressType);
    }

    if (!d_ipAddressSelector.isNull()) {
        printer.printAttribute("ipAddressSelector", d_ipAddressSelector);
    }

    if (!d_transport.isNull()) {
        printer.printAttribute("transport", d_transport);
    }

    printer.end();
    return stream;
}

}  // close package namespace
}  // close enterprise namespace
