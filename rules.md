# 分流规则

在代理客户端中, 我们让所有流量都经过另一台代理服务器。但在有些场景下, 我们希望通过流量的特征使得不同的流量经过不同的服务器, 或者希望某些流量直连:

```
                +----------+
                | Server 2 |
                +----+-----+
                     |
                     ^
                     |
+---------+   +------+-------+   +--------------+   +------------+
| User ->-+---+-> Proxy 1 ->-+---+-> Proxy 2 ->-+---+-> Server 1 |
+---------+   +------+-------+   +--------------+   +------------+
                     |
                     v
                     |
               +-----+------+   +------------+
               | Proxy 3 ->-+---+-> Server 3 |
               +------------+   +------------+
```
