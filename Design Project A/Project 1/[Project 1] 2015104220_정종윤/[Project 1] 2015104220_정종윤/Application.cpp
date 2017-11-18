#include "Application.h"


Application::Application()
{
	load_user_file(); // ���� ���� �ε�
	load_transaction_log_file();// �ŷ� ���� �ε�
	load_loan_list_file(); // ���� ����Ʈ �ε�
}

Application::~Application()
{
}

void Application::run()
{
	int choice;
	while (1) // �α��� â
	{
		int tmpId;
		string tmpPassword;

		cout << "��������������������������������������" << endl;
		cout << "��������������������������������������" << endl;
		cout << "������ BANKING  SYSTEM  PROGRAM ����" << endl;
		cout << "��������������������������������������" << endl;
		cout << "��������������������������������������" << endl;
		cout << "��������������������������������������" << endl;
		cout << "1. �α���" << endl;
		cout << "2. �α׾ƿ�" << endl;
		cout << "3. ����" << endl;
		cout << "��������������������������������������" << endl;
		cout << "-> ";
		cin >> choice;
		
		switch (choice)
		{
		case 1:	
			if (loginedUser != NULL) // �̹� �α��� �Ǿ��� ����
			{
				cout << "�̹� �α��� �� �����Դϴ�.\n������ �α��� �� �������� �̵��մϴ�." << endl;
				printMenu(); // ���� LoginedUser�� PrintMenu ȣ��
				break;
			}
			else // �α����� �Ǿ����� ���� ����
			{
				cout << "ID�� �Է��ϼ���. -> ";
				cin >> tmpId; 
				if (cin.fail()) // ���̵� �Է¿��� �߸��� ���� ���� ��� ���� ó��
				{
					cout << "Error : ���̵� �߸��� ���ڰ� �ԷµǾ����ϴ�." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					break;
				}
				cout << "Password�� �Է��ϼ���. -> ";
				cin >> tmpPassword;
				if (cin.fail()) // ��й�ȣ �Է¿��� �߸��� ���� ���� ��� ���� ó��
				{
					cout << "Error : ��й�ȣ�� �߸��� ���ڰ� �ԷµǾ����ϴ�." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					break;
				}
				login(tmpId, tmpPassword);
				break;
			}
		case 2: // �α׾ƿ� �Լ� ȣ��
			logout();
			break;
		case 3: // ���α׷� ����
			saveFiles();
			exit(100);
			break;
		default:
			if (cin.fail()) // �߸��� �� �Է� �޾��� �� ���� ó��
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
			break;
		}
	}
}

void Application::printMenu()
{
	while (1)
	{
		cout << "��������������������������������������" << endl;
		loginedUser->printUserInfo(); // �α��� �� ������� ���� ���
		cout << "��������������������������������������" << endl;
		cout << "1. ��,���\n2. �۱�\n3. ����\n4. ����� ��ȯ\n5. �ŷ����� ��ȸ\n6. �����޴���\n";
		cout << "-> ";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1: // ��,��� �޴� ���
			print_deposit_withdraw_menu();
			break;
		case 2: // �۱� �޴� ���
			print_send_money_menu();
			break;
		case 3: // ���� �޴� ���
			print_loan_menu();
			break;
		case 4: // ��ȯ �޴� ���
			print_repayment_menu();
			break;
		case 5: // �ŷ� ���� ���
			print_logined_user_transanctions();
			break;
		case 6: // �α��� �Լ� �����
			run();
			break;
		default: // �߸��� �� �Է� �޾��� �� ���� ó��
			if (cin.fail())
			{
				cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
		}
	}	
}

void Application::print_logined_user_transanctions() // ������� �ֱ� 5�� �ŷ� ���� ���
{
	cout << "��������������������������������������" << endl;
	cout << "  �����       �Ա���      �ݾ�(�� ��)" << endl;
	loginedUser->resetCache();
	for (int i = transactionCount - 1; i >= 0; i--) // ĳ�� ����
	{
		if (transactions[i].getFromId() == loginedUser->getId() || transactions[i].getToId() == loginedUser->getId()) 
		{
			loginedUser->setCache(&transactions[i]);
		}
	}
	for (int i = 0; i < loginedUser->getCacheSize(); i++)
	{
		cout << "��������������������������������������" << endl;
		loginedUser->getTrasCache()[i]->print();
	}
	cout << "��������������������������������������" << endl;
}

