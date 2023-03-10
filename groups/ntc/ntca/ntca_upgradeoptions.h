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

#ifndef INCLUDED_NTCA_UPGRADEOPTIONS
#define INCLUDED_NTCA_UPGRADEOPTIONS

#include <bsls_ident.h>
BSLS_IDENT("$Id: $")

#include <ntca_upgradetoken.h>
#include <ntccfg_platform.h>
#include <ntcscm_version.h>
#include <bdlb_nullablevalue.h>
#include <bslh_hash.h>
#include <bsls_timeinterval.h>
#include <bsl_iosfwd.h>
#include <bsl_limits.h>

namespace BloombergLP {
namespace ntca {

/// Describe the parameters to an upgrade operation.
///
/// @par Attributes
/// This class is composed of the following attributes.
///
/// @li @b token:
/// The token used to cancel the operation.
///
/// @li @b deadline:
/// The deadline within which the connection must be upgraded, in absolute time
/// since the Unix epoch.
///
/// @li @b recurse:
/// Allow callbacks to be invoked immediately and recursively if their
/// constraints are already satisified at the time the asynchronous operation
/// is initiated.
///
/// @par Thread Safety
/// This class is not thread safe.
///
/// @ingroup module_ntci_operation_upgrade
class UpgradeOptions
{
    bdlb::NullableValue<ntca::UpgradeToken> d_token;
    bdlb::NullableValue<bsls::TimeInterval> d_deadline;
    bool                                    d_recurse;

  public:
    /// Create new upgrade options having the default value.
    UpgradeOptions();

    /// Create new upgrade options having the same value as the specified
    /// 'original' object.
    UpgradeOptions(const UpgradeOptions& original);

    /// Destroy this object.
    ~UpgradeOptions();

    /// Assign the value of the specified 'other' object to this object.
    /// Return a reference to this modifiable object.
    UpgradeOptions& operator=(const UpgradeOptions& other);

    /// Reset the value of this object to its value upon default
    /// construction.
    void reset();

    /// Set the token used to cancel the operation to the specified 'value'.
    void setToken(const ntca::UpgradeToken& value);

    /// Set the deadline within which the connection must be upgraded to the
    /// specified 'value'.
    void setDeadline(const bsls::TimeInterval& value);

    /// Set the flag that allows callbacks to be invoked immediately and
    /// recursively if their constraints are already satisified at the time
    /// the asynchronous operation is initiated.
    void setRecurse(bool value);

    /// Return the token used to cancel the operation.
    const bdlb::NullableValue<ntca::UpgradeToken>& token() const;

    /// Return the deadline within which the connection must be upgraded.
    const bdlb::NullableValue<bsls::TimeInterval>& deadline() const;

    /// Return true if callbacks are allowed to be invoked immediately and
    /// recursively if their constraints are already satisified at the time
    /// the asynchronous operation is initiated, otherwise return false.
    bool recurse() const;

    /// Return true if this object has the same value as the specified
    /// 'other' object, otherwise return false.
    bool equals(const UpgradeOptions& other) const;

    /// Return true if the value of this object is less than the value of
    /// the specified 'other' object, otherwise return false.
    bool less(const UpgradeOptions& other) const;

    /// Format this object to the specified output 'stream' at the
    /// optionally specified indentation 'level' and return a reference to
    /// the modifiable 'stream'.  If 'level' is specified, optionally
    /// specify 'spacesPerLevel', the number of spaces per indentation level
    /// for this and all of its nested objects.  Each line is indented by
    /// the absolute value of 'level * spacesPerLevel'.  If 'level' is
    /// negative, suppress indentation of the first line.  If
    /// 'spacesPerLevel' is negative, suppress line breaks and format the
    /// entire output on one line.  If 'stream' is initially invalid, this
    /// operation has no effect.  Note that a trailing newline is provided
    /// in multiline mode only.
    bsl::ostream& print(bsl::ostream& stream,
                        int           level          = 0,
                        int           spacesPerLevel = 4) const;

