
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <iomanip>

#include <sstream>
#include <cstdlib>
#include <cstring>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/FormEntry.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;
using namespace cgicc;


struct Object {
    string sequence;
    int x;
    int y;
    int centerX;
    int centerY;
    int size;
    char id;
};


template<typename T>
void detectObjects(vector<vector<T>>& grid, int x, int y, const int width, const int height, Object& p1, int& objectCount, vector<vector<bool>>& visited) {

    if (x < 0 || x >= width || y < 0 || y >= height || visited[x][y] || grid[x][y] != 'T'){
        return;
    }
    visited[x][y] = true;
    grid[x][y] = p1.id;
        
    p1.size++;
    p1.centerX += x;
    p1.centerY += y;

    detectObjects(grid, x + 1, y, width, height, p1, objectCount, visited); // right
    detectObjects(grid, x - 1, y, width, height, p1, objectCount, visited); // left
    detectObjects(grid, x, y + 1, width, height, p1, objectCount, visited); // down
    detectObjects(grid, x, y - 1, width, height, p1, objectCount, visited); // up

    return;
}
void check_host_name(int hostname) { 
   if (hostname == -1) {
      perror("gethostname");
      exit(1);
   }
}
void check_host_entry(struct hostent * hostentry) { 
   if (hostentry == NULL){
      perror("gethostbyname");
      exit(1);
   }
}
void IP_formatter(char *IPbuffer) { 
   if (NULL == IPbuffer) {
      perror("inet_ntoa");
      exit(1);
   }
}


