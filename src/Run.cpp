#include "Synth.h"

#include <portaudio.h>

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <thread>
#include <future>

#include "util/FunctionUtils.h"

using namespace fnc;

Synth *synth;

unsigned char* queue = new unsigned char[32];
unsigned char queueSize = 0;

static int callback(const void *inputBuffer, void *outputBuffer,
		unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo,
		PaStreamCallbackFlags statusFlags, void *userData) {

	//Jeezus christ portaudio is actually terrible why do I have to do this
	if (synth == nullptr) {
		cnv::init();

		synth = new Synth();

		fillSine((float*) &(synth->oscillators[0].wavetable->frames[0].samples), 2048);
		//fillTest((float*) &(synth->oscillators[0].wavetable->frames[0].samples), 2048);
		//fillSquare((float*) &(synth->oscillators[0].wavetable->frames[0].samples), 2048);
		//fillSawtooth((float*) &(synth->oscillators[1].wavetable->frames[0].samples), 2048);

		synth->oscillators[0].unison = 1;
		synth->oscillators[1].unison = 1;
		synth->oscillators[2].unison = 1;

		//synth -> channelSystem -> addChannel(67);
	}

	//Check queue
	for (unsigned char i = 0; i < queueSize; i++) {
		if ((queue[i] >> 7) == 1) {
			cout << "Pressed: ";
		} else {
			cout << "Released: ";
		}

		cout << +(queue[i] & 0b01111111) << endl;

		if ((queue[i] >> 7) == 1) {
			synth -> channelSystem -> addChannel(queue[i] & 0b01111111, synth->oscillators, 3);
		} else {
			synth -> channelSystem -> removeChannel(queue[i] & 0b01111111);
		}
	}

	queueSize = 0;

	synth -> sample((float*) outputBuffer);

//	for (int i = 0; i < 256; i++) {
//		cout << ((float*) outputBuffer)[i] << "\n";
//	}
//
//	cout.flush();

	return 0;
}

void inputReader(future<void> exit_signal) {
	int port = open("/dev/tty.usbmodem14101", O_RDWR | O_NDELAY);

	tcflush(port, TCIOFLUSH);

	int available;

	while (exit_signal.wait_for(chrono::milliseconds(1)) == future_status::timeout) {
		ioctl(port, FIONREAD, &available);

		if (available > 0) {
			read(port, queue + queueSize, 1);

			queueSize++;
		}

		this_thread::yield();
	}

	close(port);
}

int main(void) {
	PaStream *stream;

	Pa_Initialize();

	Pa_OpenDefaultStream(
			&stream, 0, /* no input channels */
			1, /* stereo output */
			paFloat32, /* 32 bit floating point output */
			SAMPLE_RATE, 256, /* frames per buffer */
			callback, nullptr);

	Pa_StartStream(stream);

	cout << "Starting" << endl;

	promise<void> exit_signal;
	future<void> future = exit_signal.get_future();

	thread reader(&inputReader, move(future));

	cin.get();

	cout << "Closing" << endl;

	exit_signal.set_value();
	reader.join();

	Pa_StopStream(stream);

	Pa_CloseStream(stream);

	Pa_Terminate();

	delete synth;

	return 0;
}