void Application::print_logined_user_loans() // ���� ��ȯ�� ���
{
	int i = 0;
	while (i < MAX)
	{
		if (loginedUser->getId() == loans[i].getUserId()) // �α��� �� ������ ��ġ�ϴ� ���� ������ ã��
		{
			if (loans[i].getAmount() == 0) // ����� ���� �� ���� ó��
			{
				break;				
			}
			cout << loans[i].getAmount() << "�� �� ��ȯ���� " << loans[i].GetRepayment_Period_Month() << "�� ���ҽ��ϴ�." << endl;
			break;
		}
		i++;
	}
}

void Application::print_deposit_withdraw_menu()
{
	int choice;
	cout << "��������������������������������������" << endl;
	loginedUser->printUserInfo(); // ����� ���� ���
	cout << "��������������������������������������" << endl;
	cout << "1. �Ա�\n2. ���\n";
	cout << "��������������������������������������\n-> ";
	cin >> choice;
	int _amount;

	switch (choice)
	{
	case 1:
		cout << "�Ա��� �ݾ��� �Է��� �ּ���. : ";
		cin >> _amount;
		deposit(_amount); // �Ա� ó��
		break;
	case 2:
		cout << "����� �ݾ��� �Է��� �ּ���. : ";
		cin >> _amount;
		withdraw(_amount); // ��� ó��
		break;
	default:
		if (cin.fail()) // �߸��� �� �Է� �޾��� �� ���� ó��
		{
			cout << "Error : �ùٸ��� ���� �����Դϴ�." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			break;
		}
		break;
	}
}

void Application::print_send_money_menu()
{
	cout << "��������������������������������������" << endl;
	loginedUser->printUserInfo();
	cout << "��������������������������������������" << endl;
	int toAccount, toAmount;
	cout << "�۱��� ����� ���¹�ȣ�� �Է��� �ּ���. : ";
	cin >> toAccount;
	cout << "�۱��� �ݾ��� �Է��� �ּ���. : ";
	cin >> toAmount;
	sendMoney(toAccount, toAmount); // �۱� ó��
}

void Application::print_loan_menu()
{
	loginedUser->printUserInfo();
	cout << "��������������������������������������" << endl;
	int loanAmount, repayPeriod;
	cout << "���� ���� �ݾ��� �Է��� �ּ���. : ";
	cin >> loanAmount;
	cout << "��ȯ�� �Ⱓ�� �Է��� �ּ���.(n��) : ";
	cin >> repayPeriod;
	loan_money(loanAmount, repayPeriod); // ���� ó��
}

void Application::print_repayment_menu()
{
	bool loaned = false; // ���� ���� ������ �����ϴ��� Ȯ��
	int i = 0;
	while (i < MAX)
	{
		if (loans[i].getUserId() == loginedUser->getId()) // ��ϵ� ���� ������ �ִ��� loans �迭�� ��ϵ� ID�� �˻��Ͽ� Ȯ��
		{
			if (loans[i].getAmount() > 0)
			{
				loaned = true;
				break;
			}
		}
		i++;
	}
	
	if (loaned == false) // ���� ������ �������� �ʴ´ٸ� ���� ó��
	{
		cout << "Error : ���� ������ �������� �ʽ��ϴ�." << endl;
		return;
	}
	cout << "��������������������������������������" << endl;

	loginedUser->printUserInfo(); // ������� �����Ѵٸ� ��� ����
	if (loginedUser->getBalance() < 0) // ��ȯ �ݾ��� �����ϴٸ� ���� ó��
	{
		cout << "Error : ��ȯ �ݾ��� �����մϴ�." << endl;
	}
	cout << "��������������������������������������" << endl;
	cout << "������� ��ȯ�� �����մϴ�." << endl;
	repayment();
	cout << "��������������������������������������" << endl;
	print_logined_user_loans();
}

