#include <iostream>
#include <utility>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <algorithm>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;
using namespace cgicc;

int s_to_int(int x, string y) {
   x = std::stoi(y);
   return x;
}

bool is_notdigit(string arr) 
{ 
	for (int k = 0; k < arr.length(); k++) { 
		if ((int)arr[k]<(int)'0' || 
			(int)arr[k]>(int)'9') { 
			return true; 
		} 
	} 
	return false; 
}

int main() {
    Cgicc cgi;
    

    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>CPS 3525 Project 1</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<h2>Richard Angueira - CPS 3525 Project 1</h2>\n";
    cout << "<br>";

   //*******************************************************************************************************
   //Start NAME
    string uname = cgi("name");
    if (uname == "") {
        cout << "<font color='red'>Please enter your name...</font>" << endl;
    }
    else {
        cout << "Your name is: " << uname << endl;
    }
    cout << "<hr>";

   //*******************************************************************************************************
    //Start GENDER
    string gen = cgi("gender");
    if (gen == "") {
        cout << "<font color='red'>Please select a gender...</font>" << endl;
    }
    else {
        cout << "Your gender is: " << gen << endl;
    }
    cout << "<hr>";

   //*******************************************************************************************************
    //Start BIRTHDAY
   string bdate = cgi("birthday");
   string date[10];
   int cdate = 20231022;
   int x;

   if(bdate == ""){
      cout << "<font color='red'>Please enter your birthdate...</font>" << endl;
   }else{
       //Removes hyphen from date
      for(int i = 0; i < bdate.length(); i++){ 
            if(bdate[i] == '-'){
                date[i];
            }else{
                date[i] = bdate[i]; 
            }
      }

      //*******************************************************************************************************
      //Seperate YEAR, MONTH, DAY
      string a;
      string b;
      string c;
      string year;
      string month;
      string day;
      for (int i = 0; i < 4; i++) {
          year = a.append(date[i]);
      }
      for (int i = 4; i < 7; i++) {
          month = b.append(date[i]);
      }
      for (int i = 7; i < 10; i++) {
          day = c.append(date[i]);
      }

      int y = stoi(year);
      int m = stoi(month);
      int d = stoi(day);

      int cyear = 2023;
      int cmonth = 10;
      int cday = 22;

      //*******************************************************************************************************
      //Calculate correct age
      
      if (cyear < y) {
          cout << "<br><font color='red'>Are you from the future? Please select the correct year.</font>";
      }
      else {
         x = cyear - y;
         if (cmonth < m) {
            x--;
         }
         if (cmonth == m){
            if(cday < d){
               x--;
            }
         }
           
      }
      cout << "Your birthday is : " << bdate << endl;
   }
   cout << "<hr>";

   //*******************************************************************************************************
   //Start AGE
   string age = cgi("age");

   if(age == ""){
      cout << "<font color='red'>You forgot to enter your age...</font>" << endl;
   }else{
      if(is_notdigit(age)){
         cout << "<font color='blue'><b>" << age << "</b></font> <font color='red'>Is not a number. Please enter a number...</font>" << endl;
      }else{
         //Check if age is empty, less than 1, greater than 100
         int userage = s_to_int(userage, age);
         if (userage < 1 || userage > 99) {
            cout << "<font color='red'>Please enter an appropriate age...(Range: 1 to 99)</font>" << endl;
         }else if(x != userage){
            cout << "<font color='red'>Liar!!! Your <b>actual</b> age is: " << x << "</font><br>";
         }else{
            cout << "Your age is: " << userage << endl;
         }
      }
   }
   cout << "<hr>";

//*******************************************************************************************************
//Start COURSES
   string courses[4];
   courses[0] = cgi("CPS1231");
   courses[1] = cgi("CPS2231");
   courses[2] = cgi("CPS2232");
   courses[3] = cgi("CPS3250");
   //Check to see if atleast one checkbox is checked
   if(courses[0] == "" && courses[1] == "" && courses[2] == "" && courses[3] == ""){
      cout << "<font color='red'>You must select atleast ONE course...</font>" << endl;
   }else{
      cout << "Your course is: " << endl;
      cout << "<br><ul style = 'margin:0;'>" << endl;
      for(int i = 0; i < 4; i++){
         if(courses[i] != ""){
            cout << "<li>" << courses[i] << "</li>" << endl;
         }
      }
      cout << "</ul>" << endl;
   }
   cout << "<hr>";

//*******************************************************************************************************
//Start TOWNSHIP SECTION
   string tship = cgi("town");
   if(tship.empty()){
      cout << "<font color='red'>You must select a city...</font>" << endl;
   }else{
      cout << "Your town is: " << tship << endl;
   }
   cout << "<hr>";

//*******************************************************************************************************
//Start STRING SECTION
   string str1 = cgi("mydata");
   pair<char, int> freq[40];
   //Check if user input any values
   if(str1 == ""){
      cout << "<font color='red'>You did not enter a string...</font>" << endl;
   }else{
      cout << "Your string is: " << str1 << endl;
      
      //Sort string by ASCII
      for(int i=0; i<str1.length(); i++)
      {
         for(int j=i+1; j<str1.length(); j++) { 
            if(str1[i]>str1[j])
               {
                  char temp = str1[i];
                  str1[i] = str1[j];
                  str1[j] = temp;
               }
         }
      }
      
      //*******************************************************************************************************
      //Start TABLE
      cout << "<table border = 1 style = 'margin:0;'>" << endl;
      cout << "<br><tr>" << endl;
      cout << "<br><th>Ascii #</th>" << endl; 
      cout << "<th>Char</th>" << endl; 
      cout << "<th>Count</th>" << endl; 
      cout << "</tr>" << endl;
      
      //*******************************************************************************************************
      //Frequency Counter
      int count = 0;
      for (int i = 0; i < str1.length(); i++) {
          count = 0;
          for (int j = 0; j < str1.length(); j++) {

              if (j < i && str1[i] == str1[j]) {
                  break;
              }
              if (str1[i] == str1[j]) {
                  count++;
              }
          }
         //*******************************************************************************************************
          //Table Data
          if (count != 0) {
            //Created char,count pairs
              freq[i] = make_pair(str1[i], count);

              cout << "<tr>";
              cout << "<td>" << int(freq[i].first) << "</td>";
              cout << "<td>" << freq[i].first << "</td>";
              cout << "<td>" << freq[i].second << "</td>";
              cout << "</tr>" << endl;
          }
      }
      cout << "</table><br>";
      //*******************************************************************************************************
      //Find characters with maximum and minimum frequecy
      int max = freq[0].second;
      int min = freq[0].second;
      char max2 = freq[0].first;
      char min2 = freq[0].first;
      
      for (int i = 0; i < 40; i++)
      {
         if(freq[i].second != 0){
            if (max < freq[i].second){
               max = freq[i].second;
               max2 = freq[i].first;  
            }
            if (min > freq[i].second){
               min = freq[i].second;
               min2 = freq[i].first;
            }
         }
      }

      //*******************************************************************************************************
      //Print all maximum
      cout << "Character(s): <font color='blue'>";
      for (int i = 0; i < 40; i++){
         if(max == freq[i].second){
            cout << freq[i].first << endl;
         }
      }
      cout << "</font> ---Maximum count(s): <font color='blue'>" << max << "</font><br>";

      //*******************************************************************************************************
      //Print all minimum
      cout << "Character(s): <font color='blue'>";
      for (int i = 0; i < 40; i++){
         if(min == freq[i].second){
            cout << freq[i].first << endl;
         }
      }
      cout << "</font> ---Minimum count(s): <font color='blue'>" << min << "</font><br>";
        
   }
   
   cout << "</body>\n";
   cout << "</html>\n";

   return 0;
}
