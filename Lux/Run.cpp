//#include <Superpowered.h>

#include <OpenSource/SuperpoweredWindowsAudioIO.h>

#include <SuperpoweredAdvancedAudioPlayer.h>

using namespace Superpowered;

static bool audioProcessing(void* clientdata, float* audio, int numberOfFrames, int samplerate) {
	return true;
}

int main() {
	//Initialize(

	//	"ExampleLicenseKey-WillExpire-OnNextUpdate",

	//	false, // enableAudioAnalysis (using SuperpoweredAnalyzer, SuperpoweredLiveAnalyzer, SuperpoweredWaveform or SuperpoweredBandpassFilterbank)

	//	false, // enableFFTAndFrequencyDomain (using SuperpoweredFrequencyDomain, SuperpoweredFFTComplex, SuperpoweredFFTReal or SuperpoweredPolarFFT)

	//	false, // enableAudioTimeStretching (using SuperpoweredTimeStretching)

	//	false,  // enableAudioEffects (using any SuperpoweredFX class)

	//	true, // enableAudioPlayerAndDecoder (using SuperpoweredAdvancedAudioPlayer or SuperpoweredDecoder)

	//	false, // enableCryptographics (using Superpowered::RSAPublicKey, Superpowered::RSAPrivateKey, Superpowered::hasher or Superpowered::AES)

	//	false  // enableNetworking (using Superpowered::httpRequest)

	//);

	SuperpoweredWindowsAudioIO* audioio = new SuperpoweredWindowsAudioIO(audioProcessing, nullptr, false, true);

	//AdvancedAudioPlayer* player = new AdvancedAudioPlayer(44100, 0, 1, 0);

	//audioio -> start();

	return 0;
}