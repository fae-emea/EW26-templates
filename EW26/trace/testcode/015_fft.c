#include "test_config.h"
#ifdef TEST_015_FFT

#define MAX_TEST	(1000)

#include "stdint.h"

void cdft(int n, int isgn, double *a)
{
  void bitrv2(int n, double *a);
  void bitrv2conj(int n, double *a);
  void cftfsub(int n, double *a);
  void cftbsub(int n, double *a);
  
  if (n > 4) {
    if (isgn >= 0) {
      bitrv2(n, a);
      cftfsub(n, a);
    } else {
      bitrv2conj(n, a);
      cftbsub(n, a);
    }
  } else if (n == 4) {
    cftfsub(n, a);
  }
}


/* -------- child routines -------- */


#include <math.h>
#ifndef M_PI_2
#define M_PI_2      1.570796326794896619231321691639751442098584699687
#endif
#ifndef WR5000  /* cos(M_PI_2*0.5000) */
#define WR5000      0.707106781186547524400844362104849039284835937688
#endif
#ifndef WR2500  /* cos(M_PI_2*0.2500) */
#define WR2500      0.923879532511286756128183189396788286822416625863
#endif
#ifndef WI2500  /* sin(M_PI_2*0.2500) */
#define WI2500      0.382683432365089771728459984030398866761344562485
#endif


#ifndef RDFT_LOOP_DIV  /* control of the RDFT's speed & tolerance */
#define RDFT_LOOP_DIV 64
#endif

#ifndef DCST_LOOP_DIV  /* control of the DCT,DST's speed & tolerance */
#define DCST_LOOP_DIV 64
#endif


void bitrv2(int n, double *a)
{
  int j0, k0, j1, k1, l, m, i, j, k;
  double xr, xi, yr, yi;
  
  l = n >> 2;
  m = 2;
  while (m < l) {
    l >>= 1;
    m <<= 1;
  }
  if (m == l) {
    j0 = 0;
    for (k0 = 0; k0 < m; k0 += 2) {
      k = k0;
      for (j = j0; j < j0 + k0; j += 2) {
        xr = a[j];
        xi = a[j + 1];
        yr = a[k];
        yi = a[k + 1];
        a[j] = yr;
        a[j + 1] = yi;
        a[k] = xr;
        a[k + 1] = xi;
        j1 = j + m;
        k1 = k + 2 * m;
        xr = a[j1];
        xi = a[j1 + 1];
        yr = a[k1];
        yi = a[k1 + 1];
        a[j1] = yr;
        a[j1 + 1] = yi;
        a[k1] = xr;
        a[k1 + 1] = xi;
        j1 += m;
        k1 -= m;
        xr = a[j1];
        xi = a[j1 + 1];
        yr = a[k1];
        yi = a[k1 + 1];
        a[j1] = yr;
        a[j1 + 1] = yi;
        a[k1] = xr;
        a[k1 + 1] = xi;
        j1 += m;
        k1 += 2 * m;
        xr = a[j1];
        xi = a[j1 + 1];
        yr = a[k1];
        yi = a[k1 + 1];
        a[j1] = yr;
        a[j1 + 1] = yi;
        a[k1] = xr;
        a[k1 + 1] = xi;
        for (i = n >> 1; i > (k ^= i); i >>= 1);
      }
      j1 = j0 + k0 + m;
      k1 = j1 + m;
      xr = a[j1];
      xi = a[j1 + 1];
      yr = a[k1];
      yi = a[k1 + 1];
      a[j1] = yr;
      a[j1 + 1] = yi;
      a[k1] = xr;
      a[k1 + 1] = xi;
      for (i = n >> 1; i > (j0 ^= i); i >>= 1);
    }
  } else {
    j0 = 0;
    for (k0 = 2; k0 < m; k0 += 2) {
      for (i = n >> 1; i > (j0 ^= i); i >>= 1);
      k = k0;
      for (j = j0; j < j0 + k0; j += 2) {
        xr = a[j];
        xi = a[j + 1];
        yr = a[k];
        yi = a[k + 1];
        a[j] = yr;
        a[j + 1] = yi;
        a[k] = xr;
        a[k + 1] = xi;
        j1 = j + m;
        k1 = k + m;
        xr = a[j1];
        xi = a[j1 + 1];
        yr = a[k1];
        yi = a[k1 + 1];
        a[j1] = yr;
        a[j1 + 1] = yi;
        a[k1] = xr;
        a[k1 + 1] = xi;
        for (i = n >> 1; i > (k ^= i); i >>= 1);
      }
    }
  }
}


