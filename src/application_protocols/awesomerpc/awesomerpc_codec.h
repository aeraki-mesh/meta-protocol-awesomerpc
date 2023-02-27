#pragma once

#include "envoy/buffer/buffer.h"
#include "envoy/common/optref.h"
#include "envoy/common/pure.h"

#include "source/common/buffer/buffer_impl.h"
#include "source/common/common/logger.h"

#include "src/meta_protocol_proxy/codec/codec.h"
#include "src/application_protocols/awesomerpc/protocol.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace MetaProtocolProxy {
namespace Awesomerpc {

enum class AwesomerpcDecodeStatus {
  DecodeHeader,
  DecodePayload,
  DecodeDone,
  WaitForData,
};

/**
 * Codec for Awesomerpc protocol.
 */
class AwesomerpcCodec : public MetaProtocolProxy::Codec,
                  public Logger::Loggable<Logger::Id::misc> {
public:
  AwesomerpcCodec() {};
  ~AwesomerpcCodec() override = default;

  MetaProtocolProxy::DecodeStatus decode(Buffer::Instance& buffer,
                                         MetaProtocolProxy::Metadata& metadata) override;
  void encode(const MetaProtocolProxy::Metadata& metadata,
              const MetaProtocolProxy::Mutation& mutation, Buffer::Instance& buffer) override;
  void onError(const MetaProtocolProxy::Metadata& metadata, const MetaProtocolProxy::Error& error,
               Buffer::Instance& buffer) override;

protected:
  AwesomerpcDecodeStatus handleState(Buffer::Instance& buffer);
  AwesomerpcDecodeStatus decodeHeader(Buffer::Instance& buffer);
  AwesomerpcDecodeStatus decodeBody(Buffer::Instance& buffer);
  void toMetadata(MetaProtocolProxy::Metadata& metadata);

private:
  AwesomerpcDecodeStatus decode_status{AwesomerpcDecodeStatus::DecodeHeader};
  AwesomerpcHeader awesomerpc_header_;
  MetaProtocolProxy::MessageType messageType_;
  std::unique_ptr<Buffer::OwnedImpl> origin_msg_;
};

} // namespace Awesomerpc
} // namespace MetaProtocolProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
