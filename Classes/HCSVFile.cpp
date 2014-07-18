#include "HCSVFile.h"  
using namespace cocos2d;  
  
//获取指定行列的数据
const char* HCSVFile::getData(int rows,int cols)  
{  
    if (rows<0||rows>=data.size()||cols<0||cols>=data[rows].size()) {  
        return "";  
    }  
    
    return data[rows][cols].c_str();  
}  

////获取指定数据的列下标
//int  HCSVFile::findColsData(int cols,const char* value)  
//{  
//    for (int i=0; i<data.size(); i++) {  
//        if (strcmp(getData(i, cols), value)==0 )  
//        {  
//            return i;  
//        }  
//    }  
//    return -1;  
//}
//解析CSV文件
bool HCSVFile::openFile(const char* fileName)  
{  
	std::string block = FileUtils::getInstance()->getStringFromFile(fileName);
	std::vector<std::string> line;
	StringSplit(block, line, '\n');
    for(int i = 1; i < line.size(); i++)
    {
        std::vector<std::string> field; 
		StringSplit(line[i], field, ',');
        data.push_back(field);
        cols= (int)field.size();
    }/*
	in.close();
	in.clear();*/


    /*auto sharedFileUtils = FileUtils::getInstance();
	auto filename = String::createWithFormat(fileName);
	std::string ret = sharedFileUtils->fullPathForFilename(filename->getCString());
    
	
	unsigned char* pBuffer = NULL;
    unsigned long bufferSize = 0;
    pBuffer = CCFileUtils::sharedFileUtils()->getFileData(ret.c_str(), "r", &bufferSize);
    
    std::string s = (char *)pBuffer;
    std::string str = s.substr(0, bufferSize); 
    
    std::vector<std::string> line;
    StringSplit(str, line, '\n');
    for(int i = 0; i < line.size(); i++)
    {
        std::vector<std::string> field; 
        split(field,line[i]); 
        data.push_back(field);
        cols=max(cols, (int)field.size());
    }*/
    return true;  
}  
void HCSVFile::StringSplit( const std::string & str, std::vector<std::string> & tokens, const char & delimiters)
{
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}
//
//void HCSVFile::split(std::vector<std::string>& field,std::string line)
//{
//    std::string fld;
//    int i, j;
//    
//    if (line.length() == 0)
//        return ;
//    i = 0;
//    
//    do {
//        if (i < line.length() && line[i] == '"')
//            j = advquoted(line, fld, ++i);
//        else
//            j = advplain(line, fld, i);
//        
//        field.push_back(fld);
//        i = j + 1;
//    } while (j < line.length());
//    
//}
//
//int HCSVFile::advquoted(const std::string& s, std::string& fld, int i)
//{
//    int j;
//    fld = "";
//    for (j = i; j < s.length(); j++)
//    {
//        if (s[j] == '"' && s[++j] != '"')
//        {
//            int k = s.find_first_of(fieldsep, j);
//            if (k > s.length())
//                k = s.length();
//            for (k -= j; k-- > 0; )
//                fld += s[j++];
//            break;
//        }
//        fld += s[j];
//    }
//    return j;
//}
//
//int HCSVFile::advplain(const std::string& s, std::string& fld, int i)
//{
//    int j;
//    j = s.find_first_of(fieldsep, i);
//    if (j > s.length())
//        j = s.length();
//    fld = std::string(s, i, j-i);
//    return j;
//}

//析构函数，释放内存
HCSVFile::~HCSVFile()
{
    for (int i=0; i<data.size(); i++) {
        data[i].clear();
    }
    data.clear();
}
