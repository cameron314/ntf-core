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

#include <ntci_log.h>

#include <ntccfg_test.h>
#include <ntsa_sendcontext.h>
#include <ntsa_sendoptions.h>
#include <bslma_testallocator.h>

using namespace BloombergLP;

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

NTCCFG_TEST_CASE(1)
{
    // Concern:
    // Plan:

    ntccfg::TestAllocator ta;
    {
        ntci::Log::initialize(true);

        ntci::LogContext logContext;

        logContext.d_owner = "incoming";

        logContext.d_threadIndex      = 5;
        logContext.d_descriptorHandle = 68;
        logContext.d_sourceEndpoint   = ntsa::Endpoint("127.0.0.1:12345");

        ntci::Log::write(0,
                         bsls::LogSeverity::e_INFO,
                         __FILE__,
                         __LINE__,
                         "Object received %d bytes",
                         84730);

        ntci::Log::write(&logContext,
                         bsls::LogSeverity::e_INFO,
                         __FILE__,
                         __LINE__,
                         "Object received %d bytes",
                         84730);

        ntci::Log::flush();
        ntci::Log::exit();
    }
    NTCCFG_TEST_ASSERT(ta.numBlocksInUse() == 0);
}

NTCCFG_TEST_CASE(2)
{
    // Concern:
    // Plan:

    ntccfg::TestAllocator ta;
    {
        NTCI_LOG_CONTEXT();

        ntsa::Endpoint sourceEndpoint("127.0.0.1:1234");
        ntsa::Endpoint remoteEndpoint("127.0.0.1:5678");

        NTCI_LOG_CONTEXT_GUARD_OWNER("test");
        NTCI_LOG_CONTEXT_GUARD_THREAD(1);
        NTCI_LOG_CONTEXT_GUARD_DESCRIPTOR(2);
        NTCI_LOG_CONTEXT_GUARD_SOURCE(3);
        NTCI_LOG_CONTEXT_GUARD_CHANNEL(4);
        NTCI_LOG_CONTEXT_GUARD_SESSION(5);
        NTCI_LOG_CONTEXT_GUARD_SOURCE_ENDPOINT(sourceEndpoint);
        NTCI_LOG_CONTEXT_GUARD_REMOTE_ENDPOINT(remoteEndpoint);

        NTCI_LOG_INFO("Log function at INFO");
        NTCI_LOG_DEBUG("Log function at DEBUG");
        NTCI_LOG_TRACE("Log function at TRACE");

        ntsa::SendOptions options;
        options.setMaxBytes(123);
        options.setMaxBuffers(456);

        NTCI_LOG_STREAM_INFO << "Log stream at INFO object = " << options
                             << NTCI_LOG_STREAM_END;
        NTCI_LOG_STREAM_DEBUG << "Log stream at DEBUG object = " << options
                              << NTCI_LOG_STREAM_END;
        NTCI_LOG_STREAM_TRACE << "Log stream at TRACE object = " << options
                              << NTCI_LOG_STREAM_END;

        bsl::string bigData(&ta);
        bigData.resize(8192, 'X');

        NTCI_LOG_STREAM_DEBUG << "Data = " << bigData << NTCI_LOG_STREAM_END;
    }
    NTCCFG_TEST_ASSERT(ta.numBlocksInUse() == 0);
}

NTCCFG_TEST_DRIVER
{
    NTCCFG_TEST_REGISTER(1);
    NTCCFG_TEST_REGISTER(2);
    ;
}
NTCCFG_TEST_DRIVER_END;
