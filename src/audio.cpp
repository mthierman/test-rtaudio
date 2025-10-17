#include "audio.hpp"

#include <algorithm>

Audio::Audio(RtAudio::Api api, RtAudioErrorCallback errorCallback) {
  RtAudio::getCompiledApi(compiledApi);

  controller = std::make_unique<RtAudio>(api);
  controller->showWarnings(true);

  if (errorCallback) {
    controller->setErrorCallback(errorCallback);
  }

  auto defaultOutput{
      controller->getDeviceInfo(controller->getDefaultOutputDevice())};
  auto defaultInput{
      controller->getDeviceInfo(controller->getDefaultInputDevice())};

  output = defaultOutput;
  input = defaultInput;
}

auto Audio::start(uint32_t sampleRate, uint32_t bufferSize) -> void {
  stop();

  output.currentSampleRate = sampleRate;
  input.currentSampleRate = sampleRate;

  RtAudio::StreamParameters outParams;
  outParams.deviceId = output.ID;
  outParams.nChannels = output.outputChannels;

  RtAudio::StreamParameters inputParams;
  inputParams.deviceId = input.ID;
  inputParams.nChannels = input.inputChannels;

  RtAudio::StreamOptions options;
  options.flags = RTAUDIO_SCHEDULE_REALTIME;

  controller->openStream(&outParams, &inputParams, RTAUDIO_FLOAT32, sampleRate,
                         &bufferSize, nullptr, nullptr, &options);
}

auto Audio::stop() -> void {
  if (controller->isStreamOpen()) {
    if (controller->isStreamRunning()) {
      controller->stopStream();
    }

    controller->closeStream();
  }
}

auto Audio::getOutputs() -> std::vector<RtAudio::DeviceInfo> {
  std::vector<RtAudio::DeviceInfo> vec;

  auto ids{controller->getDeviceIds()};
  auto names{controller->getDeviceNames()};

  for (auto id : ids) {
    auto device{controller->getDeviceInfo(id)};

    if (device.outputChannels > 0) {
      vec.push_back(device);
    }
  }

  return vec;
}

auto Audio::getInputs() -> std::vector<RtAudio::DeviceInfo> {
  std::vector<RtAudio::DeviceInfo> vec;

  auto ids{controller->getDeviceIds()};
  auto names{controller->getDeviceNames()};

  for (auto id : ids) {
    auto device{controller->getDeviceInfo(id)};

    if (device.inputChannels > 0) {
      vec.push_back(device);
    }
  }

  return vec;
}
