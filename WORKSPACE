workspace(name = "meta_protocol_awesomerpc")

# http_archive is not a native function since bazel 0.19
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive", "http_file")

# 1. Determine SHA256 `wget https://github.com/envoyproxy/envoy/archive/$COMMIT.tar.gz && sha256sum $COMMIT.tar.gz`
# 2. Update .bazelversion, envoy.bazelrc and .bazelrc if needed.
#
# Note: this is needed by release builder to resolve envoy dep sha to tag.
# Commit date: 2021-05-11

ENVOY_SHA = "98c1c9e9a40804b93b074badad1cdf284b47d58b"

ENVOY_SHA256 = "4365a4c09b9a8b3c4ae34d75991fcd046f3e19d53d95dfd5c89209c30be94fe6"

ENVOY_ORG = "envoyproxy"

ENVOY_REPO = "envoy"

# To override with local envoy, just pass `--override_repository=envoy=/PATH/TO/ENVOY` to Bazel or
# persist the option in `user.bazelrc`.
http_archive(
    name = "envoy",
    sha256 = ENVOY_SHA256,
    strip_prefix = ENVOY_REPO + "-" + ENVOY_SHA,
    url = "https://github.com/" + ENVOY_ORG + "/" + ENVOY_REPO + "/archive/" + ENVOY_SHA + ".tar.gz",
)

http_archive(
    name = "io_istio_proxy",
    strip_prefix = "proxy-1.10.0",
    sha256 = "19d13bc4859dc8422b91fc28b0d8d12a34848393583eedfb08af971c658e7ffb",
    url = "https://github.com/istio/proxy/archive/refs/tags/1.10.0.tar.gz",
)

load(
    "@io_istio_proxy//bazel:repositories.bzl",
    "docker_dependencies",
    "googletest_repositories",
    "istioapi_dependencies",
)

googletest_repositories()

istioapi_dependencies()

bind(
    name = "boringssl_crypto",
    actual = "//external:ssl",
)


load("@envoy//bazel:api_binding.bzl", "envoy_api_binding")

envoy_api_binding()

load("@envoy//bazel:api_repositories.bzl", "envoy_api_dependencies")

envoy_api_dependencies()

load("@envoy//bazel:repositories.bzl", "envoy_dependencies")

envoy_dependencies()

load("@envoy//bazel:repositories_extra.bzl", "envoy_dependencies_extra")

envoy_dependencies_extra()

load("@envoy//bazel:dependency_imports.bzl", "envoy_dependency_imports")

envoy_dependency_imports()

# Bazel @rules_pkg

http_archive(
    name = "rules_pkg",
    sha256 = "aeca78988341a2ee1ba097641056d168320ecc51372ef7ff8e64b139516a4937",
    urls = [
        "https://github.com/bazelbuild/rules_pkg/releases/download/0.2.6-1/rules_pkg-0.2.6.tar.gz",
        "https://mirror.bazel.build/github.com/bazelbuild/rules_pkg/releases/download/0.2.6/rules_pkg-0.2.6.tar.gz",
    ],
)

load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")

rules_pkg_dependencies()

# Docker dependencies

docker_dependencies()

load(
    "@io_bazel_rules_docker//repositories:repositories.bzl",
    container_repositories = "repositories",
)

container_repositories()

load("@io_bazel_rules_docker//repositories:deps.bzl", container_deps = "deps")

container_deps()

load(
    "@io_bazel_rules_docker//container:container.bzl",
    "container_pull",
)

container_pull(
    name = "distroless_cc",
    # Latest as of 10/21/2019. To update, remove this line, re-build, and copy the suggested digest.
    digest = "sha256:86f16733f25964c40dcd34edf14339ddbb2287af2f7c9dfad88f0366723c00d7",
    registry = "gcr.io",
    repository = "distroless/cc",
)

container_pull(
    name = "bionic",
    # Latest as of 10/21/2019. To update, remove this line, re-build, and copy the suggested digest.
    digest = "sha256:3e83eca7870ee14a03b8026660e71ba761e6919b6982fb920d10254688a363d4",
    registry = "index.docker.io",
    repository = "library/ubuntu",
    tag = "bionic",
)

# End of docker dependencies

load("@io_istio_proxy//bazel:wasm.bzl", "wasm_dependencies")

wasm_dependencies()

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
  name = "meta_protocol_proxy",
  remote = "https://github.com/aeraki-framework/meta-protocol-proxy.git",
  commit = "dc19282",
)