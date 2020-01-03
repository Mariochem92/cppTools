#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <string.h>
#include <stdio.h>
#include <chrono>
//#include <QWidget>
//#include <QPushButton>
//#include <QApplication>
using namespace std;
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int main()
{
  char* url=new char[100];
  static const char *pagefilename = "old.html";
  static const char *pagefilename2 = "new.html";
  FILE *pagefile1;
  FILE *pagefile2;
  int flag=0;
  std::cout << "Insert Web Address to update:  "<<"\n";
  std::cin >> url;
  std::cout << "The web address to be recursively check out is: "<<" " <<url<<"\n";
  CURL* curl_handle = curl_easy_init();
  /* set URL to get here */
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
  /* Switch on full protocol/debug output while testing */ 
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);
  /* disable progress meter, set to 0L to enable and disable debug output */ 
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 0L);
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
  /* open the file */ 
  pagefile1 = fopen(pagefilename, "wb");
  if(pagefile1){
    /* write the page body to this file handle */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile1);
    /* get it! */ 
    curl_easy_perform(curl_handle);
    /* close the header file */ 
    fclose(pagefile1);
  }
  /* cleanup curl stuff */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();
  while (flag==0){
	  auto start = std::chrono::high_resolution_clock::now();
	  CURL* curl_handle = curl_easy_init();
//	  /* set URL to get here */
  	  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
//          /* open the file */
          pagefile2 = fopen(pagefilename2, "wb");
          if(pagefile2) {
//           	/* write the page body to this file handle */
            	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile2);
//            	/* get it! */
            	curl_easy_perform(curl_handle);
//            	/* close the header file */
            	fclose(pagefile2);
          }
//          /* cleanup curl stuff */
          curl_easy_cleanup(curl_handle);
          curl_global_cleanup();
//          //CHECK LENGTH OF FILES
          ifstream file1,file2;
          file1.open(pagefilename);
          int c1=0;
          string str1;
          while(true){
          	getline(file1,str1);
                c1++;
		if( file1.eof() ) break;
          }

	  //std::cout<<c1<<'\n';
          file2.open(pagefilename2);
          int c2=0;
          string str2;
          while(!file2.eof()){
          	getline(file2,str2);
                c2++;
          }
          std::cout<<c2<<'\n';
	  if (c1!=c2){
	  	flag=flag+1;std::cout<<"The number of lines has changed "<<"\n";
	  }
	  //move the pointer out of the end of file!!
	  file1.clear();
	  file2.clear();
	  file1.seekg(0, ios::beg); 
	  file2.seekg(0, ios::beg);
//  	  //compare two files line by line
  	  char string1[500], string2[500];
  	  int j = 0;
  	  while(j<c1){
  	  	file1.getline(string1,500);
  	  	file2.getline(string2,500);
  	  	j++;
		
	  //std::cout<<j<<""<<string1<<" "<<'\n';
  	  		if(strcmp(string1,string2) != 0){
	        		std::cout << j << "-th strings are not equal" << "\n";
	        		std::cout << "   " << string1 << "\n";
	        		std::cout << "   " << string2 << "\n";
  	  			flag=flag+1;
  	  		}
  	  }
	  std::cout<<"FLAG "<<flag<<'\n';
	  rename("new.html","old.html");
	  auto finish = std::chrono::high_resolution_clock::now();
	  std::chrono::duration<double> elapsed = finish - start;
	  std::cout << "Elapsed time: " << elapsed.count() << " s\n";
  }
  return 0;
}
