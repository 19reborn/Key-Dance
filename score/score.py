from scipy.io import wavfile as wav
from scipy.fftpack import fft
import numpy as np
import subprocess
from math import fabs
import os

# Get 3 input
output_file,wav_file,offset = input().split(' ')
offset = float(offset)
new_wav_file = wav_file[:-4] + '.txt'

# read .wav
rate, data = wav.read(wav_file)
data = np.array(data)
frame = len(data)
    #fft_out = fft(data)
seconds = frame / rate

# 每秒有rate个data
# 以rate/100取样，得到0.01秒为间隔的数据

# write sampled data from .wav to .txt
if not os.path.exists(new_wav_file):
    f = open(new_wav_file,'w')
    stride = int(rate/100)
    f.write(str(len(data[::stride]))+'\n')

    # average
    for i in range(0,frame,stride):
        j = i
        x0,x1 = fabs(data[i][0]),fabs(data[i][1])
        while j+1-i<stride and j+1 <frame :
            j+=1
            x0 += fabs(data[j][0])
            x1 += fabs(data[j][1])

        x0/=(j-i+1);x1/=(j-i+1)
        f.write(str(int(x0))+' '+str(int(x1))+' ')
    '''
    for x in data[::stride]:
        f.write(str(int(x[0]))+' '+str(int(x[1]))+'\n')
    '''
    f.close()
# write args to .exe
f = open("read.txt",'w')
f.write(output_file + ' ' + new_wav_file + ' ' + str(offset))
f.close()

subprocess.Popen("score.exe")
