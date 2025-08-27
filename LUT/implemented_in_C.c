#include <stdio.h>
#include <stdint.h>

#define FREQ_TMR 84000000UL   // timer frekvencia [Hz]
#define FULL_STEP_DEG 1.8     // fok / lépés
#define MICRO_STEPS 0.125f    // 1/8
#define PI 3.14159265358979323846

// LUT méret
#define LUT_SIZE 100

// Skálázók
#define T_SCALER FREQ_TMR      // idő skálázás (y tengely)
#define THETA_SCALER 1000000UL // szög skálázás (x tengely)

// Egyszerűsített arcsin LUT minta (normálisan Pythonból generálnád és beégetnéd)
int32_t LUT_x[LUT_SIZE] = 
{
            0,   10101,   20202,   30303,   40404,   50505,   60606,
        70707,   80808,   90909,  101010,  111111,  121212,  131313,
        141414,  151515,  161616,  171717,  181818,  191919,  202020,
        212121,  222222,  232323,  242424,  252525,  262626,  272727,
        282828,  292929,  303030,  313131,  323232,  333333,  343434,
        353535,  363636,  373737,  383838,  393939,  404040,  414141,
        424242,  434343,  444444,  454545,  464646,  474747,  484848,
        494949,  505050,  515151,  525252,  535353,  545454,  555555,
        565656,  575757,  585858,  595959,  606060,  616161,  626262,
        636363,  646464,  656565,  666666,  676767,  686868,  696969,
        707070,  717171,  727272,  737373,  747474,  757575,  767676,
        777777,  787878,  797979,  808080,  818181,  828282,  838383,
        848484,  858585,  868686,  878787,  888888,  898989,  909090,
        919191,  929292,  939393,  949494,  959595,  969696,  979797,
        989898, 1000000
};

int32_t LUT_y[LUT_SIZE] =
{
                0,    -848499,   -1697085,   -2545844,   -3394863,
         -4244229,   -5094030,   -5944354,   -6795287,   -7646921,
         -8499343,   -9352645,  -10206917,  -11062251,  -11918740,
        -12776479,  -13635562,  -14496087,  -15358151,  -16221854,
        -17087298,  -17954584,  -18823819,  -19695109,  -20568563,
        -21444293,  -22322412,  -23203036,  -24086286,  -24972283,
        -25861152,  -26753023,  -27648027,  -28546300,  -29447982,
        -30353218,  -31262156,  -32174950,  -33091759,  -34012746,
        -34938082,  -35867942,  -36802510,  -37741975,  -38686535,
        -39636394,  -40591766,  -41552875,  -42519953,  -43493243,
        -44473000,  -45459490,  -46452994,  -47453805,  -48462232,
        -49478601,  -50503254,  -51536554,  -52578883,  -53630649,
        -54692281,  -55764236,  -56847003,  -57941100,  -59047082,
        -60165544,  -61297123,  -62442504,  -63602428,  -64777691,
        -65969160,  -67177773,  -68404555,  -69650624,  -70917207,
        -72205657,  -73517466,  -74854290,  -76217978,  -77610601,
        -79034491,  -80492293,  -81987026,  -83522160,  -85101718,
        -86730410,  -88413802,  -90158563,  -91972782,  -93866446,
        -95852119,  -97945981, -100169480, -102552091, -105136281,
       -107987272, -111214941, -115033700, -119997578, -131946891
};

// Interpoláció LUT-ból (skálázott egész számokkal)
int32_t interpolate_from_LUT(int32_t x) {
    int sign = 1;
    if (x < 0) {
        sign = -1;
        x = -x;
    }

    if (x <= (int32_t)LUT_x[0]) return sign * (int32_t)LUT_y[0];
    if (x >= (int32_t)LUT_x[LUT_SIZE - 1]) return sign * (int32_t)LUT_y[LUT_SIZE - 1];

    // bináris keresés helyett egyszerű lineáris (mert LUT kicsi)
    int idx = 0;
    while (idx < LUT_SIZE - 1 && x > (int32_t)LUT_x[idx+1]) idx++;

    int32_t x0 = LUT_x[idx];
    int32_t x1 = LUT_x[idx+1];
    int32_t y0 = LUT_y[idx];
    int32_t y1 = LUT_y[idx+1];

    // lineáris interpoláció
    int32_t dy = y1 - y0;
    int32_t dx = x1 - x0;
    int32_t dt = x - x0;

    // (dy * dt) / dx
    int32_t y = y0 + (int32_t)((int64_t)dy * dt / dx);

    return sign * y;
}

// Skálázott t_k számítás
int32_t calculate_tk_scaled(int k, int32_t Theta_rad_scaled, int32_t T_scaled, int32_t alpha_rad_scaled) {
    int32_t pi_scaled = (int32_t)(PI * T_SCALER);
    
    int32_t neg_arcsin_arg_scaled = THETA_SCALER - 2 * THETA_SCALER * ((int64_t)k * alpha_rad_scaled) / (Theta_rad_scaled);

    int32_t neg_arcsin_scaled = interpolate_from_LUT(neg_arcsin_arg_scaled);

    int32_t tk_scaled = (int32_t)(( (int64_t)(neg_arcsin_scaled + pi_scaled/2) * T_scaled) / pi_scaled);

    
    return tk_scaled;
}

int main() {
    // Példa paraméterek
    double alpha_deg = FULL_STEP_DEG * MICRO_STEPS;
    double alpha_rad = alpha_deg * PI / 180.0;

    int32_t alpha_rad_scaled = (int32_t)(alpha_rad * THETA_SCALER);

    double Theta_deg = 90.0;
    double Theta_rad = Theta_deg * PI / 180.0;
    int32_t Theta_rad_scaled = (int32_t)(Theta_rad * THETA_SCALER);

    double T_sec = 2.0;
    int32_t T_scaled = (int32_t)(T_sec * T_SCALER);

    int n_steps = (int)(Theta_deg / alpha_deg);

    // t_k és ARR számítás
    int32_t t_k_scaled[n_steps+1];
    for (int k = 0; k <= n_steps; k++) {
        t_k_scaled[k] = calculate_tk_scaled(k, Theta_rad_scaled, T_scaled, alpha_rad_scaled);
    }

    for (int k = 0; k < n_steps; k++) {
        int32_t dt_scaled = t_k_scaled[k+1] - t_k_scaled[k];
        int32_t ARR = dt_scaled  - 1;
        printf("%i\n", ARR);
    }

    return 0;
}
