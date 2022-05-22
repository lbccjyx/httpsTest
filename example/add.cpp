#include "add.h"
// gbk环境的汉字转为utf-8环境的汉字
std::string stringUTF8(const std::string &str) {
  int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
  wchar_t *pwBuf = new wchar_t[nwLen + 1];
  ZeroMemory(pwBuf, nwLen * 2 + 2);
  ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
  int nLen =
      ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
  char *pBuf = new char[nLen + 1];
  ZeroMemory(pBuf, nLen + 1);
  ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
  std::string retStr(pBuf);
  delete[] pwBuf;
  delete[] pBuf;
  pwBuf = NULL;
  pBuf = NULL;
  return retStr;
}
// utf-8环境的汉字转为gbk环境的汉字
std::string UTF8string(std::string strTemp) {
  char buf[1024 * 60];
  snprintf(buf, sizeof(buf), u8"%s", strTemp.c_str());
  TCHAR wscBuffer[1024 * 10] = {0};
  MultiByteToWideChar(CP_UTF8, 0, buf, (int)strlen(buf) + 1, wscBuffer,
                      sizeof(wscBuffer) / sizeof(wchar_t));
  memset(buf, 0, 1024 * 9);
  WideCharToMultiByte(CP_ACP, 0, wscBuffer, -1, buf, 1024 * 9, NULL, NULL);
  return buf;
}

// UUid 的生成
std::string GetUUID(std::string &strUUID) {
  strUUID = "";
#if defined(WIN32) || defined(WINCE) || defined(WIN64)
  GUID guid;
  if (!CoCreateGuid(&guid)) {
    char buffer[64] = {0};
    _snprintf_s(buffer, sizeof(buffer),
                //"%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",    //大写
                "%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x", //小写
                guid.Data1, guid.Data2, guid.Data3, guid.Data4[0],
                guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4],
                guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    strUUID = buffer;
  }
#else
  uuid_t uu;
  uuid_generate(uu);
#endif
  return strUUID;
}

//有道签名 sha256(应用ID+input+salt+curtime+应用密钥)；
std::string youdao_sha256(std::string yyid, std::string q, std::string salt,
                          std::string sTime, std::string yymy) {
  std::string sTmpInput;
  if (q.length() > 20) {
    for (int i = 0; i < 10; i++) {
      sTmpInput.push_back(q[i]);
    }

    sTmpInput.append(std::to_string(q.length()));
    for (int i = 0; i < 10; i++) {
      sTmpInput.push_back(q[q.length() - 1 - 10 + i]);
    }
  } else {
    sTmpInput = q;
  }

  return yyid + sTmpInput + salt + sTime + yymy;
}
