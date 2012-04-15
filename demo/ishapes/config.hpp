#ifndef SIMD_DEMO_ISHAPES_CONFIG_HPP
#define SIMD_DEMO_ISHAPES_CONFIG_HPP

#define ISHAPES_B2_DEMO  1
#define ISHAPES_WIDE_FORMAT 1
#define REFRESH_PERIOD 40 //ms
/*
 painter.drawPixmap(15, 300, logo_);
    painter.drawPixmap(200, 10, simd_);
 */
#if  (ISHAPES_WIDE_FORMAT == 1)
#  define IS_WIDTH 501
#  define IS_HEIGHT 361
#  define SIMD_LOGO_X 380
#  define SIMD_LOGO_Y 10
//#  define BRAND_LOGO_X 195
//#  define BRAND_LOGO_Y 300
#  define BRAND_LOGO_X 2
#  define BRAND_LOGO_Y 300
#else
#  define IS_WIDTH  321
#  define IS_HEIGHT 361
#  define SIMD_LOGO_X 200
#  define SIMD_LOGO_Y 1
#  define BRAND_LOGO_X 15
#  define BRAND_LOGO_Y 300
#endif


#endif /* SIMD_DEMO_ISHAPES_CONFIG_HPP */
