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

#ifndef INCLUDED_NTCI_GETDOMAINNAMECALLBACKFACTORY
#define INCLUDED_NTCI_GETDOMAINNAMECALLBACKFACTORY

#include <bsls_ident.h>
BSLS_IDENT("$Id: $")

#include <ntccfg_platform.h>
#include <ntci_authorization.h>
#include <ntci_getdomainnamecallback.h>
#include <ntci_strand.h>
#include <ntcscm_version.h>
#include <bsl_memory.h>

namespace BloombergLP {
namespace ntci {

/// Provide an interface to create get domain name callbacks.
///
/// @details
/// Unless otherwise specified, the callbacks created by this class will be
/// invoked on the object's strand.
///
/// @par Thread Safety
/// This class is thread safe.
///
/// @ingroup module_ntci_operation_resolve
class GetDomainNameCallbackFactory
{
  public:
    /// Destroy this object.
    virtual ~GetDomainNameCallbackFactory();

    /// Create a new get domain name callback to invoke the specified
    /// 'function' with no cancellable authorization mechanism on this
    /// object's strand.  Optionally specify a  'basicAllocator' used to
    /// supply memory. If 'basicAllocator' is 0, the currently installed
    /// default allocator is used.
    ntci::GetDomainNameCallback createGetDomainNameCallback(
        const ntci::GetDomainNameFunction& function,
        bslma::Allocator*                  basicAllocator = 0);

    /// Create a new get domain name callback to invoke the specified
    /// 'function' with the specified cancellable 'authorization' mechanism
    /// on this object's strand. Optionally specify a 'basicAllocator' used
    /// to supply memory.  If 'basicAllocator' is 0, the currently installed
    /// default allocator is used.
    ntci::GetDomainNameCallback createGetDomainNameCallback(
        const ntci::GetDomainNameFunction&          function,
        const bsl::shared_ptr<ntci::Authorization>& authorization,
        bslma::Allocator*                           basicAllocator = 0);

    /// Create a new get domain name callback to invoke the specified
    /// 'function' with no cancellable authorization mechanism on the
    /// specified 'strand'.  Optionally specify a  'basicAllocator' used to
    /// supply memory. If 'basicAllocator' is 0, the currently installed
    /// default allocator is used.
    ntci::GetDomainNameCallback createGetDomainNameCallback(
        const ntci::GetDomainNameFunction&   function,
        const bsl::shared_ptr<ntci::Strand>& strand,
        bslma::Allocator*                    basicAllocator = 0);

    /// Create a new get domain name callback to invoke the specified
    /// 'function' with the specified cancellable 'authorization' mechanism
    /// on the specified 'strand'. Optionally specify a 'basicAllocator'
    /// used to supply memory. If 'basicAllocator' is 0, the currently
    /// installed default allocator is used.
    ntci::GetDomainNameCallback createGetDomainNameCallback(
        const ntci::GetDomainNameFunction&          function,
        const bsl::shared_ptr<ntci::Authorization>& authorization,
        const bsl::shared_ptr<ntci::Strand>&        strand,
        bslma::Allocator*                           basicAllocator = 0);

    /// Return the strand on which this object's functions should be called.
    virtual const bsl::shared_ptr<ntci::Strand>& strand() const = 0;
};

NTCCFG_INLINE
ntci::GetDomainNameCallback GetDomainNameCallbackFactory::
    createGetDomainNameCallback(const ntci::GetDomainNameFunction& function,
                                bslma::Allocator* basicAllocator)
{
    return ntci::GetDomainNameCallback(function,
                                       this->strand(),
                                       basicAllocator);
}

NTCCFG_INLINE
ntci::GetDomainNameCallback GetDomainNameCallbackFactory::
    createGetDomainNameCallback(
        const ntci::GetDomainNameFunction&          function,
        const bsl::shared_ptr<ntci::Authorization>& authorization,
        bslma::Allocator*                           basicAllocator)
{
    return ntci::GetDomainNameCallback(function,
                                       authorization,
                                       this->strand(),
                                       basicAllocator);
}

NTCCFG_INLINE
ntci::GetDomainNameCallback GetDomainNameCallbackFactory::
    createGetDomainNameCallback(const ntci::GetDomainNameFunction&   function,
                                const bsl::shared_ptr<ntci::Strand>& strand,
                                bslma::Allocator* basicAllocator)
{
    return ntci::GetDomainNameCallback(function, strand, basicAllocator);
}

NTCCFG_INLINE
ntci::GetDomainNameCallback GetDomainNameCallbackFactory::
    createGetDomainNameCallback(
        const ntci::GetDomainNameFunction&          function,
        const bsl::shared_ptr<ntci::Authorization>& authorization,
        const bsl::shared_ptr<ntci::Strand>&        strand,
        bslma::Allocator*                           basicAllocator)
{
    return ntci::GetDomainNameCallback(function,
                                       authorization,
                                       strand,
                                       basicAllocator);
}

}  // end namespace ntci
}  // end namespace BloombergLP
#endif
