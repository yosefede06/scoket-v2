import pandas as pd
import plotly.express as px
import plotly.io as pio
pio.templates.default = "simple_white"
s = []
a = 1
for i in range(21):
    s.append(a)
    a = 2 * a
t = [0.4662, 1.05988, 2.03459, 4.0568, 7.54006, 15.4366, 26.6223,
     71.3489, 143.017, 260.163, 377.164, 663.427, 1220.5, 1730.83,
     2289.23, 4292.38, 6805.4, 11636.4, 13906.8, 12860.9, 11622.2]

d = {'message_size': s, 'throughput': t}
df = pd.DataFrame(data=d)
fig = px.line(pd.DataFrame({'x': df['message_size'], 'y':  df['throughput']}), x="x", y="y",
              title=f"point-to-point (unidirectional) throughput",
              labels={"x": f"Message size (bytes)", "y": "Throughput (bytes/microseconds)"})
fig.update_traces(mode='markers+lines')
fig.show()