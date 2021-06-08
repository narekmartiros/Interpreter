#include<tuple> 
#include <type_traits>
#include<iostream>

enum class var_types{tiv,tivr,tarer,tram, zro};

class Vars
{
public:
    Vars();
    Vars(var_types vt,std::string s, int x);
    Vars(var_types vt,std::string s, double x);
    Vars(var_types vt,std::string s, std::string x);
    Vars(var_types vt,std::string s, bool x);
    Vars(var_types vt,std::string s);
    Vars(const Vars& src);
    Vars operator=(const Vars& rhs);
     ~Vars();
  
    const void* get_value();
    const std::string& get_name()const;
    const var_types& get_type()const;
    void set_value(int x);
    void set_value(double x);
    void set_value(const std::string& x);
    void set_value(bool x);
    
private:
    var_types v_type;
    std::string v_name;
    void* v_p;
};

Vars::Vars():v_type{var_types::tiv},v_name{""},v_p{nullptr}{}
Vars::Vars(var_types vt,std::string s, int x):v_type{vt},v_name{s}, v_p{new int (x)}{}
Vars::Vars(var_types vt,std::string s, double x):v_type{vt},v_name{s}, v_p{new double (x)}{}
Vars::Vars(var_types vt,std::string s, std::string x):v_type{vt},v_name{s}, v_p{new std::string (x)}{}
Vars::Vars(var_types vt,std::string s, bool x):v_type{vt},v_name{s}, v_p{new bool(x)}{}
Vars::Vars(var_types vt,std::string s):v_type{vt},v_name{s}{}

Vars::~Vars(){
    if(v_type==var_types::tiv){
        int* p=(int*)v_p;
        delete p; 
    }
    else if(v_type==var_types::tivr){
        double* p=(double*)v_p;
        delete p; 
    }
    else if(v_type==var_types::tarer){
        std::string* p=(std::string*)v_p;
        delete p;  
    }
    else if(v_type==var_types::tram){
        bool* p=(bool*)v_p;
        delete p; 
    }
}

Vars::Vars(const Vars& src):v_type{src.v_type},v_name{""}{
    if(src.v_type==var_types::tiv){
        v_p=new int(*(int*)src.v_p);
    }
    else if(src.v_type==var_types::tivr){
        v_p=new double(*(double*)src.v_p); 
    }
    else if(src.v_type==var_types::tarer){
        v_p=new std::string(*(std::string*)src.v_p);
    }
    else if(src.v_type==var_types::tram){
        v_p=new bool(*(bool*)src.v_p);
    }
}

Vars Vars::operator=(const Vars& rhs){
    if(this==&rhs){
        return *this;
    }
    if(rhs.v_type==var_types::tiv){
        *(int*)v_p=*(int*)rhs.v_p;
    }
    else if(rhs.v_type==var_types::tivr){
        *(double*)v_p=*(double*)rhs.v_p;    
    }
    else if(rhs.v_type==var_types::tarer){
        *(std::string*)v_p=*(std::string*)rhs.v_p;   
    }
    else if(rhs.v_type==var_types::tram){
        *(bool*)v_p=*(bool*)rhs.v_p;   
    } 
    return *this;
}

const void* Vars::get_value(){
    return v_p;
}
void Vars::set_value(int x){
    *(int*)v_p=x;
}
void Vars::set_value(double x){
    *(double*)v_p=x;
}
void Vars::set_value(const std::string& x){
    *(std::string*)v_p=x;
}
void Vars::set_value(bool x){
    *(bool*)v_p=x;
}
const std::string& Vars::get_name()const{
    return v_name;
}
const var_types& Vars::get_type()const{
    return v_type;
}

    
    
    