User* Application::login(int user_id, string Password)
{
	int i = 0;
	transaction* temp;

	while (users[i].getId() != NULL)
	{
		if (users[i].getId() == user_id) // ���̵� ��ġ�ϴ��� Ȯ��
		{
			if (users[i].getPW() == Password) // ��й�ȣ�� ��ġ�ϴ��� Ȯ��
			{
				cout << "���������� �α��� �Ǿ����ϴ�." << endl;
				loginedUser = &(users[i]); // loginedUser�� ���� ������ �ּҰ��� ����
				printMenu();
				return &(users[i]);
			}
			else // ��й�ȣ�� ��ġ���� ���� ��� ���� ó��
			{
				cout << "Error : ��й�ȣ�� ��ġ���� �ʽ��ϴ�." << endl;
				return NULL;
				break;
			}
		}
		i++;
	}
	cout << "Error : ����Ʈ�� ��ġ�ϴ� ID�� �����ϴ�." << endl; // ���̵� ��ġ���� ���� ��� ���� ó��
	return NULL;
}

void Application::logout()
{
	if (loginedUser != NULL) 
	{
		loginedUser = NULL;
		cout << "���������� �α׾ƿ� �Ǿ����ϴ�." << endl;
	}
	else // �α��� ���� ���°� �ƴϸ� ���� ó��
	{
		cout << "Error : ���� �α��ε� ���°� �ƴմϴ�." << endl;
	}
}

bool Application::sendMoney(int _toAccount, int _amount)
{
	if (_amount < 0) // �Ա� �ݾ��� ������ ��
	{
		cout << "Error : �Ա� �ݾ��� �ùٸ��� �ʽ��ϴ�." << endl;
		return 0; // ���� ��ȯ
	}

	if (loginedUser->getAccoutNumber() == _toAccount) // �������� �ϴ� ����� �ڱ� �ڽ��� ��
	{
		cout << "Error : �ڱ� �ڽſ��� �۱��� �� �����ϴ�." << endl;
		return 0; // ���� ��ȯ
	}

	if (loginedUser->getBalance() < _amount) // �ܾ� ������ ��
	{
		cout << "Error : �ܾ��� ������ �۱��� �� �����ϴ�." << endl;
		return 0; // ���� ��ȯ
	}
	
	int i = 0;
	while (i < MAX)
	{
		if (users[i].getAccoutNumber() == _toAccount) // �������� �ϴ� ���� ��ȣ�� ��ġ�ϴ� ���¸� ���� ��Ͽ��� ã��
		{
			loginedUser->setBalance(-_amount); // �α��� �� ������ �ܰ� _amount ��ŭ ���ҽ�Ŵ 
			users[i].setBalance(+_amount); // i�� ° user�� �ܰ� _amount ��ŭ ������Ŵ
			
			transaction* temp = new transaction();
			temp->setTransation(loginedUser->getId(), users[i].getId(), _amount); // �ӽ� Transaction�� ���� �ŷ� ������ ����

			if (transactionCount >= 100) // ���� �ŷ� ������ �� ĭ �� �ڷ� �̵�
			{
				for (int i = 99; i > 0; i--)
				{
					transactions[i] = transactions[i - 1];
				}
				transactions[0].setTransation(loginedUser->getId(), users[i].getId(), _amount);
			}
			else
			{
				for (int i = transactionCount; i > 0; i--)
				{
					transactions[i] = transactions[i - 1];
				}
				transactions[0].setTransation(loginedUser->getId(), users[i].getId(), _amount);
				transactionCount++;
			}
			loginedUser->resetCache();
			for (int i = transactionCount-1; i>=0; i--) // �ŷ� ���� ����
			{
				if (transactions[i].getFromId() == loginedUser->getId() || transactions[i].getToId() == loginedUser->getId()) 
				{
					loginedUser->setCache(&transactions[i]);
				}
			}
			cout << "���������� �۱ݵǾ����ϴ�." << endl;
			return 1; // ���� ��ȯ
		}
		i++;

		if (i == MAX) // ��ġ�ϴ� ID�� ã�� ����
		{
			cout << "Error : �۱��ϰ��� �ϴ� ID�� ã�� ���߽��ϴ�." << endl;
			return 0; // ���� ��ȯ
		}
	}
}

