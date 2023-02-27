#include <any>

#include "envoy/buffer/buffer.h"

#include "source/common/common/logger.h"

#include "src/meta_protocol_proxy/codec/codec.h"
#include "src/application_protocols/awesomerpc/awesomerpc_codec.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace MetaProtocolProxy {
namespace Awesomerpc {

MetaProtocolProxy::DecodeStatus AwesomerpcCodec::decode(Buffer::Instance& buffer,
                                                  MetaProtocolProxy::Metadata& metadata) {
  ENVOY_LOG(debug, "Awesomerpc decoder: {} bytes available", buffer.length());
  messageType_ = metadata.getMessageType();
  ASSERT(messageType_ == MetaProtocolProxy::MessageType::Request ||
         messageType_ == MetaProtocolProxy::MessageType::Response);

  while (decode_status != AwesomerpcDecodeStatus::DecodeDone) {
    decode_status = handleState(buffer);
    if (decode_status == AwesomerpcDecodeStatus::WaitForData) {
      return DecodeStatus::WaitForData;
    }
  }

  // fill the metadata with the headers exacted from the message
  toMetadata(metadata);
  // reset decode status
  decode_status = AwesomerpcDecodeStatus::DecodeHeader;
  return DecodeStatus::Done;
}

void AwesomerpcCodec::encode(const MetaProtocolProxy::Metadata& metadata,
                      const MetaProtocolProxy::Mutation& mutation, Buffer::Instance& buffer) {
  // TODO we don't need to implement encode for now.
  // This method only need to be implemented if we want to modify the respose message
  (void)metadata;
  (void)mutation;
  (void)buffer;
}

void AwesomerpcCodec::onError(const MetaProtocolProxy::Metadata& metadata,
                        const MetaProtocolProxy::Error& error, Buffer::Instance& buffer) {
  AwesomerpcHeader response;
  // Make sure to set the request id if the application protocol has one, otherwise MetaProtocol framework will 
  // complaint that the id in the error response is not equal to the one in the request
  response.set_pack_flow(metadata.getRequestId());
  response.set_pack_len(AwesomerpcHeader::HEADER_SIZE);
  switch (error.type) {
  case MetaProtocolProxy::ErrorType::RouteNotFound:
    response.set_rsp_code(static_cast<int16_t>(AwesomerpcCode::NoRoute));
    break;
  default:
    response.set_rsp_code(static_cast<int16_t>(AwesomerpcCode::Error));
    break;
  }
  response.encode(buffer);
}

AwesomerpcDecodeStatus AwesomerpcCodec::handleState(Buffer::Instance& buffer) {
  switch (decode_status)
  {
  case AwesomerpcDecodeStatus::DecodeHeader:
    return decodeHeader(buffer);
  case AwesomerpcDecodeStatus::DecodePayload:
    return decodeBody(buffer);
  default:
    PANIC("not reached");
  }
  return AwesomerpcDecodeStatus::DecodeDone;
}

AwesomerpcDecodeStatus AwesomerpcCodec::decodeHeader(Buffer::Instance& buffer) {
  ENVOY_LOG(debug, "decode awesomerpc header: {}", buffer.length());
  // Wait for more data if the header is not complete
  if (buffer.length() < AwesomerpcHeader::HEADER_SIZE) {
    ENVOY_LOG(debug, "continue {}", buffer.length());
    return AwesomerpcDecodeStatus::WaitForData;
  }

  if(!awesomerpc_header_.decode(buffer)) {
    throw EnvoyException(fmt::format("awesomerpc header invalid"));
  }
  
  return AwesomerpcDecodeStatus::DecodePayload;
}

AwesomerpcDecodeStatus AwesomerpcCodec::decodeBody(Buffer::Instance& buffer) {
  // Wait for more data if the buffer is not a complete message	
  if (buffer.length() < awesomerpc_header_.get_pack_len()) {
    return AwesomerpcDecodeStatus::WaitForData;
  }

  origin_msg_ = std::make_unique<Buffer::OwnedImpl>();

  // move the decoded message out of the buffer
  origin_msg_->move(buffer, awesomerpc_header_.get_pack_len());

  return AwesomerpcDecodeStatus::DecodeDone;
}

void AwesomerpcCodec::toMetadata(MetaProtocolProxy::Metadata& metadata) {
  metadata.setRequestId(awesomerpc_header_.get_pack_flow());
  metadata.putString("cmd", std::to_string(awesomerpc_header_.get_req_cmd()));
  metadata.originMessage().move(*origin_msg_);
}

} // namespace Awesomerpc
} // namespace MetaProtocolProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
