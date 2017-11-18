#include "MailDelivery.h"


MailDelivery::MailDelivery()
{
}


MailDelivery::~MailDelivery()
{
}

int MailDelivery::getTotalDistance(int sourceId, int destinationId) // �Ÿ� ��� �Լ�
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

int MailDelivery::getNextMailCenterId(int currentPos, int destinationId) // ���� ������ ��� �Լ�
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



bool MailDelivery::clientSendMail(User* curUser, Mail* mail) // ���� ���� ���� ��
{
	int index = getMailCenterIdByAddress(((Client*)curUser)->getAddress()); // ���� �α����� ���� ���� ���� �ε����� �޾ƿ�
	pointerOfMailCenters->at(index)->getreceivedMailList()->push_back(mail); // �ش� ���� ������ ���� ���� ��Ͽ� ������ �߰�
	
	return 0;
}

bool MailDelivery::managerSendMail(string cityName) // �Ŵ����� ���� ���� ��
{
	int index = getMailCenterIdByCityName(cityName);  // �Ķ���ͷ� ���� ������ ID (�ε���)
	int localNum = pointerOfMailCenters->at(index)->getlocalMailList()->size(); // ���� ���� �߼۵Ǵ� ���� ī��Ʈ
	int externalNum = pointerOfMailCenters->at(index)->getExternalMailList()->size(); // �ܺη� �߼۵Ǵ� ���� ī��Ʈ
	int sending[12][2] = { 0 ,}; // ����, �ܺη� �߼۵Ǵ� ���� ���ڸ� �ӽ÷� ���� ���� 2���� �迭. ù ��° �迭 �ε����� ���� ID, �ι�° �迭 �ε����� ����/������ ��Ÿ��
	
	if (localNum == 0 && externalNum == 0) // ����� ������ ���� ��� ����ó��
	{
		cout << "Error : ����� ������ �����ϴ�." << endl;
		return 0;
	}
	
	string getName;
	vector<Mail*>* localMailList = pointerOfMailCenters->at(index)->getlocalMailList(); // ���� ���� �߼��ϱ� ���� ���� ����Ʈ�� �޾ƿ�
	for (int i = 0; i < localMailList->size(); i++)
	{
		if (localMailList->at(i)->getMailType() == 0) // ���� ���� �߼��ϴ� ���� ī��Ʈ �߰�
		{
			 sending[index][0]++;
		}
		else // �������� �߼��ϴ� ���� ī��Ʈ �߰�
		{
			 sending[index][1]++;
		}
		getName = localMailList->at(i)->getReceiverId(); // �޴� ��� 
		for (int j = 0; j < pointerOfUsers->size(); j++)
		{
			if (pointerOfUsers->at(j)->getUserType() == 0) // Client���� �˻�
			{
				if (((Client*)pointerOfUsers->at(j))->getName() == getName) // �޴� ����� �����ϸ�
				{
					vector<Mail*>* receivedMailList = pointerOfUsers->at(j)->getReceivedMail(); // �޴� ����� ���� ����
					receivedMailList->push_back(localMailList->at(i));							 // ��Ͽ� �߰�
				}
			}
		}
		localMailList->erase(localMailList->begin() + i); // ������ ����
		i--; // ������ i��° �׸��� �������鼭 i+1��°�� �ڵ����� i��°�� �ǹǷ�
	}
	

	vector<Mail*>* externalMailList = pointerOfMailCenters->at(index)->getExternalMailList(); // �ٸ� �������߱�(�ܺ�)�� �߼��ϱ� ���� ���� ����Ʈ
	for (int i = 0; i < externalMailList->size(); i++)
	{
		int destination = getMailCenterIdByAddress(externalMailList->at(i)->getReceiverAddr()); // ������ ID
		int nextCity = getNextMailCenterId(index, destination); // ���� ���� ID
		if (externalMailList->at(i)->getMailType() == 0) // �ܺη� �߼��ϴ� ���� ī��Ʈ �߰�
		{
			 sending[nextCity][0]++;
		}
		else //�ܺη� �߼��ϴ� ���� ī��Ʈ �߰�
		{
			 sending[nextCity][1]++;
		}		
		pointerOfMailCenters->at(nextCity)->getreceivedMailList()->push_back(externalMailList->at(i)); // �ܺθ���Ʈ�� �ִ� ������ ���� ������ ���� ���� ��Ͽ� �߰�
		externalMailList->erase(externalMailList->begin() + i); // ������ ����
		
		i--; // ������ i��° �׸��� �������鼭 i+1��°�� �ڵ����� i��°�� �ǹǷ�
	}
	
	for (int i = 0; i < 12; i++) // ��� ���
	{
		if (!(sending[i][1] == 0 && sending[i][0] == 0))
		{
			if (i != index) // ���� �ܺη� �߼��� ���
			{
				cout << "������ : " << getCityNameByMailCenterId(i) << endl;
				cout << getCityNameByMailCenterId(i) << " ���� ���߱����� ���� " << sending[i][0] << " ��, ���� " << sending[i][1] << " �� �߼۵Ǿ����ϴ�." << endl << endl;
			}

			if (i == index) // ���� ���η� �߼��� ���
			{
				cout << cityName << " �������߱��� ������ ���� " << endl;
				cout << sending[i][0] << " ��, ���� " << sending[i][1] << " ���� ������ �߼۵Ǿ����ϴ�." << endl << endl;
			}
		}
	}
	return 0;
}
bool MailDelivery::managerReceiveMail(string cityName) // �Ŵ����� ���� ���� ��
{
	int index = getMailCenterIdByCityName(cityName);  // ���� ID �ε���
	MailCenter* curCity = pointerOfMailCenters->at(index); // ���� ����
	vector<Mail*>* receivedMailList = curCity->getreceivedMailList(); // ���� ���� ����Ʈ
	
	if (receivedMailList->size() == 0) // ���� ������ ���� �� ����ó��
	{
		cout << "Error : ������ ������ �����ϴ�." << endl;
		return 0;
	}
	
	cout << "�� " << receivedMailList->size() << "���� ������ ������Դϴ�." << endl; // ���� ���� ���
	int senderId, receiverId;
	for (int i = 0; i < receivedMailList->size(); i++) 
	{
		cout << i + 1 << ". "; // ���� �ε���(1���� ����)
		if (receivedMailList->at(i)->getMailType() == 0) // ����
			cout << "���� ( ������ : ";
		else if (receivedMailList->at(i)->getMailType() == 1) // ����
			cout << "���� ( ������ : ";
		cout << getCityNameByMailCenterId(getMailCenterIdByAddress(receivedMailList->at(i)->getReceiverAddr())) << " ) " << endl; // ������ ���
		senderId = pointerOfMailCenters->at(index)->getId();
		receiverId = getMailCenterIdByAddress(receivedMailList->at(i)->getReceiverAddr());
		
		if (senderId == receiverId) // ���� ���η� �߼��� ��
		{
			cout << "�ش� �������߱��� �����Ͽ����ϴ�." << endl << endl;
		}

		else // ���� �ܺη� �߼��� ��
		{
			int next = getNextMailCenterId(senderId, receiverId);
			cout << "�������� ��۵� �������߱��� " << getCityNameByMailCenterId(next) << "�Դϴ�. " << endl << endl;
		}
	}

	for (int i = 0; i < receivedMailList->size(); i++)
	{
		int destination = getMailCenterIdByAddress(receivedMailList->at(i)->getReceiverAddr()); // ������
		if (destination == index) // �������� ���� ������ ���
		{
			(curCity->getlocalMailList())->push_back(receivedMailList->at(i)); //���� ������ �������� ����Ʈ�� ����
			receivedMailList->erase(receivedMailList->begin() + i); // �׸��� ����
		}
		else
		{
			(curCity->getExternalMailList())->push_back(receivedMailList->at(i)); // ������ ������ ���� ���� ����Ʈ�� ����
			receivedMailList->erase(receivedMailList->begin() + i); // �׸��� ����
		}
		i--; // ������ i��° �׸��� �������鼭 i+1��°�� �ڵ����� i��°�� �ǹǷ�
	}

	cout << "��۵� ���� ���� �غ� �Ϸ�Ǿ����ϴ�." << endl;
	return 0;
}


