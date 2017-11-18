#include "MailDelivery.h"


MailDelivery::MailDelivery()
{
}


MailDelivery::~MailDelivery()
{
}

int MailDelivery::getTotalDistance(int sourceId, int destinationId) // 거리 계산 함수
{
	int dist[N], prev[N], selected[N] = { 0 }, i, m, min, start, d, j;
	int path[N];
	for (i = 0; i< N; i++)
	{
		dist[i] = IN;
		prev[i] = -1;
	}
	start = sourceId;
	selected[start] = 1;
	dist[start] = 0;
	while (selected[destinationId] == 0)
	{
		min = IN;
		m = 0;
		for (i = 0; i< N; i++)
		{
			if (pointerOfRouter[start][i] == 0)
				pointerOfRouter[start][i] = 99;
			d = dist[start] + pointerOfRouter[start][i];
			if (d< dist[i] && selected[i] == 0)
			{
				dist[i] = d;
				prev[i] = start;
			}
			if (min > dist[i] && selected[i] == 0)
			{
				min = dist[i];
				m = i;
			}
		}
		start = m;
		selected[start] = 1;
	}
	start = destinationId;
	j = 0;
	return dist[destinationId];
}

int MailDelivery::getNextMailCenterId(int currentPos, int destinationId) // 다음 목적지 계산 함수
{
	int pathStartPoint = currentPos;
	int dist[N], prev[N], selected[N] = { 0 }, i, m, min, start, d, j;
	int path[N] = { -1, };
	for (i = 0; i< N; i++)
	{
		dist[i] = IN;
		prev[i] = -1;
	}
	start = currentPos;
	selected[start] = 1;
	dist[start] = 0;
	while (selected[destinationId] == 0)
	{
		min = IN;
		m = 0;
		for (i = 0; i< N; i++)
		{
			if (pointerOfRouter[start][i] == 0)
				pointerOfRouter[start][i] = 99;
			d = dist[start] + pointerOfRouter[start][i];
			if (d< dist[i] && selected[i] == 0)
			{
				dist[i] = d;
				prev[i] = start;
			}
			if (min>dist[i] && selected[i] == 0)
			{
				min = dist[i];
				m = i;
			}
		}
		start = m;
		selected[start] = 1;
	}
	start = destinationId;
	j = 0;
	while (start != pathStartPoint)
	{
		path[j++] = start;
		start = prev[start];
	}
	return path[j - 1];
}



bool MailDelivery::clientSendMail(User* curUser, Mail* mail) // 고객이 우편물 보낼 때
{
	int index = getMailCenterIdByAddress(((Client*)curUser)->getAddress()); // 현재 로그인한 고객의 메일 센터 인덱스를 받아옴
	pointerOfMailCenters->at(index)->getreceivedMailList()->push_back(mail); // 해당 메일 센터의 받은 우편물 목록에 우편물을 추가
	
	return 0;
}

