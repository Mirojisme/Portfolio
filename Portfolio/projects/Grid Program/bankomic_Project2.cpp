// Include necessary libraries for input/output operations, string handling, vectors, file handling, and web-related functionalities.
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
#include <cgicc/FormFile.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace std;
using namespace cgicc;

// Define a structure named Object to represent objects in the grid with various properties.
struct Object {
    string sequence;  // Sequence of characters representing the object.
    int x;  // x-coordinate of the object.
    int y;  // y-coordinate of the object.
    int centerX;  // Center x-coordinate of the object.
    int centerY;  // Center y-coordinate of the object.
    int size;  // Size of the object.
    char id;  // Identifier of the object.
};

// Template function to detect objects in the grid.
template<typename T>
void detectObjects(vector<vector<T>>& grid, int x, int y, const int width, const int height, Object& obj1, int& objectCount, vector<vector<bool>>& visited) {
    // Base case: return if out of bounds, already visited, or not part of an object ('T').
    if (x < 0 || x >= width || y < 0 || y >= height || visited[x][y] || grid[x][y] != 'T') {
        return;
    }
    visited[x][y] = true;  // Mark the current cell as visited.
    grid[x][y] = obj1.id;  // Update the grid with the object ID.
    
    obj1.size++;  // Increment the size of the object.
    obj1.centerX += x;  // Accumulate x-coordinates for center calculation.
    obj1.centerY += y;  // Accumulate y-coordinates for center calculation.

    // Recursively detect objects in all four directions (right, left, up, down).
    detectObjects(grid, x + 1, y, width, height, obj1, objectCount, visited);
    detectObjects(grid, x - 1, y, width, height, obj1, objectCount, visited);
    detectObjects(grid, x, y - 1, width, height, obj1, objectCount, visited);
    detectObjects(grid, x, y + 1, width, height, obj1, objectCount, visited);
}

// Helper function to check hostname and print error if needed.
void checkHostName (int hostname) {
    if (hostname == -1) {
        perror("gethostname");
        exit(1);
    }
}

// Helper function to check host entry and print error if needed.
void checkHostEntry(struct hostent* hostentry) {
    if (hostentry == NULL) {
        perror("gethostbyname");
        exit(1);
    }
}

// Helper function to format IP and print error if needed.
void formatIP(char* IPbuffer) {
    if (NULL == IPbuffer) {
        perror("inet_ntoa");
        exit(1);
    }
}

