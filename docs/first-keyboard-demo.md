# First keyboard demo

Record a 20-30 second physical-keyboard demonstration for [issue #6](https://github.com/RohSeongmin/DSP/issues/6), following the [behavior specification](first-playable-instrument.md) from [issue #1](https://github.com/RohSeongmin/DSP/issues/1). Check each item after verification.

## Preparation

- [ ] Record the code revision, JUCE version, compiler, and build/run commands.
- [ ] Record the keyboard model, connection method, MIDI input, audio output device, sample rate, and block size.
- [ ] Set master gain to 0.2. Keep recording and playback levels unchanged.

## Recording sequence

Use MIDI note numbers and the same channel throughout.

| Action | Expected result |
| --- | --- |
| Start with all keys released. | Silence. |
| Hold note 69, then release. | A steady tone starts and stops. |
| Press/release note 69, then note 81. | The second tone is one octave higher. |
| Play note 69 gently, then firmly, releasing between presses. | Reported velocity and audible strength increase. |
| Press A = 69, press B = 72, release A, release B. | B replaces A, continues after A's release, and stops after B's release. |
| End with all keys released. | Silence continues. |

## Evidence

- [ ] Save audible output with visible physical key presses or synchronized MIDI-event evidence identifying the input device.
- [ ] Record the gentle/firm velocities. If the keyboard cannot produce different velocities, leave this check incomplete.
- [ ] Include setup details and the measured 440 Hz result from [issue #3](https://github.com/RohSeongmin/DSP/issues/3).
- [ ] Confirm that the final captured application output is silent; distinguish ambient noise from that output.
- [ ] Record clicks, other limitations, and remaining work across the six Iteration 1 issues.

[Issue #5](https://github.com/RohSeongmin/DSP/issues/5) separately verifies channel matching, zero-velocity Note On, event offsets/order, and amplitude ratios with controlled events.
