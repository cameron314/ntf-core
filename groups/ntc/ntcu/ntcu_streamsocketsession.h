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

#ifndef INCLUDED_NTCU_STREAMSOCKETSESSION
#define INCLUDED_NTCU_STREAMSOCKETSESSION

#include <bsls_ident.h>
BSLS_IDENT("$Id: $")

#include <ntca_streamsocketevent.h>
#include <ntccfg_platform.h>
#include <ntci_strand.h>
#include <ntci_streamsocket.h>
#include <ntci_streamsocketsession.h>
#include <ntcscm_version.h>
#include <bsl_memory.h>

namespace BloombergLP {
namespace ntcu {

/// @internal @brief
/// Adapt a stream socket session to a callback.
///
/// @details
/// Provide a mechanism that implements the
/// 'ntci::StreamSocketSession' interface to invoke a callback with
/// potentially bound state.
///
/// @par Thread Safety
/// This class is thread safe.
///
/// @ingroup module_ntcu
class StreamSocketSession : public ntci::StreamSocketSession
{
    ntci::StreamSocket::SessionCallback d_callback;
    bsl::shared_ptr<ntci::Strand>       d_strand_sp;
    bslma::Allocator*                   d_allocator_p;

  private:
    StreamSocketSession(const StreamSocketSession&) BSLS_KEYWORD_DELETED;
    StreamSocketSession& operator=(const StreamSocketSession&)
        BSLS_KEYWORD_DELETED;

  public:
    /// Create a new stream socket session that proxies the announcement of
    /// stream socket events to the specified 'callback' on the specified
    /// 'strand'. Optionally specify a 'basicAllocator' used to supply
    /// memory. If 'basicAllocator' is 0, the currently installed default
    /// allocator is used.
    StreamSocketSession(const ntci::StreamSocket::SessionCallback& callback,
                        const bsl::shared_ptr<ntci::Strand>&       strand,
                        bslma::Allocator* basicAllocator = 0);

    /// Destroy this object.
    ~StreamSocketSession() BSLS_KEYWORD_OVERRIDE;

    /// Process the condition that read queue flow control has been relaxed:
    /// the socket receive buffer is being automatically copied to the read
    /// queue.
    void processReadQueueFlowControlRelaxed(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::ReadQueueEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the condition that read queue flow control has been applied:
    /// the socket receive buffer is not being automatically copied to the
    /// read queue.
    void processReadQueueFlowControlApplied(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::ReadQueueEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the condition that the size of the read queue is greater
    /// than or equal to the read queue low watermark.
    void processReadQueueLowWatermark(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::ReadQueueEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the condition that the size of the read queue is greater
    /// than the read queue high watermark.
    void processReadQueueHighWatermark(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::ReadQueueEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the condition that the read queue has been discarded
    /// because a non-transient read error asynchronously occured.
    void processReadQueueDiscarded(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::ReadQueueEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the condition that write queue flow control has been
    /// relaxed: the write queue is being automatically copied to the socket
    /// send buffer.
    void processWriteQueueFlowControlRelaxed(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::WriteQueueEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the condition that write queue flow control has been
    /// applied: the write queue is not being automatically copied to the
    /// socket send buffer.
    void processWriteQueueFlowControlApplied(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::WriteQueueEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the condition that the size of the write queue has been
    /// drained down to less than or equal to the write queue low watermark.
    /// This condition will not occur until the write queue high watermark
    /// condition occurs. The write queue low watermark conditions and the
    /// high watermark conditions are guaranteed to occur serially.
    void processWriteQueueLowWatermark(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::WriteQueueEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the condition that the size of the write queue is greater
    /// than the write queue high watermark. This condition will occur the
    /// first time the write queue high watermark has been reached but
    /// then will not subsequently ooccur until the write queue low
    /// watermark. The write queue low watermark conditions and the
    /// high watermark conditions are guaranteed to occur serially.
    void processWriteQueueHighWatermark(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::WriteQueueEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the condition that the write queue has been discarded
    /// because a non-transient write error asynchronously occured.
    void processWriteQueueDiscarded(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::WriteQueueEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the initiation of a downgrade from encrypted to unencrypted
    /// communication.
    void processDowngradeInitiated(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::DowngradeEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the completion of a downgrade from encrypted to unencrypted
    /// communication.
    void processDowngradeComplete(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::DowngradeEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the initiation of the shutdown sequence from the specified
    /// 'origin'.
    void processShutdownInitiated(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::ShutdownEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the socket being shut down for reading.
    void processShutdownReceive(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::ShutdownEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the socket being shut down for writing.
    void processShutdownSend(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::ShutdownEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process the completion of the shutdown sequence.
    void processShutdownComplete(
        const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
        const ntca::ShutdownEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Process an error.
    void processError(const bsl::shared_ptr<ntci::StreamSocket>& streamSocket,
                      const ntca::ErrorEvent& event) BSLS_KEYWORD_OVERRIDE;

    /// Return the strand on which this object's functions should be called.
    const bsl::shared_ptr<ntci::Strand>& strand() const BSLS_KEYWORD_OVERRIDE;
};

}  // close package namespace
}  // close enterprise namespace
#endif
