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

#include <ntca_getdomainnameeventtype.h>

#include <bsls_ident.h>
BSLS_IDENT_RCSID(ntca_getdomainnameeventtype_cpp, "$Id$ $CSID$")

#include <bdlb_string.h>
#include <bsls_assert.h>
#include <bsl_ostream.h>

namespace BloombergLP {
namespace ntca {

int GetDomainNameEventType::fromInt(GetDomainNameEventType::Value* result,
                                    int                            number)
{
    switch (number) {
    case GetDomainNameEventType::e_COMPLETE:
    case GetDomainNameEventType::e_ERROR:
        *result = static_cast<GetDomainNameEventType::Value>(number);
        return 0;
    default:
        return -1;
    }
}

int GetDomainNameEventType::fromString(GetDomainNameEventType::Value* result,
                                       const bslstl::StringRef&       string)
{
    if (bdlb::String::areEqualCaseless(string, "COMPLETE")) {
        *result = e_COMPLETE;
        return 0;
    }
    if (bdlb::String::areEqualCaseless(string, "ERROR")) {
        *result = e_ERROR;
        return 0;
    }

    return -1;
}

const char* GetDomainNameEventType::toString(
    GetDomainNameEventType::Value value)
{
    switch (value) {
    case e_COMPLETE: {
        return "COMPLETE";
    } break;
    case e_ERROR: {
        return "ERROR";
    } break;
    }

    BSLS_ASSERT(!"invalid enumerator");
    return 0;
}

bsl::ostream& GetDomainNameEventType::print(
    bsl::ostream&                 stream,
    GetDomainNameEventType::Value value)
{
    return stream << toString(value);
}

bsl::ostream& operator<<(bsl::ostream&                 stream,
                         GetDomainNameEventType::Value rhs)
{
    return GetDomainNameEventType::print(stream, rhs);
}

}  // close package namespace
}  // close enterprise namespace
