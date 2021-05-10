#include "pch.h"
#include "CFunctionProc.h"

CFunctionProc::CFunctionProc() {
	
}
CFunctionProc::~CFunctionProc() {
	
}



void CFunctionProc::SketchToData_L(double x1, double y1, double x2, double y2, FuncInfo_Line *data)
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; i < INDEX; i++) {
		data->degree[i] = false;
		data->coef[i] = 0.0;
		data->expo[i] = 0;
	}

	double a, c, m;
	// y = -m(x-a) + c
	m = (y2 - y1) / (double)(x2 - x1);
	a = m * (-x1);
	c = a + y1;
	
	data->degree[0] = true;
	data->coef[0] = m;
	data->expo[0] = 1;
	data->degree[1] = true;
	data->coef[1] = c;
	data->expo[1] = 0;
}


void CFunctionProc::SketchToData_E(double x1, double y1, double x2, double y2, FuncInfo_Ellipse* data)
{
	// TODO: 여기에 구현 코드 추가.
	
	data->a = 0.0;
	data->b = 0.0;
	data->x = 0.0;
	data->y = 0.0;
	

	double x, y, a, b, r_x, r_y;
	// (x-x1)^2/a + (y-y1)^2/b + 1
	// 오른쪽 방향 +x, 위쪽 방향 -y
	x = (x2 + x1) / 2.0;
	y = (y2 + y1) / 2.0;
	a = x2 - x;
	b = y2 - y;

	data->x = x;
	data->y = y;
	data->a = a*a;
	data->b = b*b;
}


void CFunctionProc::StrToData_L(CString str, FuncInfo_Line* data)
{
	// TODO: 여기에 구현 코드 추가.
	char* Cstr;
	char stack[20];
	//int degree;
	int count, i, j, sign = 1;
	count = i = j = 0;
	Cstr = CStringToChar(str);
	for (int i = 0; i < 20; i++) {
		stack[i] = NULL;
	}
	if (*Cstr == '-') {
		sign = -1;
	}
	for (; *Cstr != '\0'; Cstr++) {
		if (isdigit(*Cstr) || *Cstr == '.') {
			stack[j++] = *Cstr;
		}
		else if (*Cstr == 'x') {
			if (*(Cstr + 1) == '^') {
				stack[j] = '\0';
				data->degree[count] = true;
				data->expo[count] = *(Cstr + 2) - '0';
				data->coef[count] = sign * atof(stack);
				count++;
				for (int i = 0; i < 20; i++) {
					stack[i] = NULL;
				}
				j = 0;
				sign = 1;
				Cstr = Cstr + 2;//degree 패스
			}
			else {
				stack[j] = '\0';
				data->degree[count] = true;
				data->expo[count] = 1;
				data->coef[count] = sign * atof(stack);
				count++;
				for (int i = 0; i < 20; i++) {
					stack[i] = NULL;
				}
				j = 0;
				sign = 1;
			}
		}
		else if (*Cstr == '-') {
			sign = -1;
		}
	}
	stack[j] = '\0';
	data->degree[count] = true;
	data->expo[count] = 0;
	data->coef[count] = sign * atof(stack);
	count++;
	for (int i = 0; i < 20; i++) {
		stack[i] = NULL;
	}
}


char* CFunctionProc::CStringToChar(CString& str)
{
	// TODO: 여기에 구현 코드 추가.
	char* temp;
	int sLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	temp = new char[sLen + 1];
	WideCharToMultiByte(CP_ACP, 0, str, -1, temp, sLen, NULL, NULL);

	return temp;
}


double CFunctionProc::LogicToPhysicalValue(bool xy, int x_Real, int y_Real, double x_Max, double y_Max, int SizeW, int SizeH)
{
	// TODO: 여기에 구현 코드 추가.
	if (xy) {
		double x_per = (x_Real / (double)SizeW) * 100;
		double x = (x_Max / 50.0 * x_per);

		return x;
	}
	else {
		double y_per = (y_Real / (double)SizeH) * 100;
		double y = -(y_Max / 50.0 * y_per);
		
		return y;
	}
}

