#include "token.h"


void Token::printToken()
{
    const char* tokenStrings[] ={"IDENTIFIER","CONSTANT","STRING_LITERAL","SIZEOF","PTR_OP","INC_OP",
  "DEC_OP","LEFT_OP","RIGHT_OP","LE_OP","GE_OP","EQ_OP","NE_OP","AND_OP","OR_OP","MUL_ASSIGN","DIV_ASSIGN",
  "MOD_ASSIGN","ADD_ASSIGN","SUB_ASSIGN","LEFT_ASSIGN","RIGHT_ASSIGN","AND_ASSIGN","XOR_ASSIGN","OR_ASSIGN",
  "TYPE_NAME","TYPEDEF","EXTERN","STATIC","AUTO","REGISTER","CHAR","SHORT","INT","LONG","SIGNED","UNSIGNED",
  "FLOAT","DOUBLE","CONST","VOLATILE","VOID","STRUCT","UNION","ENUM","ELLIPSIS","CASE","DEFAULT","IF","ELSE",
  "SWITCH","WHILE","DO","FOR","GOTO","CONTINUE","BREAK","RETURN","ERROR"};
  
        if(this->getText().size()==1 && ((this->getText().at(0)>=123 && this->getText().at(0)<=126) || (this->getText().at(0)>=91 && this->getText().at(0)<=94) || (this->getText().at(0)>=40 && this->getText().at(0)<=47) || (this->getText().at(0)>=58 && this->getText().at(0)<=63) || (this->getText().at(0)>=37 && this->getText().at(0)<=38) || this->getText().at(0)==33))
        {
            cout<<this->getText()<<'\t'<<this->getText()<<endl;
        }
        if(this->getType()>=IDENTIFIER) 
        {
            cout<<tokenStrings[this->getType()-IDENTIFIER]<<'\t'<<this->getText()<<endl;
        }


}

void varToken::add_line(int l)
{
    
    this->lines.get()->insert(l);
}

shared_ptr<set<int>> varToken::getLines()
{
    return this->lines;
}

tokenType Token::getType()
{
    return this->type;
}

string Token::getText()
{
    return this->text;
}


