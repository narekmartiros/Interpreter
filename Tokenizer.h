#include <string>
#include<vector>
#include<iostream>
#include <fstream>
#include <bits/stdc++.h>

using token_container=std::vector<std::vector<std::string>>;

class Tokenizer
{
public:
   Tokenizer(const std::string& filename);
   ~Tokenizer();
   void tokenize_source_code();
   const std::vector<std::string>& get_raw(size_t index)const;
   int get_raw_counts()const;
   int get_raw_size(size_t index)const;
   
private:
   std::ifstream file1;
   token_container temp;
};

Tokenizer::Tokenizer(const std::string& filename){file1.open(filename);}
Tokenizer::~Tokenizer(){file1.close();};

void Tokenizer::tokenize_source_code(){
    std::string temp_s;
    std::vector<std::string> tmp;
    while (!file1.eof()){
      std::string m;
		std::getline(file1,temp_s);
		std::istringstream ss(temp_s);
		while(ss>>m){
         std::string s=m;
			tmp.push_back(s);
		}
      temp.push_back(tmp);
      tmp.clear();
	}
    file1.close();
}

const std::vector<std::string>& Tokenizer::get_raw(size_t index)const{
   return temp[index];
}

int Tokenizer::get_raw_counts()const{
   return temp.size();
}

int Tokenizer::get_raw_size(size_t index)const{
   return temp[index].size();
}