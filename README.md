
Manage any private protocols in Istio service meshes with [MetaProtocol](https://github.com/aeraki-framework/meta-protocol-proxy) and [Aeraki](https://github.com/aeraki-framework/aeraki)!

# meta-protocol-tencent

Tencent private protocols built on top of [Aeraki MetaProtocol Proxy](https://github.com/aeraki-framework/meta-protocol-proxy)

Supported protocols: 

* trpc(both unary and stream)
* qza 
* videopacket

Supported features:

* Metadata(Can be any headers, even property extracted from message body) based routing
* Weight based routing
* Traffic mirroing
* Local rate limit
* Global rate limit
* Circuit breaker
* Request level metrics

How to build:
https://github.com/aeraki-mesh/meta-protocol-proxy#build-metaprotocol-proxy

Please contact huabingzhao@tencent.com if you want to manage your private protocols in Istio service meshes in a native way.