void bitrv2conj(int n, double *a)
{
  int j0, k0, j1, k1, l, m, i, j, k;
  double xr, xi, yr, yi;
  
  l = n >> 2;
  m = 2;
  while (m < l) {
    l >>= 1;
    m <<= 1;
  }
  if (m == l) {
    j0 = 0;
    for (k0 = 0; k0 < m; k0 += 2) {
      k = k0;
      for (j = j0; j < j0 + k0; j += 2) {
        xr = a[j];
        xi = -a[j + 1];
        yr = a[k];
        yi = -a[k + 1];
        a[j] = yr;
        a[j + 1] = yi;
        a[k] = xr;
        a[k + 1] = xi;
        j1 = j + m;
        k1 = k + 2 * m;
        xr = a[j1];
        xi = -a[j1 + 1];
        yr = a[k1];
        yi = -a[k1 + 1];
        a[j1] = yr;
        a[j1 + 1] = yi;
        a[k1] = xr;
        a[k1 + 1] = xi;
        j1 += m;
        k1 -= m;
        xr = a[j1];
        xi = -a[j1 + 1];
        yr = a[k1];
        yi = -a[k1 + 1];
        a[j1] = yr;
        a[j1 + 1] = yi;
        a[k1] = xr;
        a[k1 + 1] = xi;
        j1 += m;
        k1 += 2 * m;
        xr = a[j1];
        xi = -a[j1 + 1];
        yr = a[k1];
        yi = -a[k1 + 1];
        a[j1] = yr;
        a[j1 + 1] = yi;
        a[k1] = xr;
        a[k1 + 1] = xi;
        for (i = n >> 1; i > (k ^= i); i >>= 1);
      }
      k1 = j0 + k0;
      a[k1 + 1] = -a[k1 + 1];
      j1 = k1 + m;
      k1 = j1 + m;
      xr = a[j1];
      xi = -a[j1 + 1];
      yr = a[k1];
      yi = -a[k1 + 1];
      a[j1] = yr;
      a[j1 + 1] = yi;
      a[k1] = xr;
      a[k1 + 1] = xi;
      k1 += m;
      a[k1 + 1] = -a[k1 + 1];
      for (i = n >> 1; i > (j0 ^= i); i >>= 1);
    }
  } else {
    a[1] = -a[1];
    a[m + 1] = -a[m + 1];
    j0 = 0;
    for (k0 = 2; k0 < m; k0 += 2) {
      for (i = n >> 1; i > (j0 ^= i); i >>= 1);
      k = k0;
      for (j = j0; j < j0 + k0; j += 2) {
        xr = a[j];
        xi = -a[j + 1];
        yr = a[k];
        yi = -a[k + 1];
        a[j] = yr;
        a[j + 1] = yi;
        a[k] = xr;
        a[k + 1] = xi;
        j1 = j + m;
        k1 = k + m;
        xr = a[j1];
        xi = -a[j1 + 1];
        yr = a[k1];
        yi = -a[k1 + 1];
        a[j1] = yr;
        a[j1 + 1] = yi;
        a[k1] = xr;
        a[k1 + 1] = xi;
        for (i = n >> 1; i > (k ^= i); i >>= 1);
      }
      k1 = j0 + k0;
      a[k1 + 1] = -a[k1 + 1];
      a[k1 + m + 1] = -a[k1 + m + 1];
    }
  }
}



void cftfsub(int n, double *a)
{
  void cft1st(int n, double *a);
  void cftmdl(int n, int l, double *a);
  int j, j1, j2, j3, l;
  double x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;
  
  l = 2;
  if (n > 8) {
    cft1st(n, a);
    l = 8;
    while ((l << 2) < n) {
      cftmdl(n, l, a);
      l <<= 2;
    }
  }
  if ((l << 2) == n) {
    for (j = 0; j < l; j += 2) {
      j1 = j + l;
      j2 = j1 + l;
      j3 = j2 + l;
      x0r = a[j] + a[j1];
      x0i = a[j + 1] + a[j1 + 1];
      x1r = a[j] - a[j1];
      x1i = a[j + 1] - a[j1 + 1];
      x2r = a[j2] + a[j3];
      x2i = a[j2 + 1] + a[j3 + 1];
      x3r = a[j2] - a[j3];
      x3i = a[j2 + 1] - a[j3 + 1];
      a[j] = x0r + x2r;
      a[j + 1] = x0i + x2i;
      a[j2] = x0r - x2r;
      a[j2 + 1] = x0i - x2i;
      a[j1] = x1r - x3i;
      a[j1 + 1] = x1i + x3r;
      a[j3] = x1r + x3i;
      a[j3 + 1] = x1i - x3r;
    }
  } else {
    for (j = 0; j < l; j += 2) {
      j1 = j + l;
      x0r = a[j] - a[j1];
      x0i = a[j + 1] - a[j1 + 1];
      a[j] += a[j1];
      a[j + 1] += a[j1 + 1];
      a[j1] = x0r;
      a[j1 + 1] = x0i;
    }
  }
}


