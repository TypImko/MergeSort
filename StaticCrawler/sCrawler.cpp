#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>
#include <cstdio>
#include <cstdlib>
#include <C:/curlBase/include/curl/curl.h>
#include <stdexcept>
#include "C:/rapidjson-master/include/rapidjson/error/error.h"
#include "C:/rapidjson-master/include/rapidjson/reader.h"
#include <thread>

#include <mutex>

struct ParseException : std::runtime_error, rapidjson::ParseResult {
    ParseException(rapidjson::ParseErrorCode code, const char* msg, size_t offset) : 
        std::runtime_error(msg), 
        rapidjson::ParseResult(code, offset) {}
};

#define RAPIDJSON_PARSE_ERROR_NORETURN(code, offset) \
    throw ParseException(code, #code, offset)

#include <C:/rapidjson-master/include/rapidjson/document.h>
#include <chrono>

using namespace std;
using namespace rapidjson;

bool debug = false;

// Updated service URL
const string SERVICE_URL = "http://hollywood-graph-crawler.bridgesuncc.org/neighbors/";

// Function to HTTP ecnode parts of URLs. for instance, replace spaces with '%20' for URLs
string url_encode(CURL* curl, string input) {
  char* out = curl_easy_escape(curl, input.c_str(), input.size());
  string s = out;
  curl_free(out);
  return s;
}

// Callback function for writing response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Function to fetch neighbors using libcurl with debugging
string fetch_neighbors(CURL* curl, const string& node) {

    string url = SERVICE_URL + url_encode(curl, node);
    string response;

    if (debug)
      cout << "Sending request to: " << url << endl;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Verbose Logging

    // Set a User-Agent header to avoid potential blocking by the server
    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "User-Agent: C++-Client/1.0");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        cerr << "CURL error: " << curl_easy_strerror(res) << endl;
    } else {
      if (debug)
        cout << "CURL request successful!" << endl;
    }

    // Cleanup
    curl_slist_free_all(headers);

    if (debug) 
      cout << "Response received: " << response << endl;  // Debug log

    return (res == CURLE_OK) ? response : "{}";
}

// Function to parse JSON and extract neighbors
vector<string> get_neighbors(const string& json_str) {
    vector<string> neighbors;
    try {
      Document doc;
      doc.Parse(json_str.c_str());
      
      if (doc.HasMember("neighbors") && doc["neighbors"].IsArray()) {
        for (const auto& neighbor : doc["neighbors"].GetArray())
	  neighbors.push_back(neighbor.GetString());
      }
    } catch (const ParseException& e) {
      std::cerr<<"Error while parsing JSON: "<<json_str<<std::endl;
      throw e;
    }
    return neighbors;
}

// BFS Traversal Function
vector<vector<string>> bfs(CURL* curl, const string& start, int depth) {
  vector<vector<string>> levels;
  unordered_set<string> visited;
  
  levels.push_back({start});
  visited.insert(start);

  //My New Variables for Parallelism Here:
  vector<std::thread> sThreads;
  size_t nCount = 1;
  size_t maxThreads = 5;
  vector<vector<string>> cNeighbors;

  mutex threadMutex;

  int startPoint = 0;
  int end = 0;

  //lambda for the threads: 
  auto Frontier = [&] (int de, string& se, int strt, int nd){
    try {
      threadMutex.lock();
      if (debug)
        std::cout<<"Trying to expand"<<se<<"\n";
      vector<string> neighbor = get_neighbors(fetch_neighbors(curl, se));
      for (int i = strt; i < nd; i++) {
        if (debug)
          std::cout<<"neighbor "<<neighbor[i]<<"\n";
        if (!visited.count(neighbor[i])) {
          visited.insert(neighbor[i]);
          levels[de+1].push_back(neighbor[i]);
        }
      }
      threadMutex.unlock();
          } catch (const ParseException& e) {
      std::cerr<<"Error while fetching neighbors of: "<<se<<std::endl;
      throw e;
          }

  };

  for (int d = 0;  d < depth; d++) {
    if (debug)
      std::cout<<"starting level: "<<d<<"\n";
    levels.push_back({});
    //Here is where the Parallelism Starts
    for (string& s : levels[d]) {
      nCount = 0;

      for (const auto& neighbor : get_neighbors(fetch_neighbors(curl, s))) {
        nCount++;
      }
      //Creates maximum number of threads
      for(int i = 0; i < maxThreads; i++){
        //Divides the nodes into threads evenly.
        int maxPerThread = nCount / maxThreads + (i < nCount % maxThreads);
        std::thread cThread (Frontier, d, std::ref(s), startPoint, end);
        sThreads.push_back(std::move(cThread));
        startPoint += maxPerThread;
        end += maxPerThread;
        if(end < nCount)
        {
          end = nCount;
        }
      }

      for (auto & t : sThreads){
        if(t.joinable()){
          t.join();
        } else {
          std::cout<<"The requested thread is DEAD. AND YOU KILLED IT. IT HAD A FAMILY OF STRINGS, YOU MONSTER!" << endl;
        }

      }

     /*
     for(size_t n = 0; i < nodeCount; n++)
     */
    }
    //Here is where the Parallelism Ends.
  }
  
  return levels;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <node_name> <depth>\n";
        return 1;
    }

    string start_node = argv[1];     // example "Tom%20Hanks"
    int depth;
    try {
        depth = stoi(argv[2]);
    } catch (const exception& e) {
        cerr << "Error: Depth must be an integer.\n";
        return 1;
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        cerr << "Failed to initialize CURL" << endl;
        return -1;
    }


    const auto start{std::chrono::steady_clock::now()};
    
    
    for (const auto& n : bfs(curl, start_node, depth)) {
      for (const auto& node : n)
	cout << "- " << node << "\n";
      std::cout<<n.size()<<"\n";
    }
    
    const auto finish{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{finish - start};
    std::cout << "Time to crawl: "<<elapsed_seconds.count() << "s\n";
    
    curl_easy_cleanup(curl);

    
    return 0;
}
