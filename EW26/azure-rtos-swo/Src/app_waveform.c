#include <math.h>
#include <stdint.h>

#include "app_waveform.h"

int gWaveform[WAVELENGTH], gScaledWave[WAVELENGTH];

/**
  * @brief  Updates the global waveform according to the selected type
  */
void makeWave(wave_t type)
{
  switch (type)
  {
  case SINE:
    for (int i = 0; i < WAVELENGTH; i++)
    {
      float val = sinf(2 * PI * i / WAVELENGTH);
      gWaveform[i] = (uint16_t)((val + 1) * 2048);
    }
    break;
    
  case SQUARE:
    for(int i = 0; i < (WAVELENGTH / 2); i++)
    {
      gWaveform[i] = 4095;
    }
    for(int i = (WAVELENGTH / 2); i < WAVELENGTH; i++)
    {
      gWaveform[i] = 0;
    }
    break;
    
  case RAMP:
    for (int i = 0; i < WAVELENGTH; i++)
    {
      gWaveform[i] = (i * 4095) / WAVELENGTH;
    }
    break;
    
  case TRIANGLE:
    for (int i = 0; i < (WAVELENGTH / 2); i++)
    {
      gWaveform[i] = (i * 4095) / (WAVELENGTH / 2);
    }
    for (int i = (WAVELENGTH / 2); i < WAVELENGTH; i++)
    {
      gWaveform[i] = 4095 - (((i - (WAVELENGTH / 2)) * 4095) / (WAVELENGTH / 2));
    }
    break;
    
  case DC:
  default:
    break;
  }
}

/**
  * @brief  Scales the global Scaled Waveform
  */
void scaleWave(vol_t volume)
{
  float scale_factor;
  uint32_t i, public_log_volume;
  (void)public_log_volume; /* UNUSED */
  
  scale_factor = VOLUME_MAX * (powf(1.001f, volume) / 60);
  public_log_volume = (uint32_t)(4096 * scale_factor); 

  for (i = 0; i < WAVELENGTH; i++)
  {
    gScaledWave[i] = (uint16_t)((float)gWaveform[i] * scale_factor);
  }

}
