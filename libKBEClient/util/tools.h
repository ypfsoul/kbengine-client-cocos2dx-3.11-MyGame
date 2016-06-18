#ifndef _TOOLS_H_
#define  _TOOLS_H_

#include "cocos2d.h"
#include "KBEClientCoreMacros.h"

NS_GC_BEGIN
// 
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
// #include "iconv.h"
// #endif

//��ȡһ���ļ��ĳ��ȣ�[int]pszFileName���ļ�����[out]size���ļ����ȣ�
void getLocalFileLength(const char* pszFileName, long long* pSize);

float heronsformula(float x1,float y1,float x2,float y2,float x3,float y3);

bool triangleContainPoint(float x1,float y1,float x2,float y2,float x3,float y3,float px,float py);

// #if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
// //�ַ�ת����ʹcocos2d-x��win32ƽ̨֧��������ʾ
// int GBKToUTF8(std::string &gbkStr,const char* toCode,const char* formCode);
// #endif

class tLinkData//����������
{
public:
	std::string showStr;//��ʾ����
	std::string linkStr;//��������
	int value;//һЩֵ
	int startPos;//�����������ִ��п�ʼλ��
	int endPos;//�����������ִ��н���λ��
};
class tColorStrData//��ɫ����
{
public:
	std::string showStr;//��ʾ����
	cocos2d::ccColor3B color;//��ɫֵ
	int startPos;//�����������ִ��п�ʼλ��
	int endPos;//�����������ִ��н���λ��
};

std::vector<tLinkData> getLinkDataFromStr(std::string str, char frontSplit='(', char middleSplit=',', char backSplit=')');//��str���ҳ�link����
tColorStrData getColorStrDataFromStr(std::string str, char frontSplit='[', char middleSplit='#', char backSplit=']');//��str���ҳ���ɫ����

cocos2d::CCRect getRect2(cocos2d::CCNode* pNode);
cocos2d::CCRect getRect(cocos2d::CCNode* pNode);

NS_GC_END

#endif //_TOOLS_H_