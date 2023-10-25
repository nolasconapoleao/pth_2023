#pragma once

#include <string>
#include "curl/include/curl/curl.h"

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    (static_cast<std::string *>(userp))->append(static_cast<char *>(contents), size * nmemb);
    return size * nmemb;
}

std::string get_request(const std::string &request_url, const std::string &userpassword = "") {
  CURL *curl;
  CURLcode res;
  std::string buffer;

  curl = curl_easy_init();
  if(curl) {
    struct curl_slist *chunk = NULL;

    /* Remove a header curl would otherwise add by itself */
    chunk = curl_slist_append(chunk, "Accept:");

    /* Modify a header curl otherwise adds differently */
    // chunk = curl_slist_append(chunk, "Host: swapi.dev");

    /* set our custom set of headers */
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    curl_easy_setopt(curl, CURLOPT_URL, request_url.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

    if(userpassword != "") {
        curl_easy_setopt(curl, CURLOPT_USERNAME, userpassword.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);

    /* free the custom headers */
    curl_slist_free_all(chunk);
  }

  return buffer;
}

int post_request(const std::string &request_url, const std::string &body) {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    struct curl_slist *chunk = NULL;
    std::string buffer;

    /* Remove a header curl would otherwise add by itself */
    chunk = curl_slist_append(chunk, "Accept:");
    chunk = curl_slist_append(chunk, "Content-Type: application/json");

    /* set our custom set of headers */
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    curl_easy_setopt(curl, CURLOPT_URL, request_url.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);

    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);

    /* free the custom headers */
    curl_slist_free_all(chunk);
  }

  return res;
}
