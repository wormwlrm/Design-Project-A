#pragma once
#include "Mail.h"
class MailCenter
{
private:
	int id;	//우편집중국 ID
	string cityName;//도시 이름
	int neighborCnt;//인접한 우편집중국 개수
	int* neighborIds;//

	Mail* recievedMailList[10];//받은 우편물 리스트
	Mail* localMailList[10];//내부로 발송될 우편물 리스트
	Mail*** externalMailList;//외부로 발송될 우편물 리스트
public:
	MailCenter();
	~MailCenter();
};