bool MailDelivery::managerSendMail(string cityName) // 매니저가 우편물 보낼 때
{
	int index = getMailCenterIdByCityName(cityName);  // 파라미터로 받은 도시의 ID (인덱스)
	int localNum = pointerOfMailCenters->at(index)->getlocalMailList()->size(); // 지역 내로 발송되는 우편물 카운트
	int externalNum = pointerOfMailCenters->at(index)->getExternalMailList()->size(); // 외부로 발송되는 우편물 카운트
	int sending[12][2] = { 0 ,}; // 내부, 외부로 발송되는 우편물 숫자를 임시로 세기 위한 2차원 배열. 첫 번째 배열 인덱스는 도시 ID, 두번째 배열 인덱스는 편지/소포를 나타냄
	
	if (localNum == 0 && externalNum == 0) // 배송할 우편물이 없을 경우 예외처리
	{
		cout << "Error : 배송할 우편물이 없습니다." << endl;
		return 0;
	}
	
	string getName;
	vector<Mail*>* localMailList = pointerOfMailCenters->at(index)->getlocalMailList(); // 지역 내로 발송하기 위한 메일 리스트를 받아옴
	for (int i = 0; i < localMailList->size(); i++)
	{
		if (localMailList->at(i)->getMailType() == 0) // 지역 내로 발송하는 편지 카운트 추가
		{
			 sending[index][0]++;
		}
		else // 지역내로 발송하는 우편물 카운트 추가
		{
			 sending[index][1]++;
		}
		getName = localMailList->at(i)->getReceiverId(); // 받는 사람 
		for (int j = 0; j < pointerOfUsers->size(); j++)
		{
			if (pointerOfUsers->at(j)->getUserType() == 0) // Client에서 검색
			{
				if (((Client*)pointerOfUsers->at(j))->getName() == getName) // 받는 사람이 존재하면
				{
					vector<Mail*>* receivedMailList = pointerOfUsers->at(j)->getReceivedMail(); // 받는 사람의 받은 우편물
					receivedMailList->push_back(localMailList->at(i));							 // 목록에 추가
				}
			}
		}
		localMailList->erase(localMailList->begin() + i); // 보내고 지움
		i--; // 벡터의 i번째 항목이 지워지면서 i+1번째가 자동으로 i번째가 되므로
	}
	

	vector<Mail*>* externalMailList = pointerOfMailCenters->at(index)->getExternalMailList(); // 다른 우편집중국(외부)로 발송하기 위한 메일 리스트
	for (int i = 0; i < externalMailList->size(); i++)
	{
		int destination = getMailCenterIdByAddress(externalMailList->at(i)->getReceiverAddr()); // 목적지 ID
		int nextCity = getNextMailCenterId(index, destination); // 다음 도시 ID
		if (externalMailList->at(i)->getMailType() == 0) // 외부로 발송하는 편지 카운트 추가
		{
			 sending[nextCity][0]++;
		}
		else //외부로 발송하는 우편물 카운트 추가
		{
			 sending[nextCity][1]++;
		}		
		pointerOfMailCenters->at(nextCity)->getreceivedMailList()->push_back(externalMailList->at(i)); // 외부리스트에 있는 우편물을 다음 도시의 받은 우편물 목록에 추가
		externalMailList->erase(externalMailList->begin() + i); // 보내고 지움
		
		i--; // 벡터의 i번째 항목이 지워지면서 i+1번째가 자동으로 i번째가 되므로
	}
	
	for (int i = 0; i < 12; i++) // 결과 출력
	{
		if (!(sending[i][1] == 0 && sending[i][0] == 0))
		{
			if (i != index) // 지역 외부로 발송할 경우
			{
				cout << "목적지 : " << getCityNameByMailCenterId(i) << endl;
				cout << getCityNameByMailCenterId(i) << " 우편 집중국으로 편지 " << sending[i][0] << " 건, 소포 " << sending[i][1] << " 건 발송되었습니다." << endl << endl;
			}

			if (i == index) // 지역 내부로 발송할 경우
			{
				cout << cityName << " 우편집중국에 도착한 우편물 " << endl;
				cout << sending[i][0] << " 건, 소포 " << sending[i][1] << " 건이 고객에게 발송되었습니다." << endl << endl;
			}
		}
	}
	return 0;
}
bool MailDelivery::managerReceiveMail(string cityName) // 매니저가 우편물 받을 때
{
	int index = getMailCenterIdByCityName(cityName);  // 도시 ID 인덱스
	MailCenter* curCity = pointerOfMailCenters->at(index); // 현재 도시
	vector<Mail*>* receivedMailList = curCity->getreceivedMailList(); // 받은 우편물 리스트
	
	if (receivedMailList->size() == 0) // 받은 우편물이 없을 때 예외처리
	{
		cout << "Error : 도착한 우편물이 없습니다." << endl;
		return 0;
	}
	
	cout << "총 " << receivedMailList->size() << "개의 우편물이 대기중입니다." << endl; // 우편물 갯수 출력
	int senderId, receiverId;
	for (int i = 0; i < receivedMailList->size(); i++) 
	{
		cout << i + 1 << ". "; // 우편물 인덱스(1부터 시작)
		if (receivedMailList->at(i)->getMailType() == 0) // 편지
			cout << "편지 ( 목적지 : ";
		else if (receivedMailList->at(i)->getMailType() == 1) // 소포
			cout << "소포 ( 목적지 : ";
		cout << getCityNameByMailCenterId(getMailCenterIdByAddress(receivedMailList->at(i)->getReceiverAddr())) << " ) " << endl; // 목적지 출력
		senderId = pointerOfMailCenters->at(index)->getId();
		receiverId = getMailCenterIdByAddress(receivedMailList->at(i)->getReceiverAddr());
		
		if (senderId == receiverId) // 지역 내부로 발송할 시
		{
			cout << "해당 우편집중국에 도착하였습니다." << endl << endl;
		}

		else // 지역 외부로 발송할 시
		{
			int next = getNextMailCenterId(senderId, receiverId);
			cout << "다음으로 배송될 우편집중국은 " << getCityNameByMailCenterId(next) << "입니다. " << endl << endl;
		}
	}

	for (int i = 0; i < receivedMailList->size(); i++)
	{
		int destination = getMailCenterIdByAddress(receivedMailList->at(i)->getReceiverAddr()); // 목적지
		if (destination == index) // 목적지가 현재 도시일 경우
		{
			(curCity->getlocalMailList())->push_back(receivedMailList->at(i)); //현재 도시의 지역내부 리스트로 보냄
			receivedMailList->erase(receivedMailList->begin() + i); // 그리고 지움
		}
		else
		{
			(curCity->getExternalMailList())->push_back(receivedMailList->at(i)); // 목적지 도시의 받은 우편물 리스트로 보냄
			receivedMailList->erase(receivedMailList->begin() + i); // 그리고 지움
		}
		i--; // 벡터의 i번째 항목이 지워지면서 i+1번째가 자동으로 i번째가 되므로
	}

	cout << "배송된 우편물 전송 준비가 완료되었습니다." << endl;
	return 0;
}


