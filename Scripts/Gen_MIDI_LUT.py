f = open("midi.txt", 'r')

pitches = f.read().rstrip().split("\n")
#I2S3.RealAudioFreq=46.875 KHz
sampleRate = 46875
sineSize = 4096 # for now

f1 = open("MIDI_LUT.txt", 'w')
percentErrors = []
absoluteErrors = []
f1.write("{")
note = 0
for i in pitches:
    jump = (float(i)/(sampleRate))*(sineSize)
    error = (jump - round(jump))
    absoluteErrors.append(error)

    percentError = abs((error/float(i))*100)
    percentErrors.append(percentError)

    print("----------------" + str(note) + "----------------")
    print("absolute error (Hz): " + str(round(error,3)) )
    print("percent error: "+ str(round(percentError,2)) + "%")
    f1.write(str(round(jump*16)))
    f1.write(", ")
    note+=1

averageError = sum(percentErrors)/len(percentErrors)
print("Average Error: " + str(averageError) + "%")
