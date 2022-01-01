#pragma once

#include "common/buffer/buffer_impl.h"
#include "common/common/logger.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace MetaProtocolProxy {
namespace Awesomerpc {

enum class AwesomerpcCode {
  NoRoute = 1,
  Error = 1,
};

struct AwesomerpcHeader : public Logger::Loggable<Logger::Id::filter> {
  static const uint32_t HEADER_SIZE;
  int8_t _version;
  uint32_t _pack_flow;
  uint32_t _pack_len;
  int16_t _req_cmd;
  int16_t _rsp_code;

  bool decode(Buffer::Instance& buffer);
  bool encode(Buffer::Instance& buffer);

  uint32_t get_pack_flow() const {return _pack_len;};
  uint32_t get_pack_len() const {return _pack_len;};
  int16_t get_req_cmd() const {return _req_cmd;};
  void set_pack_flow(uint32_t pack_flow) {_pack_flow = pack_flow;};
  void set_pack_len(uint32_t pack_len) {_pack_len = pack_len;};
  void set_rsp_code(int16_t rsp_code) {_rsp_code = rsp_code;};
};

} // namespace Awesomerpc
} // namespace MetaProtocolProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