string MailDelivery::getCityNameByMailCenterId(int id) // ID를 이용해 도시 이름을 반환하는 함수
{
	if (id == 0)
		return "서울";
	else if (id == 1)
		return "인천";
	else if (id == 2)
		return "원주";
	else if (id == 3)
		return "강릉";
	else if (id == 4)
		return "대전";
	else if (id == 5)
		return "대구";
	else if (id == 6)
		return "광주";
	else if (id == 7)
		return "목포";
	else if (id == 8)
		return "여수";
	else if (id == 9)
		return "울산";
	else if (id == 10)
		return "부산";
	else if (id == 11)
		return "제주";

}

int MailDelivery::getMailCenterIdByCityName(string cityName) //도시 이름을 이용해 아이디를 반환하는 함수
{
	int index;
	if (cityName == "서울")
		index = 0;
	else if (cityName == "인천")
		index = 1;
	else if (cityName == "원주")
		index = 2;
	else if (cityName == "강릉")
		index = 3;
	else if (cityName == "대전")
		index = 4;
	else if (cityName == "대구")
		index = 5;
	else if (cityName == "광주")
		index = 6;
	else if (cityName == "목포")
		index = 7;
	else if (cityName == "여수")
		index = 8;
	else if (cityName == "울산")
		index = 9;
	else if (cityName == "부산")
		index = 10;
	else if (cityName == "제주")
		index = 11;
	return index;
}

int MailDelivery::getMailCenterIdByAddress(string address) // 주소를 이용해 도시 아이디를 반환하는 함수
{
	int index = 0;
	istringstream sin(address);
	string addr, addr2;
	sin >> addr;
	sin >> addr2;

	if (addr == "서울특별시")
		index = 0;
	else if (addr == "인천광역시")
		index = 1;
	else if (addr2 == "원주시")
		index = 2;
	else if (addr2 == "강릉시")
		index = 3;
	else if (addr == "대전광역시")
		index = 4;
	else if (addr == "대구광역시")
		index = 5;
	else if (addr == "광주광역시;")
		index = 6;
	else if (addr2 == "목포시")
		index = 7;
	else if (addr2 == "여수시")
		index = 8;
	else if (addr == "울산광역시")
		index = 9;
	else if (addr == "부산광역시")
		index = 10;
	else if (addr == "제주특별자치도")
		index = 11;

	return index;
}