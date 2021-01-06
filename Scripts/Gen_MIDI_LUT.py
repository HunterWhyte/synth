f = open("midi.txt", 'r')

pitches = f.read().rstrip().split("\n")
#I2S3.RealAudioFreq=46.875 KHz
sampleRate = 46875
sineSize = 4096 # 12 bit

f1 = open("MIDI_LUT.txt", 'w')
percentErrors = []
absoluteErrors = []
f1.write("{")
note = 0
for i in pitches:
    jump = (float(i)/(sampleRate))*(sineSize) # frequency/(samplerate*LUTsize) = 12 bits of integer + fractional component
    jump = int(jump*(2**20))# = 12 + 20 = 32 bit integer
    #jump = jump>>24
    #jump = jump<<24
    print(hex(jump))
    f1.write(hex(jump))
    f1.write(", ")

    #error = (jump - round(jump))
    #absoluteErrors.append(error)

    #percentError = abs((error/float(i))*100)
    #percentErrors.append(percentError)

    
    #print("----------------" + str(note) + "----------------")
    #print("absolute error (Hz): " + str(round(error,3)) )
    #print("percent error: "+ str(round(percentError,2)) + "%")
    #f1.write(str((jump*16)))
    #f1.write(", ")
    #note+=1


#averageError = sum(percentErrors)/len(percentErrors)
#print("Average Error: " + str(averageError) + "%")

