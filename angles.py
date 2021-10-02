import math

with open("trig.h", "w") as f:
	f.write("i16_t Sin[64] = {")
	for i in range(64):
		x = round(math.sin((i/64) * (math.pi * 2)) * 256)
		if i % 8 == 0:
			f.write("\n    ")
		f.write("{}".format(x))
		if i < 63:
			f.write(", ")
	f.write("};\n")
	f.write("i16_t Cos[64] = {")
	for i in range(64):
		x = round(math.cos((i/64) * (math.pi * 2)) * 256)
		if i % 8 == 0:
			f.write("\n    ")
		f.write("{}".format(x))
		if i < 63:
			f.write(", ")
	f.write("};\n")
