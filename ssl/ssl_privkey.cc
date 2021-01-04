/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.] */

#include <openssl/ssl.h>

#include <assert.h>
#include <limits.h>

#include <openssl/ec.h>
#include <openssl/ec_key.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/mem.h>

#include "internal.h"
#include "../crypto/internal.h"


BSSL_NAMESPACE_BEGIN

bool ssl_is_key_type_supported(int key_type) {
  return key_type == EVP_PKEY_RSA ||
         key_type == EVP_PKEY_EC ||
         key_type == EVP_PKEY_ED25519 ||
///// OQS_TEMPLATE_FRAGMENT_CHECK_KEY_TYPE_START
         key_type == EVP_PKEY_OQS_SIG_DEFAULT ||
         key_type == EVP_PKEY_DILITHIUM2 ||
         key_type == EVP_PKEY_DILITHIUM3 ||
         key_type == EVP_PKEY_DILITHIUM4 ||
         key_type == EVP_PKEY_FALCON512 ||
         key_type == EVP_PKEY_FALCON1024 ||
         key_type == EVP_PKEY_PICNICL1FS ||
         key_type == EVP_PKEY_PICNICL1UR ||
         key_type == EVP_PKEY_PICNICL1FULL ||
         key_type == EVP_PKEY_PICNIC3L1 ||
         key_type == EVP_PKEY_PICNIC3L3 ||
         key_type == EVP_PKEY_PICNIC3L5 ||
         key_type == EVP_PKEY_RAINBOWICLASSIC ||
         key_type == EVP_PKEY_RAINBOWICIRCUMZENITHAL ||
         key_type == EVP_PKEY_RAINBOWICOMPRESSED ||
         key_type == EVP_PKEY_RAINBOWIIICLASSIC ||
         key_type == EVP_PKEY_RAINBOWIIICIRCUMZENITHAL ||
         key_type == EVP_PKEY_RAINBOWIIICOMPRESSED ||
         key_type == EVP_PKEY_RAINBOWVCLASSIC ||
         key_type == EVP_PKEY_RAINBOWVCIRCUMZENITHAL ||
         key_type == EVP_PKEY_RAINBOWVCOMPRESSED ||
         key_type == EVP_PKEY_SPHINCSHARAKA128FROBUST ||
         key_type == EVP_PKEY_SPHINCSHARAKA128FSIMPLE ||
         key_type == EVP_PKEY_SPHINCSHARAKA128SROBUST ||
         key_type == EVP_PKEY_SPHINCSHARAKA128SSIMPLE ||
         key_type == EVP_PKEY_SPHINCSHARAKA192FROBUST ||
         key_type == EVP_PKEY_SPHINCSHARAKA192FSIMPLE ||
         key_type == EVP_PKEY_SPHINCSHARAKA192SROBUST ||
         key_type == EVP_PKEY_SPHINCSHARAKA192SSIMPLE ||
         key_type == EVP_PKEY_SPHINCSHARAKA256FROBUST ||
         key_type == EVP_PKEY_SPHINCSHARAKA256FSIMPLE ||
         key_type == EVP_PKEY_SPHINCSHARAKA256SROBUST ||
         key_type == EVP_PKEY_SPHINCSHARAKA256SSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHA256128FROBUST ||
         key_type == EVP_PKEY_SPHINCSSHA256128FSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHA256128SROBUST ||
         key_type == EVP_PKEY_SPHINCSSHA256128SSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHA256192FROBUST ||
         key_type == EVP_PKEY_SPHINCSSHA256192FSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHA256192SROBUST ||
         key_type == EVP_PKEY_SPHINCSSHA256192SSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHA256256FROBUST ||
         key_type == EVP_PKEY_SPHINCSSHA256256FSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHA256256SROBUST ||
         key_type == EVP_PKEY_SPHINCSSHA256256SSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHAKE256128FROBUST ||
         key_type == EVP_PKEY_SPHINCSSHAKE256128FSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHAKE256128SROBUST ||
         key_type == EVP_PKEY_SPHINCSSHAKE256128SSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHAKE256192FROBUST ||
         key_type == EVP_PKEY_SPHINCSSHAKE256192FSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHAKE256192SROBUST ||
         key_type == EVP_PKEY_SPHINCSSHAKE256192SSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHAKE256256FROBUST ||
         key_type == EVP_PKEY_SPHINCSSHAKE256256FSIMPLE ||
         key_type == EVP_PKEY_SPHINCSSHAKE256256SROBUST ||
         key_type == EVP_PKEY_SPHINCSSHAKE256256SSIMPLE;
///// OQS_TEMPLATE_FRAGMENT_CHECK_KEY_TYPE_END
}

static bool ssl_set_pkey(CERT *cert, EVP_PKEY *pkey) {
  if (!ssl_is_key_type_supported(pkey->type)) {
    OPENSSL_PUT_ERROR(SSL, SSL_R_UNKNOWN_CERTIFICATE_TYPE);
    return false;
  }

  if (cert->chain != nullptr &&
      sk_CRYPTO_BUFFER_value(cert->chain.get(), 0) != nullptr &&
      // Sanity-check that the private key and the certificate match.
      !ssl_cert_check_private_key(cert, pkey)) {
    return false;
  }

  cert->privatekey = UpRef(pkey);
  return true;
}

typedef struct {
  uint16_t sigalg;
  int pkey_type;
  int curve;
  const EVP_MD *(*digest_func)(void);
  bool is_rsa_pss;
} SSL_SIGNATURE_ALGORITHM;

