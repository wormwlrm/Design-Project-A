#include "Application.h"


Application::Application()
{
	load_user_file(); // 유저 파일 로드
	load_transaction_log_file();// 거래 내역 로드
	load_loan_list_file(); // 대출 리스트 로드
}

Application::~Application()
{
}

void Application::run()
{
	int choice;
	while (1) // 로그인 창
	{
		int tmpId;
		string tmpPassword;

		cout << "┌─────────────────┐" << endl;
		cout << "│┌───────────────┐│" << endl;
		cout << "││≪ BANKING  SYSTEM  PROGRAM ≫││" << endl;
		cout << "│└───────────────┘│" << endl;
		cout << "└─────────────────┘" << endl;
		cout << "───────────────────" << endl;
		cout << "1. 로그인" << endl;
		cout << "2. 로그아웃" << endl;
		cout << "3. 종료" << endl;
		cout << "───────────────────" << endl;
		cout << "-> ";
		cin >> choice;
		
		switch (choice)
		{
		case 1:	
			if (loginedUser != NULL) // 이미 로그인 되어진 상태
			{
				cout << "이미 로그인 된 상태입니다.\n기존에 로그인 된 계정으로 이동합니다." << endl;
				printMenu(); // 기존 LoginedUser의 PrintMenu 호출
				break;
			}
			else // 로그인이 되어있지 않은 상태
			{
				cout << "ID를 입력하세요. -> ";
				cin >> tmpId; 
				if (cin.fail()) // 아이디 입력에서 잘못된 문자 받을 경우 예외 처리
				{
					cout << "Error : 아이디에 잘못된 문자가 입력되었습니다." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					break;
				}
				cout << "Password를 입력하세요. -> ";
				cin >> tmpPassword;
				if (cin.fail()) // 비밀번호 입력에서 잘못된 문자 받을 경우 예외 처리
				{
					cout << "Error : 비밀번호에 잘못된 문자가 입력되었습니다." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					break;
				}
				login(tmpId, tmpPassword);
				break;
			}
		case 2: // 로그아웃 함수 호출
			logout();
			break;
		case 3: // 프로그램 종료
			saveFiles();
			exit(100);
			break;
		default:
			if (cin.fail()) // 잘못된 값 입력 받았을 때 예외 처리
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
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
		cout << "───────────────────" << endl;
		loginedUser->printUserInfo(); // 로그인 된 사용자의 정보 출력
		cout << "───────────────────" << endl;
		cout << "1. 입,출금\n2. 송금\n3. 대출\n4. 대출금 반환\n5. 거래내역 조회\n6. 이전메뉴로\n";
		cout << "-> ";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1: // 입,출금 메뉴 출력
			print_deposit_withdraw_menu();
			break;
		case 2: // 송금 메뉴 출력
			print_send_money_menu();
			break;
		case 3: // 대출 메뉴 출력
			print_loan_menu();
			break;
		case 4: // 상환 메뉴 출력
			print_repayment_menu();
			break;
		case 5: // 거래 내역 출력
			print_logined_user_transanctions();
			break;
		case 6: // 로그인 함수 재출력
			run();
			break;
		default: // 잘못된 값 입력 받았을 때 예외 처리
			if (cin.fail())
			{
				cout << "Error : 올바르지 않은 선택입니다." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
		}
	}	
}

void Application::print_logined_user_transanctions() // 사용자의 최근 5개 거래 내역 출력
{
	cout << "───────────────────" << endl;
	cout << "  출금인       입금인      금액(만 원)" << endl;
	loginedUser->resetCache();
	for (int i = transactionCount - 1; i >= 0; i--) // 캐시 갱신
	{
		if (transactions[i].getFromId() == loginedUser->getId() || transactions[i].getToId() == loginedUser->getId()) 
		{
			loginedUser->setCache(&transactions[i]);
		}
	}
	for (int i = 0; i < loginedUser->getCacheSize(); i++)
	{
		cout << "───────────────────" << endl;
		loginedUser->getTrasCache()[i]->print();
	}
	cout << "───────────────────" << endl;
}

void Application::print_logined_user_loans() // 대출 상환시 출력
{
	int i = 0;
	while (i < MAX)
	{
		if (loginedUser->getId() == loans[i].getUserId()) // 로그인 된 유저와 일치하는 대출 내역을 찾음
		{
			if (loans[i].getAmount() == 0) // 대출금 없을 시 예외 처리
			{
				break;				
			}
			cout << loans[i].getAmount() << "만 원 상환까지 " << loans[i].GetRepayment_Period_Month() << "월 남았습니다." << endl;
			break;
		}
		i++;
	}
}

void Application::print_deposit_withdraw_menu()
{
	int choice;
	cout << "───────────────────" << endl;
	loginedUser->printUserInfo(); // 사용자 정보 출력
	cout << "───────────────────" << endl;
	cout << "1. 입금\n2. 출금\n";
	cout << "───────────────────\n-> ";
	cin >> choice;
	int _amount;

	switch (choice)
	{
	case 1:
		cout << "입금할 금액을 입력해 주세요. : ";
		cin >> _amount;
		deposit(_amount); // 입금 처리
		break;
	case 2:
		cout << "출금할 금액을 입력해 주세요. : ";
		cin >> _amount;
		withdraw(_amount); // 출금 처리
		break;
	default:
		if (cin.fail()) // 잘못된 값 입력 받았을 때 예외 처리
		{
			cout << "Error : 올바르지 않은 선택입니다." << endl;
			cin.clear();
			cin.ignore(256, '\n');
			break;
		}
		break;
	}
}

void Application::print_send_money_menu()
{
	cout << "───────────────────" << endl;
	loginedUser->printUserInfo();
	cout << "───────────────────" << endl;
	int toAccount, toAmount;
	cout << "송금할 사람의 계좌번호를 입력해 주세요. : ";
	cin >> toAccount;
	cout << "송금할 금액을 입력해 주세요. : ";
	cin >> toAmount;
	sendMoney(toAccount, toAmount); // 송금 처리
}

void Application::print_loan_menu()
{
	loginedUser->printUserInfo();
	cout << "───────────────────" << endl;
	int loanAmount, repayPeriod;
	cout << "대출 받을 금액을 입력해 주세요. : ";
	cin >> loanAmount;
	cout << "반환할 기간을 입력해 주세요.(n월) : ";
	cin >> repayPeriod;
	loan_money(loanAmount, repayPeriod); // 대출 처리
}

void Application::print_repayment_menu()
{
	bool loaned = false; // 먼저 대출 내역이 존재하는지 확인
	int i = 0;
	while (i < MAX)
	{
		if (loans[i].getUserId() == loginedUser->getId()) // 등록된 대출 내역이 있는지 loans 배열에 등록된 ID를 검색하여 확인
		{
			if (loans[i].getAmount() > 0)
			{
				loaned = true;
				break;
			}
		}
		i++;
	}
	
	if (loaned == false) // 대출 내역이 존재하지 않는다면 예외 처리
	{
		cout << "Error : 대출 내역이 존재하지 않습니다." << endl;
		return;
	}
	cout << "───────────────────" << endl;

	loginedUser->printUserInfo(); // 대출금이 존재한다면 계속 진행
	if (loginedUser->getBalance() < 0) // 상환 금액이 부족하다면 예외 처리
	{
		cout << "Error : 상환 금액이 부족합니다." << endl;
	}
	cout << "───────────────────" << endl;
	cout << "대출금을 상환을 시작합니다." << endl;
	repayment();
	cout << "───────────────────" << endl;
	print_logined_user_loans();
}

User* Application::login(int user_id, string Password)
{
	int i = 0;
	transaction* temp;

	while (users[i].getId() != NULL)
	{
		if (users[i].getId() == user_id) // 아이디가 일치하는지 확인
		{
			if (users[i].getPW() == Password) // 비밀번호가 일치하는지 확인
			{
				cout << "성공적으로 로그인 되었습니다." << endl;
				loginedUser = &(users[i]); // loginedUser에 현재 유저의 주소값을 저장
				printMenu();
				return &(users[i]);
			}
			else // 비밀번호가 일치하지 않을 경우 예외 처리
			{
				cout << "Error : 비밀번호가 일치하지 않습니다." << endl;
				return NULL;
				break;
			}
		}
		i++;
	}
	cout << "Error : 리스트에 일치하는 ID가 없습니다." << endl; // 아이디가 일치하지 않을 경우 예외 처리
	return NULL;
}

void Application::logout()
{
	if (loginedUser != NULL) 
	{
		loginedUser = NULL;
		cout << "성공적으로 로그아웃 되었습니다." << endl;
	}
	else // 로그인 중인 상태가 아니면 예외 처리
	{
		cout << "Error : 현재 로그인된 상태가 아닙니다." << endl;
	}
}

bool Application::sendMoney(int _toAccount, int _amount)
{
	if (_amount < 0) // 입금 금액이 음수일 때
	{
		cout << "Error : 입금 금액이 올바르지 않습니다." << endl;
		return 0; // 실패 반환
	}

	if (loginedUser->getAccoutNumber() == _toAccount) // 보내고자 하는 사람이 자기 자신일 때
	{
		cout << "Error : 자기 자신에게 송금할 수 없습니다." << endl;
		return 0; // 실패 반환
	}

	if (loginedUser->getBalance() < _amount) // 잔액 부족일 때
	{
		cout << "Error : 잔액이 부족해 송금할 수 없습니다." << endl;
		return 0; // 실패 반환
	}
	
	int i = 0;
	while (i < MAX)
	{
		if (users[i].getAccoutNumber() == _toAccount) // 보내고자 하는 계좌 번호와 일치하는 계좌를 유저 목록에서 찾음
		{
			loginedUser->setBalance(-_amount); // 로그인 된 유저의 잔고를 _amount 만큼 감소시킴 
			users[i].setBalance(+_amount); // i번 째 user의 잔고를 _amount 만큼 증가시킴
			
			transaction* temp = new transaction();
			temp->setTransation(loginedUser->getId(), users[i].getId(), _amount); // 임시 Transaction에 현재 거래 내역을 저장

			if (transactionCount >= 100) // 기존 거래 내역을 한 칸 씩 뒤로 이동
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
			for (int i = transactionCount-1; i>=0; i--) // 거래 내역 갱신
			{
				if (transactions[i].getFromId() == loginedUser->getId() || transactions[i].getToId() == loginedUser->getId()) 
				{
					loginedUser->setCache(&transactions[i]);
				}
			}
			cout << "성공적으로 송금되었습니다." << endl;
			return 1; // 성공 반환
		}
		i++;

		if (i == MAX) // 일치하는 ID를 찾지 못함
		{
			cout << "Error : 송금하고자 하는 ID를 찾지 못했습니다." << endl;
			return 0; // 실패 반환
		}
	}
}

bool Application::deposit(int _amount)
{
	if (_amount < 0) // 입금 금액이 음수일 때
	{
		cout << "Error : 입금 금액이 올바르지 않습니다." << endl;
		return 0;
	}
	
	loginedUser->setBalance(_amount);
	
	transaction* temp = new transaction();
	temp->setTransation(-1, loginedUser->getId(), _amount);
	loginedUser->setCache(temp);

	if (transactionCount >= 100) // 기존 거래 내역을 한 칸 씩 뒤로 이동
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
	for (int i = transactionCount - 1; i >= 0; i--) // 거래 내역 갱신
	{
		if (transactions[i].getFromId() == loginedUser->getId() || transactions[i].getToId() == loginedUser->getId()) 
		{
			loginedUser->setCache(&transactions[i]);
		}
	}

	return 1; // 성공 반환
}

bool Application::withdraw(int _amount)
{
	if (_amount < 0 || _amount > loginedUser->getBalance()) // 출금 금액이 음수이거나, 잔고를 넘어섰을 때 예외 처리
	{
		cout << "Error : 출금 금액이 올바르지 않습니다." << endl;
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

	return 1; // 성공 반환
}

bool Application::loan_money(int _amount, int _repayment_priod_month) // 대출 받은 금액만큼 현재 유저의 잔액을 갱신하고 거래 내역을 추가
{
	if (_amount < 0 || _repayment_priod_month < 0) // 파라미터 값에 잘못된 값이 들어와 있다면 예외 처리
	{
		cout << "Error : 올바르지 않은 금액 또는 상환 기간이 입력되었습니다." << endl;
		return 0; // 실패 반환
	}
	
	int i = 0;
	while(i < MAX) // 등록된 대출 내역이 있는지 loans 배열에 등록된 ID를 검색하여 확인
	{
		if (loans[i].getUserId() == loginedUser->getId()) // 등록된 대출 내역이 있다면 예외 처리
		{
			if(loans[i].getAmount() > 0)
			{
				cout << "Error : 잔여 상환금이 존재하는 사용자입니다." << endl;
				return 0;
			}// 실패 반환
		}
		i++;
	}

	if (_amount > 1000 - (loginedUser->getCreditRating() - 1) * 100 || loginedUser->getCreditRating() == 10) // 신용 등급에 맞는 대출 금액을 선택했는지, 신용 등급이 10은 아닌지 예외 처리
	{
		cout << "Error : 신용 등급이 10이거나, 신용 등급에 맞지 않는 대출 금액을 선택하셨습니다." << endl;
		return 0; // 실패 반환
	}

	
	i = 0;
	while (i < MAX) 
	{
		if (loans[i].getUserId() == loginedUser->getId())  // 현재 로그인 된 사용자의 loans 배열에 접근함
		{
			loans[i].setLoan(loginedUser->getId(), _amount, _repayment_priod_month); // 등록된 대출 내역이 없다면 신규 등록
			loginedUser->setBalance(_amount); // 대출금을 잔고에 추가

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
			
			cout << "대출에 성공하였습니다." << endl;
			
			return 1; // 성공 반환
		}
		i++;
	}

	return 0;
}

bool Application::repayment() // 상환한 금액만큼 현재 유저의 잔액을 갱신하고 거래 내역을 추가
{
	int i = 0;
	while (i < MAX)
	{
		if (loans[i].getUserId() == loginedUser->getId()) // 현재 로그인 된 사용자의 loans 배열에 접근함
		{
			int repay_amount = loans[i].getAmount() / loans[i].GetRepayment_Period_Month(); // 이번에 상환할 금액
			int repay_period = 1; // 상환과 동시에 1개월이 흐름

			if (loginedUser->getBalance() < repay_amount) // 상환금이 현재 잔여금보다 클 경우 예외 처리
			{
				cout << "Error : 대출 상환금이 부족합니다!\n신용 등급이 하락하였습니다." << endl;
				loginedUser->setCreditRating(1);
				return 0; // 실패 반환
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

			if (loans[i].GetRepayment_Period_Month() == 0) // 상환이 모두 끝났을 때
			{
				cout << "상환에 성공하였습니다!\n신용 등급이 상승하였습니다." << endl;
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
	ifstream loadUser("users.txt"); // users.txt 파일을 불러옴
	string line;
	userCount = 0;

	while (getline(loadUser,line))  // loadUser에서 String이 있다면 실행
	{
		istringstream get(line);
		int _Id;
		string _password;
		string _name;
		int _accountNumer;
		int _balance;
		int _creaditRating;
		get >> _Id >> _password >> _name >> _accountNumer >> _balance >> _creaditRating; // 임시 변수에 \t 를 기준으로 대입
		
		users[userCount].setUser(_Id, _password, _name, _accountNumer, _balance, _creaditRating); // users 배열에 저장
		userCount++; 
	}
	loadUser.close();
}

void Application::load_transaction_log_file() 
{
	ifstream loadTransaction("transactions.txt"); // transactions.txt 파일을 불러옴
	string line;

	while (getline(loadTransaction, line)) // loadTransaction에서 String이 있다면 실행
	{
		istringstream get(line);
		int _fromID;
		int _toID;
		int _amount;

		get >> _fromID >> _toID >> _amount; // 임시 변수에 \t 를 기준으로 대입

		transactions[transactionCount].setTransation(_fromID, _toID, _amount);
		for (int i = 0; i < MAX; i++)
		{
			if (users[i].getId() == _fromID || users[i].getId() == _toID)
			{
				users[i].setCache(&transactions[transactionCount]);
			}
		}
		transactionCount++;// transactions 배열에 저장	
	}
	loadTransaction.close();
}

void Application::load_loan_list_file()
{
	ifstream loadLoan("loans.txt"); // loans.txt 파일을 불러옴
	string line;

	while (getline(loadLoan, line)) // loadLoan에서 String이 있다면 실행
	{
		istringstream get(line);
		int _userId;
		int _amount;
		int _repayment_priod_month;

		get >> _userId >> _amount >> _repayment_priod_month; // 임시 변수에 \t 를 기준으로 대입

		loans[loanCount].setLoan(_userId, _amount, _repayment_priod_month);// loans 배열에 저장	
		loanCount++;

	}
	loadLoan.close();
}

void Application::saveFiles()
{
	ofstream saveUser("users.txt");
	ofstream saveTransaction("transactions.txt");
	ofstream saveLoan("loans.txt");

	for (int i = 0; i < MAX; i++) // User 클래스의 정보를 파일로 출력
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

	for (int i = 0; i < MAX*5; i++) // Transaction 클래스의 정보를 파일로 출력
	{
		int _amount = transactions[i].getAmount();
		int _fromId = transactions[i].getFromId();
		int _ToId = transactions[i].getToId();

		saveTransaction << _fromId << "\t" << _ToId << "\t" << _amount << endl;
	}

	for (int i = 0; i < MAX; i++) // loan 클래스의 정보를 파일로 출력
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
