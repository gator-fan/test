/*
 *  Copyright (c) 2015, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

#include <proxygen/lib/http/Window.h>
#include <proxygen/lib/http/codec/HTTPCodecFilter.h>

namespace folly {
class IOBufQueue;
}

namespace proxygen {

/**
 * This class implements the logic for managing per-session flow
 * control. Not every codec is interested in per-session flow control, so
 * this filter can only be added in that case or else it is an error.
 */
class FlowControlFilter:
      public PassThroughHTTPCodecFilter {
 public:
  class Callback {
   public:
    virtual ~Callback() {}
    /**
     * Notification channel to alert when the send window state changes.
     */
    virtual void onConnectionSendWindowOpen() = 0;
    virtual void onConnectionSendWindowClosed() = 0;
  };

  static const uint32_t kDefaultCapacity;

  /**
   * Construct a flow control filter.
   * @param callback     A channel to be notified when the window is not
   *                     full anymore.
   * @param writeBuf     The buffer to write egress on. This constructor
   *                     may generate a window update frame on this buffer.
   * @param codec        The codec implementation.
   * @param recvCapacity The initial size of the conn-level recv window.
   *                     It must be >= 65536.  If greater than 65536 it
   *                     will generate an immediate window update into
   *                     writeBuf.
   */
  explicit
  FlowControlFilter(Callback& callback,
                    folly::IOBufQueue& writeBuf,
                    HTTPCodec* codec,
                    uint32_t recvCapacity = kDefaultCapacity);

  /**
   * Modify the session receive window
   *
   * @param writeBuf     The buffer to write egress on. This constructor
   *                     may generate a window update frame on this buffer.
   * @param capacity     The initial size of the conn-level recv window.
   *                     It must be >= 65536.
   */
  void setReceiveWindowSize(folly::IOBufQueue& writeBuf, uint32_t capacity);

  /**
   * Notify the flow control filter that some ingress bytes were
   * processed. If the number of bytes to acknowledge exceeds half the
   * receive window's capacity, a WINDOW_UPDATE frame will be written.
   * @param writeBuf The buffer to write egress on. This function may
   *                 generate a WINDOW_UPDATE on this buffer.
   * @param delta    The number of bytes that were processed.
   * @returns true iff we wrote a WINDOW_UPDATE frame to the write buf.
   */
  bool ingressBytesProcessed(folly::IOBufQueue& writeBuf, uint32_t delta);

  /**
   * @returns the number of bytes available in the connection-level send window
   */
  uint32_t getAvailableSend() const;

  // Filter functions

  bool isReusable() const override;

  void onBody(StreamID stream, std::unique_ptr<folly::IOBuf> chain) override;

  void onWindowUpdate(StreamID stream, uint32_t amount) override;

  size_t generateBody(folly::IOBufQueue& writeBuf,
                      StreamID stream,
                      std::unique_ptr<folly::IOBuf> chain,
                      bool eom) override;

  size_t generateWindowUpdate(folly::IOBufQueue& writeBuf,
                              StreamID stream,
                              uint32_t delta) override;

 private:

  Callback& notify_;
  Window recvWindow_;
  Window sendWindow_;
  int32_t toAck_{0};
  bool error_:1;
  bool sendsBlocked_:1;
};

}