    /// Defines the traits of this type. These traits can be used to select,
    /// at compile-time, the most efficient algorithm to manipulate objects
    /// of this type.
    NTCCFG_DECLARE_NESTED_BITWISE_MOVABLE_TRAITS(UpgradeOptions);
};

/// Write the specified 'object' to the specified 'stream'. Return
/// a modifiable reference to the 'stream'.
///
/// @related ntca::UpgradeOptions
bsl::ostream& operator<<(bsl::ostream& stream, const UpgradeOptions& object);

/// Return true if the specified 'lhs' has the same value as the specified
/// 'rhs', otherwise return false.
///
/// @related ntca::UpgradeOptions
bool operator==(const UpgradeOptions& lhs, const UpgradeOptions& rhs);

/// Return true if the specified 'lhs' does not have the same value as the
/// specified 'rhs', otherwise return false.
///
/// @related ntca::UpgradeOptions
bool operator!=(const UpgradeOptions& lhs, const UpgradeOptions& rhs);

/// Return true if the value of the specified 'lhs' is less than the value
/// of the specified 'rhs', otherwise return false.
///
/// @related ntca::UpgradeOptions
bool operator<(const UpgradeOptions& lhs, const UpgradeOptions& rhs);

/// Contribute the values of the salient attributes of the specified 'value'
/// to the specified hash 'algorithm'.
///
/// @related ntca::UpgradeOptions
template <typename HASH_ALGORITHM>
void hashAppend(HASH_ALGORITHM& algorithm, const UpgradeOptions& value);

NTCCFG_INLINE
UpgradeOptions::UpgradeOptions()
: d_token()
, d_deadline()
, d_recurse(false)
{
}

NTCCFG_INLINE
UpgradeOptions::UpgradeOptions(const UpgradeOptions& original)
: d_token(original.d_token)
, d_deadline(original.d_deadline)
, d_recurse(original.d_recurse)
{
}

NTCCFG_INLINE
UpgradeOptions::~UpgradeOptions()
{
}

NTCCFG_INLINE
UpgradeOptions& UpgradeOptions::operator=(const UpgradeOptions& other)
{
    d_token    = other.d_token;
    d_deadline = other.d_deadline;
    d_recurse  = other.d_recurse;
    return *this;
}

NTCCFG_INLINE
void UpgradeOptions::reset()
{
    d_token.reset();
    d_deadline.reset();
    d_recurse = false;
}

NTCCFG_INLINE
void UpgradeOptions::setToken(const ntca::UpgradeToken& value)
{
    d_token = value;
}

NTCCFG_INLINE
void UpgradeOptions::setDeadline(const bsls::TimeInterval& value)
{
    d_deadline = value;
}

NTCCFG_INLINE
void UpgradeOptions::setRecurse(bool value)
{
    d_recurse = value;
}

NTCCFG_INLINE
const bdlb::NullableValue<ntca::UpgradeToken>& UpgradeOptions::token() const
{
    return d_token;
}

NTCCFG_INLINE
const bdlb::NullableValue<bsls::TimeInterval>& UpgradeOptions::deadline() const
{
    return d_deadline;
}

NTCCFG_INLINE
bool UpgradeOptions::recurse() const
{
    return d_recurse;
}

NTCCFG_INLINE
bsl::ostream& operator<<(bsl::ostream& stream, const UpgradeOptions& object)
{
    return object.print(stream, 0, -1);
}

NTCCFG_INLINE
bool operator==(const UpgradeOptions& lhs, const UpgradeOptions& rhs)
{
    return lhs.equals(rhs);
}

NTCCFG_INLINE
bool operator!=(const UpgradeOptions& lhs, const UpgradeOptions& rhs)
{
    return !operator==(lhs, rhs);
}

NTCCFG_INLINE
bool operator<(const UpgradeOptions& lhs, const UpgradeOptions& rhs)
{
    return lhs.less(rhs);
}

template <typename HASH_ALGORITHM>
void hashAppend(HASH_ALGORITHM& algorithm, const UpgradeOptions& value)
{
    using bslh::hashAppend;

    hashAppend(algorithm, value.token());
    hashAppend(algorithm, value.deadline());
    hashAppend(algorithm, value.recurse());
}

}  // close package namespace
}  // close enterprise namespace
#endif