static const SSL_SIGNATURE_ALGORITHM kSignatureAlgorithms[] = {
    {SSL_SIGN_RSA_PKCS1_MD5_SHA1, EVP_PKEY_RSA, NID_undef, &EVP_md5_sha1,
     false},
    {SSL_SIGN_RSA_PKCS1_SHA1, EVP_PKEY_RSA, NID_undef, &EVP_sha1, false},
    {SSL_SIGN_RSA_PKCS1_SHA256, EVP_PKEY_RSA, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_RSA_PKCS1_SHA384, EVP_PKEY_RSA, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_RSA_PKCS1_SHA512, EVP_PKEY_RSA, NID_undef, &EVP_sha512, false},

    {SSL_SIGN_RSA_PSS_RSAE_SHA256, EVP_PKEY_RSA, NID_undef, &EVP_sha256, true},
    {SSL_SIGN_RSA_PSS_RSAE_SHA384, EVP_PKEY_RSA, NID_undef, &EVP_sha384, true},
    {SSL_SIGN_RSA_PSS_RSAE_SHA512, EVP_PKEY_RSA, NID_undef, &EVP_sha512, true},

    {SSL_SIGN_ECDSA_SHA1, EVP_PKEY_EC, NID_undef, &EVP_sha1, false},
    {SSL_SIGN_ECDSA_SECP256R1_SHA256, EVP_PKEY_EC, NID_X9_62_prime256v1,
     &EVP_sha256, false},
    {SSL_SIGN_ECDSA_SECP384R1_SHA384, EVP_PKEY_EC, NID_secp384r1, &EVP_sha384,
     false},
    {SSL_SIGN_ECDSA_SECP521R1_SHA512, EVP_PKEY_EC, NID_secp521r1, &EVP_sha512,
     false},

    {SSL_SIGN_ED25519, EVP_PKEY_ED25519, NID_undef, nullptr, false},
///// OQS_TEMPLATE_FRAGMENT_LIST_SSL_SIG_ALGS_START
    {SSL_SIGN_OQS_SIG_DEFAULT, EVP_PKEY_OQS_SIG_DEFAULT, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_DILITHIUM2, EVP_PKEY_DILITHIUM2, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_DILITHIUM3, EVP_PKEY_DILITHIUM3, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_DILITHIUM4, EVP_PKEY_DILITHIUM4, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_FALCON512, EVP_PKEY_FALCON512, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_FALCON1024, EVP_PKEY_FALCON1024, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_PICNICL1FS, EVP_PKEY_PICNICL1FS, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_PICNICL1UR, EVP_PKEY_PICNICL1UR, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_PICNICL1FULL, EVP_PKEY_PICNICL1FULL, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_PICNIC3L1, EVP_PKEY_PICNIC3L1, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_PICNIC3L3, EVP_PKEY_PICNIC3L3, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_PICNIC3L5, EVP_PKEY_PICNIC3L5, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_RAINBOWICLASSIC, EVP_PKEY_RAINBOWICLASSIC, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_RAINBOWICIRCUMZENITHAL, EVP_PKEY_RAINBOWICIRCUMZENITHAL, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_RAINBOWICOMPRESSED, EVP_PKEY_RAINBOWICOMPRESSED, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_RAINBOWIIICLASSIC, EVP_PKEY_RAINBOWIIICLASSIC, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_RAINBOWIIICIRCUMZENITHAL, EVP_PKEY_RAINBOWIIICIRCUMZENITHAL, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_RAINBOWIIICOMPRESSED, EVP_PKEY_RAINBOWIIICOMPRESSED, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_RAINBOWVCLASSIC, EVP_PKEY_RAINBOWVCLASSIC, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_RAINBOWVCIRCUMZENITHAL, EVP_PKEY_RAINBOWVCIRCUMZENITHAL, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_RAINBOWVCOMPRESSED, EVP_PKEY_RAINBOWVCOMPRESSED, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSHARAKA128FROBUST, EVP_PKEY_SPHINCSHARAKA128FROBUST, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSHARAKA128FSIMPLE, EVP_PKEY_SPHINCSHARAKA128FSIMPLE, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSHARAKA128SROBUST, EVP_PKEY_SPHINCSHARAKA128SROBUST, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSHARAKA128SSIMPLE, EVP_PKEY_SPHINCSHARAKA128SSIMPLE, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSHARAKA192FROBUST, EVP_PKEY_SPHINCSHARAKA192FROBUST, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSHARAKA192FSIMPLE, EVP_PKEY_SPHINCSHARAKA192FSIMPLE, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSHARAKA192SROBUST, EVP_PKEY_SPHINCSHARAKA192SROBUST, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSHARAKA192SSIMPLE, EVP_PKEY_SPHINCSHARAKA192SSIMPLE, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSHARAKA256FROBUST, EVP_PKEY_SPHINCSHARAKA256FROBUST, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSHARAKA256FSIMPLE, EVP_PKEY_SPHINCSHARAKA256FSIMPLE, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSHARAKA256SROBUST, EVP_PKEY_SPHINCSHARAKA256SROBUST, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSHARAKA256SSIMPLE, EVP_PKEY_SPHINCSHARAKA256SSIMPLE, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSSHA256128FROBUST, EVP_PKEY_SPHINCSSHA256128FROBUST, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSSHA256128FSIMPLE, EVP_PKEY_SPHINCSSHA256128FSIMPLE, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSSHA256128SROBUST, EVP_PKEY_SPHINCSSHA256128SROBUST, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSSHA256128SSIMPLE, EVP_PKEY_SPHINCSSHA256128SSIMPLE, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSSHA256192FROBUST, EVP_PKEY_SPHINCSSHA256192FROBUST, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSSHA256192FSIMPLE, EVP_PKEY_SPHINCSSHA256192FSIMPLE, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSSHA256192SROBUST, EVP_PKEY_SPHINCSSHA256192SROBUST, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSSHA256192SSIMPLE, EVP_PKEY_SPHINCSSHA256192SSIMPLE, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSSHA256256FROBUST, EVP_PKEY_SPHINCSSHA256256FROBUST, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSSHA256256FSIMPLE, EVP_PKEY_SPHINCSSHA256256FSIMPLE, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSSHA256256SROBUST, EVP_PKEY_SPHINCSSHA256256SROBUST, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSSHA256256SSIMPLE, EVP_PKEY_SPHINCSSHA256256SSIMPLE, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSSHAKE256128FROBUST, EVP_PKEY_SPHINCSSHAKE256128FROBUST, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSSHAKE256128FSIMPLE, EVP_PKEY_SPHINCSSHAKE256128FSIMPLE, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSSHAKE256128SROBUST, EVP_PKEY_SPHINCSSHAKE256128SROBUST, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSSHAKE256128SSIMPLE, EVP_PKEY_SPHINCSSHAKE256128SSIMPLE, NID_undef, &EVP_sha256, false},
    {SSL_SIGN_SPHINCSSHAKE256192FROBUST, EVP_PKEY_SPHINCSSHAKE256192FROBUST, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSSHAKE256192FSIMPLE, EVP_PKEY_SPHINCSSHAKE256192FSIMPLE, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSSHAKE256192SROBUST, EVP_PKEY_SPHINCSSHAKE256192SROBUST, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSSHAKE256192SSIMPLE, EVP_PKEY_SPHINCSSHAKE256192SSIMPLE, NID_undef, &EVP_sha384, false},
    {SSL_SIGN_SPHINCSSHAKE256256FROBUST, EVP_PKEY_SPHINCSSHAKE256256FROBUST, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSSHAKE256256FSIMPLE, EVP_PKEY_SPHINCSSHAKE256256FSIMPLE, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSSHAKE256256SROBUST, EVP_PKEY_SPHINCSSHAKE256256SROBUST, NID_undef, &EVP_sha512, false},
    {SSL_SIGN_SPHINCSSHAKE256256SSIMPLE, EVP_PKEY_SPHINCSSHAKE256256SSIMPLE, NID_undef, &EVP_sha512, false},
///// OQS_TEMPLATE_FRAGMENT_LIST_SSL_SIG_ALGS_END
};

static const SSL_SIGNATURE_ALGORITHM *get_signature_algorithm(uint16_t sigalg) {
  for (size_t i = 0; i < OPENSSL_ARRAY_SIZE(kSignatureAlgorithms); i++) {
    if (kSignatureAlgorithms[i].sigalg == sigalg) {
      return &kSignatureAlgorithms[i];
    }
  }
  return NULL;
}

