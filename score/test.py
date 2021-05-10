from scipy.io import wavfile as wav
from scipy.fftpack import fft
import numpy as np
wav_file="./xndy.WAV"
rate, data = wav.read(wav_file)
data = np.array(data)
frame = len(data)
    #fft_out = fft(data)
seconds = frame / rate
print(seconds)