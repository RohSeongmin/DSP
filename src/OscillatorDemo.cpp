#define NOMINMAX
#include <cmath>
#include <vector>
#include <iostream>
#include <limits>
#include <numbers>
#include <windows.h>
#include <mmsystem.h>


const int sampleRate = 48000;
const int length_sec = 3;

std::vector<short> makeSinWave(double frequency, int sampleRate);
bool playAudio(std::vector<short>& samples, int sampleRate);

int main(){
    double frequency = 0;

    while(1){
        std::cout<< "Enter Frequency in Hz (stop: -1): ";
        if(!(std::cin >> frequency)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<< "Frequency must be a number.\n";
        }
        else if (frequency == -1) return -1;
        else if(!std::isfinite(frequency) || frequency <= 0 || frequency >= (sampleRate / 2)){
            std::cout<< "Frequency must be between 0 and half of the sample Rate.\n";
        }
        else break;
    }    
    
    std::vector<short> samples = makeSinWave(frequency, sampleRate);
    
    if(!playAudio(samples, sampleRate)){
        std::cout << "Audio playback failed.\n";
        return 1;
    }

    std::cout << "Finished.\n";
}

std::vector<short> makeSinWave(double frequency, int sampleRate){
        const double pi = std::numbers::pi;
        const double volume = 0.2; // I1-FR-03
        const int sampleCount = sampleRate * length_sec;

        std::vector<short> samples(sampleCount);

        for(int i = 0; i < sampleCount; i++){
            double time = double(i) / sampleRate;
            double sound = volume * std::sin(2 * pi * frequency * time);

            samples[i] = short(sound * 32767);
        }
        
        return samples;
}

bool playAudio(std::vector<short>& samples, int sampleRate){
    WAVEFORMATEX format{};
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = 1; 
    format.nSamplesPerSec = sampleRate;
    format.wBitsPerSample = 16; //sample bit도 변수로 두면 어떨까?
    format.nBlockAlign = format.nChannels * (format.wBitsPerSample / 8); 
    format.nAvgBytesPerSec = sampleRate * format.nBlockAlign;

    HWAVEOUT device{}; // audio output device var
    if (waveOutOpen(&device, WAVE_MAPPER, &format, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) return false;

    WAVEHDR buffer{};
    buffer.lpData = reinterpret_cast<char*>(samples.data());//direct address short* -> char*
    buffer.dwBufferLength = DWORD(samples.size() * sizeof(short)); //data size byte

    if (waveOutPrepareHeader(device, &buffer, sizeof(buffer)) != MMSYSERR_NOERROR){
        waveOutClose(device);
        return false;
    }
    bool success = waveOutWrite(device, &buffer,sizeof(buffer)) == MMSYSERR_NOERROR;
    if (success){
        while ((buffer.dwFlags & WHDR_DONE) == 0) Sleep(10);
    }

    waveOutUnprepareHeader(device, &buffer, sizeof(buffer));
    waveOutClose(device);

    return success;
}