string MailDelivery::getCityNameByMailCenterId(int id) // ID�� �̿��� ���� �̸��� ��ȯ�ϴ� �Լ�
{
	if (id == 0)
		return "����";
	else if (id == 1)
		return "��õ";
	else if (id == 2)
		return "����";
	else if (id == 3)
		return "����";
	else if (id == 4)
		return "����";
	else if (id == 5)
		return "�뱸";
	else if (id == 6)
		return "����";
	else if (id == 7)
		return "����";
	else if (id == 8)
		return "����";
	else if (id == 9)
		return "���";
	else if (id == 10)
		return "�λ�";
	else if (id == 11)
		return "����";

}

int MailDelivery::getMailCenterIdByCityName(string cityName) //���� �̸��� �̿��� ���̵� ��ȯ�ϴ� �Լ�
{
	int index;
	if (cityName == "����")
		index = 0;
	else if (cityName == "��õ")
		index = 1;
	else if (cityName == "����")
		index = 2;
	else if (cityName == "����")
		index = 3;
	else if (cityName == "����")
		index = 4;
	else if (cityName == "�뱸")
		index = 5;
	else if (cityName == "����")
		index = 6;
	else if (cityName == "����")
		index = 7;
	else if (cityName == "����")
		index = 8;
	else if (cityName == "���")
		index = 9;
	else if (cityName == "�λ�")
		index = 10;
	else if (cityName == "����")
		index = 11;
	return index;
}

int MailDelivery::getMailCenterIdByAddress(string address) // �ּҸ� �̿��� ���� ���̵� ��ȯ�ϴ� �Լ�
{
	int index = 0;
	istringstream sin(address);
	string addr, addr2;
	sin >> addr;
	sin >> addr2;

	if (addr == "����Ư����")
		index = 0;
	else if (addr == "��õ������")
		index = 1;
	else if (addr2 == "���ֽ�")
		index = 2;
	else if (addr2 == "������")
		index = 3;
	else if (addr == "����������")
		index = 4;
	else if (addr == "�뱸������")
		index = 5;
	else if (addr == "���ֱ�����;")
		index = 6;
	else if (addr2 == "������")
		index = 7;
	else if (addr2 == "������")
		index = 8;
	else if (addr == "��걤����")
		index = 9;
	else if (addr == "�λ걤����")
		index = 10;
	else if (addr == "����Ư����ġ��")
		index = 11;

	return index;
}