bool ssl_has_private_key(const SSL_HANDSHAKE *hs) {
  if (hs->config->cert->privatekey != nullptr ||
      hs->config->cert->key_method != nullptr ||
      ssl_signing_with_dc(hs)) {
    return true;
  }

  return false;
}

static bool pkey_supports_algorithm(const SSL *ssl, EVP_PKEY *pkey,
                                    uint16_t sigalg) {
  const SSL_SIGNATURE_ALGORITHM *alg = get_signature_algorithm(sigalg);
  if (alg == NULL ||
      EVP_PKEY_id(pkey) != alg->pkey_type) {
    return false;
  }

  if (ssl_protocol_version(ssl) >= TLS1_3_VERSION) {
    // RSA keys may only be used with RSA-PSS.
    if (alg->pkey_type == EVP_PKEY_RSA && !alg->is_rsa_pss) {
      return false;
    }

    // EC keys have a curve requirement.
    if (alg->pkey_type == EVP_PKEY_EC &&
        (alg->curve == NID_undef ||
         EC_GROUP_get_curve_name(
             EC_KEY_get0_group(EVP_PKEY_get0_EC_KEY(pkey))) != alg->curve)) {
      return false;
    }
  }

  return true;
}

static bool setup_ctx(SSL *ssl, EVP_MD_CTX *ctx, EVP_PKEY *pkey,
                      uint16_t sigalg, bool is_verify) {
  if (!pkey_supports_algorithm(ssl, pkey, sigalg)) {
    OPENSSL_PUT_ERROR(SSL, SSL_R_WRONG_SIGNATURE_TYPE);
    return false;
  }

  const SSL_SIGNATURE_ALGORITHM *alg = get_signature_algorithm(sigalg);
  const EVP_MD *digest = alg->digest_func != NULL ? alg->digest_func() : NULL;
  EVP_PKEY_CTX *pctx;
  if (is_verify) {
    if (!EVP_DigestVerifyInit(ctx, &pctx, digest, NULL, pkey)) {
      return false;
    }
  } else if (!EVP_DigestSignInit(ctx, &pctx, digest, NULL, pkey)) {
    return false;
  }

  if (alg->is_rsa_pss) {
    if (!EVP_PKEY_CTX_set_rsa_padding(pctx, RSA_PKCS1_PSS_PADDING) ||
        !EVP_PKEY_CTX_set_rsa_pss_saltlen(pctx, -1 /* salt len = hash len */)) {
      return false;
    }
  }

  return true;
}

enum ssl_private_key_result_t ssl_private_key_sign(
    SSL_HANDSHAKE *hs, uint8_t *out, size_t *out_len, size_t max_out,
    uint16_t sigalg, Span<const uint8_t> in) {
  SSL *const ssl = hs->ssl;
  const SSL_PRIVATE_KEY_METHOD *key_method = hs->config->cert->key_method;
  EVP_PKEY *privatekey = hs->config->cert->privatekey.get();
  if (ssl_signing_with_dc(hs)) {
    key_method = hs->config->cert->dc_key_method;
    privatekey = hs->config->cert->dc_privatekey.get();
  }

  if (key_method != NULL) {
    enum ssl_private_key_result_t ret;
    if (hs->pending_private_key_op) {
      ret = key_method->complete(ssl, out, out_len, max_out);
    } else {
      ret = key_method->sign(ssl, out, out_len, max_out,
                             sigalg, in.data(), in.size());
    }
    if (ret == ssl_private_key_failure) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_PRIVATE_KEY_OPERATION_FAILED);
    }
    hs->pending_private_key_op = ret == ssl_private_key_retry;
    return ret;
  }

  *out_len = max_out;
  ScopedEVP_MD_CTX ctx;
  if (!setup_ctx(ssl, ctx.get(), privatekey, sigalg, false /* sign */) ||
      !EVP_DigestSign(ctx.get(), out, out_len, in.data(), in.size())) {
    return ssl_private_key_failure;
  }
  return ssl_private_key_success;
}

bool ssl_public_key_verify(SSL *ssl, Span<const uint8_t> signature,
                           uint16_t sigalg, EVP_PKEY *pkey,
                           Span<const uint8_t> in) {
  ScopedEVP_MD_CTX ctx;
  if (!setup_ctx(ssl, ctx.get(), pkey, sigalg, true /* verify */)) {
    return false;
  }
  bool ok = EVP_DigestVerify(ctx.get(), signature.data(), signature.size(),
                             in.data(), in.size());
#if defined(BORINGSSL_UNSAFE_FUZZER_MODE)
  ok = true;
  ERR_clear_error();
#endif
  return ok;
}

enum ssl_private_key_result_t ssl_private_key_decrypt(SSL_HANDSHAKE *hs,
                                                      uint8_t *out,
                                                      size_t *out_len,
                                                      size_t max_out,
                                                      Span<const uint8_t> in) {
  SSL *const ssl = hs->ssl;
  if (hs->config->cert->key_method != NULL) {
    enum ssl_private_key_result_t ret;
    if (hs->pending_private_key_op) {
      ret = hs->config->cert->key_method->complete(ssl, out, out_len, max_out);
    } else {
      ret = hs->config->cert->key_method->decrypt(ssl, out, out_len, max_out,
                                                  in.data(), in.size());
    }
    if (ret == ssl_private_key_failure) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_PRIVATE_KEY_OPERATION_FAILED);
    }
    hs->pending_private_key_op = ret == ssl_private_key_retry;
    return ret;
  }

  RSA *rsa = EVP_PKEY_get0_RSA(hs->config->cert->privatekey.get());
  if (rsa == NULL) {
    // Decrypt operations are only supported for RSA keys.
    OPENSSL_PUT_ERROR(SSL, ERR_R_INTERNAL_ERROR);
    return ssl_private_key_failure;
  }

  // Decrypt with no padding. PKCS#1 padding will be removed as part of the
  // timing-sensitive code by the caller.
  if (!RSA_decrypt(rsa, out_len, out, max_out, in.data(), in.size(),
                   RSA_NO_PADDING)) {
    return ssl_private_key_failure;
  }
  return ssl_private_key_success;
}

bool ssl_private_key_supports_signature_algorithm(SSL_HANDSHAKE *hs,
                                                  uint16_t sigalg) {
  SSL *const ssl = hs->ssl;
  if (!pkey_supports_algorithm(ssl, hs->local_pubkey.get(), sigalg)) {
    return false;
  }

  // Ensure the RSA key is large enough for the hash. RSASSA-PSS requires that
  // emLen be at least hLen + sLen + 2. Both hLen and sLen are the size of the
  // hash in TLS. Reasonable RSA key sizes are large enough for the largest
  // defined RSASSA-PSS algorithm, but 1024-bit RSA is slightly too small for
  // SHA-512. 1024-bit RSA is sometimes used for test credentials, so check the
  // size so that we can fall back to another algorithm in that case.
  const SSL_SIGNATURE_ALGORITHM *alg = get_signature_algorithm(sigalg);
  if (alg->is_rsa_pss && (size_t)EVP_PKEY_size(hs->local_pubkey.get()) <
                             2 * EVP_MD_size(alg->digest_func()) + 2) {
    return false;
  }

  return true;
}

