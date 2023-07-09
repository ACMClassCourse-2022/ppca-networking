# 按 TLS 域名分流

TLS 协议全称为 Transport Layer Security, 是一个提供加密字节流传输的协议。TLS 在日常生活中的应用很广泛; 例如, HTTP/1.1 的 HTTPS 就是建立在 TLS 协议上的 HTTP/1.1 连接。

在一般的 TLS 握手过程中, 客户端会在 Client Hello 包中明文发送所访问的域名, 称为 Server Name Indication (SNI) 扩展。你可以通过解析 TLS Client Hello 包来获取 SNI 中的域名信息, 从而实现分流。

现在常用的 TLS 协议版本有 TLS/1.2 和 TLS/1.3。它们的握手方式是前向兼容的。

## 参考资料

- [RFC 8446: The Transport Layer Security (TLS) Protocol Version 1.3](https://www.rfc-editor.org/rfc/rfc8446); 重点关注 4.1.2 节
- [RFC 6066: Transport Layer Security (TLS) Extensions: Extension Definitions § 3. Server Name Indication](https://www.rfc-editor.org/rfc/rfc6066#section-3)
