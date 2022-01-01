load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
)

# compile proto
load("@envoy_api//bazel:api_build_system.bzl", "api_proto_package")

api_proto_package(
    deps = ["@com_github_cncf_udpa//udpa/annotations:pkg"],
)

envoy_cc_library(
    name = "config",
    visibility = ["//:__pkg__"],
    repository = "@envoy",
    srcs = ["config.cc"],
    hdrs = ["config.h"],
    deps = [
        ":pkg_cc_proto",
        ":codec_lib",
        "@envoy//include/envoy/registry",
        "@meta_protocol_proxy//src/meta_protocol_proxy/codec:factory_lib",
    ],
)

envoy_cc_library(
    name = "codec_lib",
    repository = "@envoy",
    srcs = ["awesomerpc_codec.cc"],
    hdrs = ["awesomerpc_codec.h"],
    deps = [
        "@envoy//include/envoy/buffer:buffer_interface",
        "@envoy//source/common/common:logger_lib",
        "@envoy//source/common/buffer:buffer_lib",
        "@meta_protocol_proxy//src/meta_protocol_proxy/codec:codec_interface",
        ":protocol",
    ],
)

envoy_cc_library(
    name = "protocol",
    repository = "@envoy",
    srcs = ["protocol.cc"],
    hdrs = ["protocol.h"],
    deps = [
        "@envoy//source/common/buffer:buffer_lib",
        "@envoy//source/common/common:minimal_logger_lib",
    ]
)
