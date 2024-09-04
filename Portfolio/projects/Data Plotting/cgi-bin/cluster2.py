#!/usr/bin/python
import cgi
import cgitb
import pandas as pd # type: ignore
from sklearn.mixture import GaussianMixture # type: ignore
import matplotlib # type: ignore
matplotlib.use('WebAgg')
import matplotlib.pyplot as plt,mpld3 # type: ignore
import numpy as np
import mysql.connector

print("Content-type:text/html\r\n\r\n")
print("")

print("<html>")
print("<head>")
print("<title>Clustering Result</title>")
print("</head>")
print("<body>")
print("<h1>Clustering Result</h1>")

cgitb.enable()

# Connect to MySQL database
mydb = mysql.connector.connect(
    host='imc.kean.edu',
    user='rangueir',
    password='',
    database='datamining'
)

cursor = mydb.cursor()

cursor.execute('select state_name, income_individual_median, home_value from uszips where income_individual_median is not null and home_value is not null group by zip;')

rows = cursor.fetchall()

sn = [row[0] for row in rows]
iim = [row[1] for row in rows]
hv = [row[2] for row in rows]

# Perform clustering with Gaussian Mixture Models
data = np.column_stack((iim, hv))
gmm = GaussianMixture(n_components=4)  # Assuming 2 clusters
cluster = gmm.fit_predict(data)

# Plotting clusters
plt.figure(figsize=(12, 10))

# Plotting clusters with different colors
cluster_labels = np.unique(cluster)
colors = plt.cm.rainbow(np.linspace(0, 1, len(cluster_labels)))

for cluster_num, color in zip(cluster_labels, colors):
    cluster_data = data[cluster == cluster_num]
    plt.scatter(cluster_data[:, 0], cluster_data[:, 1], c=color, label='Cluster {}'.format(cluster_num),s=2)

plt.xlabel('Income Individual Median')
plt.ylabel('Home Value')
plt.title('Clustering Result')
plt.legend()

# Convert Matplotlib plot to HTML
html_plot = mpld3.fig_to_html(plt.gcf())

# Print the HTML plot
print(html_plot)

mydb.close()
print("The goals for selecting the two columns median income and home_value, becuse it seemed that there may be some possibility that the higher an individuals income would be the better chance they would have a higher home value. The clusters do show some correlation between the increased individual income influences home value.")
print("</body>")
print("</html>")
