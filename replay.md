# HTTP 操作

HTTP 一般是由一次请求和一次响应构成的协议, 没有完全意义上的双向通信。HTTP 协议是无状态 (stateless) 的: 两次 HTTP 请求之间在 HTTP 层的逻辑上是完全分离的。因此, 你可以对 HTTP 请求和对应的响应做捕获/修改/重放操作。

你可以通过 [Firefox devtools 中的网络面板](https://firefox-source-docs.mozilla.org/devtools-user/network_monitor/) 对 HTTP 的捕获、修改、重放建立一个直观的感受: 选中一个 HTTP 请求后点击鼠标右键, 选择「编辑并重发」。(Chrome 和 Edge 的对应功能不是很稳定, 甚至有时候找不到; 因此推荐使用 Firefox devtools 而非 cr/edge devtools。)

你需要支持:

- 实时解析流量中的 (明文) HTTP 请求和响应
- 按照预先写好的规则 (最好是可编程的规则) 实时重写 HTTP 包 (method, headers, body)
- 记录 HTTP 请求和响应
- 对记录的 HTTP 请求进行修改
- 向服务器重新发送记录下来的 HTTP 包

以下功能是加分项:

- 实现 HTTPS 加密协议的以上功能 (需要先实现 [TLS 劫持](tls.md))

此任务大致分为几个部分:

- 解析 HTTP 请求和响应
- 请求、响应的实时修改
- HTTP 会话的记录
- 对记录下的 HTTP 请求进行重放
