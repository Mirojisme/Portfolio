#!/usr/bin/python

import mysql.connector
import cgi
import numpy as np
import matplotlib
matplotlib.use('WebAgg')
import matplotlib.pyplot as plt,mpld3


print ("Content-type: text/html\r\n\r\n")
print ("")


print ("<HTML>")

def categorize_income(income):
    if income < 20000:
        return "< 20K"
    elif income < 40000:
        return "20-40K"
    elif income < 60000:
        return "40-60K"
    elif income < 80000:
        return "60-80K"
    elif income < 100000:
        return "80-100K"
    else:
        return "> 100K"

mydb = mysql.connector.connect(
    host='imc.kean.edu',
    user='rangueir',
    password='',
    database='2024S_rangueir'
)

cursor = mydb.cursor()

cursor.execute('SELECT income, education_college_or_above, population, county FROM County where income is not null and education_college_or_above is not null')

rows = cursor.fetchall()

income = [row[0] for row in rows]
education_college_or_above = [row[1] for row in rows]
population = [row[2] for row in rows]
county = [row[3] for row in rows]

mydb.close()

fig1, ax = plt.subplots(figsize=(15,8))

scatter = ax.scatter(income, education_college_or_above, s = 2, alpha = 1)
ax.set_title('Scatter Plot of Income vs Education (College or Above)')
ax.set_xlabel('Income')
ax.set_ylabel('Education (College or Above)')

print (mpld3.fig_to_html(fig1, d3_url=None, mpld3_url=None, no_extras=False, template_type='general', figid=None, use_http=False)) 

income_ranges = ['< 20K', '20-40K', '40-60K', '60-80K', '80-100K', '> 100K']
num_counties = {range: 0 for range in income_ranges}
populations = {range: 0 for range in income_ranges}
for row in rows:
    income_range = categorize_income(row[0])
    num_counties[income_range] += 1
    populations[income_range] += row[2] * row[1]

plt.bar(num_counties.keys(), num_counties.values(), label='Population with college or above')
plt.title('Histogram of the number of Counties by Income bracket vs Education (College or Above)')
plt.xlabel('Income')
#plt.xlim([0,120000])
plt.ylabel('Education (college or above)')
plt.savefig('../CPS4721/images/hist1.png')
plt.close()

print ("<img src = '../CPS4721/images/hist1.png' width='75%'>")

plt.bar(populations.keys(), populations.values())
plt.title('Histogram of Total Population with Education (College or Above) in Income Ranges')
plt.xlabel('Income Range')
plt.ylabel('Total Population with Education (College or Above)')
plt.savefig('../CPS4721/images/hist2.png')
plt.close()

print ("<img src = '../CPS4721/images/hist2.png' width='75%'>")

print ("<ul>")
print ("Scatter Plot:")

print ("<li>Advantage: Provides a visual representation of the relationship between income and education_college_or_above ratio in each county. It allows easy identification of trends and patterns.</li>")
print ("<li>Findings: We can observe whether there's a correlation between income levels and the proportion of people with college or higher degrees.</li>")

print ("Histogram of Counties in Each Income Range:")

print ("<li>Advantage: Shows the distribution of counties across different income ranges, providing an overview of income distribution among counties.</li>")
print ("<li>Findings: We can see how many counties fall into each income range, helping to understand the distribution of income levels.</li>")

print ("Histogram of Total Population in Each Income Range:")

print ("<li>Advantage: Illustrates the total population of people with college or above degrees in each income range, providing insights into the distribution of educated population across income levels.</li>")
print ("<li>Findings: We can understand the concentration of educated population within different income brackets.</li>")
print ("</ul>")
#print (mpld3.fig_to_html(fig2, d3_url=None, mpld3_url=None, no_extras=False, template_type='general', figid=None, use_http=False))

print ("</HTML>")
