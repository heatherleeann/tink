// Copyright 2017 Google Inc.
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
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TINK_SUBTLE_ECIES_HKDF_SENDER_KEM_BORINGSSL_H_
#define TINK_SUBTLE_ECIES_HKDF_SENDER_KEM_BORINGSSL_H_

#include "absl/strings/string_view.h"
#include "cc/util/statusor.h"
#include "openssl/ec.h"
#include "proto/common.pb.h"

namespace crypto {
namespace tink {

// HKDF-based KEM (key encapsulation mechanism) for ECIES sender,
// using Boring SSL for the underlying cryptographic operations.
class EciesHkdfSenderKemBoringSsl {
 public:
  // Container for data of keys generated by the KEM.
  class KemKey {
   public:
    KemKey() {}
    explicit KemKey(const std::string& kem_bytes,
                    const std::string& symmetric_key);
    std::string get_kem_bytes();

    std::string get_symmetric_key();

   private:
    std::string kem_bytes_;
    std::string symmetric_key_;
  };

  // Constructs a sender KEM for the specified curve and recipient's
  // public key point.  The public key's coordinates are big-endian byte array.
  static
  crypto::tink::util::StatusOr<std::unique_ptr<EciesHkdfSenderKemBoringSsl>>
      New(google::crypto::tink::EllipticCurveType curve,
          const std::string& pubx,
          const std::string& puby);

  // Generates ephemeral key pairs, computes ECDH's shared secret based on
  // generated ephemeral key and recipient's public key, then uses HKDF
  // to derive the symmetric key from the shared secret, 'hkdf_info' and
  // hkdf_salt.
  crypto::tink::util::StatusOr<std::unique_ptr<KemKey>> GenerateKey(
      google::crypto::tink::HashType hash,
      absl::string_view hkdf_salt,
      absl::string_view hkdf_info,
      uint32_t key_size_in_bytes,
      google::crypto::tink::EcPointFormat point_format) const;

 private:
  EciesHkdfSenderKemBoringSsl(
      google::crypto::tink::EllipticCurveType curve,
      const std::string& pubx, const std::string& puby);

  google::crypto::tink::EllipticCurveType curve_;
  std::string pubx_;
  std::string puby_;
  bssl::UniquePtr<EC_POINT> peer_pub_key_;
};

}  // namespace tink
}  // namespace crypto

#endif  // TINK_SUBTLE_ECIES_HKDF_SENDER_KEM_BORINGSSL_H_
