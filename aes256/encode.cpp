/*************************************************************************
 * @File Name: encode.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年07月09日 星期四 19时02分19秒
 ************************************************************************/

#include <iostream>
#include <openssl/evp.h>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//static const uint8_t *WPRICE_AES_KEY256 = (const uint8_t *) "12345678901234567890123456789012";
static const uint8_t *WPRICE_AES_KEY256 = (const uint8_t *) "33dc0cae145f8471acd8791d19f23aed";
static const uint8_t *WPRICE_AES_IV = (const uint8_t *) "1234567890123456";

std::vector<uint8_t> aes256_ecb_encrypt(const uint8_t *src, size_t slen, const uint8_t key[], const uint8_t iv[])
{
  std::vector<uint8_t> buff;
  uint8_t *workSpace = nullptr;

  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (ctx == NULL) {
    return buff;
  }

  try {
    workSpace = new uint8_t(slen + EVP_MAX_BLOCK_LENGTH);
    if (workSpace == nullptr) {
      throw -1;
    }
    int rstCount = 0;

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, iv) != 1) {
      throw -2;
    }

    if (EVP_EncryptUpdate(ctx, workSpace, &rstCount, src, slen) != 1) {
    throw -3;
  }

  int padResSize;
  if (EVP_EncryptFinal_ex(ctx, workSpace + rstCount, &padResSize) != 1) {
    throw -4;
  }
  rstCount += padResSize;

  buff.assign(workSpace, workSpace + rstCount);

  delete(workSpace);
  } catch (int errCode) {
    cerr << "ERROR: ErrorCode = " << errCode << endl;

    if (errCode != -1 && workSpace != nullptr) {
    delete(workSpace);
  }

  buff.clear();
  }

  EVP_CIPHER_CTX_free(ctx);

  return buff;
}

std::vector<uint8_t> base64_encode_urlsafe(const uint8_t *src, const size_t len)
{
  const uint8_t w[] = {
  0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,   // ABCDEFGHIJKLMNOP
    0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,   // QRSTUVWXYZabcdef
    0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,   // ghijklmnopqrstuv
    0x77, 0x78, 0x79, 0x7A, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x2D, 0x5F    // wxyz0123456789-_
};

std::vector<uint8_t> buff;
buff.reserve(len * 4 / 3 + 8);

size_t bit_offset = 0;
for ( size_t byte_offset = 0; byte_offset + bit_offset / 8 < len; ) {
  uint8_t bit6_data;
  switch (bit_offset) {
    case  0:
      bit6_data = (*(src + byte_offset)) >> 2;
      break;
    case  6:
      bit6_data = ((*(src + byte_offset)) & 0x03) << 4;
      if ( byte_offset + 1 < len ) {
        bit6_data |= (*(src + byte_offset + 1)) >> 4;
      }
      break;
    case  12:
      bit6_data = ((*(src + byte_offset + 1)) & 0x0F) << 2;
      if ( byte_offset + 2 < len ) {
        bit6_data |= (*(src + byte_offset + 2)) >> 6;
      }
      break;
    default:
      bit6_data = (*(src + byte_offset + 2)) & 0x3F;
      break;
  }
  buff.push_back(w[bit6_data]);

  bit_offset += 6;
  if ( bit_offset >= 24 ) {
    byte_offset += 3;
    bit_offset = 0;
  }
}

return buff;
}

std::string encrypt_wprice(const std::string &text)
{
  std::vector<uint8_t> dec = aes256_ecb_encrypt((uint8_t *) text.c_str(), text.length(), WPRICE_AES_KEY256, WPRICE_AES_IV);

  std::vector<uint8_t> res;
  if (!dec.empty()) {
    res = base64_encode_urlsafe(dec.data(), dec.size());
  }

  return std::string((char *) res.data(), res.size());
}

int main() {
  std::string decrypted1 = "0.05";
  std::string encrypted1 = encrypt_wprice(decrypted1);
  cout << encrypted1 << endl;

  std::string decrypted4 = "0.1";
  std::string encrypted4 = encrypt_wprice(decrypted4);
  cout << encrypted4 << endl;

  std::string decrypted2 = "-0.05";
  std::string encrypted2 = encrypt_wprice(decrypted2);
  cout << encrypted2 << endl;

  std::string decrypted3 = "0";
  std::string encrypted3 = encrypt_wprice(decrypted3);
  cout << encrypted3 << endl;


  return 0;
}