BSSL_NAMESPACE_END

using namespace bssl;

int SSL_use_RSAPrivateKey(SSL *ssl, RSA *rsa) {
  if (rsa == NULL || ssl->config == NULL) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_PASSED_NULL_PARAMETER);
    return 0;
  }

  UniquePtr<EVP_PKEY> pkey(EVP_PKEY_new());
  if (!pkey ||
      !EVP_PKEY_set1_RSA(pkey.get(), rsa)) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_EVP_LIB);
    return 0;
  }

  return ssl_set_pkey(ssl->config->cert.get(), pkey.get());
}

int SSL_use_RSAPrivateKey_ASN1(SSL *ssl, const uint8_t *der, size_t der_len) {
  UniquePtr<RSA> rsa(RSA_private_key_from_bytes(der, der_len));
  if (!rsa) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_ASN1_LIB);
    return 0;
  }

  return SSL_use_RSAPrivateKey(ssl, rsa.get());
}

int SSL_use_PrivateKey(SSL *ssl, EVP_PKEY *pkey) {
  if (pkey == NULL || ssl->config == NULL) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_PASSED_NULL_PARAMETER);
    return 0;
  }

  return ssl_set_pkey(ssl->config->cert.get(), pkey);
}

int SSL_use_PrivateKey_ASN1(int type, SSL *ssl, const uint8_t *der,
                            size_t der_len) {
  if (der_len > LONG_MAX) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_OVERFLOW);
    return 0;
  }

  const uint8_t *p = der;
  UniquePtr<EVP_PKEY> pkey(d2i_PrivateKey(type, NULL, &p, (long)der_len));
  if (!pkey || p != der + der_len) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_ASN1_LIB);
    return 0;
  }

  return SSL_use_PrivateKey(ssl, pkey.get());
}

int SSL_CTX_use_RSAPrivateKey(SSL_CTX *ctx, RSA *rsa) {
  if (rsa == NULL) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_PASSED_NULL_PARAMETER);
    return 0;
  }

  UniquePtr<EVP_PKEY> pkey(EVP_PKEY_new());
  if (!pkey ||
      !EVP_PKEY_set1_RSA(pkey.get(), rsa)) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_EVP_LIB);
    return 0;
  }

  return ssl_set_pkey(ctx->cert.get(), pkey.get());
}

int SSL_CTX_use_RSAPrivateKey_ASN1(SSL_CTX *ctx, const uint8_t *der,
                                   size_t der_len) {
  UniquePtr<RSA> rsa(RSA_private_key_from_bytes(der, der_len));
  if (!rsa) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_ASN1_LIB);
    return 0;
  }

  return SSL_CTX_use_RSAPrivateKey(ctx, rsa.get());
}

int SSL_CTX_use_PrivateKey(SSL_CTX *ctx, EVP_PKEY *pkey) {
  if (pkey == NULL) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_PASSED_NULL_PARAMETER);
    return 0;
  }

  return ssl_set_pkey(ctx->cert.get(), pkey);
}

int SSL_CTX_use_PrivateKey_ASN1(int type, SSL_CTX *ctx, const uint8_t *der,
                                size_t der_len) {
  if (der_len > LONG_MAX) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_OVERFLOW);
    return 0;
  }

  const uint8_t *p = der;
  UniquePtr<EVP_PKEY> pkey(d2i_PrivateKey(type, NULL, &p, (long)der_len));
  if (!pkey || p != der + der_len) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_ASN1_LIB);
    return 0;
  }

  return SSL_CTX_use_PrivateKey(ctx, pkey.get());
}

void SSL_set_private_key_method(SSL *ssl,
                                const SSL_PRIVATE_KEY_METHOD *key_method) {
  if (!ssl->config) {
    return;
  }
  ssl->config->cert->key_method = key_method;
}

void SSL_CTX_set_private_key_method(SSL_CTX *ctx,
                                    const SSL_PRIVATE_KEY_METHOD *key_method) {
  ctx->cert->key_method = key_method;
}

// OQS note: This was changed from 23 to 30 to accommodate
// large algorithm names (such as "Rainbow-IIIc-Cyclic-Compressed").
static constexpr size_t kMaxSignatureAlgorithmNameLen = 30;

