#define MAX 20

#include "User.h"
#include "loan.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Application
{
public:
	Application(); // 파일 로드 및 변수 초기화
	~Application();
public:
	void run(); // 시작 화면 출력
private:
	void printMenu(); // 기본 메뉴 출력
	void print_logined_user_transanctions(); // 로그인된 유저의 거래 내역 출력
	void print_logined_user_loans(); // 로그인된 유저의 대출 출력
	void print_deposit_withdraw_menu(); // 입,출금 메뉴 출력
	void print_send_money_menu(); // 송금 메뉴 출력
	void print_loan_menu(); // 대출 메뉴 출력
	void print_repayment_menu(); // 상환 메뉴 출력

	User* login(int user_id, string Password); // 사용자 로그인
	void logout(); // 사용자 로그아웃

	bool sendMoney(int _toAccount, int _amount); // 송금
	bool deposit(int _amount); // 입금 
	bool withdraw(int _amount); // 출금 
	bool loan_money(int _amount, int _repayment_priod_month); // 대출
	bool repayment(); // 대출금 반환

	void load_user_file(); // 사용자 파일을 불러옴
	void load_transaction_log_file(); // 거래 내역 파일을 불러옴
	void load_loan_list_file(); // 대출 리스트 파일을 불러옴
	void saveFiles(); // 파일 저장

private:
	User users[MAX];
	int userCount = 0;

	transaction transactions[5 * MAX];
	int transactionCount = 0;

	loan loans[100];
	int loanCount = 0;
	
	User* loginedUser;
};

