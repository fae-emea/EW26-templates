#ifndef _WAVEFORM_H_
#define _WAVEFORM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define PI               (3.1415927f)
#define WAVELENGTH       (160)
#define VOLUME_THRESHOLD (6)
#define VOLUME_MAX       (1.0f)

typedef enum {
  SINE,
  SQUARE,
  RAMP,
  TRIANGLE,
  DC,
} wave_t;

typedef unsigned int vol_t;

extern int gWaveform[], gScaledWave[];

void makeWave(wave_t);
void scaleWave(vol_t);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WAVEFORM_H_ */