// This was "constexpr" rather than "const", but that triggered a bug in MSVC
// where it didn't pad the strings to the correct length.
static const struct {
  uint16_t signature_algorithm;
  const char name[kMaxSignatureAlgorithmNameLen];
} kSignatureAlgorithmNames[] = {
    {SSL_SIGN_RSA_PKCS1_MD5_SHA1, "rsa_pkcs1_md5_sha1"},
    {SSL_SIGN_RSA_PKCS1_SHA1, "rsa_pkcs1_sha1"},
    {SSL_SIGN_RSA_PKCS1_SHA256, "rsa_pkcs1_sha256"},
    {SSL_SIGN_RSA_PKCS1_SHA384, "rsa_pkcs1_sha384"},
    {SSL_SIGN_RSA_PKCS1_SHA512, "rsa_pkcs1_sha512"},
    {SSL_SIGN_ECDSA_SHA1, "ecdsa_sha1"},
    {SSL_SIGN_ECDSA_SECP256R1_SHA256, "ecdsa_secp256r1_sha256"},
    {SSL_SIGN_ECDSA_SECP384R1_SHA384, "ecdsa_secp384r1_sha384"},
    {SSL_SIGN_ECDSA_SECP521R1_SHA512, "ecdsa_secp521r1_sha512"},
    {SSL_SIGN_RSA_PSS_RSAE_SHA256, "rsa_pss_rsae_sha256"},
    {SSL_SIGN_RSA_PSS_RSAE_SHA384, "rsa_pss_rsae_sha384"},
    {SSL_SIGN_RSA_PSS_RSAE_SHA512, "rsa_pss_rsae_sha512"},
    {SSL_SIGN_ED25519, "ed25519"},
///// OQS_TEMPLATE_FRAGMENT_NAME_SIG_ALG_START
    {SSL_SIGN_OQS_SIG_DEFAULT, "oqs_sig_default"},
    {SSL_SIGN_DILITHIUM2, "dilithium2"},
    {SSL_SIGN_DILITHIUM3, "dilithium3"},
    {SSL_SIGN_DILITHIUM4, "dilithium4"},
    {SSL_SIGN_FALCON512, "falcon512"},
    {SSL_SIGN_FALCON1024, "falcon1024"},
    {SSL_SIGN_PICNICL1FS, "picnicl1fs"},
    {SSL_SIGN_PICNICL1UR, "picnicl1ur"},
    {SSL_SIGN_PICNICL1FULL, "picnicl1full"},
    {SSL_SIGN_PICNIC3L1, "picnic3l1"},
    {SSL_SIGN_PICNIC3L3, "picnic3l3"},
    {SSL_SIGN_PICNIC3L5, "picnic3l5"},
    {SSL_SIGN_RAINBOWICLASSIC, "rainbowIclassic"},
    {SSL_SIGN_RAINBOWICIRCUMZENITHAL, "rainbowIcircumzenithal"},
    {SSL_SIGN_RAINBOWICOMPRESSED, "rainbowIcompressed"},
    {SSL_SIGN_RAINBOWIIICLASSIC, "rainbowIIIclassic"},
    {SSL_SIGN_RAINBOWIIICIRCUMZENITHAL, "rainbowIIIcircumzenithal"},
    {SSL_SIGN_RAINBOWIIICOMPRESSED, "rainbowIIIcompressed"},
    {SSL_SIGN_RAINBOWVCLASSIC, "rainbowVclassic"},
    {SSL_SIGN_RAINBOWVCIRCUMZENITHAL, "rainbowVcircumzenithal"},
    {SSL_SIGN_RAINBOWVCOMPRESSED, "rainbowVcompressed"},
    {SSL_SIGN_SPHINCSHARAKA128FROBUST, "sphincsharaka128frobust"},
    {SSL_SIGN_SPHINCSHARAKA128FSIMPLE, "sphincsharaka128fsimple"},
    {SSL_SIGN_SPHINCSHARAKA128SROBUST, "sphincsharaka128srobust"},
    {SSL_SIGN_SPHINCSHARAKA128SSIMPLE, "sphincsharaka128ssimple"},
    {SSL_SIGN_SPHINCSHARAKA192FROBUST, "sphincsharaka192frobust"},
    {SSL_SIGN_SPHINCSHARAKA192FSIMPLE, "sphincsharaka192fsimple"},
    {SSL_SIGN_SPHINCSHARAKA192SROBUST, "sphincsharaka192srobust"},
    {SSL_SIGN_SPHINCSHARAKA192SSIMPLE, "sphincsharaka192ssimple"},
    {SSL_SIGN_SPHINCSHARAKA256FROBUST, "sphincsharaka256frobust"},
    {SSL_SIGN_SPHINCSHARAKA256FSIMPLE, "sphincsharaka256fsimple"},
    {SSL_SIGN_SPHINCSHARAKA256SROBUST, "sphincsharaka256srobust"},
    {SSL_SIGN_SPHINCSHARAKA256SSIMPLE, "sphincsharaka256ssimple"},
    {SSL_SIGN_SPHINCSSHA256128FROBUST, "sphincssha256128frobust"},
    {SSL_SIGN_SPHINCSSHA256128FSIMPLE, "sphincssha256128fsimple"},
    {SSL_SIGN_SPHINCSSHA256128SROBUST, "sphincssha256128srobust"},
    {SSL_SIGN_SPHINCSSHA256128SSIMPLE, "sphincssha256128ssimple"},
    {SSL_SIGN_SPHINCSSHA256192FROBUST, "sphincssha256192frobust"},
    {SSL_SIGN_SPHINCSSHA256192FSIMPLE, "sphincssha256192fsimple"},
    {SSL_SIGN_SPHINCSSHA256192SROBUST, "sphincssha256192srobust"},
    {SSL_SIGN_SPHINCSSHA256192SSIMPLE, "sphincssha256192ssimple"},
    {SSL_SIGN_SPHINCSSHA256256FROBUST, "sphincssha256256frobust"},
    {SSL_SIGN_SPHINCSSHA256256FSIMPLE, "sphincssha256256fsimple"},
    {SSL_SIGN_SPHINCSSHA256256SROBUST, "sphincssha256256srobust"},
    {SSL_SIGN_SPHINCSSHA256256SSIMPLE, "sphincssha256256ssimple"},
    {SSL_SIGN_SPHINCSSHAKE256128FROBUST, "sphincsshake256128frobust"},
    {SSL_SIGN_SPHINCSSHAKE256128FSIMPLE, "sphincsshake256128fsimple"},
    {SSL_SIGN_SPHINCSSHAKE256128SROBUST, "sphincsshake256128srobust"},
    {SSL_SIGN_SPHINCSSHAKE256128SSIMPLE, "sphincsshake256128ssimple"},
    {SSL_SIGN_SPHINCSSHAKE256192FROBUST, "sphincsshake256192frobust"},
    {SSL_SIGN_SPHINCSSHAKE256192FSIMPLE, "sphincsshake256192fsimple"},
    {SSL_SIGN_SPHINCSSHAKE256192SROBUST, "sphincsshake256192srobust"},
    {SSL_SIGN_SPHINCSSHAKE256192SSIMPLE, "sphincsshake256192ssimple"},
    {SSL_SIGN_SPHINCSSHAKE256256FROBUST, "sphincsshake256256frobust"},
    {SSL_SIGN_SPHINCSSHAKE256256FSIMPLE, "sphincsshake256256fsimple"},
    {SSL_SIGN_SPHINCSSHAKE256256SROBUST, "sphincsshake256256srobust"},
    {SSL_SIGN_SPHINCSSHAKE256256SSIMPLE, "sphincsshake256256ssimple"},
///// OQS_TEMPLATE_FRAGMENT_NAME_SIG_ALG_END
};

const char *SSL_get_signature_algorithm_name(uint16_t sigalg,
                                             int include_curve) {
  if (!include_curve) {
    switch (sigalg) {
      case SSL_SIGN_ECDSA_SECP256R1_SHA256:
        return "ecdsa_sha256";
      case SSL_SIGN_ECDSA_SECP384R1_SHA384:
        return "ecdsa_sha384";
      case SSL_SIGN_ECDSA_SECP521R1_SHA512:
        return "ecdsa_sha512";
    }
  }

  for (const auto &candidate : kSignatureAlgorithmNames) {
    if (candidate.signature_algorithm == sigalg) {
      return candidate.name;
    }
  }

  return NULL;
}

int SSL_get_signature_algorithm_key_type(uint16_t sigalg) {
  const SSL_SIGNATURE_ALGORITHM *alg = get_signature_algorithm(sigalg);
  return alg != nullptr ? alg->pkey_type : EVP_PKEY_NONE;
}

const EVP_MD *SSL_get_signature_algorithm_digest(uint16_t sigalg) {
  const SSL_SIGNATURE_ALGORITHM *alg = get_signature_algorithm(sigalg);
  if (alg == nullptr || alg->digest_func == nullptr) {
    return nullptr;
  }
  return alg->digest_func();
}

int SSL_is_signature_algorithm_rsa_pss(uint16_t sigalg) {
  const SSL_SIGNATURE_ALGORITHM *alg = get_signature_algorithm(sigalg);
  return alg != nullptr && alg->is_rsa_pss;
}

int SSL_CTX_set_signing_algorithm_prefs(SSL_CTX *ctx, const uint16_t *prefs,
                                        size_t num_prefs) {
  return ctx->cert->sigalgs.CopyFrom(MakeConstSpan(prefs, num_prefs));
}

