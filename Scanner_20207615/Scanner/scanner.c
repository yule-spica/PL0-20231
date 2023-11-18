#include <stdio.h>
#include "scanner.h"
#include <ctype.h>
#include <string.h>

TokenType Token;
int		  Num;
char	  Id[MAX_IDENT_LEN + 1];
char	  Sub[MAX_IDENT_LEN + 1];

FILE * f;
char ch;

TokenType checkKeyword(){
	//TODO: Kiem tra tham so truyen vao co phai la mot Tu khoa khong
	//................

	int i;
	for(i = 0; i < KEYWORDS_COUNT; i++)
		if(strcmp(Id, keywords[i].string) == 0)
			return keywords[i].Token;
	return IDENT;
}

char getCh(){
  return fgetc(f);
}

TokenType getToken(){
//TODO:
//..............
	while (ch == ' ' || ch == '\n') {
		ch = getCh();
	}
	if (isalpha(ch)) {
		memset(Id, 0, MAX_IDENT_LEN); memset(Sub, 0, MAX_IDENT_LEN);
		int i = 0;
		Id[i] = toupper(ch);
		Sub[i] = ch;
		i++;
		while (isalpha(ch) || isdigit(ch)) {
			ch = getCh();
			Id[i] = toupper(ch);
			Sub[i] = ch;
			i++;
		}
		Id[i-1] = 0;
		return IDENT;
	}
	else if (isdigit(ch)) {
		while (isdigit(ch))
			ch = getCh();
		return NUMBER;
	}
	else if (ch == ';') {
		ch = getCh();
		return SEMICOLON;
	}
	else if (ch == ',') {
		ch = getCh();
		return COMMA;
	}
	else if (ch == '=') {
		ch = getCh();
		return EQU;
	}
	else if (ch == '+') {
		ch = getCh();
		return PLUS;
	}
	else if (ch == '-') {
		ch = getCh();
		return MINUS;
	}
	else if (ch == '*') {
		ch = getCh();
		return TIMES;
	}
	else if (ch == '/') {
		ch = getCh();
		return SLASH;
	}
	else if (ch == '<') {
		ch = getCh();
		if (ch == '=') {
			ch = getCh();
			return LEQ;
		}
		else if (ch = '>') {
			ch = getCh();
			return NEQ;
		}
		return LSS;
	}
	else if (ch == '>') {
		ch = getCh();
		if (ch == '=') {
			ch = getCh();
			return GEQ;
		}
		return GTR;
	}
	else if (ch == '(') {
		ch = getCh();
		return LPARENT;
	}
	else if (ch == ')') {
		ch = getCh();
		return RPARENT;
	}
	else if (ch == '[') {
		ch = getCh();
		return LBRACK;
	}
	else if (ch == ']') {
		ch = getCh();
		return RBRACK;
	}
	else if (ch == ':') {
		ch = getCh();
		if (ch == '=') {
			ch = getCh();
			return ASSIGN;
		}
	}
	else if (ch == '.') {
		ch = getCh();
		return PERIOD;
	}
	else if (ch == '%') {
		ch = getCh();
		return PERCENT;
	}
    return NONE;
}


void compile(char * filename){
  	if((f = fopen(filename,"rt")) == NULL) printf("File %s not found",filename);
  	else{
		ch =' ';
		do{
		 	Token = getToken();
			if (Token == IDENT) {
				printf("%s", TabToken[checkKeyword()]);
				if(checkKeyword() == IDENT) {
					printf(": %s", Sub);
				}
			}
			else printf("%s",TabToken[Token]);
			printf("\n");
			// if(Token==IDENT) printf("(%s) \n",Id);
			// else if(Token==NUMBER) printf("(%d) \n",Num);
			// else printf("\n");
		}while(Token != NONE);
	}
  	fclose(f);
}
