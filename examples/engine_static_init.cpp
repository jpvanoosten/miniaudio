/*
This example demonstrates how to initialize an audio engine and play a sound.

This will play the sound specified on the command line.
*/
#define MINIAUDIO_IMPLEMENTATION
#include "../miniaudio.h"

#include <stdio.h>

#include <memory>

class AudioDeviceImpl
{
public:
    static AudioDeviceImpl& get();

    void playSound(const char* filename)
    {
        ma_engine_play_sound(&engine, filename, NULL);
    }

protected:
    friend std::default_delete<AudioDeviceImpl>;
    AudioDeviceImpl();
    ~AudioDeviceImpl();

private:
    ma_engine engine;
};

struct MakeAudioDevice : AudioDeviceImpl
{
    MakeAudioDevice() : AudioDeviceImpl() {}
};

std::unique_ptr<AudioDeviceImpl> impl = std::make_unique<MakeAudioDevice>();

AudioDeviceImpl& AudioDeviceImpl::get()
{
    //    static AudioDeviceImpl impl;
    return *impl;
}

AudioDeviceImpl::AudioDeviceImpl()
{
    ma_result result;
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine.");
    }
}

AudioDeviceImpl::~AudioDeviceImpl()
{
    ma_engine_uninit(&engine);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("No input file.");
        return -1;
    }

    AudioDeviceImpl::get().playSound(argv[1]);

    printf("Press Enter to quit...");
    getchar();

    return 0;
}
