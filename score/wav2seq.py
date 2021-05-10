from scipy.io import wavfile as wav
from scipy.fftpack import fft
import subprocess
import numpy as np


wavs= "You_Autumn"
out = "./song_sampled/"+wavs+"_sampled"+".txt"
wavs+=".wav"
rate, data = wav.read(wavs)
frame = len(data)
#fft_out = fft(data)
seconds = frame / rate

# 每秒有rate个data
# 以rate/100取样，得到0.01秒为间隔的数据

f = open(out,'w+')
f.write(str(len(data[::int(rate/100)]))+' ')
for x in data[::int(rate/100)]:
    f.write(str(int(x[0]))+' '+str(int(x[1]))+' ')