bool Application::deposit(int _amount)
{
	if (_amount < 0) // �Ա� �ݾ��� ������ ��
	{
		cout << "Error : �Ա� �ݾ��� �ùٸ��� �ʽ��ϴ�." << endl;
		return 0;
	}
	
	loginedUser->setBalance(_amount);
	
	transaction* temp = new transaction();
	temp->setTransation(-1, loginedUser->getId(), _amount);
	loginedUser->setCache(temp);

	if (transactionCount >= 100) // ���� �ŷ� ������ �� ĭ �� �ڷ� �̵�
	{
		for (int i = 99; i > 0 ; i--)
		{
			transactions[i] = transactions[i - 1];
		}
		transactions[0].setTransation(-1, loginedUser->getId(), _amount);
	}
	else
	{
		for (int i = transactionCount; i > 0; i--)
		{
			transactions[i] = transactions[i - 1];
		}
		transactions[0].setTransation(-1, loginedUser->getId(), _amount);
		transactionCount++;
	}

	loginedUser->resetCache();
	for (int i = transactionCount - 1; i >= 0; i--) // �ŷ� ���� ����
	{
		if (transactions[i].getFromId() == loginedUser->getId() || transactions[i].getToId() == loginedUser->getId()) 
		{
			loginedUser->setCache(&transactions[i]);
		}
	}

	return 1; // ���� ��ȯ
}

bool Application::withdraw(int _amount)
{
	if (_amount < 0 || _amount > loginedUser->getBalance()) // ��� �ݾ��� �����̰ų�, �ܰ� �Ѿ�� �� ���� ó��
	{
		cout << "Error : ��� �ݾ��� �ùٸ��� �ʽ��ϴ�." << endl;
		return 0;
	}

	loginedUser->setBalance(-_amount);
	
	transaction* temp = new transaction();
	temp->setTransation(loginedUser->getId(), -1, _amount);
	loginedUser->setCache(temp);

	if (transactionCount >= 100)
	{
		for (int i = 99; i > 0; i--)
		{
			transactions[i] = transactions[i - 1];
		}
		transactions[0].setTransation(loginedUser->getId(),-1, _amount);

	}
	else
	{
		for (int i = transactionCount; i > 0; i--)
		{
			transactions[i] = transactions[i - 1];
		}
		transactions[0].setTransation(loginedUser->getId(), -1, _amount);
		transactionCount++;
	}

	loginedUser->resetCache();
	for (int i = transactionCount - 1; i >= 0; i--)
	{
		if (transactions[i].getFromId() == loginedUser->getId() || transactions[i].getToId() == loginedUser->getId()) {
			loginedUser->setCache(&transactions[i]);
		}
	}

	return 1; // ���� ��ȯ
}

