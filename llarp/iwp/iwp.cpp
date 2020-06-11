#include <iwp/iwp.hpp>
#include <iwp/linklayer.hpp>
#include <memory>
#include <router/abstractrouter.hpp>

namespace llarp
{
  namespace iwp
  {
    LinkLayer_ptr
    NewInboundLink(
        std::shared_ptr<KeyManager> keyManager,
        GetRCFunc getrc,
        LinkMessageHandler h,
        SignBufferFunc sign,
        SessionEstablishedHandler est,
        SessionRenegotiateHandler reneg,
        TimeoutHandler timeout,
        SessionClosedHandler closed,
        PumpDoneHandler pumpDone,
        WorkerFunc_t work)
    {
      return std::make_shared<LinkLayer>(
          keyManager, getrc, h, sign, est, reneg, timeout, closed, pumpDone, work, true);
    }

    LinkLayer_ptr
    NewOutboundLink(
        std::shared_ptr<KeyManager> keyManager,
        GetRCFunc getrc,
        LinkMessageHandler h,
        SignBufferFunc sign,
        SessionEstablishedHandler est,
        SessionRenegotiateHandler reneg,
        TimeoutHandler timeout,
        SessionClosedHandler closed,
        PumpDoneHandler pumpDone,
        WorkerFunc_t work)
    {
      return std::make_shared<LinkLayer>(
          keyManager, getrc, h, sign, est, reneg, timeout, closed, pumpDone, work, false);
    }
  }  // namespace iwp
}  // namespace llarp
