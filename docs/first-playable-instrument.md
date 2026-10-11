# First playable instrument

[Issue #1](https://github.com/RohSeongmin/DSP/issues/1)

## Purpose and scope

Build a JUCE standalone instrument that plays one sine-wave voice from a physical MIDI keyboard.

JUCE receives MIDI events and passes them to the C++ DSP core. The core generates audio samples, which JUCE sends to the output device. The core does not depend on JUCE types. Both stereo channels carry the same signal; no audio input is required.

Iteration 1 uses immediate note gating. ADSR, advanced repeated-note handling, polyphony, delay, sustain, pitch bend, DAW automation, and preset storage are deferred. Abrupt note changes may produce clicks.

## Requirements

| ID | Requirement |
| --- | --- |
| I1-FR-01 | Generate a sine wave using equal temperament with A4 = 440 Hz. MIDI notes 69 and 81 produce 440 Hz and 880 Hz. |
| I1-FR-02 | Maintain one active voice across all MIDI channels. A positive-velocity Note On replaces the current note. |
| I1-FR-03 | Scale signal amplitude linearly with velocity. Fix master gain at 0.2 for the velocity comparison. |
| I1-FR-04 | Stop only when Note Off matches the active MIDI channel and note number. Ignore other releases. |
| I1-FR-05 | Treat zero-velocity Note On as Note Off. |
| I1-FR-06 | Apply events at their sample offsets within the audio block. Process events at the same offset in delivered order. |
| I1-FR-07 | Output zero-valued samples at startup and from the matching release offset onward. |

For MIDI note number `n` and positive velocity `v`:

```text
frequency_hz = 440 * 2^((n - 69) / 12)
peak_amplitude = 0.2 * v / 127
output_sample = peak_amplitude * sine_sample
```

MIDI 1.0 uses note numbers 0-127 and velocities 0-127. Channels are displayed as 1-16. Use note numbers rather than application-specific octave labels.

The voice is `idle` or `active(channel, note, velocity)`. Releasing the current note does not restore an earlier held note. A repeated Note On for the same channel and pitch replaces velocity; the next matching release stops it. Other MIDI messages leave the voice unchanged.

## Acceptance scenarios

Unless specified otherwise, use MIDI channel 1.

| Input | Expected result |
| --- | --- |
| Press note 69 at velocity 64, then release. | A 440 Hz tone starts, then stops immediately. |
| Press/release note 69, then note 81. | Two tones one octave apart; silence follows each release. |
| Press/release note 69 at velocity 32, then 96. | The second tone has three times the signal amplitude. |
| Press A = 69, press B = 72, release A, release B. | B replaces A, continues after A's release, and stops after B's release. |
| Press A = 69, press B = 72, then release B while holding A. | Output becomes silent; A does not resume. |
| Activate note 69 on channel 1; release note 69 on channel 2. | The channel 1 voice continues. |
| Activate note 69; send Note On 69 with velocity 0. | Output becomes silent. |

Exact velocities are used in controlled checks. The physical demo uses the keyboard's actual gentle/firm velocities.

## Completion

Issue #1 is complete when this specification and the [demo checklist](first-keyboard-demo.md) are reviewed and adopted.

Implementation and evidence are tracked in [#4: setup](https://github.com/RohSeongmin/DSP/issues/4), [#2: MIDI input](https://github.com/RohSeongmin/DSP/issues/2), [#3: oscillator](https://github.com/RohSeongmin/DSP/issues/3), [#5: voice behavior](https://github.com/RohSeongmin/DSP/issues/5), and [#6: demo](https://github.com/RohSeongmin/DSP/issues/6).
