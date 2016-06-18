include_directories(
  libKBEClient/client
  libKBEClient/net
  libKBEClient/util
)

set(GAME_LIB_KBECLIENT_SRC

  libKBEClient/client/GameNetClient.cpp
  libKBEClient/client/KAccount.cpp
  libKBEClient/client/KAvatar.cpp
  libKBEClient/net/base_sock.cpp
  libKBEClient/net/net_client.cpp
  libKBEClient/util/tools.cpp
  libKBEClient/KBEApplication.cpp
  libKBEClient/KBEGameSocket.cpp
  libKBEClient/KBundle.cpp
  libKBEClient/KDataTypes.cpp
  libKBEClient/KEntity.cpp
  libKBEClient/KEntitydef.cpp
  libKBEClient/KMailbox.cpp
  libKBEClient/KMemoryStream.cpp
  libKBEClient/KMessage.cpp
  libKBEClient/KNetworkInterface.cpp

)
