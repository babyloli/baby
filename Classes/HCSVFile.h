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
    //用以存储数据
     
private:  
	int cols;  
	std::string fieldsep;  
	std::vector<std::vector<std::string>>  data; 

    void StringSplit( const std::string & str, std::vector<std::string> & tokens, const char & delimiters);      
    //void split(std::vector<std::string>& field, std::string line);  
    //int  advplain(const std::string& line, std::string& fld, int);  
    //int  advquoted(const std::string& line, std::string& fld, int);  
    
public:   
    //打开CSV文件  
    bool            openFile(const char* fileName);  
    //根据行列获取数据  
    const   char*   getData(int rows, int cols);  
    //获取指定数据的列下标  
    //int             findColsData(int cols, const char* value);  
    //得到总列数  
    inline  int     getCols(){ return cols; }  
    //得到总行数  
    inline  int     getRows(){ return data.size(); }  
};  

#endif
