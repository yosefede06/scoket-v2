import pandas as pd
import plotly.express as px
t=[0.52247,
   0.04807	,
   2.01005	,
   4.66472	,
   8.51064	,
   17.6503	,
   34.0788	,
   62.3174	,
   95.7009	,
   106.644	,
   112.626	,
   116.047	,
   116.885	,
   117.097	,

   117.471	,
   117.539	,
   117.596	,
   117.64	,
   117.643	,
   117.665	, 117.681]
s = []
a = 1
for line in range(21):
    s.append(a)
    # t.append(line.strip())
    a = 2 * a
d = {'message_size': s, 'throughput': t}
df = pd.DataFrame(data=d)
fig = px.line(pd.DataFrame({'x': df['message_size'], 'y':  df['throughput']}), x="x", y="y",
              title=f"Point-To-Point (Unidirectional) Throughput Over 1,000 Messages Per Size",
              labels={"x": f"Message size (Bytes)", "y": "Throughput (Bytes/Microseconds)"})
fig.update_traces(mode='markers+lines')
fig.show()