int main() {

    Cgicc cgi;
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>CPS 3525 Project 2</title>\n";
    
    //Style hides file upload section
    cout << "<style>";
    cout << "#myDIV {display: none;}";
    cout << "</style>";

    //Script shows file upload section when button is clicked
    cout << "<script>";
    cout << "function myFunction() {";
    cout << "var x = document.getElementById('myDIV');";
    cout << "if (x.style.display === 'none') {x.style.display = 'block';} else {x.style.display = 'none';";
    cout << "}";
    cout << "}";
    cout << "</script>";


    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<h2>Richard Angueira - CPS 3525 Project 2</h2>\n";
    cout << "Current Date: <p id='stamp'></p>";

    //Show current date and time
    cout << "<script>";
    cout << "var currentDate = new Date();";
    cout << "var datetimeString = currentDate.toLocaleString();"; 
    cout << "document.getElementById('stamp').innerHTML = datetimeString;";
    cout << "</script>";

    //Get user browser info and IP address
    string browser = getenv("HTTP_USER_AGENT");
    cout << "User Browser and OS: " << browser;
    cout << "<br>";
    string address = getenv("REMOTE_ADDR");
    cout << "User IP address: " << address;
    cout << "<br>";

    //Get text from textbox
    string text = cgi("mydata");
    int length = text.size();
    string dim = text;

    for(int i = 0; i < length; i++){
        if(text[i] == ','){
            text[i] = ' ';
        }else if(text[i] == '\n'){
            break;
        }
    }
    cout << "<br>";
    
    //Create object
    Object p1;

    //Save user text to object sequence
    int m = 0;
    for(int i = 4; i < length; i++){
        if(text[i]=='\n' || text[i]==' '){
            continue;
            i = i - 1;
        }else{
            p1.sequence[m] = text[i];
            m++;
        }
    }

    //Get first line of text to get dimensions
    stringstream ss(dim);
    vector<int> h;
    string token;
    while(getline(ss, token, ',')){
        int value;
        std::istringstream(token) >> value;
        h.push_back(value);
    }

    //Save dimensions
    p1.x = h[0];
    p1.y = h[1];

    //Create vector and store grid without first row
    vector<vector<char>> mdarray(p1.x + 1, vector<char>(p1.y + 1));
    int k = 0;
    for(int i = 0; i <= p1.x; i++){
        for(int j = 0; j <= p1.y; j++){
            
            mdarray[i][j] = p1.sequence[k];
            k++;
        }
    }

    //Display dimensions and grid
    cout << "Height: " << p1.x << ", Width: " << p1.y << "<br>";
    cout << "<br>";
    for(int i = 0; i <= p1.x; i++){
        for(int j = 0; j <= p1.y; j++){

            cout << mdarray[i][j] << endl;
            
        }
        cout << "<br>";
    }

    
    vector<vector<char>> textGrid(mdarray.size());
    for (int i = 0; i < mdarray.size(); i++) {
        textGrid[i].resize(mdarray[i].size());
        for (int j = 0; j < mdarray[i].size(); j++) {
            textGrid[i][j] = static_cast<char>(mdarray[i][j]);
        }
    }

    //Send text grid into the recursion function
    vector<vector<float>> details;
    vector<vector<bool>> visited(mdarray.size(), vector<bool>(mdarray[0].size(), false));
    int objectCount = 1;
    for(int i = 0; i <= p1.x; i++){
        for(int j = 0; j <= p1.y; j++){
            if (textGrid[i][j] == 'T' && !visited[i][j]) {
                p1.centerX = 0;
                p1.centerY = 0;
                p1.size = 0;
                p1.id = (char(objectCount + 48));
                float xStart = static_cast<float>(i);
                float yStart = static_cast<float>(j - 1);
                detectObjects(textGrid, i, j, p1.x, p1.y, p1, objectCount, visited);
                p1.centerX /= p1.size;
                p1.centerY /= p1.size;

                float xEnd = static_cast<float>(i);
                float yEnd = static_cast<float>(j);

                float xCenter = static_cast<float>((xStart + xEnd) / 2);
                float yCenter = static_cast<float>((yStart + yEnd) / 2);
                
                cout << textGrid[i][j] << endl;

                //Save values from recursion function into new 'v' vector and push into 'details' vector
                vector<float> v {objectCount, static_cast<float>(yStart), static_cast<float>(xStart), p1.size, static_cast<float>(yCenter), static_cast<float>(xCenter)};
                details.push_back(v);
                objectCount++;
            }else{
                cout << textGrid[i][j] << endl;
            }     
        }
        cout << "<br>";
    }
    
    //display values from details vector
    for(int i = 0; i < details.size(); i++){
        cout << std::fixed << std::setprecision(0) << "Object id " << details[i][0];
        cout << std::fixed << std::setprecision(0) << " starts at (" << details[i][1] <<", " << details[i][2] << "), size: ";  
        cout << std::fixed << std::setprecision(0) << details[i][3];
        cout << std::fixed << std::setprecision(2) << " chars, center at (" << details[i][4] << ", " << details[i][5] << ")";
        cout << "<br>";
    }
    cout << "Total number of objects: " << objectCount - 1;
    

/*-------------------------------------------------------------------File Input-------------------------------------------------------------------------*/
    cout << "<hr>";
    //Button to display hidden section
    cout << "<button onclick='myFunction()'>Click here to see data uploaded from file!</button>";
    cout << "<div id='myDIV'>";

    //Retrieve user uploaded file 
    string file;
    const_file_iterator fileupload = cgi.getFile("objectFile");
    
    //Save data from file as string
    string filedata = fileupload -> getData();
    string filedim = filedata;

    int flength = filedata.size();
    
    //This is all very similar to the first part of the assignment
    Object p2;

    for(int i = 0; i < flength; i++){
        if(filedata[i] == ','){
            filedata[i] = ' ';
        }else if(filedata[i] == '\n'){
            break;
        }
    }

    for(int i = 4; i < flength; i++){
        if(filedata[i]=='\n' || filedata[i]==' '){
            continue;
        }
        p2.sequence += filedata[i]; // Append character to p2.sequence
    }
    
    stringstream ss2(filedim);
    vector<int> g;
    string filetoken;
    while (getline(ss2, filetoken, ',')) {
        int value;
        std::istringstream(filetoken) >> value;
        g.push_back(value);
    }

    p2.x = g[0];
    p2.y = g[1];

    vector<vector<char>> farray(p2.x + 1, vector<char>(p2.y + 1));

    cout << "Height: " << p2.x << ", Width: " << p2.y << "<br>";
    cout << "<br>";
    int l = 0;
    for(int i = 0; i <= p2.x; ++i){
        for(int j = 0; j <= p2.y; ++j){
            
            farray[i][j] = p2.sequence[l];
            
            l++;
        }
    }
    
    for(int i = 0; i <= p2.x; i++){
        for(int j = 0; j <= p2.y; j++){

            cout << farray[i][j] << endl;
            
        }
        cout << "<br>";
    }

    vector<vector<char>> fileGrid(farray.size());
    for (int i = 0; i < farray.size(); i++) {
        fileGrid[i].resize(farray[i].size());
        for (int j = 0; j < farray[i].size(); j++) {
            fileGrid[i][j] = static_cast<char>(farray[i][j]);
        }
    }

    vector<vector<float>> filedetails;
    vector<vector<bool>> fvisited(farray.size(), vector<bool>(farray[0].size(), false));
    int fobjectCount = 1;
    for(int i = 0; i <= p2.x; i++){
        for(int j = 0; j <= p2.y; j++){
            if (fileGrid[i][j] == 'T' && !fvisited[i][j]) {
                p2.centerX = 0;
                p2.centerY = 0;
                p2.size = 0;
                p2.id = (char(fobjectCount + 48));
                float xStart = static_cast<float>(i);
                float yStart = static_cast<float>(j - 1);
                detectObjects(fileGrid, i, j, p2.x, p2.y, p2, fobjectCount, fvisited);
                p2.centerX /= p2.size;
                p2.centerY /= p2.size;

                float xEnd = static_cast<float>(i);
                float yEnd = static_cast<float>(j);

                float xCenter = static_cast<float>((xStart + xEnd) / 2);
                float yCenter = static_cast<float>((yStart + yEnd) / 2);
                
                cout << fileGrid[i][j] << endl;

                vector<float> v {fobjectCount, static_cast<float>(yStart), static_cast<float>(xStart), p2.size, static_cast<float>(yCenter), static_cast<float>(xCenter)};
                filedetails.push_back(v);
                fobjectCount++;
            }else{
                cout << fileGrid[i][j] << endl;
            }     
        }
        cout << "<br>";
    }
    
    for(int i = 0; i < filedetails.size(); i++){
        cout << std::fixed << std::setprecision(0) << "Object id " << filedetails[i][0];
        cout << std::fixed << std::setprecision(0) << " starts at (" << filedetails[i][1] <<", " << filedetails[i][2] << "), size: ";  
        cout << std::fixed << std::setprecision(0) << filedetails[i][3];
        cout << std::fixed << std::setprecision(2) << " chars, center at (" << filedetails[i][4] << ", " << filedetails[i][5] << ")";
        cout << "<br>";
    }
    cout << "Total number of objects: " << fobjectCount - 1;

    cout << "<hr>";

    //Compare text objectCounts and file objectCounts
    if(objectCount - 1 > fobjectCount - 1){
        cout << "File input has " << fobjectCount - 1 << " object(s), and web input has " << objectCount - 1 << " object(s). Web input has a greater number of objects.";
    }else if(objectCount - 1 < fobjectCount - 1){
        cout << "File input has " << fobjectCount - 1 << " object(s), and web input has " << objectCount - 1 << " object(s). File input has a greater number of objects.";
    }else{
        cout << "File input has " << fobjectCount - 1 << " object(s), and web input has " << objectCount - 1 << " object(s). Web input and File input have the same number of objects.";
    }

    cout << "</div>";

    cout << "</body>\n";
    cout << "</html>\n";
    return 0;
}