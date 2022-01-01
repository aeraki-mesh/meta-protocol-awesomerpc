#include "envoy/registry/registry.h"

#include "src/meta_protocol_proxy/codec/factory.h"
#include "src/application_protocols/awesomerpc/config.h"
#include "src/application_protocols/awesomerpc/awesomerpc_codec.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace MetaProtocolProxy {
namespace Awesomerpc {

MetaProtocolProxy::CodecPtr AwesomerpcCodecConfig::createCodec(const Protobuf::Message&) {
  return std::make_unique<Awesomerpc::AwesomerpcCodec>();
};

/**
 * Static registration for the trpc codec. @see RegisterFactory.
 */
REGISTER_FACTORY(AwesomerpcCodecConfig, MetaProtocolProxy::NamedCodecConfigFactory);

} // namespace Awesomerpc
} // namespace MetaProtocolProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
