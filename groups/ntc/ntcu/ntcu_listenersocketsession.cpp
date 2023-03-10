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

#include <ntcu_listenersocketsession.h>

#include <bsls_ident.h>
BSLS_IDENT_RCSID(ntcu_listenersocketsession_cpp, "$Id$ $CSID$")

#include <bslma_allocator.h>
#include <bslma_default.h>
#include <bsls_assert.h>

namespace BloombergLP {
namespace ntcu {

ListenerSocketSession::ListenerSocketSession(
    const ntci::ListenerSocket::SessionCallback& callback,
    const bsl::shared_ptr<ntci::Strand>&         strand,
    bslma::Allocator*                            basicAllocator)
: d_callback(NTCCFG_FUNCTION_COPY(callback, basicAllocator))
, d_strand_sp(strand)
, d_allocator_p(bslma::Default::allocator(basicAllocator))
{
}

ListenerSocketSession::~ListenerSocketSession()
{
}

void ListenerSocketSession::processAcceptQueueFlowControlRelaxed(
    const bsl::shared_ptr<ntci::ListenerSocket>& listenerSocket,
    const ntca::AcceptQueueEvent&                event)
{
    BSLS_ASSERT(event.type() ==
                ntca::AcceptQueueEventType::e_FLOW_CONTROL_RELAXED);
    d_callback(listenerSocket, ntca::ListenerSocketEvent(event));
}

void ListenerSocketSession::processAcceptQueueFlowControlApplied(
    const bsl::shared_ptr<ntci::ListenerSocket>& listenerSocket,
    const ntca::AcceptQueueEvent&                event)
{
    BSLS_ASSERT(event.type() ==
                ntca::AcceptQueueEventType::e_FLOW_CONTROL_APPLIED);
    d_callback(listenerSocket, ntca::ListenerSocketEvent(event));
}

void ListenerSocketSession::processAcceptQueueLowWatermark(
    const bsl::shared_ptr<ntci::ListenerSocket>& listenerSocket,
    const ntca::AcceptQueueEvent&                event)
{
    BSLS_ASSERT(event.type() == ntca::AcceptQueueEventType::e_LOW_WATERMARK);
    d_callback(listenerSocket, ntca::ListenerSocketEvent(event));
}

void ListenerSocketSession::processAcceptQueueHighWatermark(
    const bsl::shared_ptr<ntci::ListenerSocket>& listenerSocket,
    const ntca::AcceptQueueEvent&                event)
{
    BSLS_ASSERT(event.type() == ntca::AcceptQueueEventType::e_HIGH_WATERMARK);
    d_callback(listenerSocket, ntca::ListenerSocketEvent(event));
}

void ListenerSocketSession::processAcceptQueueDiscarded(
    const bsl::shared_ptr<ntci::ListenerSocket>& listenerSocket,
    const ntca::AcceptQueueEvent&                event)
{
    BSLS_ASSERT(event.type() == ntca::AcceptQueueEventType::e_DISCARDED);
    d_callback(listenerSocket, ntca::ListenerSocketEvent(event));
}

void ListenerSocketSession::processShutdownInitiated(
    const bsl::shared_ptr<ntci::ListenerSocket>& listenerSocket,
    const ntca::ShutdownEvent&                   event)
{
    BSLS_ASSERT(event.type() == ntca::ShutdownEventType::e_INITIATED);
    d_callback(listenerSocket, ntca::ListenerSocketEvent(event));
}

void ListenerSocketSession::processShutdownReceive(
    const bsl::shared_ptr<ntci::ListenerSocket>& listenerSocket,
    const ntca::ShutdownEvent&                   event)
{
    BSLS_ASSERT(event.type() == ntca::ShutdownEventType::e_RECEIVE);
    d_callback(listenerSocket, ntca::ListenerSocketEvent(event));
}

void ListenerSocketSession::processShutdownSend(
    const bsl::shared_ptr<ntci::ListenerSocket>& listenerSocket,
    const ntca::ShutdownEvent&                   event)
{
    BSLS_ASSERT(event.type() == ntca::ShutdownEventType::e_SEND);
    d_callback(listenerSocket, ntca::ListenerSocketEvent(event));
}

void ListenerSocketSession::processShutdownComplete(
    const bsl::shared_ptr<ntci::ListenerSocket>& listenerSocket,
    const ntca::ShutdownEvent&                   event)
{
    BSLS_ASSERT(event.type() == ntca::ShutdownEventType::e_COMPLETE);
    d_callback(listenerSocket, ntca::ListenerSocketEvent(event));
}

void ListenerSocketSession::processError(
    const bsl::shared_ptr<ntci::ListenerSocket>& listenerSocket,
    const ntca::ErrorEvent&                      event)
{
    d_callback(listenerSocket, ntca::ListenerSocketEvent(event));
}

const bsl::shared_ptr<ntci::Strand>& ListenerSocketSession::strand() const
{
    return d_strand_sp;
}

}  // close package namespace
}  // close enterprise namespace
