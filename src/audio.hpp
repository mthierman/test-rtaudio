#pragma once

#include <memory>
#include <print>
#include <string>
#include <vector>

#include "RtAudio.h"

struct Audio {
  explicit Audio(
      RtAudio::Api api = RtAudio::Api::UNSPECIFIED,
      RtAudioErrorCallback errorCallback = [](RtAudioErrorType type,
                                              const std::string &errorText) {
        //
        std::println("{}", errorText);
      });

  auto start(uint32_t sampleRate = 48000, uint32_t bufferSize = 0) -> void;
  auto stop() -> void;

  auto getOutputs() -> std::vector<RtAudio::DeviceInfo>;
  auto getInputs() -> std::vector<RtAudio::DeviceInfo>;

  std::vector<RtAudio::Api> compiledApi;
  RtAudio::DeviceInfo output;
  RtAudio::DeviceInfo input;

  std::unique_ptr<RtAudio> controller;
};
