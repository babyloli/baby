#ifndef _CSV_FILE_  
#define _CSV_FILE_  

#include "cocos2d.h"
#include <fstream>
#include "Utils.h"
//#include <iostream>

class HCSVFile {  
    
public:  
	HCSVFile(){}
    ~HCSVFile();  
    //���Դ洢����
     
private:  
	int cols;  
	std::string fieldsep;  
	std::vector<std::vector<std::string>>  data; 

    void StringSplit( const std::string & str, std::vector<std::string> & tokens, const char & delimiters);      
    //void split(std::vector<std::string>& field, std::string line);  
    //int  advplain(const std::string& line, std::string& fld, int);  
    //int  advquoted(const std::string& line, std::string& fld, int);  
    
public:   
    //��CSV�ļ�  
    bool            openFile(const char* fileName);  
    //�������л�ȡ����  
    const   char*   getData(int rows, int cols);  
    //��ȡָ�����ݵ����±�  
    //int             findColsData(int cols, const char* value);  
    //�õ�������  
    inline  int     getCols(){ return cols; }  
    //�õ�������  
    inline  int     getRows(){ return data.size(); }  
};  

#endif
