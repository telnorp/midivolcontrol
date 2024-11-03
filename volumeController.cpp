#include <iostream>
#include <Windows.h>
#include <Mmdeviceapi.h>
#include <Endpointvolume.h>
#include "RtMidi.h"

void SetSystemVolume(float level) 
{
    CoInitialize(nullptr);
    IMMDeviceEnumerator* deviceEnumerator = nullptr;
    CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&deviceEnumerator));
     
    IMMDevice* defaultDevice = nullptr;
    deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
     
    IAudioEndpointVolume* endpointVolume = nullptr;
    defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr, (LPVOID*)&endpointVolume); 
      
    endpointVolume->SetMasterVolumeLevelScalar(level, nullptr);  //0.0-1.0
     
    endpointVolume->Release(); 
    defaultDevice->Release(); 
    deviceEnumerator->Release(); 
    CoUninitialize(); 
} 

// midi check funktio
static void midiCallback(double deltatime, std::vector<unsigned char>* message, void* userData)
{
    if (message->size() == 3) 
    { 
        unsigned char status = message->at(0); 
        unsigned char ccNumber = message->at(1);  
        unsigned char ccValue = message->at(2); 

        if (status == 0xB0 && ccNumber == 0x16) // https://www.rapidtables.com/convert/number/hex-to-decimal.html        
        { 
            //täs numerot eli status 176 ja cc on 
            float volumeLevel = ccValue / 127.0f;  // skaala
            SetSystemVolume(volumeLevel); 
        } 
    } 
} 

int main() 
{
    try 
    {
        RtMidiIn midiIn;
        midiIn.openPort(0);  // avaa eka midi portti
        midiIn.setCallback(&midiCallback); 

        std::cout << "listening on port 22." << std::endl;
        while (true) 
        {
            Sleep(100);  // pää looppi
        }
    }
    catch (RtMidiError& error) 
    {
        error.printMessage();
        #pragma warning(disable:4305)
        #pragma warning(disable:4309)
        return 0x4552524F52;
        #pragma warning(default:4305)
        #pragma warning(default:4309)
    }

    return 0x4F4B;
}