void cftbsub(int n, double *a)
{
  void cft1st(int n, double *a);
  void cftmdl(int n, int l, double *a);
  int j, j1, j2, j3, l;
  double x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;
  
  l = 2;
  if (n > 8) {
    cft1st(n, a);
    l = 8;
    while ((l << 2) < n) {
      cftmdl(n, l, a);
      l <<= 2;
    }
  }
  if ((l << 2) == n) {
    for (j = 0; j < l; j += 2) {
      j1 = j + l;
      j2 = j1 + l;
      j3 = j2 + l;
      x0r = a[j] + a[j1];
      x0i = -a[j + 1] - a[j1 + 1];
      x1r = a[j] - a[j1];
      x1i = -a[j + 1] + a[j1 + 1];
      x2r = a[j2] + a[j3];
      x2i = a[j2 + 1] + a[j3 + 1];
      x3r = a[j2] - a[j3];
      x3i = a[j2 + 1] - a[j3 + 1];
      a[j] = x0r + x2r;
      a[j + 1] = x0i - x2i;
      a[j2] = x0r - x2r;
      a[j2 + 1] = x0i + x2i;
      a[j1] = x1r - x3i;
      a[j1 + 1] = x1i - x3r;
      a[j3] = x1r + x3i;
      a[j3 + 1] = x1i + x3r;
    }
  } else {
    for (j = 0; j < l; j += 2) {
      j1 = j + l;
      x0r = a[j] - a[j1];
      x0i = -a[j + 1] + a[j1 + 1];
      a[j] += a[j1];
      a[j + 1] = -a[j + 1] - a[j1 + 1];
      a[j1] = x0r;
      a[j1 + 1] = x0i;
    }
  }
}


