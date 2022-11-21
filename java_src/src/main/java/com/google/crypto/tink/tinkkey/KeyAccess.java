// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////
package com.google.crypto.tink.tinkkey;

import com.google.errorprone.annotations.Immutable;

/**
 * An access token for {@code TinkKey}. Access to Tink keys is governed by {@code KeyHandle}. A
 * {@code TinkKey} which does not have a secret should be accessible by tokens generated by {@code
 * KeyAccess.publicAccess()}. A {@code TinkKey} with a secret should need a token generated by
 * {@code SecretKeyAccess.secretAccess()}.
 *
 * @deprecated Use {@link com.google.crypto.tink.SecretKeyAccess} instead.
 */
@Immutable
@Deprecated
public final class KeyAccess {

  private final boolean canAccessSecret;

  private KeyAccess(boolean canAccessSecret) {
    this.canAccessSecret = canAccessSecret;
  }

  /**
   * Returns a {@code KeyAccess} instance where {@code canAccessSecret()} returns false.
   **/
  public static KeyAccess publicAccess() {
    return new KeyAccess(false);
  }

  static KeyAccess secretAccess() {
    return new KeyAccess(true);
  }

  /**
   * Returns true if the {@code KeyAccess} instance grants access to a key's secret
   **/
  public boolean canAccessSecret() {
    return canAccessSecret;
  }
}
