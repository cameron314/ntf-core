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

#include <ntsa_ipv4endpoint.h>
#include <ntscfg_test.h>
#include <bslma_testallocator.h>

using namespace BloombergLP;
using namespace ntsa;

//=============================================================================
//                                 TEST PLAN
//-----------------------------------------------------------------------------
//                                 Overview
//                                 --------
//
//-----------------------------------------------------------------------------

// [ 1]
//-----------------------------------------------------------------------------
// [ 1]
//-----------------------------------------------------------------------------

NTSCFG_TEST_CASE(1)
{
    // Concern:
    // Plan:

    ntsa::Ipv4Endpoint ipv4Endpoint("127.0.0.1:12345");

    NTSCFG_TEST_EQ(ipv4Endpoint.host(), ntsa::Ipv4Address::loopback());
    NTSCFG_TEST_EQ(ipv4Endpoint.port(), 12345);
}

NTSCFG_TEST_DRIVER
{
    NTSCFG_TEST_REGISTER(1);
}
NTSCFG_TEST_DRIVER_END;
