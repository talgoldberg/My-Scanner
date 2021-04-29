#include "symtab.h"
#include <vector>
#include <regex>

void SymbolTable::initReserved()
{
   const char* tokenStrings[] ={"IDENTIFIER","CONSTANT","STRING_LITERAL","SIZEOF","PTR_OP","INC_OP",
  "DEC_OP","LEFT_OP","RIGHT_OP","LE_OP","GE_OP","EQ_OP","NE_OP","AND_OP","OR_OP","MUL_ASSIGN","DIV_ASSIGN",
  "MOD_ASSIGN","ADD_ASSIGN","SUB_ASSIGN","LEFT_ASSIGN","RIGHT_ASSIGN","AND_ASSIGN","XOR_ASSIGN","OR_ASSIGN",
  "TYPE_NAME","TYPEDEF","EXTERN","STATIC","AUTO","REGISTER","CHAR","SHORT","INT","LONG","SIGNED","UNSIGNED",
  "FLOAT","DOUBLE","CONST","VOLATILE","VOID","STRUCT","UNION","ENUM","ELLIPSIS","CASE","DEFAULT","IF","ELSE",
  "SWITCH","WHILE","DO","FOR","GOTO","CONTINUE","BREAK","RETURN","ERROR"};
        
        
        vector<string> vec;
        ifstream file("reserved.txt");
        string line;
        
        while(getline(file,line))
        {
            vec.push_back(line);
        }
        
        file.close();

        vector<pair<string,int>> pavec;
        string toktype;
        string valtoktype;
        int val; 
        bool visit=false;
        
        for(int i=0; i<vec.size(); i++){
            for(int j=0; j<vec[i].size(); j++){
                
                if(vec[i].at(j) != '\t' && visit == false)
                    toktype+=vec[i].at(j);
                
                if(vec[i].at(j) == '\t')
                    visit=true;
                
                if(visit == true)
                    valtoktype+=vec[i].at(j);
            }
            
            if(vec[i]!=" " && !valtoktype.empty())
            {
                
                val=stoi(valtoktype);
                pair<string,int> element;
                element.first=toktype;
                element.second=val;
                pavec.push_back(element);
                toktype.clear(); 
                valtoktype.clear();
                visit=false;
            }
        }

        for(int i=0; i<pavec.size(); i++)
        {
            
          
            shared_ptr<Token> sp(new Token((tokenType)(pavec[i].second),pavec[i].first));
            symMap.insert(pair<string, shared_ptr<Token>>(pavec[i].first,sp));
           
        }

  

}

