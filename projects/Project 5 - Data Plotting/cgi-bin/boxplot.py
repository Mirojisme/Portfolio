#!/usr/bin/python
import mysql.connector
import numpy as np
import matplotlib
matplotlib.use('WebAgg')
import matplotlib.pyplot as plt

print ("Content-type: text/html\r\n\r\n")
print ("")


print ("<HTML>")

mydb = mysql.connector.connect(
    host='imc.kean.edu',
    user='rangueir',
    password='',
    database='2024S_rangueir'
)

cursor = mydb.cursor()

cursor.execute("SELECT home_value, education_college_or_above FROM County where home_value is not null and education_college_or_above is not null")
data = cursor.fetchall()
home_value = [row[0] for row in data]
edu_college_above = [row[1] for row in data]

Q1 = np.quantile(home_value, .25)
Q2 = np.quantile(home_value, .50)
Q3 = np.quantile(home_value, .75)
IQR = Q3 - Q1
lower_limit = Q1 - 1.5 * IQR
upper_limit = Q3 + 1.5 * IQR
#outliers = home_value[(home_value < lower_limit) | (home_value > upper_limit)]


plt.figure(figsize=(10, 5))

plt.boxplot(home_value)
plt.title('Boxplot of Home Value')
plt.ylabel('Home Value')
plt.savefig('../CPS4721/images/box1.png')
plt.close()

print ("<img src = '../CPS4721/images/box1.png'>")

print("<br>")
print("Home Value:")
print("<br>")
print("Q1:", Q1)
print("<br>")
print("Q2:", Q2)
print("<br>")
print("Q3:", Q3)
print("<br>")
print("Lower Limit:", lower_limit)
print("<br>")
print("Upper Limit:", upper_limit)
print("<br>")
for element in home_value:
        if element > upper_limit or element < lower_limit:
                print element
                print ("<br>")

eduQ1 = np.quantile(edu_college_above, .25)
eduQ2 = np.quantile(edu_college_above, .50)
eduQ3 = np.quantile(edu_college_above, .75)
eduIQR = eduQ3 - eduQ1
edu_lower_limit = Q1 - 1.5 * eduIQR
edu_upper_limit = Q3 + 1.5 * eduIQR
#outliers = home_value[(home_value < lower_limit) | (home_value > upper_limit)]

plt.figure(figsize=(10, 5))

plt.boxplot(edu_college_above)
plt.title('Boxplot of Education (College or above)')
plt.ylabel('Education')
plt.savefig('../CPS4721/images/box2.png')
plt.close()

print ("<img src = '../CPS4721/images/box2.png'>")

print("<br>")
print("Education (College or above):")
print("<br>")
print("Q1:", eduQ1)
print("<br>")
print("Q2:", eduQ2)
print("<br>")
print("Q3:", eduQ3)
print("<br>")
print("Lower Limit:", edu_lower_limit)
print("<br>")
print("Upper Limit:", edu_upper_limit)
print("<br>")
for eduelement in edu_college_above:
        if eduelement > edu_upper_limit or eduelement < edu_lower_limit:
                print eduelement
                print ("<br>")
print("<ul>")
print("<li>Outliers in home_value attribute may indicate extremely high or low home values compared to the rest of the counties. Similarly, outliers in education_college_or_above attribute may indicate counties with unusually high or low percentages of population with college or above education.</li>")
print("<li>Outliers for these attributes may not necessarily come from the same counties. They might be from different counties depending on various factors such as economic development, educational opportunities, and population demographics.</li>")
print("<li>The state with more outliers could indicate regions with higher variability in home values or education levels.</li>")

print("Factors contributing to outliers could include:")
print("<li>Economic disparities: Counties with booming economies may have higher home values, while economically depressed areas may have lower values.</li>")
print("<li>Educational opportunities: Counties with prestigious universities or strong educational systems may have higher percentages of college-educated residents.</li>")
print("<li>Geographic location: Counties in highly desirable locations (e.g., coastal areas, major cities) may have higher home values.</li>")
print("<li>Population demographics: Counties with significant income disparities or large proportions of transient populations may exhibit outliers in both attributes.</li>")
print("</ul>")
print ("</HTML>")
