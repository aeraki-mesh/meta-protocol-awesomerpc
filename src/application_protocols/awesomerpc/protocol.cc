#include "src/application_protocols/awesomerpc/protocol.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace MetaProtocolProxy {
namespace Awesomerpc {

const uint32_t AwesomerpcHeader::HEADER_SIZE = 13;

bool AwesomerpcHeader::decode(Buffer::Instance& buffer) {
  if (buffer.length() < HEADER_SIZE) {
    ENVOY_LOG(error, "Awesomerpc Header decode buffer.length:{} < {}.", buffer.length(), HEADER_SIZE);
    return false;
  }

  uint64_t pos = 0;
  _version = buffer.peekBEInt<int8_t>(pos);
  pos += sizeof(int8_t);
  _pack_flow = buffer.peekBEInt<uint32_t>(pos);
  pos += sizeof(uint32_t);
  _pack_len = buffer.peekBEInt<uint16_t>(pos);
  pos += sizeof(uint16_t);
  _req_cmd = buffer.peekBEInt<int16_t>(pos);
  pos += sizeof(int16_t);
  _rsp_code = buffer.peekBEInt<int16_t>(pos);
  pos += sizeof(int16_t);

  ASSERT(pos == HEADER_SIZE);

  return true;
}

bool AwesomerpcHeader::encode(Buffer::Instance& buffer) {
  buffer.writeBEInt(_version);
  buffer.writeBEInt(_pack_flow);
  buffer.writeBEInt(_pack_len);
  buffer.writeBEInt(_req_cmd);
  buffer.writeBEInt(_rsp_code);
  return true;
}

} // namespace Awesomerpc
} // namespace MetaProtocolProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
