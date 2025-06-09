import pandas as pd
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

data = pd.read_csv('creditCardClustering/creditCardData.csv')

cleanedData = data.dropna()
cleanedData = cleanedData.drop('CUST_ID',axis=1)

print(cleanedData)