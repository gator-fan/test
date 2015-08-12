/*
 * Copyright 2015 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef THRIFT_ASYNC_HEADERCHANNEL_H_
#define THRIFT_ASYNC_HEADERCHANNEL_H_ 1

#include <thrift/lib/cpp/transport/THeader.h>

enum THRIFT_SECURITY_POLICY {
  THRIFT_SECURITY_DISABLED = 1,
  THRIFT_SECURITY_PERMITTED = 2,
  THRIFT_SECURITY_REQUIRED = 3,
};

namespace apache { namespace thrift {

/**
 * HeaderChannel manages persistent headers and some other channel level
 * information.
 */
class HeaderChannel {
  public:
    HeaderChannel()
      : header_(new apache::thrift::transport::THeader)
      , clientType_(THRIFT_HEADER_CLIENT_TYPE)
      , prevClientType_(THRIFT_HEADER_CLIENT_TYPE) {
      setSupportedClients(nullptr);
    }

    void setPersistentHeader(const std::string& key,
                             const std::string& value) {
      persistentWriteHeaders_[key] = value;
    }

    transport::THeader::StringToStringMap& getPersistentReadHeaders() {
      return persistentReadHeaders_;
    }

    transport::THeader::StringToStringMap& getPersistentWriteHeaders() {
      return persistentWriteHeaders_;
    }

    // If clients is nullptr, a security policy of THRIFT_SECURITY_DISABLED
    // will be used.
    void setSupportedClients(std::bitset<CLIENT_TYPES_LEN> const* clients);
    bool isSupportedClient(CLIENT_TYPE ct);
    void checkSupportedClient(CLIENT_TYPE ct);

    void setClientType(CLIENT_TYPE ct);
    CLIENT_TYPE getClientType() { return clientType_; }
    void updateClientType(CLIENT_TYPE ct);

    void setSecurityPolicy(THRIFT_SECURITY_POLICY policy);

  protected:
    std::shared_ptr<apache::thrift::transport::THeader> header_;

  private:
    // Map to use for persistent headers
    transport::THeader::StringToStringMap persistentReadHeaders_;
    transport::THeader::StringToStringMap persistentWriteHeaders_;

    CLIENT_TYPE clientType_;
    CLIENT_TYPE prevClientType_;
    std::bitset<CLIENT_TYPES_LEN> supported_clients;

    THRIFT_SECURITY_POLICY securityPolicy_;
};

}} // apache::thrift

#endif // #ifndef THRIFT_ASYNC_HEADERCHANNEL_H_
