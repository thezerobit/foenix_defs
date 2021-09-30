halfstep_ratio = 2**(1/12)

A2 = 110.0

def calcPSG(freq):
	return round(3579545.0 / (32.0 * freq))

freq = 110.0
for i in range(12):
	print(hex(calcPSG(freq)) + "\n")
	freq = freq * halfstep_ratio
	