void CFunctionProc::StrToData_E(CString str, FuncInfo_Ellipse* data)
{
	// TODO: 여기에 구현 코드 추가.
	double a = 0, b = 0, x = 0, y = 0;
	char* Cstr = CStringToChar(str);
	CString Sstr_x, Sstr_y, Sstr_a, Sstr_b;
	int i, j;
	j = str.GetLength();
	bool PosOrNeg = FALSE;
	//(x - x1) ^ 2 / a + (y - y1) ^ 2 / b = 1
	//(x-3)^2/25+(y+1)^2/16

	for (i = 0; i < j; i++) {
		if (isdigit(Cstr[i]) && x == 0) {
			if (Cstr[i - 1] == '+')
				PosOrNeg = TRUE;
			else if (Cstr[i - 1] == '-')
				PosOrNeg = FALSE;
			while (isdigit(Cstr[i]) || Cstr[i] == '.')
			{
				Sstr_x += Cstr[i];
				i++;
			}
			x = _ttof(Sstr_x);
			if (PosOrNeg)
				x = x * -1;
			i += 3;
			continue;
		}
		if (isdigit(Cstr[i]) && a == 0) {

			while (isdigit(Cstr[i]) || Cstr[i] == '.')
			{
				Sstr_a += Cstr[i];
				i++;
			}
			a = _ttof(Sstr_a);
			i += 3;
			continue;
		}
		if (isdigit(Cstr[i]) && y == 0) {
			if (Cstr[i - 1] == '+')
				PosOrNeg = TRUE;
			else if (Cstr[i - 1] == '-')
				PosOrNeg = FALSE;
			while (isdigit(Cstr[i]) || Cstr[i] == '.')
			{
				Sstr_y += Cstr[i];
				i++;
			}
			y = _ttof(Sstr_y);
			if (PosOrNeg)
				y = y * -1;
			i += 3;
			continue;
		}
		if (isdigit(Cstr[i]) && b == 0) {

			while (isdigit(Cstr[i]) || Cstr[i] == '.')
			{
				Sstr_b += Cstr[i];
				i++;
			}
			b = _ttof(Sstr_b);
			i += 3;
			continue;
		}
	}

	data->x = x;
	data->y = y;
	data->a = a;
	data->b = b;
}


void CFunctionProc::DataToCString_L(FuncInfo_Line data, CString &str)
{
	// TODO: 여기에 구현 코드 추가.
	str = _T("");
	CString tmp;
	for (int i = 0; i < INDEX; i++) {
		if (data.degree[i]) {
			tmp.Format(_T("%.3lf"), data.coef[i]);
			str = str + tmp + _T("x^");
			tmp.Format(_T("%d"), data.expo[i]);
			str = str + tmp;
			if (data.degree[i + 1] && i+1 < 10) {
				if (data.coef[i + 1] < 0) {
					
				}
				else {
					str = str + _T("+");
				}
			}
			else {
				break;
			}
		}
	}
}


void CFunctionProc::DataToCString_E(FuncInfo_Ellipse data, CString &str)
{
	// TODO: 여기에 구현 코드 추가.
	str = _T("");
	CString a, b, x, y;
	a.Format(_T("%.3lf"), data.a);
	b.Format(_T("%.3lf"), data.b);
	if (data.x < 0) {
		x.Format(_T("%.3lf"), -data.x);
		str += _T("(x+") + x;
	}
	else {
		x.Format(_T("%.3lf"), data.x);
		str += _T("(x-") + x;
	}
	str += _T(")^2/") + a;
	if (data.y < 0) {
		y.Format(_T("%.3lf"), -data.y);
		str += _T("+(y+") + y;
	}
	else {
		y.Format(_T("%.3lf"), data.y);
		str += _T("+(y-") + y;
	}
	str += _T(")^2/") + b;
}