void cft1st(int n, double *a)
{
  int j, kj, kr;
  double ew, wn4r, wk1r, wk1i, wk2r, wk2i, wk3r, wk3i;
  double x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;
  
  x0r = a[0] + a[2];
  x0i = a[1] + a[3];
  x1r = a[0] - a[2];
  x1i = a[1] - a[3];
  x2r = a[4] + a[6];
  x2i = a[5] + a[7];
  x3r = a[4] - a[6];
  x3i = a[5] - a[7];
  a[0] = x0r + x2r;
  a[1] = x0i + x2i;
  a[4] = x0r - x2r;
  a[5] = x0i - x2i;
  a[2] = x1r - x3i;
  a[3] = x1i + x3r;
  a[6] = x1r + x3i;
  a[7] = x1i - x3r;
  wn4r = WR5000;
  x0r = a[8] + a[10];
  x0i = a[9] + a[11];
  x1r = a[8] - a[10];
  x1i = a[9] - a[11];
  x2r = a[12] + a[14];
  x2i = a[13] + a[15];
  x3r = a[12] - a[14];
  x3i = a[13] - a[15];
  a[8] = x0r + x2r;
  a[9] = x0i + x2i;
  a[12] = x2i - x0i;
  a[13] = x0r - x2r;
  x0r = x1r - x3i;
  x0i = x1i + x3r;
  a[10] = wn4r * (x0r - x0i);
  a[11] = wn4r * (x0r + x0i);
  x0r = x3i + x1r;
  x0i = x3r - x1i;
  a[14] = wn4r * (x0i - x0r);
  a[15] = wn4r * (x0i + x0r);
  ew = M_PI_2 / n;
  kr = 0;
  for (j = 16; j < n; j += 16) {
    for (kj = n >> 2; kj > (kr ^= kj); kj >>= 1);
    wk1r = cos(ew * kr);
    wk1i = sin(ew * kr);
    wk2r = 1 - 2 * wk1i * wk1i;
    wk2i = 2 * wk1i * wk1r;
    wk3r = wk1r - 2 * wk2i * wk1i;
    wk3i = 2 * wk2i * wk1r - wk1i;
    x0r = a[j] + a[j + 2];
    x0i = a[j + 1] + a[j + 3];
    x1r = a[j] - a[j + 2];
    x1i = a[j + 1] - a[j + 3];
    x2r = a[j + 4] + a[j + 6];
    x2i = a[j + 5] + a[j + 7];
    x3r = a[j + 4] - a[j + 6];
    x3i = a[j + 5] - a[j + 7];
    a[j] = x0r + x2r;
    a[j + 1] = x0i + x2i;
    x0r -= x2r;
    x0i -= x2i;
    a[j + 4] = wk2r * x0r - wk2i * x0i;
    a[j + 5] = wk2r * x0i + wk2i * x0r;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    a[j + 2] = wk1r * x0r - wk1i * x0i;
    a[j + 3] = wk1r * x0i + wk1i * x0r;
    x0r = x1r + x3i;
    x0i = x1i - x3r;
    a[j + 6] = wk3r * x0r - wk3i * x0i;
    a[j + 7] = wk3r * x0i + wk3i * x0r;
    x0r = wn4r * (wk1r - wk1i);
    wk1i = wn4r * (wk1r + wk1i);
    wk1r = x0r;
    wk3r = wk1r - 2 * wk2r * wk1i;
    wk3i = 2 * wk2r * wk1r - wk1i;
    x0r = a[j + 8] + a[j + 10];
    x0i = a[j + 9] + a[j + 11];
    x1r = a[j + 8] - a[j + 10];
    x1i = a[j + 9] - a[j + 11];
    x2r = a[j + 12] + a[j + 14];
    x2i = a[j + 13] + a[j + 15];
    x3r = a[j + 12] - a[j + 14];
    x3i = a[j + 13] - a[j + 15];
    a[j + 8] = x0r + x2r;
    a[j + 9] = x0i + x2i;
    x0r -= x2r;
    x0i -= x2i;
    a[j + 12] = -wk2i * x0r - wk2r * x0i;
    a[j + 13] = -wk2i * x0i + wk2r * x0r;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    a[j + 10] = wk1r * x0r - wk1i * x0i;
    a[j + 11] = wk1r * x0i + wk1i * x0r;
    x0r = x1r + x3i;
    x0i = x1i - x3r;
    a[j + 14] = wk3r * x0r - wk3i * x0i;
    a[j + 15] = wk3r * x0i + wk3i * x0r;
  }
}


