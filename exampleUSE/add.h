#pragma once
#include <httplib.h>
#include <iostream>



// gbk环境的汉字转为utf-8环境的汉字
std::string stringUTF8(const std::string &str);

// utf-8环境的汉字转为gbk环境的汉字
std::string UTF8string(std::string strTemp);

// UUid 的生成
std::string GetUUID(std::string &strUUID);

std::string youdao_sha256(std::string yyid, std::string q, std::string salt,
                          std::string sTime, std::string yymy);