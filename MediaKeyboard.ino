#define ENCODER_OPTIMIZE_INTERRUPTS

#include <Bounce.h>
#include <Encoder.h>

int debounceTime = 10;

Bounce prev      = Bounce(3, debounceTime);
Bounce cyber1    = Bounce(4, debounceTime);
Bounce cyber2    = Bounce(5, debounceTime);
Bounce playPause = Bounce(6, debounceTime);
Bounce next      = Bounce(7, debounceTime);
Bounce mute      = Bounce(10, debounceTime);

Encoder volumeKnob(8, 9);

long volumePos = volumeKnob.read();

void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
}

void loop() {

  long newVolumePos = volumeKnob.read();
  
  playPause.update();
  next.update();
  prev.update();
  mute.update();
  cyber1.update();
  cyber2.update();

  // Buttons
  if (playPause.fallingEdge()) {
    Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
    Keyboard.release(KEY_MEDIA_PLAY_PAUSE);
  }
  if (next.fallingEdge()) {
    Keyboard.press(KEY_MEDIA_NEXT_TRACK);
    Keyboard.release(KEY_MEDIA_NEXT_TRACK);
  }
  if (prev.fallingEdge()) {
    Keyboard.press(KEY_MEDIA_PREV_TRACK);
    Keyboard.release(KEY_MEDIA_PREV_TRACK);
  }
  if (mute.fallingEdge()) {
    Keyboard.press(KEY_MEDIA_MUTE);
    Keyboard.release(KEY_MEDIA_MUTE);
  }
  if (cyber1.fallingEdge()) {
    // If I can't get the door
    Keyboard.write("@channel can anyone get that? I'm occupied.");
    Keyboard.press(KEY_ENTER);
    Keyboard.release(KEY_ENTER);
  }
  if (cyber2.fallingEdge()) {
    // Do something at some point
  }

  // Volume Encoder
  if (newVolumePos > volumePos + 3) {
    Keyboard.press(KEY_MEDIA_VOLUME_DEC);
    Keyboard.release(KEY_MEDIA_VOLUME_DEC);
    volumePos = newVolumePos;
  } else if (newVolumePos < volumePos - 3) {
    Keyboard.press(KEY_MEDIA_VOLUME_INC);
    Keyboard.release(KEY_MEDIA_VOLUME_INC);
    volumePos = newVolumePos;
  }

}
