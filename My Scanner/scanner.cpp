#include "scanner.h"

shared_ptr<Token> Scanner::nextToken()
{   
    regex OneD("[0-9]");
    regex D("[1-9][0-9]*");
    float a=122.E12;
    bool visit=false;
    string op;
    string token;
    string exptok;
    char cheak=0;
    char cheak_for_string=0;
    while (nextChar())
    {
    
            
        if(ch!='\r' && visit==false && (ch>=123 && ch<=126) || (ch>=91 && ch<=94) || (ch>=40 && ch<=47) || (ch>=58 && ch<=63) || (ch>=37 && ch<=38) || ch==33)
        {   
            

            if(ch=='+' && cheak=='+')
            {
                op+=ch;
                return symTab.lookupToken(op);
            }
            if(ch=='-' && cheak=='-')
            {
                op+=ch;
                return symTab.lookupToken(op);
            }
            if(ch=='>' && cheak=='-')
            {
                op+=ch;
                return symTab.lookupToken(op);
            }
            if(ch=='&' && cheak=='&')
            {
                op+=ch;
                return symTab.lookupToken(op);
            }
            if(ch=='|' && cheak=='|')
            {
                op+=ch;
                return symTab.lookupToken(op);
            }
            if(ch=='=' && cheak=='<')
            {
                op+=ch;
                return symTab.lookupToken(op);
            }
            if(ch=='=' && cheak=='>')
            {
                op+=ch;
                return symTab.lookupToken(op);
            }
            if(ch=='=' && cheak=='=')
            {
                op+=ch;
                return symTab.lookupToken(op);
            }
            if(ch=='=' && cheak=='!')
            {
                op+=ch;
                return symTab.lookupToken(op);
            }
            if(((ch==';' || ch==')' || ch==']' || ch==',') && (cheak=='}' || cheak==')' || cheak==']' )) || (ch==')' && cheak=='(') || (ch=='(' && cheak==')') || (ch=='[' && cheak==']') || (ch=='{' && cheak==')') || (ch==']' && cheak=='['))
            {
                inputFile.seekg(-1,ios::cur);
                return symTab.lookupToken(op);
            }
            if((ch=='{' || ch=='(' || ch=='[') && cheak==',')
            {
                inputFile.seekg(-1,ios::cur);
                return symTab.lookupToken(op);
            }
            if((ch=='(' && cheak=='(') || (ch==')' && cheak==')') || (ch=='[' && cheak=='[') || (ch==']' && cheak==']') || (ch=='{' && cheak=='{') || (ch=='}' && cheak=='}') ||(ch=='}' && cheak=='{'))
            {
                inputFile.seekg(-1,ios::cur);
                return symTab.lookupToken(op);
            }
            if(ch=='/' && (cheak==';' || cheak=='{' || cheak=='}' || cheak==')'))
            {
                inputFile.seekg(-1,ios::cur);
                return symTab.lookupToken(op);
            }

            cheak=ch;
            op+=ch;
          
        }

        if(op=="/*" || op=="//")
        {   
            
            bool ans=true;
            char prev=0;
            if(op=="/*")
            {
                while(ans && nextChar())
                {
                    if (ch == '/' && prev == '*')
                    {
                        ans=false;
                    
                    }
		            prev = ch;
                }
                

            }
            else 
            {
                while(ans && nextChar())
                {
                    if(ch=='\n' || ch=='\r')
                    {
                        ans=false;
                        inputFile.seekg(-1,ios::cur);
                    }
                }
            }

            nextChar();
            op.clear();
        }
        
        if(ch!='\r' && visit==false && ((regex_match(token,D) && op==";") || (regex_match(token,OneD) && op==";")))
        {
           
             inputFile.seekg(-1,ios::cur);
             return symTab.lookupToken(token);
        }
        
        if(visit==true)
        {
            token+=ch;
            if(cheak_for_string==ch)
                return symTab.lookupToken(token);

        }

        if(ch!='\r' && op.empty() && (ch=='"' || ch=='\'') && visit==false)
        {
            visit=true;
            cheak_for_string=ch;
            token+=ch;
        }
        if(ch!='\r' && !op.empty() && (ch=='"' || ch=='\'') && visit==false)
        {
            inputFile.seekg(-1,ios::cur);
            return symTab.lookupToken(op);
        }

       if(ch!='\r' && visit==false && ch!=' ' && ch!='\t' && ch!='\n' && ch!='"' && ch!='\'' && !((ch>=123 && ch<=126) || (ch>=91 && ch<=94) || (ch>=40 && ch<=47) || (ch>=58 && ch<=63) || (ch>=37 && ch<=38) || ch==33))
       { 
           token+=ch;
           
       }
       
       if(ch!='\r' && visit==false && ch=='.' &&((regex_match(token,D) && op==".") || (regex_match(token,OneD) && op==".")))
       {    
    
            
            exptok+=token;
            exptok+=ch;
            
            bool findchar=true;
            while(findchar && nextChar())
            {
           
                if(ch==';' || ch==',')
                {
                    findchar=false;
                }
                if(ch!=';' && ch!=',')
                {
                    exptok+=ch;
                }
        
            }

            int temp=0;
            int temp1=0;
            for(int i=0; i<exptok.size(); i++)
            {
                if(exptok.at(i)=='e' || exptok.at(i)=='E')
                    temp++;
                if(exptok.at(i)=='.')
                    temp1++;
            }

            if(temp>1 || temp1>1)
            {
                 inputFile.seekg(-1,ios::cur);
               return symTab.lookupToken(exptok);
                

            }
       
        inputFile.seekg(-1,ios::cur);
        return symTab.lookupToken(exptok);

       }

       if(ch!='\r' && visit==false && ((ch>=48 && ch<=57) || (ch=='E' || ch=='e')) &&((regex_match(token,D) && op==".") || (regex_match(token,OneD) && op==".")))
       {    
           
            exptok+=op; 
            exptok+=token;
            
            bool findchar=true;
            while(findchar && nextChar())
            {
           
                if(ch==';' || ch==',')
                {
                    findchar=false;
                }
                if(ch!=';' && ch!=',')
                {
                    exptok+=ch;
                }
        
            }

            int temp=0;
            int temp1=0;
            for(int i=0; i<exptok.size(); i++)
            {
                if(exptok.at(i)=='e' || exptok.at(i)=='E')
                    temp++;
                if(exptok.at(i)=='.')
                    temp1++;
            }

            if(temp>1 || temp1>1)
            {
                 inputFile.seekg(-1,ios::cur);
                return symTab.lookupToken(exptok);
                

            }

             inputFile.seekg(-1,ios::cur);
            return symTab.lookupToken(exptok);
       }
       
       if(ch!='\r' && visit==false && (ch==' ' || ((ch>=123 && ch<=126) || (ch>=91 && ch<=94) || (ch>=40 && ch<=47) || (ch>=58 && ch<=63) || (ch>=37 && ch<=38) || ch==33))&& !token.empty())
       {    
           if(ch!=' ')
           inputFile.seekg(-1,ios::cur);
          
           shared_ptr<Token> sp=symTab.lookupToken(token);
           if(sp.get()->getType()==IDENTIFIER)
           {
                sp.get()->add_line(lineno);
                return sp;
           }
                
           
           if(sp.get()->getType()!=IDENTIFIER)
           {
             
               return sp;
           }
                
       }
       if(ch!='\r' && visit==false && ch=='\n' && !op.empty())
       {
           
           return symTab.lookupToken(op);
       }

       if(ch!='\r' && visit==false && !((ch>=123 && ch<=126) || (ch>=91 && ch<=94) || (ch>=40 && ch<=47) || (ch>=58 && ch<=63) || (ch>=37 && ch<=38) || ch==33) && !op.empty() && op.size()==1)
       {
           
           if(!token.empty())
           {
               inputFile.seekg(-1,ios::cur);
               return symTab.lookupToken(op);
           }
           
           else 
           {    
                    return symTab.lookupToken(op);
                 
           }
       }

       
        
    }
    
}