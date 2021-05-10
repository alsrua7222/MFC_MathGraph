// CTest.cpp: 구현 파일
//

#include "pch.h"
#include "Function_1.h"
#include "CTest.h"



// CTest

IMPLEMENT_DYNAMIC(CTest, CWnd)

CTest::CTest()
{

}

CTest::~CTest()
{
}


BEGIN_MESSAGE_MAP(CTest, CWnd)
END_MESSAGE_MAP()



// CTest 메시지 처리기




int CTest::TestText(CString str)
{
	// TODO: 여기에 구현 코드 추가.
	int length = str.GetLength();
	char stack1[4], stack2[4];
	for (int i = 0; i < 4; i++) stack1[i] = stack2[i] = NULL;
	int cnt1, cnt2;
	cnt1 = cnt2 = 1;
	for (int i = 0; i < length; i++) {
		switch (str[i]) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (stack1[0] == 'x') {
				if (stack1[1] != '^') {
					return 1001;
				}
			}
			break;
		case '+':
		case '-':
			if (stack2[cnt2 - 1] == '+' || stack2[cnt2 - 1] == '-') {
				return 1002;
			}
			stack1[0] = stack1[1] = NULL;
			cnt1 = 1;
			stack2[cnt2++] = str[i];
			break;
		case 'x':
		case '^':
			if (stack1[cnt1 - 1] == '^') {
				return 1001;
			}
			stack2[0] = NULL;
			cnt2 = 1;
			stack1[cnt1++] = str[i];
			break;
		default:
			return 1003;
		}
	}
	return 1000;
}

int CTest::CGetDegree(char* str)
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; *str !='\0'; i++) {
		if (*str == '^') {
			return *(str+1) - '0';
		}
		str++;
	}

	return 1; //없으면 1차 계수
}

/*
int CTest::CCut(char* str, int pos, int* expo)
{
	// TODO: 여기에 구현 코드 추가.
	char temp[10];
	int cnt = 1;
	for (int i = 0; *str != '\0'; str++) {
		if (pos == 0) {//첫번째
			for (;;) {
				temp[i++] = *str;
				str++;
				if (*str == 'x') {
					temp[i] = '\0';
					(*expo) = *(str + 2) - '0';

					return atoi(temp);
				}
			}
		}
		else {
			for (;;) {
				temp[i++] = *str;
				str++;
				if (*str == '\0') {
					temp[i] = '\0';
					(*expo) = 0;
					return atoi(temp);
				}
				if (*str == 'x') {
					break;
				}

			}
			str++;
			if (*str == '^') {
				cnt++;
			}
			if (cnt == pos) {
				temp[i] = '\0';
				(*expo) = *(str + 1) - '0';

				return atoi(temp);
			}
			else if (*str != '^') {//x가 있을때 상수 자르기 
				if (*expo == 1) {
					i = 0;
					while (1) {
						temp[i++] = *str;
						str++;
						if (*str == '\0') {
							temp[i] = '\0';
							(*expo) = 0;
							return atoi(temp);
						}
					}
				}
				temp[i] = '\0';
				(*expo) = 1;
				return atoi(temp);
			}
			str++;
			i = 0;       //마지막의 제곱승 
		}
		str++;
	}
	return 0;
}
*/




CString CTest::CErrorCode(int errorcode)
{
	// TODO: 여기에 구현 코드 추가.
	CString str;
	switch (errorcode) {
	case 1000:
		str = _T("처리 완료되었습니다.");
		break;
	case 1001:
		str = _T("'^'가 빠져있거나 두번 적용 되어 있습니다.");
		break;
	case 1002:
		str = _T("부호가 한번 더 썼거나 이상하게 배치되어 있습니다.");
		break;
	case 1003:
		str = _T("이외 문자('*', '/', 'w', 'y' 등)가 배치되어 있습니다.");
		break;
	default:
		break;
	}

	return str;
}


void CTest::toString_MSG(CFunction1Dlg::FuncInfo_Line* info)
{
	// TODO: 여기에 구현 코드 추가.
	CString str;
	for (int i = 0; i < 10; i++) {
		if (info->degree[i] == true) {
			CString coef, expo;
			coef.Format(_T("%d"), info->coef[i]);
			expo.Format(_T("%d"), info->expo[i]);
			str += coef + _T("x^") + expo;
		}
		if (i != 9)str += "+";
	}
	MessageBox(str);
}


bool CTest::TestText_E(CString str)
{
	// TODO: 여기에 구현 코드 추가.
	//(x - x1) ^ 2 / a + (y - y1) ^ 2 / b = 1

	int length = str.GetLength();
	int count = 0;
	for (int i = 0; i < length; i++) {
		switch (count)
		{
		case 0:
		case 10:
			if (str[i] == '(') {
				count++;
				continue;
			}
			else break;
		case 1:
			if (str[i] == 'x') {
				count++;
				continue;
			}
			else break;
		case 2:
		case 12:
			if (str[i] == '+' || str[i] == '-') {
				count++;
				continue;
			}
			else break;
		case 3:
		case 8:
		case 13:
		case 18:
			if (isdigit(str[i])) {
				while (isdigit(str[i + 1]) && str[i + 1] == '.') {
					i++;
				}
				count++;
				continue;
			}
			else break;
		case 4:
		case 14:
			if (str[i] == ')') {
				count++;
				continue;
			}
			else break;
		case 5:
		case 15:
			if (str[i] == '^') {
				count++;
				continue;
			}
			else if (str[i] == '²') {
				count += 2;
			}
			else break;
		case 6:
		case 16:
			if (str[i] == '2') {
				count++;
				continue;
			}
			else break;
		case 7:
		case 17:
			if (str[i] == '/') {
				count++;
				continue;
			}
			else break;
		case 9:
			if (str[i] == '+') {
				count++;
				continue;
			}
			else break;
		case 11:
			if (str[i] == 'y') {
				count++;
				continue;
			}
			else break;
		case 19:
			if (str[i] == '=') {
				count++;
				continue;
			}
			else break;
		case 20:
			if (str[i] == '1') {
				return true;
			}
			else break;
		default:
			break;
		}
	}
	return false;

}
