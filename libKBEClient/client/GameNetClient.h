#pragma once

#include "KBEClientcore.h"

#define HEARTBEAT_INTERVAL	15

class GameNetClient: public NetClient
{
public:
	GameNetClient();
	//void handlMessage(Message& message);
	void noticeSocketDisconnect(int len, int sockErr);
	void tick(float dt);

private:
	void handleHeartBeat(float dt);
	void reConnectBtnCallback(void* result, void* bindData);//�������ӷ�����



private:
	float heartBeatTime;
};