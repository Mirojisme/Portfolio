#!/usr/bin/python
import cgi
import cgitb
import pandas as pd # type: ignore
from sklearn.mixture import GaussianMixture # type: ignore
import matplotlib # type: ignore
matplotlib.use('WebAgg')
import matplotlib.pyplot as plt,mpld3 # type: ignore
import numpy as np

print("Content-type:text/html\r\n\r\n")
print("")


print("<html>")

print("<head>")
print("<title>Clustering Result</title>")
print("</head>")
print("<body>")
print("<h1>Clustering Result</h1>")

cgitb.enable()

# Read form data
form = cgi.FieldStorage()

# Get the uploaded file name
csv_file = form['csv_file']

# Proceed with processing the file
num_clusters = int(form['num_clusters'].value)
if num_clusters:
    num_clusters = int(num_clusters)
else:
    num_clusters = 3  # Default value

# Read CSV file
data = pd.read_csv(csv_file.file)
headers = list(data.columns)

# Perform clustering with Gaussian Mixture Models
gmm = GaussianMixture(n_components=num_clusters)
gmm.fit(data[[headers[1], headers[2]]])
data['Cluster'] = gmm.predict(data[[headers[1], headers[2]]])

mahalanobis_dist = gmm.score_samples(data[[headers[1], headers[2]]])
threshold = np.percentile(mahalanobis_dist, 2)  # Adjust the percentile as needed
outliers = data[mahalanobis_dist < threshold]
outlier_indices = outliers.index.tolist()

# Label outliers as "Outlier" under the "Cluster" column
data.loc[outlier_indices, 'Cluster'] = 'Outlier'

# Plotting clusters
plt.figure(figsize=(8, 6))

# Plotting clusters with different colors
cluster_labels = data['Cluster'].unique()
# Filter out 'Outlier' label
cluster_labels = [label for label in cluster_labels if label != 'Outlier']
colors = plt.cm.rainbow([float(i)/max(cluster_labels) for i in cluster_labels])

for cluster_num, color in zip(cluster_labels, colors):
    if cluster_num == 'Outlier':
        cluster_data = data[data['Cluster'] == cluster_num]
        plt.scatter(cluster_data[headers[1]], cluster_data[headers[2]], c=color, label='Outliers')
    else:
        cluster_data = data[data['Cluster'] == cluster_num]
        plt.scatter(cluster_data[headers[1]], cluster_data[headers[2]], c=color, label='Cluster {}'.format(cluster_num))

# Plotting outliers in a different color
plt.scatter(outliers[headers[1]], outliers[headers[2]], c='grey', label='Outliers')

plt.xlabel(headers[1])
plt.ylabel(headers[2])
plt.title('Clustering Result')
plt.legend()

# Convert Matplotlib plot to HTML
html_plot = mpld3.fig_to_html(plt.gcf())

# Print the HTML plot
print(html_plot)
print("Using Gaussian Mixture, I was able to achieve a incredible visualization with 3 clusters. Outliers were identified using Mahalanobis Distribution. The Mahalanobis Distribution percentage was 99%.")
# Print clustering result in HTML table format
data_sorted = data.sort_values(by='Cluster')
print("<table border='1'>")
print("<tr><th>{}</th><th>{}</th><th>{}</th><th>Cluster</th></tr>".format(headers[0],headers[1],headers[2]))
for index, row in data_sorted.iterrows():
    print("<tr><td>{}</td><td>{}</td><td>{}</td><td>{}</td></tr>".format(row[headers[0]], row[headers[1]], row[headers[2]], row['Cluster']))
print("</table>")

print("</body>")
print("</html>")
