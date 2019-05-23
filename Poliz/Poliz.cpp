#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
void Test(const char* out) {
	int i, k = 0, e = 0;
	bool y;
	for (int h = 0; h < strlen(out); h++) {
		if (out[h] == '(')
		{
			e = e + 1;
		}
		if (out[h] == ')') {
			e = e + 1;
		}

	}
	if (e % 2 != 0) {
		puts("Error");
		exit(0);
	}
	for (int h = 0; h < strlen(out); h++) {
		if ((out[h] == '+') || (out[h] == '*') || (out[h] == '/') || (out[h] == '-')) {
			if ((out[h + 1] == '+') || (out[h + 1] == '*') || (out[h + 1] == '/') || (out[h + 1] == '-') || (out[h + 1] == '\0')) k = 1;
		}
	}
	if (k == 1) {
		puts("Error");
		exit(0);
	}
}
struct stek
{
	char value;
	struct stek* next;
};
stek* p;
void Push(stek * &Next, char data) {
	stek* NewStek = new stek;
	NewStek->value = data;
	NewStek->next = Next;
	Next = NewStek;
}
char Pop(stek * &Next) {
	char temp = Next->value;
	stek* NewStek = Next;
	Next = Next->next;
	delete NewStek;
	return temp;
}
struct steki
{
	int valuei;
	struct steki* nexti;
};
steki* pi;
void Pushi(steki * &Nexti, int datai) {
	steki* NewSteki = new steki;
	NewSteki->valuei = datai;
	NewSteki->nexti = Nexti;
	Nexti = NewSteki;
}
char Popi(steki * &Nexti) {
	char tempi = Nexti->valuei;
	steki* NewSteki = Nexti;
	Nexti = Nexti->nexti;
	delete NewSteki;
	return tempi;
}

int Prior(char h) {
	switch (h)
	{
	case '*':
		return 3;
	case '/':
		return 3;
	case '+':
		return 2;
	case '-':
		return 2;
	case '(':
		return 0;
	case ')':
		return 0;
	case NULL:
		return -1;
	default:
		break;
	}

}
void Postfix(const char* i, char* o) {
	int k = 0, l = 0;
	while (i[k]) {
		char c = i[k];
		switch (c)
		{
		case '(':
			Push(p, c);
			break;
		case ')':
			while (p->value != '(') {
				c = Pop(p);
				o[l] = c;
				l++;
			}
			Pop(p);
			break;
		case '+':
		case '*':
		case '/':
			if (p != NULL)
				while (Prior(c) < Prior(p->value)) {
					o[l] = Pop(p);
					l++;
				}
			Push(p, c);
			break;
		case '-':
			if ((i[k - 1] == '(') || (k == 0)) {
				o[l + 1] = '!';
				break;
			}
			else {
				if (p != NULL)
					while (Prior(c) < Prior(p->value)) {
						o[l] = Pop(p);
						l++;
					}
				Push(p, c);
			}
			break;
		default:
			o[l] = c;
			if (o[l + 1] != '!')
				l++;
			else l = l + 2;
			break;
		}
		k++;
	}
	while (p != 0) {
		o[l] = Pop(p);
		l++;
	}
}
int Per(char c) {
	switch (c)
	{
	case '1':
		Pushi(pi, 1);
		break;
	case '2':
		Pushi(pi, 2);
		break;
	case '3':
		Pushi(pi, 5);
		break;
	case '4':
		Pushi(pi, 4);
		break;
	case '5':
		Pushi(pi, 5);
		break;
	case '6':
		Pushi(pi, 6);
		break;
	case '7':
		Pushi(pi, 7);
		break;
	case '8':
		Pushi(pi, 8);
		break;
	case '9':
		Pushi(pi, 9);
		break;
	case '0':
		Pushi(pi, 0);
		break;
	default:
		printf_s("%c\t", c);
		int a;
		scanf_s("%d", &a);
		Pushi(pi, a);
		break;
	}
	return 0;
}
int main() {
	int i = 0, st = 0;;
	char in[20];
	char out[20] = "";
	gets_s(in, 20);
	Test(in);
	Postfix(in, out);
	cout << out << endl;
	for (int j = 0; j < strlen(out); j++) {
		if ((out[j] != '+') && (out[j] != '*') && (out[j] != '/') && (out[j] != '-') && (out[j] != '!')) {
			Per(out[j]);
		}
		else if (out[j] == '!') {
			st = Popi(pi) * (-1);
			Pushi(pi, st);
			st = 0;
		}
		else if (out[j] == '+') {
			int n1, n2;
			n2 = Popi(pi);
			n1 = Popi(pi);
			Pushi(pi, n1 + n2);
			n1 = 0;
			n2 = 0;
		}
		else if (out[j] == '*') {
			int n1, n2;
			n2 = Popi(pi);
			n1 = Popi(pi);
			Pushi(pi, n1 * n2);
			n1 = 0;
			n2 = 0;
		}
		else if (out[j] == '/') {
			int n1, n2;
			n2 = Popi(pi);
			n1 = Popi(pi);
			Pushi(pi, n1 / n2);
			n1 = 0;
			n2 = 0;
		}
		else if (out[j] == '-') {
			int n1, n2;
			n2 = Popi(pi);
			n1 = Popi(pi);
			Pushi(pi, n1 - n2);
			n1 = 0;
			n2 = 0;
		}
	}
	i = Popi(pi);
	printf_s("%d", i);
	return 0;
}