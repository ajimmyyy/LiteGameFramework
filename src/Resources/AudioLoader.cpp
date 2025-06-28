//
// Created by jimmy on 2025/6/27.
//

// #include <AL/al.h>
// #include <sndfile.h>
//
// AudioClip AudioLoader::LoadFromFile(const std::string& path) {
//     SF_INFO sfInfo;
//     SNDFILE* file = sf_open(path.c_str(), SFM_READ, &sfInfo);
//     if (!file)
//         throw std::runtime_error("Failed to load audio: " + path);
//
//     std::vector<short> samples(sfInfo.frames * sfInfo.channels);
//     sf_read_short(file, samples.data(), samples.size());
//     sf_close(file);
//
//     ALuint buffer;
//     alGenBuffers(1, &buffer);
//     ALenum format = (sfInfo.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
//
//     alBufferData(buffer, format, samples.data(), samples.size() * sizeof(short), sfInfo.samplerate);
//
//     return { buffer, static_cast<float>(sfInfo.frames) / sfInfo.samplerate, path };
// }
