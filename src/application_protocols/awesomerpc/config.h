#pragma once

#include "src/meta_protocol_proxy/codec/factory.h"
#include "src/application_protocols/awesomerpc/awesomerpc_codec.pb.h"
#include "src/application_protocols/awesomerpc/awesomerpc_codec.pb.validate.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace MetaProtocolProxy {
namespace Awesomerpc {

class AwesomerpcCodecConfig
    : public MetaProtocolProxy::CodecFactoryBase<aeraki::meta_protocol::codec::AwesomerpcCodec> {
public:
  AwesomerpcCodecConfig() : CodecFactoryBase("aeraki.meta_protocol.codec.awesomerpc") {}
  MetaProtocolProxy::CodecPtr createCodec(const Protobuf::Message& config) override;
};

} // namespace Awesomerpc
} // namespace MetaProtocolProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
