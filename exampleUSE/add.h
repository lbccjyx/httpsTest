#pragma once
#include <httplib.h>
#include <iostream>



// gbk�����ĺ���תΪutf-8�����ĺ���
std::string stringUTF8(const std::string &str);

// utf-8�����ĺ���תΪgbk�����ĺ���
std::string UTF8string(std::string strTemp);

// UUid ������
std::string GetUUID(std::string &strUUID);

std::string youdao_sha256(std::string yyid, std::string q, std::string salt,
                          std::string sTime, std::string yymy);