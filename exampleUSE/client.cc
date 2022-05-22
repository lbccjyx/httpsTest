//
//  client.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <httplib.h>
#include <iostream>
#include"add.h"
using namespace httplib;

#define CA_CERT_FILE "./client.crt"


// http://fanyi.youdao.com/openapi.do?keyfrom=lewe518&key=70654389&type=data&doctype=json&version=1.1&q=
int main(void) {
#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
  //system("C:\\certmgr.exe /add /c D:/OpenSSL-Win64/bin/cnf/client.crt /s root");
  httplib::SSLClient cli("https://openapi.youdao.com/api"); // https
  cli.set_ca_cert_path(CA_CERT_FILE);
  cli.enable_server_certificate_verification(false);
#else
  auto port = 80;
  httplib::Client cli("https://openapi.youdao.com/api");
#endif
  // std::string GetUUID(std::string &strUUID)
  time_t t;
  time(&t);
  std::string sTime = std::to_string(t);
  std::string sUUID;
  GetUUID(sUUID);


  std::string chineseCharacters = "书包";
  std::string sYyid = "3e5327fa42754c3d";
  std::string sYymy = "26gZryk5SH3xgBh7MYkWySqCWF47juXt";
  std::string sQ = stringUTF8(chineseCharacters);
  std::string sSign = youdao_sha256(sYyid, sQ, sUUID, sTime, sYymy);
  Params dic;
  dic.emplace("q", sQ);
  dic.emplace("from", "auto");
  dic.emplace("to", "auto");
  dic.emplace("appKey", sYyid); //应用ID
  dic.emplace("salt", sUUID);   //uuid，唯一通用识别码
  dic.emplace("sign", sSign); // sha256(应用ID+input+salt+curtime+应用密钥)
  dic.emplace("signType", "v3");
  dic.emplace("curtime", sTime);
  dic.emplace("ext", "");
  dic.emplace("voice", "");
  dic.emplace("strict", "");
  dic.emplace("vocabId", "");

   cli.set_connection_timeout(20);

   std::cout << "detail::params_to_query_str(dic):\n " <<detail::params_to_query_str(dic) << std::endl;
  httplib::Headers headers ;
   //headers={"Content-Type","application/x-www-form-urlencoded"};
  std::string body;

  if (auto res = cli.Get("/", dic, Headers(), Progress())) {
    std::cout << res->status << std::endl;
    std::cout << res->get_header_value("Content-Type") << std::endl;
    std::cout << res->body << std::endl;

      if (res != nullptr) 
      {
          if (res->status != 200) 
          { 
              std::cout << res->status <<std::endl; 
          }
      }else 
      {
        std::cout << "error code: " << res.error() << std::endl;
      }

  }




#ifdef CPPHTTPLIB_OPENSSL_SUPPORT

  auto result = cli.get_openssl_verify_result();
  if (result) {
    std::cout << "verify error: " << X509_verify_cert_error_string(result)<< std::endl;   }
#endif

  std::cout << "程序结束" << std::endl;
  return 0;
}