void cftmdl(int n, int l, double *a)
{
  int j, j1, j2, j3, k, kj, kr, m, m2;
  double ew, wn4r, wk1r, wk1i, wk2r, wk2i, wk3r, wk3i;
  double x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;
  
  m = l << 2;
  for (j = 0; j < l; j += 2) {
    j1 = j + l;
    j2 = j1 + l;
    j3 = j2 + l;
    x0r = a[j] + a[j1];
    x0i = a[j + 1] + a[j1 + 1];
    x1r = a[j] - a[j1];
    x1i = a[j + 1] - a[j1 + 1];
    x2r = a[j2] + a[j3];
    x2i = a[j2 + 1] + a[j3 + 1];
    x3r = a[j2] - a[j3];
    x3i = a[j2 + 1] - a[j3 + 1];
    a[j] = x0r + x2r;
    a[j + 1] = x0i + x2i;
    a[j2] = x0r - x2r;
    a[j2 + 1] = x0i - x2i;
    a[j1] = x1r - x3i;
    a[j1 + 1] = x1i + x3r;
    a[j3] = x1r + x3i;
    a[j3 + 1] = x1i - x3r;
  }
  wn4r = WR5000;
  for (j = m; j < l + m; j += 2) {
    j1 = j + l;
    j2 = j1 + l;
    j3 = j2 + l;
    x0r = a[j] + a[j1];
    x0i = a[j + 1] + a[j1 + 1];
    x1r = a[j] - a[j1];
    x1i = a[j + 1] - a[j1 + 1];
    x2r = a[j2] + a[j3];
    x2i = a[j2 + 1] + a[j3 + 1];
    x3r = a[j2] - a[j3];
    x3i = a[j2 + 1] - a[j3 + 1];
    a[j] = x0r + x2r;
    a[j + 1] = x0i + x2i;
    a[j2] = x2i - x0i;
    a[j2 + 1] = x0r - x2r;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    a[j1] = wn4r * (x0r - x0i);
    a[j1 + 1] = wn4r * (x0r + x0i);
    x0r = x3i + x1r;
    x0i = x3r - x1i;
    a[j3] = wn4r * (x0i - x0r);
    a[j3 + 1] = wn4r * (x0i + x0r);
  }
  ew = M_PI_2 / n;
  kr = 0;
  m2 = 2 * m;
  for (k = m2; k < n; k += m2) {
    for (kj = n >> 2; kj > (kr ^= kj); kj >>= 1);
    wk1r = cos(ew * kr);
    wk1i = sin(ew * kr);
    wk2r = 1 - 2 * wk1i * wk1i;
    wk2i = 2 * wk1i * wk1r;
    wk3r = wk1r - 2 * wk2i * wk1i;
    wk3i = 2 * wk2i * wk1r - wk1i;
    for (j = k; j < l + k; j += 2) {
      j1 = j + l;
      j2 = j1 + l;
      j3 = j2 + l;
      x0r = a[j] + a[j1];
      x0i = a[j + 1] + a[j1 + 1];
      x1r = a[j] - a[j1];
      x1i = a[j + 1] - a[j1 + 1];
      x2r = a[j2] + a[j3];
      x2i = a[j2 + 1] + a[j3 + 1];
      x3r = a[j2] - a[j3];
      x3i = a[j2 + 1] - a[j3 + 1];
      a[j] = x0r + x2r;
      a[j + 1] = x0i + x2i;
      x0r -= x2r;
      x0i -= x2i;
      a[j2] = wk2r * x0r - wk2i * x0i;
      a[j2 + 1] = wk2r * x0i + wk2i * x0r;
      x0r = x1r - x3i;
      x0i = x1i + x3r;
      a[j1] = wk1r * x0r - wk1i * x0i;
      a[j1 + 1] = wk1r * x0i + wk1i * x0r;
      x0r = x1r + x3i;
      x0i = x1i - x3r;
      a[j3] = wk3r * x0r - wk3i * x0i;
      a[j3 + 1] = wk3r * x0i + wk3i * x0r;
    }
    x0r = wn4r * (wk1r - wk1i);
    wk1i = wn4r * (wk1r + wk1i);
    wk1r = x0r;
    wk3r = wk1r - 2 * wk2r * wk1i;
    wk3i = 2 * wk2r * wk1r - wk1i;
    for (j = k + m; j < l + (k + m); j += 2) {
      j1 = j + l;
      j2 = j1 + l;
      j3 = j2 + l;
      x0r = a[j] + a[j1];
      x0i = a[j + 1] + a[j1 + 1];
      x1r = a[j] - a[j1];
      x1i = a[j + 1] - a[j1 + 1];
      x2r = a[j2] + a[j3];
      x2i = a[j2 + 1] + a[j3 + 1];
      x3r = a[j2] - a[j3];
      x3i = a[j2 + 1] - a[j3 + 1];
      a[j] = x0r + x2r;
      a[j + 1] = x0i + x2i;
      x0r -= x2r;
      x0i -= x2i;
      a[j2] = -wk2i * x0r - wk2r * x0i;
      a[j2 + 1] = -wk2i * x0i + wk2r * x0r;
      x0r = x1r - x3i;
      x0i = x1i + x3r;
      a[j1] = wk1r * x0r - wk1i * x0i;
      a[j1 + 1] = wk1r * x0i + wk1i * x0r;
      x0r = x1r + x3i;
      x0i = x1i - x3r;
      a[j3] = wk3r * x0r - wk3i * x0i;
      a[j3 + 1] = wk3r * x0i + wk3i * x0r;
    }
  }
}

/* random number generator, 0 <= RND < 1 */
#define RND(p) ((*(p) = (*(p) * 7141 + 54773) % 259200) * (1.0 / 259200.0))

void putdata(int nini, int nend, double *a)
{
  int j, seed = 0;
  
  for (j = nini; j <= nend; j++) {
    a[j] = RND(&seed);
  }
}

#define NMAX 64

int test_015(void)
{
  int n = NMAX;
  volatile double result;
  double a[NMAX + 1];
  int i;
  for(i = 0; i < MAX_TEST;i++)
  {
    /* check of CDFT */
    putdata(0, n - 1, a);
    cdft(n, 1, a);
    cdft(n, -1, a);
    result = a[NMAX-1];
    if((int)result != 3)
    {
        for(;;);
    }
  }
	return 0;
}

#endif
