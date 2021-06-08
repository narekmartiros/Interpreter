#include "Tokenizer.h"
#include "vars.h"
#include<algorithm>




class Parser
{
    public:
    void parse(Tokenizer& tk);
    
    private:
    bool is_type(const std::string& s);
    bool is_existing_var_name(const std::string& s);
    bool is_new_var_name(const std::string& s);
    bool is_integer(const std::string& s);
    bool is_bool(const std::string& s);
    bool is_double(const std::string& s);
    bool is_string(const std::string& s);
    bool is_operator(const std::string& s);
    bool string_to_bool(const std::string& s);
    int string_to_enum(const std::string& s);

    std::map<std::string,Vars> variables;
};

bool Parser::is_type(const std::string& s){
    return string_to_enum(s)?true:false;
}

int  Parser::string_to_enum(const std::string& s){
    if(s=="tiv"){
        return 1;
    }
    else if(s=="tivr"){
        return 2;
    }
    else if(s=="tarer"){
        return 3;
    }
    else if(s=="tram"){
        return 4;
    }
    else
    return 0;
}

bool Parser::is_existing_var_name(const std::string & s){
    for(auto& x:variables){
        if(x.first==s){
            return true;
        }
    }
    return false;
}

bool Parser::is_new_var_name(const std::string& s){
    if((s[0]!='"'&&s[s.size()-1]!='"')&&!is_bool(s)&&!is_double(s)&&!is_integer(s)&&!is_existing_var_name(s)&&!is_type(s)){
        return true;
    }
    else return false;
}

bool Parser::is_integer(const std::string& s){
    bool x=true;
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            x= false;

    if((s[0]!='"'&&s[s.size()-1]!='"')&&x){
        return true;
    }
    else 
        return false;
}

bool Parser::is_bool(const std::string& s){
   return ((s=="true"||s=="false")&&(s[0]!='"'&&s[s.size()-1]!='"'))?true:false;
}

bool Parser::is_double(const std::string& s){
    int count=0;
    int pos=0;
    for(int i=0;i<s.size();++i){
        if(s[0]=='.'||s[s.size()-1]=='.')
        ++pos;
        if(s[i]=='.'){
            ++count;
        }
    }
    return (pos==0&&count<=1)?true:false;
}

bool Parser::is_string(const std::string& s){
    if(s[0]=='"'&&s[s.size()-1]=='"'){
        return true;
    }
    else 
        return false;
}

bool Parser::string_to_bool(const std::string& s){
    if(s=="true"||s=="false"){
        return true;
    }
    else 
        return false;
}

void Parser::parse( Tokenizer& tk) {
    int i=0;
    while (i<tk.get_raw_counts())
    {
        auto tok=tk.get_raw(i);
        if(tok.size()>2)
        {   
            // new variable definition
            if(is_type(tok[0])&&tok[2]=="="){
                if(string_to_enum(tok[0])==1){
                    if(is_integer(tok[3])){
                        variables.emplace(tok[1],Vars(var_types::tiv,tok[1],std::stoi(tok[3])));
                    }
                }
                else if(string_to_enum(tok[0])==2){
                    if(is_double(tok[3])){
                        variables.emplace(tok[1],Vars(var_types::tivr,tok[1],std::stod(tok[3])));
                    }
                }
                else if(string_to_enum(tok[0])==3){
                    if(is_string(tok[3])){
                        variables.emplace(tok[1],Vars(var_types::tarer,tok[1],tok[3]));
                    }
                }
                else if(string_to_enum(tok[0])==4){
                    if(is_bool(tok[3])){
                        variables.emplace(tok[1],Vars(var_types::tram,tok[1],string_to_bool(tok[3])));
                    }
                }
            }
            // new variable declaration
            if(is_type(tok[0])&&is_new_var_name(tok[1])&&tok.size()<2){
                if(string_to_enum(tok[0])==1){
                    if(is_integer(tok[3])){
                        variables.emplace(tok[1],Vars(var_types::tiv,tok[1]));
                    }
                }
                else if(string_to_enum(tok[0])==2){
                    if(is_double(tok[3])){
                        variables.emplace(tok[1],Vars(var_types::tivr,tok[1]));
                    }
                }
                else if(string_to_enum(tok[0])==3){
                    if(is_string(tok[3])){
                        variables.emplace(tok[1],Vars(var_types::tarer,tok[1]));
                    }
                }
                else if(string_to_enum(tok[0])==4){
                    if(is_bool(tok[3])){
                        variables.emplace(tok[1],Vars(var_types::tram,tok[1]));
                    }
                }
            }
            //variable assignement
            if((is_existing_var_name(tok[0])&&is_existing_var_name(tok[2]))&&(tok[1]=="="&&tok.size()==3)){
                if((variables[tok[0]].get_type()==variables[tok[2]].get_type())&&(variables[tok[0]].get_type()==var_types::tiv)){
                    variables[tok[0]]=variables[tok[2]];
                }
                else if((variables[tok[0]].get_type()==variables[tok[2]].get_type())&&(variables[tok[0]].get_type()==var_types::tivr)){
                     variables[tok[0]]=variables[tok[2]];
                }
                else if((variables[tok[0]].get_type()==variables[tok[2]].get_type())&&(variables[tok[0]].get_type()==var_types::tarer)){
                    variables[tok[0]]=variables[tok[2]];
                }
                else if((variables[tok[0]].get_type()==variables[tok[2]].get_type())&&(variables[tok[0]].get_type()==var_types::tram)){
                     variables[tok[0]]=variables[tok[2]];
                }
            }
            //literal assignement
            if(!is_new_var_name(tok[2])&&(tok.size()==3)){
                if(is_integer(tok[2])&&variables[tok[0]].get_type()==var_types::tiv){
                    std::cout<<"sdfs";
                    variables[tok[0]].set_value(std::stoi(tok[2]));
                }
                else if(is_double(tok[2])&&variables[tok[0]].get_type()==var_types::tivr){
                    variables[tok[0]].set_value(std::stod(tok[2]));
                }
                else if(is_string(tok[2])&&variables[tok[0]].get_type()==var_types::tarer){
                    variables[tok[0]].set_value(tok[2]);
                }
                else if(is_bool(tok[2])&&variables[tok[0]].get_type()==var_types::tram){
                    variables[tok[0]].set_value(string_to_bool(tok[2]));
                }
            }

        }
     
        //cout operation
        if(tok.size()>=2&&tok[0]=="tpel"&&is_existing_var_name(tok[1])){
                    if(variables[tok[1]].get_type()==var_types::tiv){
                        int* x=(int*)variables[tok[1]].get_value();
                        std::cout<<*x;
                    }
                    else if(variables[tok[1]].get_type()==var_types::tivr){
                        double* x=(double*)variables[tok[1]].get_value();
                        std::cout<<*x;
                    }
                    else if(variables[tok[1]].get_type()==var_types::tarer){
                        std::string* x=(std::string*)variables[tok[1]].get_value();
                        std::cout<<*x;
                    }
                    else if(variables[tok[1]].get_type()==var_types::tiv){
                        bool* x=(bool*)variables[tok[1]].get_value();
                        std::cout<<*x;
                    }
        }
        else if (tok.size()>=2&&tok[0]=="tpel"){
            std::cout<<tok[1];
        }
        
        
            
     ++i;
    }

}