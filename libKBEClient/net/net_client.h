#pragma once

#include "base_sock.h"
//#include "message.h"
#include "cocos2d.h"
#include "../util/basic_types.h"

NS_GC_BEGIN

class NetClient: public cocos2d::CCObject
{
public:
	NetClient();
	virtual ~NetClient();
	virtual bool connect(const char* host, uint16 port);//����socket
	virtual void close();//�ر�socket
	virtual void tick(float dt);//����
	//virtual void handlMessage(Message& message)=0;//������Ϣ
	//virtual void sendMessage(Message& message);//������Ϣ
	virtual void sendData(char* data,int size);
	virtual void noticeSocketDisconnect(int len, int sockErr);//֪ͨsocket�Ͽ�����
	void setMessageLengthLenC2S(size_t len);
	void setMessageOpcodeLenC2S(size_t len);
	void setMessageLengthLenS2C(size_t len);
	void setMessageOpcodeLenS2C(size_t len);
protected:
	BaseSock* sock;
	bool isConnect;
private:
	//ByteBuffer buffer;
	size_t messageLengthLenC2S;//�ͻ����ļ�����ֵ��С
	size_t messageOpcodeLenC2S;//�ͻ�����Ϣͷ��С
	size_t messageLengthLenS2C;//�ͻ����ļ�����ֵ��С
	size_t messageOpcodeLenS2C;//�ͻ�����Ϣͷ��С
};

NS_GC_END
