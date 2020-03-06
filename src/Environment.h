#pragma once

namespace aue {

constexpr unsigned int SAMPLE_RATE = 44100;

//SUB_BUFFER_SIZE * 8 should always be a multiple of 256 to allow for 100% utilization of avx load operations
constexpr unsigned short SUB_BUFFER_SIZE = 256;

};

namespace sye {

constexpr unsigned char VOICES = 4; //May not be needed

constexpr bool MONO = false;

};