shared_ptr<Token> SymbolTable::lookupToken(string text)
{
    if(symMap.find(text)==symMap.end())
    {
        
        if(text.size()==1 && ((text.at(0)>=123 && text.at(0)<=126) || (text.at(0)>=91 && text.at(0)<=94) || (text.at(0)>=40 && text.at(0)<=47) || (text.at(0)>=58 && text.at(0)<=63) || (text.at(0)>=37 && text.at(0)<=38) || text.at(0)==33))
        {
          
           shared_ptr<Token> sp(new Token((tokenType)((int)text.at(0)),text));
           insertToken(text,sp);
           return sp;
        }
        regex OneD("[0-9]");
        regex D("[1-9][0-9]*");
        regex L("[a-zA-Z_]([a-zA-Z_]|[0-9])*");
        regex C("\'[^\']\'");
        regex S("\"[^\"]*\"");
        regex OpDoublePlus("\\+\\+");
        regex OpDoubleMinus("\\-\\-");
        regex OpPtr("\\-\\>");
        regex OpAnd("\\&\\&");
        regex OpOr("\\|\\|");
        regex OpSmaller("\\<\\=");
        regex OpGreater("\\>\\=");
        regex OpEqual("\\=\\=");
        regex OpNotEqual("\\!\\=");
        regex E("[0-9]+[Ee][+-]?[0-9]+");
        regex E_smaller_then_one("[0-9]*\\.[0-9]+([Ee][+-]?[0-9]+)?");
        regex E_larger_then_one("[0-9]+\\.[0-9]*([Ee][+-]?[0-9]+)?");
        
         if(regex_match(text,OneD))
        {
        
           shared_ptr<Token> sp(new Token(CONSTANT,text));
           insertToken(text,sp);
           return sp; 
        }
        
        if(regex_match(text,OpDoublePlus))
        {
           shared_ptr<Token> sp(new Token(INC_OP,text));
           insertToken(text,sp);
           return sp; 
        }
        
        if(regex_match(text,OpDoubleMinus))
        {
           shared_ptr<Token> sp(new Token(DEC_OP,text));
           insertToken(text,sp);
           return sp; 
        }

        if(regex_match(text,OpPtr))
        {
           shared_ptr<Token> sp(new Token(PTR_OP,text));
           insertToken(text,sp);
           return sp; 
        }

        if(regex_match(text,OpAnd))
        {
           shared_ptr<Token> sp(new Token(AND_OP,text));
           insertToken(text,sp);
           return sp; 
        }

        if(regex_match(text,OpOr))
        {
           shared_ptr<Token> sp(new Token(OR_OP,text));
           insertToken(text,sp);
           return sp; 
        }

        if(regex_match(text,OpSmaller))
        {
           shared_ptr<Token> sp(new Token(LE_OP,text));
           insertToken(text,sp);
           return sp; 
        }

        if(regex_match(text,OpGreater))
        {
           shared_ptr<Token> sp(new Token(GE_OP,text));
           insertToken(text,sp);
           return sp; 
        }

        if(regex_match(text,OpEqual))
        {
           shared_ptr<Token> sp(new Token(EQ_OP,text));
           insertToken(text,sp);
           return sp; 
        }

        if(regex_match(text,OpNotEqual))
        {
           shared_ptr<Token> sp(new Token(NE_OP,text));
           insertToken(text,sp);
           return sp; 
        }

        if(regex_match(text,S))
        {
           string change;
           for(int i=0; i<text.size(); i++)
           {
              if(text.at(i)!= '"')
               change+=text.at(i);
           }
           
           shared_ptr<Token> sp(new Token(STRING_LITERAL,change));
           insertToken(change,sp);
           return sp;  
        }
        
        if(regex_match(text,C))
        {
           string change;
           for(int i=0; i<text.size(); i++)
           {
              if(text.at(i)!= '\'')
               change+=text.at(i);
           }
           shared_ptr<Token> sp(new Token(CONSTANT,change));
           insertToken(change,sp);
           return sp;     
        }
        
        if(regex_match(text,D))
        {
           shared_ptr<Token> sp(new Token(CONSTANT,text));
           insertToken(text,sp);
           return sp;  
        }
            
        if(regex_match(text,L))
        { 
           shared_ptr<Token> sp(new varToken(text));
           insertToken(text,sp);
           return sp;   
        }
        
        if(regex_match(text,E))
        {
           shared_ptr<Token> sp(new Token(CONSTANT,text));
           insertToken(text,sp);
           return sp;     
        }

        if(regex_match(text,E_smaller_then_one))
        {
           shared_ptr<Token> sp(new Token(CONSTANT,text));
           insertToken(text,sp);
           return sp;     
        }
        
        if(regex_match(text,E_larger_then_one))
        {
           shared_ptr<Token> sp(new Token(CONSTANT,text));
           insertToken(text,sp);
           return sp;     
        }

         shared_ptr<Token> sp(new Token(ERROR,text));
         return sp;
        
    }
    else
    {
      
       return symMap.find(text)->second;
       
    }
    
}

void SymbolTable::insertToken(string text, shared_ptr<Token> tokenp)
{
    symMap.insert(pair<string, shared_ptr<Token>>(text,tokenp));
}

void SymbolTable::xref()
{
        for(auto const& i: symMap)
        {
           
           if(i.second.get()->getType()==IDENTIFIER)
           {    
               
               set<int> :: iterator it;
               cout<<i.first<<'\t';
   
               for(it=i.second.get()->getLines()->begin(); it!=i.second.get()->getLines()->end(); it++)
               {
                    cout<<*it<<" ";
               }
               cout<<'\n';
           }
        }
}