int SSL_set_signing_algorithm_prefs(SSL *ssl, const uint16_t *prefs,
                                    size_t num_prefs) {
  if (!ssl->config) {
    return 0;
  }
  return ssl->config->cert->sigalgs.CopyFrom(MakeConstSpan(prefs, num_prefs));
}

static constexpr struct {
  int pkey_type;
  int hash_nid;
  uint16_t signature_algorithm;
} kSignatureAlgorithmsMapping[] = {
    {EVP_PKEY_RSA, NID_sha1, SSL_SIGN_RSA_PKCS1_SHA1},
    {EVP_PKEY_RSA, NID_sha256, SSL_SIGN_RSA_PKCS1_SHA256},
    {EVP_PKEY_RSA, NID_sha384, SSL_SIGN_RSA_PKCS1_SHA384},
    {EVP_PKEY_RSA, NID_sha512, SSL_SIGN_RSA_PKCS1_SHA512},
    {EVP_PKEY_RSA_PSS, NID_sha256, SSL_SIGN_RSA_PSS_RSAE_SHA256},
    {EVP_PKEY_RSA_PSS, NID_sha384, SSL_SIGN_RSA_PSS_RSAE_SHA384},
    {EVP_PKEY_RSA_PSS, NID_sha512, SSL_SIGN_RSA_PSS_RSAE_SHA512},
    {EVP_PKEY_EC, NID_sha1, SSL_SIGN_ECDSA_SHA1},
    {EVP_PKEY_EC, NID_sha256, SSL_SIGN_ECDSA_SECP256R1_SHA256},
    {EVP_PKEY_EC, NID_sha384, SSL_SIGN_ECDSA_SECP384R1_SHA384},
    {EVP_PKEY_EC, NID_sha512, SSL_SIGN_ECDSA_SECP521R1_SHA512},
    {EVP_PKEY_ED25519, NID_undef, SSL_SIGN_ED25519},
///// OQS_TEMPLATE_FRAGMENT_ADD_SIG_ALG_MAPPINGS_START
    {EVP_PKEY_OQS_SIG_DEFAULT, NID_sha256, SSL_SIGN_OQS_SIG_DEFAULT},
    {EVP_PKEY_DILITHIUM2, NID_sha256, SSL_SIGN_DILITHIUM2},
    {EVP_PKEY_DILITHIUM3, NID_sha256, SSL_SIGN_DILITHIUM3},
    {EVP_PKEY_DILITHIUM4, NID_sha384, SSL_SIGN_DILITHIUM4},
    {EVP_PKEY_FALCON512, NID_sha256, SSL_SIGN_FALCON512},
    {EVP_PKEY_FALCON1024, NID_sha512, SSL_SIGN_FALCON1024},
    {EVP_PKEY_PICNICL1FS, NID_sha256, SSL_SIGN_PICNICL1FS},
    {EVP_PKEY_PICNICL1UR, NID_sha256, SSL_SIGN_PICNICL1UR},
    {EVP_PKEY_PICNICL1FULL, NID_sha256, SSL_SIGN_PICNICL1FULL},
    {EVP_PKEY_PICNIC3L1, NID_sha256, SSL_SIGN_PICNIC3L1},
    {EVP_PKEY_PICNIC3L3, NID_sha384, SSL_SIGN_PICNIC3L3},
    {EVP_PKEY_PICNIC3L5, NID_sha512, SSL_SIGN_PICNIC3L5},
    {EVP_PKEY_RAINBOWICLASSIC, NID_sha256, SSL_SIGN_RAINBOWICLASSIC},
    {EVP_PKEY_RAINBOWICIRCUMZENITHAL, NID_sha256, SSL_SIGN_RAINBOWICIRCUMZENITHAL},
    {EVP_PKEY_RAINBOWICOMPRESSED, NID_sha256, SSL_SIGN_RAINBOWICOMPRESSED},
    {EVP_PKEY_RAINBOWIIICLASSIC, NID_sha384, SSL_SIGN_RAINBOWIIICLASSIC},
    {EVP_PKEY_RAINBOWIIICIRCUMZENITHAL, NID_sha384, SSL_SIGN_RAINBOWIIICIRCUMZENITHAL},
    {EVP_PKEY_RAINBOWIIICOMPRESSED, NID_sha384, SSL_SIGN_RAINBOWIIICOMPRESSED},
    {EVP_PKEY_RAINBOWVCLASSIC, NID_sha512, SSL_SIGN_RAINBOWVCLASSIC},
    {EVP_PKEY_RAINBOWVCIRCUMZENITHAL, NID_sha512, SSL_SIGN_RAINBOWVCIRCUMZENITHAL},
    {EVP_PKEY_RAINBOWVCOMPRESSED, NID_sha512, SSL_SIGN_RAINBOWVCOMPRESSED},
    {EVP_PKEY_SPHINCSHARAKA128FROBUST, NID_sha256, SSL_SIGN_SPHINCSHARAKA128FROBUST},
    {EVP_PKEY_SPHINCSHARAKA128FSIMPLE, NID_sha256, SSL_SIGN_SPHINCSHARAKA128FSIMPLE},
    {EVP_PKEY_SPHINCSHARAKA128SROBUST, NID_sha256, SSL_SIGN_SPHINCSHARAKA128SROBUST},
    {EVP_PKEY_SPHINCSHARAKA128SSIMPLE, NID_sha256, SSL_SIGN_SPHINCSHARAKA128SSIMPLE},
    {EVP_PKEY_SPHINCSHARAKA192FROBUST, NID_sha384, SSL_SIGN_SPHINCSHARAKA192FROBUST},
    {EVP_PKEY_SPHINCSHARAKA192FSIMPLE, NID_sha384, SSL_SIGN_SPHINCSHARAKA192FSIMPLE},
    {EVP_PKEY_SPHINCSHARAKA192SROBUST, NID_sha384, SSL_SIGN_SPHINCSHARAKA192SROBUST},
    {EVP_PKEY_SPHINCSHARAKA192SSIMPLE, NID_sha384, SSL_SIGN_SPHINCSHARAKA192SSIMPLE},
    {EVP_PKEY_SPHINCSHARAKA256FROBUST, NID_sha512, SSL_SIGN_SPHINCSHARAKA256FROBUST},
    {EVP_PKEY_SPHINCSHARAKA256FSIMPLE, NID_sha512, SSL_SIGN_SPHINCSHARAKA256FSIMPLE},
    {EVP_PKEY_SPHINCSHARAKA256SROBUST, NID_sha512, SSL_SIGN_SPHINCSHARAKA256SROBUST},
    {EVP_PKEY_SPHINCSHARAKA256SSIMPLE, NID_sha512, SSL_SIGN_SPHINCSHARAKA256SSIMPLE},
    {EVP_PKEY_SPHINCSSHA256128FROBUST, NID_sha256, SSL_SIGN_SPHINCSSHA256128FROBUST},
    {EVP_PKEY_SPHINCSSHA256128FSIMPLE, NID_sha256, SSL_SIGN_SPHINCSSHA256128FSIMPLE},
    {EVP_PKEY_SPHINCSSHA256128SROBUST, NID_sha256, SSL_SIGN_SPHINCSSHA256128SROBUST},
    {EVP_PKEY_SPHINCSSHA256128SSIMPLE, NID_sha256, SSL_SIGN_SPHINCSSHA256128SSIMPLE},
    {EVP_PKEY_SPHINCSSHA256192FROBUST, NID_sha384, SSL_SIGN_SPHINCSSHA256192FROBUST},
    {EVP_PKEY_SPHINCSSHA256192FSIMPLE, NID_sha384, SSL_SIGN_SPHINCSSHA256192FSIMPLE},
    {EVP_PKEY_SPHINCSSHA256192SROBUST, NID_sha384, SSL_SIGN_SPHINCSSHA256192SROBUST},
    {EVP_PKEY_SPHINCSSHA256192SSIMPLE, NID_sha384, SSL_SIGN_SPHINCSSHA256192SSIMPLE},
    {EVP_PKEY_SPHINCSSHA256256FROBUST, NID_sha512, SSL_SIGN_SPHINCSSHA256256FROBUST},
    {EVP_PKEY_SPHINCSSHA256256FSIMPLE, NID_sha512, SSL_SIGN_SPHINCSSHA256256FSIMPLE},
    {EVP_PKEY_SPHINCSSHA256256SROBUST, NID_sha512, SSL_SIGN_SPHINCSSHA256256SROBUST},
    {EVP_PKEY_SPHINCSSHA256256SSIMPLE, NID_sha512, SSL_SIGN_SPHINCSSHA256256SSIMPLE},
    {EVP_PKEY_SPHINCSSHAKE256128FROBUST, NID_sha256, SSL_SIGN_SPHINCSSHAKE256128FROBUST},
    {EVP_PKEY_SPHINCSSHAKE256128FSIMPLE, NID_sha256, SSL_SIGN_SPHINCSSHAKE256128FSIMPLE},
    {EVP_PKEY_SPHINCSSHAKE256128SROBUST, NID_sha256, SSL_SIGN_SPHINCSSHAKE256128SROBUST},
    {EVP_PKEY_SPHINCSSHAKE256128SSIMPLE, NID_sha256, SSL_SIGN_SPHINCSSHAKE256128SSIMPLE},
    {EVP_PKEY_SPHINCSSHAKE256192FROBUST, NID_sha384, SSL_SIGN_SPHINCSSHAKE256192FROBUST},
    {EVP_PKEY_SPHINCSSHAKE256192FSIMPLE, NID_sha384, SSL_SIGN_SPHINCSSHAKE256192FSIMPLE},
    {EVP_PKEY_SPHINCSSHAKE256192SROBUST, NID_sha384, SSL_SIGN_SPHINCSSHAKE256192SROBUST},
    {EVP_PKEY_SPHINCSSHAKE256192SSIMPLE, NID_sha384, SSL_SIGN_SPHINCSSHAKE256192SSIMPLE},
    {EVP_PKEY_SPHINCSSHAKE256256FROBUST, NID_sha512, SSL_SIGN_SPHINCSSHAKE256256FROBUST},
    {EVP_PKEY_SPHINCSSHAKE256256FSIMPLE, NID_sha512, SSL_SIGN_SPHINCSSHAKE256256FSIMPLE},
    {EVP_PKEY_SPHINCSSHAKE256256SROBUST, NID_sha512, SSL_SIGN_SPHINCSSHAKE256256SROBUST},
    {EVP_PKEY_SPHINCSSHAKE256256SSIMPLE, NID_sha512, SSL_SIGN_SPHINCSSHAKE256256SSIMPLE},
///// OQS_TEMPLATE_FRAGMENT_ADD_SIG_ALG_MAPPINGS_END
};

