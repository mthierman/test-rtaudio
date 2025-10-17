#include "RtAudio.h"
#include <print>

auto wmain() -> int {
  std::vector<RtAudio::Api> compiled_apis;
  RtAudio::getCompiledApi(compiled_apis);

  if (compiled_apis.empty()) {
    std::println("No compiled APIs! Check your RtAudio build options");

    return 1;
  }

  std::println("Compiled APIs:");

  for (auto compiled_api : compiled_apis) {
    auto display_name{RtAudio::getApiDisplayName(compiled_api)};
    auto name{RtAudio::getApiName(compiled_api)};
    std::println("Name: {} - Display Name: {}", display_name, name);
  }

  return 0;
}