bool Application::loan_money(int _amount, int _repayment_priod_month) // ���� ���� �ݾ׸�ŭ ���� ������ �ܾ��� �����ϰ� �ŷ� ������ �߰�
{
	if (_amount < 0 || _repayment_priod_month < 0) // �Ķ���� ���� �߸��� ���� ���� �ִٸ� ���� ó��
	{
		cout << "Error : �ùٸ��� ���� �ݾ� �Ǵ� ��ȯ �Ⱓ�� �ԷµǾ����ϴ�." << endl;
		return 0; // ���� ��ȯ
	}
	
	int i = 0;
	while(i < MAX) // ��ϵ� ���� ������ �ִ��� loans �迭�� ��ϵ� ID�� �˻��Ͽ� Ȯ��
	{
		if (loans[i].getUserId() == loginedUser->getId()) // ��ϵ� ���� ������ �ִٸ� ���� ó��
		{
			if(loans[i].getAmount() > 0)
			{
				cout << "Error : �ܿ� ��ȯ���� �����ϴ� ������Դϴ�." << endl;
				return 0;
			}// ���� ��ȯ
		}
		i++;
	}

	if (_amount > 1000 - (loginedUser->getCreditRating() - 1) * 100 || loginedUser->getCreditRating() == 10) // �ſ� ��޿� �´� ���� �ݾ��� �����ߴ���, �ſ� ����� 10�� �ƴ��� ���� ó��
	{
		cout << "Error : �ſ� ����� 10�̰ų�, �ſ� ��޿� ���� �ʴ� ���� �ݾ��� �����ϼ̽��ϴ�." << endl;
		return 0; // ���� ��ȯ
	}

	
	i = 0;
	while (i < MAX) 
	{
		if (loans[i].getUserId() == loginedUser->getId())  // ���� �α��� �� ������� loans �迭�� ������
		{
			loans[i].setLoan(loginedUser->getId(), _amount, _repayment_priod_month); // ��ϵ� ���� ������ ���ٸ� �ű� ���
			loginedUser->setBalance(_amount); // ������� �ܰ� �߰�

			transaction* temp = new transaction();
			temp->setTransation(-1, loginedUser->getId(), _amount);
			loginedUser->setCache(temp);

			if (transactionCount >= 100)
			{
				for (int j = 99; j > 0; j--)
				{
					transactions[j] = transactions[j - 1];
				}
				transactions[0].setTransation(-1, loginedUser->getId(), _amount);
			}

			else
			{
				for (int j = transactionCount; j > 0; j--)
				{
					transactions[j] = transactions[j - 1];
				}
				transactions[0].setTransation(-1, loginedUser->getId(), _amount);
				transactionCount++;
			}

			loginedUser->resetCache();
			for (int i = transactionCount - 1; i >= 0; i--)
			{
				if (transactions[i].getFromId() == loginedUser->getId() || transactions[i].getToId() == loginedUser->getId()) {
					loginedUser->setCache(&transactions[i]);
				}
			}
			
			cout << "���⿡ �����Ͽ����ϴ�." << endl;
			
			return 1; // ���� ��ȯ
		}
		i++;
	}

	return 0;
}

bool Application::repayment() // ��ȯ�� �ݾ׸�ŭ ���� ������ �ܾ��� �����ϰ� �ŷ� ������ �߰�
{
	int i = 0;
	while (i < MAX)
	{
		if (loans[i].getUserId() == loginedUser->getId()) // ���� �α��� �� ������� loans �迭�� ������
		{
			int repay_amount = loans[i].getAmount() / loans[i].GetRepayment_Period_Month(); // �̹��� ��ȯ�� �ݾ�
			int repay_period = 1; // ��ȯ�� ���ÿ� 1������ �帧

			if (loginedUser->getBalance() < repay_amount) // ��ȯ���� ���� �ܿ��ݺ��� Ŭ ��� ���� ó��
			{
				cout << "Error : ���� ��ȯ���� �����մϴ�!\n�ſ� ����� �϶��Ͽ����ϴ�." << endl;
				loginedUser->setCreditRating(1);
				return 0; // ���� ��ȯ
			}

			loans[i].setAmount(repay_amount);
			loans[i].setRepayment_Period_Month(repay_period);
			loginedUser->setBalance(-repay_amount);

			transaction* temp = new transaction();
			temp->setTransation(loginedUser->getId(), -1, repay_amount);
			loginedUser->setCache(temp);

			if (transactionCount >= 100)
			{
				for (int i = 99; i > 0; i--)
				{
					transactions[i] = transactions[i - 1];
				}
				transactions[0].setTransation(loginedUser->getId(), -1, repay_amount);
			}
			else
			{
				for (int i = transactionCount; i > 0; i--)
				{
					transactions[i] = transactions[i - 1];
				}
				transactions[0].setTransation(loginedUser->getId(), -1, repay_amount);
				transactionCount++;
			}

			if (loans[i].GetRepayment_Period_Month() == 0) // ��ȯ�� ��� ������ ��
			{
				cout << "��ȯ�� �����Ͽ����ϴ�!\n�ſ� ����� ����Ͽ����ϴ�." << endl;
				loginedUser->setCreditRating(-1);
			}

			loginedUser->resetCache();
			for (int i = transactionCount - 1; i >= 0; i--)
			{
				if (transactions[i].getFromId() == loginedUser->getId() || transactions[i].getToId() == loginedUser->getId()) 
				{
					loginedUser->setCache(&transactions[i]);
				}
			}

			return 1;
		}
		i++;
	}
	return 0;
}