// Main function for the CGI program.
int main() {
    // Initialize the CGI object.
    Cgicc cgi;
    
    // Send the HTTP header indicating content type as HTML.
    cout << "Content-type:text/html\r\n\r\n";
    cout << "<html>\n";
    cout << "<head>\n";
    cout << "<title>Michael Banko - Project 2</title>\n";
    
    // Hide the file upload section initially using CSS.
    cout << "<style>";
    cout << "#myDIV {display: none;}";
    cout << "</style>";

    // JavaScript function to toggle the visibility of the file upload section.
    cout << "<script>";
    cout << "function hideFileUpload() {";
    cout << "  var myDiv = document.getElementById('myDIV');";
    cout << "  if (myDiv.style.display === 'none') {";
    cout << "    myDiv.style.display = 'block';";
    cout << "  } else {";
    cout << "    myDiv.style.display = 'none';";
    cout << "  }";
    cout << "}";
    cout << "</script>";    

    // Close header tag and open body tag.
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<h2>Michael Banko - Project 2</h2>\n";
    cout << "Current Date and Time: <span id='stamp'></span>";

    // Display the current date and time using JavaScript.
    cout << "<script>";
    cout << "var currentDate = new Date();";
    cout << "var datetimeString = currentDate.toLocaleString();"; 
    cout << "document.getElementById('stamp').innerHTML = datetimeString;";
    cout << "</script>";
    cout << "<br>";

    // Retrieve the user's browser and OS information and display it.
    string userBrowser = getenv("HTTP_USER_AGENT");
    cout << "User Browser and User OS: " << userBrowser;
    cout << "<br>";
    
    // Retrieve the user's IP address and display it.
    string userIPAddress = getenv("REMOTE_ADDR");
    cout << "User IP address: " << userIPAddress;
    cout << "<br>";

    // Retrieve the text data entered by the user.
    string userText = cgi("mydata");
    int length = userText.size();
    string dimensions = userText;

    // Process the input text to remove commas and stop at new lines.
    for (int i = 0; i < length; i++) {
        if (userText[i] == ',') {
            userText[i] = ' ';
        } 
        else if (userText[i] == '\n') {
            break;
        }
    }
    cout << "<br>";
    
    // Create an object instance.
    Object obj1;

    // Save user text to the object's sequence property.
    int j = 0;
    for (int i = 4; i < length; i++) {
        if (userText[i] == '\n' || userText[i] == ' ') {
            continue;
            i = i - 1;
        } 
        else {
            obj1.sequence[j] = userText[i];
            j++;
        }
    }

    // Get the first line of text to determine dimensions.
    stringstream ss(dimensions);
    vector<int> h;
    string token;
    while (getline(ss, token, ',')) {
        int value;
        istringstream(token) >> value;
        h.push_back(value);
    }

    // Store the retrieved dimensions.
    obj1.x = h[0];
    obj1.y = h[1];

    // Create a 2D vector to store the grid without the first row.
    vector<vector<char>> mdarray(obj1.x + 1, vector<char>(obj1.y + 1));
    int m = 0;
    for (int i = 0; i <= obj1.x; i++) {
        for (int k = 0; k <= obj1.y; k++) {
            mdarray[i][k] = obj1.sequence[m];
            m++;
        }
    }

    // Display the dimensions and the grid.
    cout << "Height: " << obj1.x << ", Width: " << obj1.y << "<br>";
    cout << "<br>";
    
    // Loop to retrieve elements
    for (int i = 0; i <= obj1.x; i++) {
        for (int k = 0; k <= obj1.y; k++) {
            cout << mdarray[i][k] << endl;
        }
        cout << "<br>";
    }

    // Convert the grid to a character grid for easier processing.
    vector<vector<char>> textGrid(mdarray.size());
    for (int i = 0; i < mdarray.size(); i++) {
        textGrid[i].resize(mdarray[i].size());

        for (int k = 0; k < mdarray[i].size(); k++) {
            textGrid[i][k] = static_cast<char>(mdarray[i][k]);
        }
    }

    // Prepare to send the text grid to the recursive function to detect objects.
    vector<vector<float>> details;
    vector<vector<bool>> visited(mdarray.size(), vector<bool>(mdarray[0].size(), false));
    int counterObject = 1;
    
    // Iterate through the grid and detect objects.
    for (int i = 0; i <= obj1.x; i++) {
        for (int k = 0; k <= obj1.y; k++) {
            // If a 'T' character is found and it hasn't been visited yet, start object detection.
            if (textGrid[i][k] == 'T' && !visited[i][k]) {
                // Initialize the object properties.
                obj1.centerX = 0;
                obj1.centerY = 0;
                obj1.size = 0;
                obj1.id = static_cast<char>(counterObject + 48);
                float xStart = static_cast<float>(i);
                float yStart = static_cast<float>(k);
                
                // Call the detectObjects function to perform object detection.
                detectObjects(textGrid, i, k, obj1.x, obj1.y, obj1, counterObject, visited);
                
                // Calculate the center of the object.
                obj1.centerX /= obj1.size;
                obj1.centerY /= obj1.size;

                float xEnd = static_cast<float>(i);
                float yEnd = static_cast<float>(k);

                float xCenter = static_cast<float>((xStart + xEnd) / 2);
                float yCenter = static_cast<float>((yStart + yEnd) / 2);
                
                cout << textGrid[i][k] << endl;

            // Save the detected object details.
            vector<float> u {counterObject, static_cast<float>(yStart), static_cast<float>(xStart), obj1.size, static_cast<float>(yCenter), static_cast<float>(xCenter)};
            details.push_back(u);
            counterObject++;
        } 
        else {
            // Output non-'T' characters as is.
            cout << textGrid[i][k] << endl;
        }     
    }
    cout << "<br>";
}

// Display the details of detected objects.
for (int i = 0; i < details.size(); i++) {
    cout << fixed << setprecision(0) << "Object ID " << details[i][0];
    cout << fixed << setprecision(0) << " starts at (" << details[i][1] << ", " << details[i][2] << "), Size: ";  
    cout << fixed << setprecision(0) << details[i][3];
    cout << fixed << setprecision(2) << " Chars, Center at (" << details[i][4] << ", " << details[i][5] << ")";
    cout << "<br>";
}

// Output the total number of detected objects.
cout << "Total Number of Objects: " << counterObject - 1;

// Break line to shift button down
cout << "<br>";

// Button to display the hidden file upload section.
cout << "<button onclick='hideFileUpload()'>Click here to see the data uploaded from the file</button>";
cout << "<div id='myDIV' style='display: none;'>";

// Retrieve user uploaded file.
const_file_iterator fileUpload = cgi.getFile("objectFile");

// Save data from the uploaded file as a string.
string fileData = fileUpload -> getData();
string fileDimensions = fileData;
int fileLength = fileData.size();

// Process the file data similarly to the text data.
Object obj2;

for (int i = 0; i < fileLength; i++) {
    if (fileData[i] == ',') {
        fileData[i] = ' ';
    } 
    else if (fileData[i] == '\n') {
        break;
    }
}

for (int i = 4; i < fileLength; i++) {
    if (fileData[i] == '\n' || fileData[i] == ' ') {
        continue;
    }
    obj2.sequence += fileData[i]; // Append character to obj2.sequence
}

// Parse the file data dimensions.
stringstream ss2(fileDimensions);
vector<int> g;
string fileToken;
while (getline(ss2, fileToken, ',')) {
    int value;
    istringstream(fileToken) >> value;
    g.push_back(value);
}

// Store the retrieved dimensions from file data.
obj2.x = g[0]+1;
obj2.y = g[1]-1;

// Create a 2D vector to represent the file data grid.
vector<vector<char>> fileArray(obj2.x + 1, vector<char>(obj2.y + 1));
int l = 0;
for (int i = 0; i <= obj2.x; ++i) {
    for (int k = 0; k <= obj2.y; ++k) {
        // Ensure that l is within the bounds of obj2.sequence.
        if (l < obj2.sequence.size()) {
            fileArray[i][k] = obj2.sequence[l];
            l++;
        }
    }
}

// Display the file data grid.
cout << "Height: " << obj2.x - 1 << ", Width: " << obj2.y + 1 << "<br>";
cout << "<br>";
for (int i = 0; i <= obj2.x; i++) {
    for (int k = 0; k <= obj2.y; k++) {
        cout << fileArray[i][k] << endl;
    }
    cout << "<br>";
}

// Convert the file data grid to a character grid for easier processing.
vector<vector<char>> fileGrid(fileArray.size());
for (int i = 0; i < fileArray.size(); i++) {
    fileGrid[i].resize(fileArray[i].size());
    for (int k = 0; k < fileArray[i].size(); k++) {
        fileGrid[i][k] = static_cast<char>(fileArray[i][k]);
    }
}

// Prepare to send the file grid to the recursive function to detect objects.
vector<vector<float>> fileDetails;
vector<vector<bool>> fileVisited(fileArray.size(), vector<bool>(fileArray[0].size(), false));
int fileCounterObject = 1;

// Iterate through the file data grid and detect objects.
for (int i = 0; i <= obj2.x; i++) {
    for (int k = 0; k <= obj2.y; k++) {
        // If a 'T' character is found and it hasn't been visited yet, start object detection.
        if (fileGrid[i][k] == 'T' && !fileVisited[i][k]) {
            // Initialize the object properties.
            obj2.centerX = 0;
            obj2.centerY = 0;
            obj2.size = 0;
            obj2.id = static_cast<char>(fileCounterObject + 48);
            float xStart = static_cast<float>(i);
            float yStart = static_cast<float>(k);
            
            // Call the detectObjects function to perform object detection.
            detectObjects(fileGrid, i, k, obj2.x, obj2.y, obj2, fileCounterObject, fileVisited);
            
            // Calculate the center of the object.
            obj2.centerX /= obj2.size;
            obj2.centerY /= obj2.size;

            float xEnd = static_cast<float>(i);
            float yEnd = static_cast<float>(k);

            float xCenter = static_cast<float>((xStart + xEnd) / 2);
            float yCenter = static_cast<float>((yStart + yEnd) / 2);
            
            cout << fileGrid[i][k] << endl;

            // Save the detected object details.
            vector<float> v {fileCounterObject, static_cast<float>(yStart), static_cast<float>(xStart), obj2.size, static_cast<float>(yCenter), static_cast<float>(xCenter)};
            fileDetails.push_back(v);
            fileCounterObject++;
        } 
        else {
            // Output non-'T' characters as is.
            cout << fileGrid[i][k] << endl;
        }     
    }
    cout << "<br>";
}

// Display the details of detected objects in the file data grid.
for (int i = 0; i < fileDetails.size(); i++) {
    cout << fixed << setprecision(0) << "Object ID " << fileDetails[i][0];
    cout << fixed << setprecision(0) << " starts at (" << fileDetails[i][1] <<", " << fileDetails[i][2] << "), Size: ";  
    cout << fixed << setprecision(0) << fileDetails[i][3];
    cout << fixed << setprecision(2) << " Chars, Center at (" << fileDetails[i][4] << ", " << fileDetails[i][5] << ")";
    cout << "<br>";
}

// Output the total number of detected objects in the file data grid.
cout << "Total Number of Objects: " << fileCounterObject - 1;

// Break to move comparison results below the fileGrid
cout << "<br>";

// Compare the number of detected objects in text and file data.
if (counterObject - 1 > fileCounterObject - 1) {
    cout << "File input has " << fileCounterObject - 1 << " object(s), and web input has " << counterObject - 1 << " object(s). Web input has a greater number of objects!";
} 
else if (counterObject - 1 < fileCounterObject - 1) {
    cout << "File input has " << fileCounterObject - 1 << " object(s), and web input has " << counterObject - 1 << " object(s). File input has a greater number of objects!";
} 
else {
    cout << "File input has " << fileCounterObject - 1 << " object(s), and web input has " << counterObject - 1 << " object(s). Web input and File input have the same number of objects!";
}

// Close the hidden file upload section.
cout << "</div>";

// Close the body and HTML tags.
cout << "</body>\n";
cout << "</html>\n";
return 0;
}