static bool parse_sigalg_pairs(Array<uint16_t> *out, const int *values,
                               size_t num_values) {
  if ((num_values & 1) == 1) {
    return false;
  }

  const size_t num_pairs = num_values / 2;
  if (!out->Init(num_pairs)) {
    return false;
  }

  for (size_t i = 0; i < num_values; i += 2) {
    const int hash_nid = values[i];
    const int pkey_type = values[i+1];

    bool found = false;
    for (const auto &candidate : kSignatureAlgorithmsMapping) {
      if (candidate.pkey_type == pkey_type && candidate.hash_nid == hash_nid) {
        (*out)[i / 2] = candidate.signature_algorithm;
        found = true;
        break;
      }
    }

    if (!found) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_INVALID_SIGNATURE_ALGORITHM);
      ERR_add_error_dataf("unknown hash:%d pkey:%d", hash_nid, pkey_type);
      return false;
    }
  }

  return true;
}

static int compare_uint16_t(const void *p1, const void *p2) {
  uint16_t u1 = *((const uint16_t *)p1);
  uint16_t u2 = *((const uint16_t *)p2);
  if (u1 < u2) {
    return -1;
  } else if (u1 > u2) {
    return 1;
  } else {
    return 0;
  }
}

static bool sigalgs_unique(Span<const uint16_t> in_sigalgs) {
  if (in_sigalgs.size() < 2) {
    return true;
  }

  Array<uint16_t> sigalgs;
  if (!sigalgs.CopyFrom(in_sigalgs)) {
    return false;
  }

  qsort(sigalgs.data(), sigalgs.size(), sizeof(uint16_t), compare_uint16_t);

  for (size_t i = 1; i < sigalgs.size(); i++) {
    if (sigalgs[i - 1] == sigalgs[i]) {
      OPENSSL_PUT_ERROR(SSL, SSL_R_DUPLICATE_SIGNATURE_ALGORITHM);
      return false;
    }
  }

  return true;
}

int SSL_CTX_set1_sigalgs(SSL_CTX *ctx, const int *values, size_t num_values) {
  Array<uint16_t> sigalgs;
  if (!parse_sigalg_pairs(&sigalgs, values, num_values) ||
      !sigalgs_unique(sigalgs)) {
    return 0;
  }

  if (!SSL_CTX_set_signing_algorithm_prefs(ctx, sigalgs.data(),
                                           sigalgs.size()) ||
      !ctx->verify_sigalgs.CopyFrom(sigalgs)) {
    return 0;
  }

  return 1;
}

int SSL_set1_sigalgs(SSL *ssl, const int *values, size_t num_values) {
  if (!ssl->config) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
    return 0;
  }

  Array<uint16_t> sigalgs;
  if (!parse_sigalg_pairs(&sigalgs, values, num_values) ||
      !sigalgs_unique(sigalgs)) {
    return 0;
  }

  if (!SSL_set_signing_algorithm_prefs(ssl, sigalgs.data(), sigalgs.size()) ||
      !ssl->config->verify_sigalgs.CopyFrom(sigalgs)) {
    return 0;
  }

  return 1;
}

