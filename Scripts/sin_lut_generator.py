import math


f1 = open("sin_LUT.txt", 'w')
f1.write("{")
samples = 4096
intSize = 16
LUT = []
radCoef = 2*math.pi/(samples)
for i in range(samples):
    fullResY = math.sin(radCoef*i)/2 + 0.5
    integerY = int(fullResY*(2**intSize))
    print(integerY)
    LUT.append(integerY)   
    f1.write(str(integerY) + ", ")
print(LUT)