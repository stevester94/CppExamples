//Toodledo API access

#include "md5.h"
#include <string>
#include <iostream>
#include <curl/curl.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;


#define APP_TOKEN "api56d886468fd70"
#define APP_ID "ssmackeyTDAPI"
#define USER_ID "td52d2442ce2e79"
#define CACHED_SESSION_TOKEN "td56dc219d4a09d"

string curlData;

string* generateSignature(string userID, string appToken) {
  string* signature = new string(md5(userID + appToken));
  return signature;
}

string* generateKey(string* appToken, string* userPassword, string* sessionToken) {
  string* key = new string(md5(md5(*userPassword) + *appToken + *sessionToken));
  return key;
}

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up) { //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c < size*nmemb; c++) {
        curlData.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}

string* getURL(string & URL) {
  CURL* curl;
  curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
  curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
  // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress

  curl_easy_perform(curl);

  cout << "CURL DATA:" << curlData << endl;

  curl_easy_cleanup(curl);
  curl_global_cleanup();

  return &curlData;
}

string* getTasks(string* key) {
  string url("http://api.toodledo.com/2/tasks/get.php?key=");
  url = url + *key;

  string response = *getURL(url);

  cout << "response: " << response << endl;
  json j = json::parse(response);
  for(auto it = j.begin(); it != j.end(); it++) {
    cout << (*it)["title"].dump() << endl;
  }
}

string* getSessionToken(string* userID, string* signature) {
  string requestURL = "http://api.toodledo.com/2/account/token.php?userid=";
  requestURL = requestURL + *userID + ";appid=" + APP_ID + ";sig=" + *signature;
  string* sessionToken;
  string* response;

  response = getURL(requestURL);

  json j = json::parse(*response);
  sessionToken = new string(j["token"].dump());

  return sessionToken;
}



int main() {
  string userID(USER_ID);
  string appToken(APP_TOKEN);
  string* signature; //MD5 hash of userID and appToken
  string* sessionToken;
  string* key;
  string* password = new string("!");

  signature = generateSignature(userID, appToken);

  cout << *signature << endl;

  sessionToken = getSessionToken(&userID, signature);
  *sessionToken = (CACHED_SESSION_TOKEN); //Because fuck toodledo tokens limiting

  key = generateKey(&appToken, password, sessionToken);

  cout << "key: " << *key << endl;

  getTasks(key);




}
