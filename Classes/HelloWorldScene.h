#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "KAccount.h"
#include "KBEApplication.h"
#include "KBEGameSocket.h"
#include "KBundle.h"
#include "KMessage.h"
#include "cocos2d.h"

void inline testKBE()
{
    KBEGameSocket& game_sock = KBEGameSocket::getInstance();
    std::string s_ip = "192.168.0.102";
    bool c_ok = game_sock.connectionServer(s_ip.c_str(), 48653);
    if (!c_ok)
    {
        printf("not connected!\n");
        MessageBox("not connected", "net");
    }
    else
    {
        printf("connected!\n");
        MessageBox("connected", "net");
    }

    //KMessage::bindmessage();
    KBE_init();
    //send ["Loginapp_importClientMessages"]);
    KBEngineClient::KBundle* bundle = new KBundle();

    KNetworkInterface* network = new KNetworkInterface();

    bundle->newmessage(*KMessage::messages["Loginapp_importClientMessages"]);
    bundle->send(*network);

    //next we should recv huge client methods....


    /*KBEngineClient::Message msg;
	msg.setOpcode(100);
	game_sock.sendMessage(msg);*/
    //TODO works like a clientapp. say hello. send importEntiityDef message.
    //pack1:
    //Message.messages["Loginapp_importClientMessages"] = new Message(5, "importClientMessages", 0, 0, new List<Byte>(), null);
    //bundle.newMessage(Message.messages["Loginapp_importClientMessages"]);
    //bundle.send(networkInterface_);
    //bundle get stream from message.
    //scene->addChild(game_sock ,19999,19999);
}


class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