static bool parse_sigalgs_list(Array<uint16_t> *out, const char *str) {
  // str looks like "RSA+SHA1:ECDSA+SHA256:ecdsa_secp256r1_sha256".

  // Count colons to give the number of output elements from any successful
  // parse.
  size_t num_elements = 1;
  size_t len = 0;
  for (const char *p = str; *p; p++) {
    len++;
    if (*p == ':') {
      num_elements++;
    }
  }

  if (!out->Init(num_elements)) {
    return false;
  }
  size_t out_i = 0;

  enum {
    pkey_or_name,
    hash_name,
  } state = pkey_or_name;

  char buf[kMaxSignatureAlgorithmNameLen];
  // buf_used is always < sizeof(buf). I.e. it's always safe to write
  // buf[buf_used] = 0.
  size_t buf_used = 0;

  int pkey_type = 0, hash_nid = 0;

  // Note that the loop runs to len+1, i.e. it'll process the terminating NUL.
  for (size_t offset = 0; offset < len+1; offset++) {
    const char c = str[offset];

    switch (c) {
      case '+':
        if (state == hash_name) {
          OPENSSL_PUT_ERROR(SSL, SSL_R_INVALID_SIGNATURE_ALGORITHM);
          ERR_add_error_dataf("+ found in hash name at offset %zu", offset);
          return false;
        }
        if (buf_used == 0) {
          OPENSSL_PUT_ERROR(SSL, SSL_R_INVALID_SIGNATURE_ALGORITHM);
          ERR_add_error_dataf("empty public key type at offset %zu", offset);
          return false;
        }
        buf[buf_used] = 0;

        if (strcmp(buf, "RSA") == 0) {
          pkey_type = EVP_PKEY_RSA;
        } else if (strcmp(buf, "RSA-PSS") == 0 ||
                   strcmp(buf, "PSS") == 0) {
          pkey_type = EVP_PKEY_RSA_PSS;
        } else if (strcmp(buf, "ECDSA") == 0) {
          pkey_type = EVP_PKEY_EC;
        } else {
          OPENSSL_PUT_ERROR(SSL, SSL_R_INVALID_SIGNATURE_ALGORITHM);
          ERR_add_error_dataf("unknown public key type '%s'", buf);
          return false;
        }

        state = hash_name;
        buf_used = 0;
        break;

      case ':':
        OPENSSL_FALLTHROUGH;
      case 0:
        if (buf_used == 0) {
          OPENSSL_PUT_ERROR(SSL, SSL_R_INVALID_SIGNATURE_ALGORITHM);
          ERR_add_error_dataf("empty element at offset %zu", offset);
          return false;
        }

        buf[buf_used] = 0;

        if (state == pkey_or_name) {
          // No '+' was seen thus this is a TLS 1.3-style name.
          bool found = false;
          for (const auto &candidate : kSignatureAlgorithmNames) {
            if (strcmp(candidate.name, buf) == 0) {
              assert(out_i < num_elements);
              (*out)[out_i++] = candidate.signature_algorithm;
              found = true;
              break;
            }
          }

          if (!found) {
            OPENSSL_PUT_ERROR(SSL, SSL_R_INVALID_SIGNATURE_ALGORITHM);
            ERR_add_error_dataf("unknown signature algorithm '%s'", buf);
            return false;
          }
        } else {
          if (strcmp(buf, "SHA1") == 0) {
            hash_nid = NID_sha1;
          } else if (strcmp(buf, "SHA256") == 0) {
            hash_nid = NID_sha256;
          } else if (strcmp(buf, "SHA384") == 0) {
            hash_nid = NID_sha384;
          } else if (strcmp(buf, "SHA512") == 0) {
            hash_nid = NID_sha512;
          } else {
            OPENSSL_PUT_ERROR(SSL, SSL_R_INVALID_SIGNATURE_ALGORITHM);
            ERR_add_error_dataf("unknown hash function '%s'", buf);
            return false;
          }

          bool found = false;
          for (const auto &candidate : kSignatureAlgorithmsMapping) {
            if (candidate.pkey_type == pkey_type &&
                candidate.hash_nid == hash_nid) {
              assert(out_i < num_elements);
              (*out)[out_i++] = candidate.signature_algorithm;
              found = true;
              break;
            }
          }

          if (!found) {
            OPENSSL_PUT_ERROR(SSL, SSL_R_INVALID_SIGNATURE_ALGORITHM);
            ERR_add_error_dataf("unknown pkey:%d hash:%s", pkey_type, buf);
            return false;
          }
        }

        state = pkey_or_name;
        buf_used = 0;
        break;

      default:
        if (buf_used == sizeof(buf) - 1) {
          OPENSSL_PUT_ERROR(SSL, SSL_R_INVALID_SIGNATURE_ALGORITHM);
          ERR_add_error_dataf("substring too long at offset %zu", offset);
          return false;
        }

        if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') || c == '-' || c == '_') {
          buf[buf_used++] = c;
        } else {
          OPENSSL_PUT_ERROR(SSL, SSL_R_INVALID_SIGNATURE_ALGORITHM);
          ERR_add_error_dataf("invalid character 0x%02x at offest %zu", c,
                              offset);
          return false;
        }
    }
  }

  assert(out_i == out->size());
  return true;
}

int SSL_CTX_set1_sigalgs_list(SSL_CTX *ctx, const char *str) {
  Array<uint16_t> sigalgs;
  if (!parse_sigalgs_list(&sigalgs, str) ||
      !sigalgs_unique(sigalgs)) {
    return 0;
  }

  if (!SSL_CTX_set_signing_algorithm_prefs(ctx, sigalgs.data(),
                                           sigalgs.size()) ||
      !SSL_CTX_set_verify_algorithm_prefs(ctx, sigalgs.data(),
                                          sigalgs.size())) {
    return 0;
  }

  return 1;
}

int SSL_set1_sigalgs_list(SSL *ssl, const char *str) {
  if (!ssl->config) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
    return 0;
  }

  Array<uint16_t> sigalgs;
  if (!parse_sigalgs_list(&sigalgs, str) ||
      !sigalgs_unique(sigalgs)) {
    return 0;
  }

  if (!SSL_set_signing_algorithm_prefs(ssl, sigalgs.data(), sigalgs.size()) ||
      !SSL_set_verify_algorithm_prefs(ssl, sigalgs.data(), sigalgs.size())) {
    return 0;
  }

  return 1;
}

int SSL_CTX_set_verify_algorithm_prefs(SSL_CTX *ctx, const uint16_t *prefs,
                                       size_t num_prefs) {
  return ctx->verify_sigalgs.CopyFrom(MakeConstSpan(prefs, num_prefs));
}

int SSL_set_verify_algorithm_prefs(SSL *ssl, const uint16_t *prefs,
                                   size_t num_prefs) {
  if (!ssl->config) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_SHOULD_NOT_HAVE_BEEN_CALLED);
    return 0;
  }

  return ssl->config->verify_sigalgs.CopyFrom(MakeConstSpan(prefs, num_prefs));
}
