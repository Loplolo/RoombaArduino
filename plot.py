import plotly.graph_objects as go
import pandas as pd

df = pd.read_csv("points.csv", header=0, sep = ",")
fig = go.Figure()
fig.add_trace(go.Scatter(x=df["x"].to_list(), y=df["y"].to_list(), fill="toself"))
fig.show()
