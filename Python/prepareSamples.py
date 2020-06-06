# Preps the relevant samples from the initial set of samples

# osc1:
# Lo  :   P_15_Pre1_F0_RR1.wav:  [205702-608161]    @ 87.307 hz
# Mid :   K_59_Pre1_F2_RR1.wav:  [188987-558744]    @ 349.228 hz
# Hi  :  K_107_Pre1_F4_RR1.wav:  [195046-576658]    @ 1396.913 hz

import librosa
import numpy as np

SR = 96000
rootDir = "..\\organ samples\\"

fileLo = rootDir+"1\\P_11_Pre1_F0_RR1.wav"
fileMid= rootDir+"1\\K_59_Pre1_F2_RR1.wav"
fileHi = rootDir+"1\\K_107_Pre1_F4_RR1.wav"

startLo = 205702
endLo = 608161
startMid = 188987
endMid = 558744
startHi = 195046
endHi = 576658

startStop = [[startLo,endLo],[startMid,endMid],[startHi,endHi]]

lo, sr  = librosa.load(fileLo,  sr=SR,mono=True,dtype=float)
mid, sr = librosa.load(fileMid, sr=SR,mono=True,dtype=float)
hi, sr  = librosa.load(fileHi,  sr=SR,mono=True,dtype=float)

samples = [lo,mid,hi]
names = ['Lo','Mid','Hi']
startStop = [[startLo,endLo],[startMid,endMid],[startHi,endHi]]


f = open("..\\Source\\SampleData\\osc1Samples.cpp",'w')
for i in range(len(samples)):
    f.write("float osc1"+names[i]+"[] = {")
    for s in range(startStop[i][0],startStop[i][1]+1):
        if i != startStop[i][1]:
            f.write('{0:.8f}'.format(samples[i][s])+",")
        else:
            f.write('{0:.8f}'.format(samples[i][s]))
    f.write("};\n")
    f.write("\n\n")
f.close();