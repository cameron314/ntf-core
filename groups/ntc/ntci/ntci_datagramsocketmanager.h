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

#ifndef INCLUDED_NTCI_DATAGRAMSOCKETMANAGER
#define INCLUDED_NTCI_DATAGRAMSOCKETMANAGER

#include <bsls_ident.h>
BSLS_IDENT("$Id: $")

#include <ntccfg_platform.h>
#include <ntci_strand.h>
#include <ntcscm_version.h>
#include <ntsa_endpoint.h>
#include <ntsa_error.h>
#include <ntsi_descriptor.h>
#include <bsl_memory.h>

namespace BloombergLP {

namespace ntci {
class DatagramSocket;
}
namespace ntci {

/// Provide an interface to manage the application of datagram sockets.
///
/// @par Thread Safety
/// This class is thread safe.
///
/// @ingroup module_ntci_socket
class DatagramSocketManager
{
  public:
    /// Destroy this object.
    virtual ~DatagramSocketManager();

    /// Process the establishment of the specified 'datagramSocket'.
    virtual void processDatagramSocketEstablished(
        const bsl::shared_ptr<ntci::DatagramSocket>& datagramSocket);

    /// Process the closure of the specified 'datagramSocket'.
    virtual void processDatagramSocketClosed(
        const bsl::shared_ptr<ntci::DatagramSocket>& datagramSocket);

    /// Return the strand on which this object's functions should be called.
    virtual const bsl::shared_ptr<ntci::Strand>& strand() const;
};

}  // close package namespace
}  // close enterprise namespace
#endif
