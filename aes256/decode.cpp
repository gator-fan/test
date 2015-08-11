/*************************************************************************
 * @File Name: decode.cpp
 * @Author: wangfan
 * @Mail: wangfan@mvad.com 
 * @Created Time: 2015年07月09日 星期四 18时45分01秒
 ************************************************************************/

#include <iostream>
#include <openssl/evp.h>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//static const uint8_t *WPRICE_AES_KEY256 = (const uint8_t *) "33dc0cae145f8471acd8791d19f23aed";
static const uint8_t *WPRICE_AES_KEY256 = (const uint8_t *) "33dc0cae145f8471acd8791d19f23aed";
//static const uint8_t *WPRICE_AES_IV = (const uint8_t *) "1234567890123456";
static const uint8_t *WPRICE_AES_IV = (const uint8_t *) "12345678901234567890";

std::vector<uint8_t> aes256_ecb_decrypt(const uint8_t *src, size_t slen, const uint8_t key[], const uint8_t iv[])
{
  std::vector<uint8_t> buff;
  uint8_t *workSpace = nullptr;

  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (ctx == NULL) {
    return buff;
  }

  try {
    workSpace = new uint8_t(slen);
    if (workSpace == nullptr) {
      throw -1;
    }
    int rstCount = 0;

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, key, iv) != 1) {
      throw -2;
    }

    if (EVP_DecryptUpdate(ctx, workSpace, &rstCount, src, slen) != 1) {
      throw -3;
    }

    int padResSize;
    if (EVP_DecryptFinal_ex(ctx, workSpace + rstCount, &padResSize) != 1) {
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

std::vector<uint8_t> base64_decode_urlsafe(const char *src, const size_t *len)
{
  const uint8_t w[] = {
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3E,0xFF,0xFF,
    0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,
    0x0F,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0xFF,0xFF,0xFF,0xFF,0x3F,
    0xFF,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
    0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x31,0x32,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,
  };
  const char *p = src;
  std::vector<uint8_t> buff;
  unsigned int x = 0;
  int rem = 0;
  if (len) buff.reserve(*len / 4 * 3 + 4);

  for (size_t i = 0; *p && (!len || i < *len); p++, i++) {
    if (*p < 0 || w[*p & 0x7f] == 0xFF)
      continue;
    x = x << 6 | w[*p & 0x7f];
    rem += 6;
    if (rem >= 8) {
      rem -= 8;
      buff.push_back((uint8_t) (x >> rem));
    }
  }
  return buff;
}

std::string decrypt_wprice(const std::string &text)
{
  size_t tlen = text.length();
  std::vector<uint8_t> enc = base64_decode_urlsafe(text.c_str(), &tlen);
  //std::vector<uint8_t> res = aes256_ecb_decrypt(enc.data(), enc.size(), WPRICE_AES_KEY256, WPRICE_AES_IV);
  std::vector<uint8_t> res = aes256_ecb_decrypt(enc.data(), enc.size(), WPRICE_AES_KEY256, NULL);

  return std::string((char *) res.data(), res.size());
}

int main() {
  std::string encrypted = "yXMU_lpw6LhxGlyUqqbdqg";
  std::string decrypted = decrypt_wprice(encrypted);
  cout << decrypted << endl;

  std::string encrypted1 = "exsL3GWlfXpLyQ5dB-8qGA";
  std::string decrypted1 = decrypt_wprice(encrypted1);
  cout << decrypted1 << endl;

  std::string encrypted2 = "mfUiVFNku3mLFYNFRKApuA";
  std::string decrypted2 = decrypt_wprice(encrypted2);
  cout << decrypted2 << endl;

  std::string encrypted3 = "w69C8dyd7krygjU5S6R2dg";
  std::string decrypted3 = decrypt_wprice(encrypted3);
  cout << decrypted3 << endl;

  return 0;
}