void Application::load_user_file()
{
	ifstream loadUser("users.txt"); // users.txt ������ �ҷ���
	string line;
	userCount = 0;

	while (getline(loadUser,line))  // loadUser���� String�� �ִٸ� ����
	{
		istringstream get(line);
		int _Id;
		string _password;
		string _name;
		int _accountNumer;
		int _balance;
		int _creaditRating;
		get >> _Id >> _password >> _name >> _accountNumer >> _balance >> _creaditRating; // �ӽ� ������ \t �� �������� ����
		
		users[userCount].setUser(_Id, _password, _name, _accountNumer, _balance, _creaditRating); // users �迭�� ����
		userCount++; 
	}
	loadUser.close();
}

void Application::load_transaction_log_file() 
{
	ifstream loadTransaction("transactions.txt"); // transactions.txt ������ �ҷ���
	string line;

	while (getline(loadTransaction, line)) // loadTransaction���� String�� �ִٸ� ����
	{
		istringstream get(line);
		int _fromID;
		int _toID;
		int _amount;

		get >> _fromID >> _toID >> _amount; // �ӽ� ������ \t �� �������� ����

		transactions[transactionCount].setTransation(_fromID, _toID, _amount);
		for (int i = 0; i < MAX; i++)
		{
			if (users[i].getId() == _fromID || users[i].getId() == _toID)
			{
				users[i].setCache(&transactions[transactionCount]);
			}
		}
		transactionCount++;// transactions �迭�� ����	
	}
	loadTransaction.close();
}

void Application::load_loan_list_file()
{
	ifstream loadLoan("loans.txt"); // loans.txt ������ �ҷ���
	string line;

	while (getline(loadLoan, line)) // loadLoan���� String�� �ִٸ� ����
	{
		istringstream get(line);
		int _userId;
		int _amount;
		int _repayment_priod_month;

		get >> _userId >> _amount >> _repayment_priod_month; // �ӽ� ������ \t �� �������� ����

		loans[loanCount].setLoan(_userId, _amount, _repayment_priod_month);// loans �迭�� ����	
		loanCount++;

	}
	loadLoan.close();
}

void Application::saveFiles()
{
	ofstream saveUser("users.txt");
	ofstream saveTransaction("transactions.txt");
	ofstream saveLoan("loans.txt");

	for (int i = 0; i < MAX; i++) // User Ŭ������ ������ ���Ϸ� ���
	{
		int _Id = users[i].getId();
		string _password = users[i].getPW();
		string _name = users[i].getName();
		int _accountNumer = users[i].getAccoutNumber();
		int _balance = users[i].getBalance();
		int _creaditRating = users[i].getCreditRating();

		saveUser << _Id << "\t" << _password << "\t" << _name << "\t" << _accountNumer << "\t"
			<< _balance << "\t" << _creaditRating << endl;
	}

	for (int i = 0; i < MAX*5; i++) // Transaction Ŭ������ ������ ���Ϸ� ���
	{
		int _amount = transactions[i].getAmount();
		int _fromId = transactions[i].getFromId();
		int _ToId = transactions[i].getToId();

		saveTransaction << _fromId << "\t" << _ToId << "\t" << _amount << endl;
	}

	for (int i = 0; i < MAX; i++) // loan Ŭ������ ������ ���Ϸ� ���
	{
		int _userId = loans[i].getUserId();
		int _amount = loans[i].getAmount();
		int _repayment_period_month = loans[i].GetRepayment_Period_Month();

		saveLoan << i + 1 << "\t" << _amount << "\t" << _repayment_period_month << endl;
	}
	
	saveUser.close();
	saveTransaction.close();
	saveLoan.close();
}
