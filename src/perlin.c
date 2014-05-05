
/*=====================================================*\
  Mercredi 29 mai 2013
  Arash HABIBI
  Perlin.c
  \*=====================================================*/

#include "perlin.h"

//-----------------------------------------------------------

static vector _vector_interpolate (vector v1, vector v2, double blend)
{
    return v_add (v_multiply (1 - blend, v1), v_multiply (blend, v2));
}

//-----------------------------------------------------------
// This is a polynomial function which :
// - for x=0 yields y=0
// - for x=1 yields y=1
// - for x=0 and x=1 has a zero first derivative.

static double _contrast (double x)
{
    return x * x * (3 - 2 * x);
}

//-----------------------------------------------------------
// For alpha=0, the return value is x
// For alpha=1, the return value is y
// For intermediate values -> interpolation

//-----------------------------------------------------------

static double _scalar_cubic_interpolate (vector p, double * grid_values)
{
    double res, fx,fy,fz; // fractional part

    int nx = (int) (floor (p.x));
    int ny = (int) (floor (p.y));
    int nz = (int) (floor (p.z));

    fx = p.x - nx;
    fy = p.y - ny;
    fz = p.z - nz;

    fx = _contrast (fx);
    fy = _contrast (fy);
    fz = _contrast (fz);

    res=0.0;

    res += (1-fx) * (1-fy) * (1-fz) * grid_values[PRLN_000];
    res +=   fx   * (1-fy) * (1-fz) * grid_values[PRLN_100];
    res += (1-fx) *   fy   * (1-fz) * grid_values[PRLN_010];
    res +=   fx   *   fy   * (1-fz) * grid_values[PRLN_110];
    res += (1-fx) * (1-fy) *   fz   * grid_values[PRLN_001];
    res +=   fx   * (1-fy) *   fz   * grid_values[PRLN_101];
    res += (1-fx) *   fy   *   fz   * grid_values[PRLN_011];
    res +=   fx   *   fy   *   fz   * grid_values[PRLN_111];

    return res;
}

//-----------------------------------------------------------

static vector _vector_linear_interpolate (vector p, vector * grid_vectors)
{
    double fx,fy,fz; // fractional part

    int nx = (int) (floor (p.x));
    int ny = (int) (floor (p.y));
    int nz = (int) (floor (p.z));

    fx = p.x - nx;
    fy = p.y - ny;
    fz = p.z - nz;

    fx = _contrast (fx);
    fy = _contrast (fy);
    fz = _contrast (fz);

    vector interp_y0z0 = _vector_interpolate (grid_vectors[PRLN_000], grid_vectors[PRLN_100], fx);
    vector interp_y1z0 = _vector_interpolate (grid_vectors[PRLN_010], grid_vectors[PRLN_110], fx);
    vector interp_y0z1 = _vector_interpolate (grid_vectors[PRLN_001], grid_vectors[PRLN_101], fx);
    vector interp_y1z1 = _vector_interpolate (grid_vectors[PRLN_011], grid_vectors[PRLN_111], fx);

    vector interp_z0 = _vector_interpolate (interp_y0z0, interp_y1z0, fy);
    vector interp_z1 = _vector_interpolate (interp_y0z1, interp_y1z1, fy);

    vector interp_vector = _vector_interpolate (interp_z0, interp_z1, fz);

    return interp_vector;
}


//-----------------------------------------------------------

static void _compute_dot_products (vector p, vector * random_vectors, double * dot_products)
{
    int nx = (int) (floor (p.x));
    int ny = (int) (floor (p.y));
    int nz = (int) (floor (p.z));

    int i;
    for (i = 0; i < 8; i++)
    {
        int nnx = nx, nny = ny, nnz = nz;
        if (i >= 4)
            nnz++;
        if (i % 4 > 1)
            nny++;
        if (i % 2 > 0)
            nnx++;
        vector a = v_new (nnx, nny, nnz);
        vector ap = v_substract (p, a);
        dot_products[i] = v_dot (random_vectors[i], ap);
    }
}

//-----------------------------------------------------------

static void _compute_cross_products(vector p, vector * random_vectors, vector * cross_products)
{
    int nx = (int) (floor (p.x));
    int ny = (int) (floor (p.y));
    int nz = (int) (floor (p.z));

    int i;
    for(i = 0; i < 8; i++)
    {
        int nnx=nx,nny=ny,nnz=nz;
        if (i >= 4)
            nnz++;
        if (i % 4 > 1)
            nny++;
        if (i % 2 > 0)
            nnx++;
        vector a = v_new (nnx, nny, nnz);
        vector ap = v_substract (p, a);
        cross_products[i] = v_cross (random_vectors[i], ap);
    }
}

//-----------------------------------------------------------

static double my_rand (long int x)
{
    x = (x << 13) ^ x;
    return 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0;
}

//-----------------------------------------------------------
// 2^32 = (approximately) 2^11 * 2^11 * 2^10
// If we don't want to have the same seed for two different
// points in space we have to write :
// seed = 2^11*2^11*nx + 2^11*ny + nz
// Even better, instead of 2^11*2^11 and 2^10, we could find
// prime numbers in those vicinities.

static vector _compute_random_vector (int nx, int ny, int nz)
{
    long seed = 2097013 * nx + 2039 * ny + nz;
    double x = my_rand (seed);
    double y = my_rand (seed + 1);
    double z = my_rand (seed + 2);
    vector v_rand = v_new(x,y,z);
    return v_unit (v_rand);
}

//-----------------------------------------------------------

static void _compute_random_vertex_vectors(vector p, vector * v_rand)
{
    int nx = (int) (floor (p.x));
    int ny = (int) (floor (p.y));
    int nz = (int) (floor (p.z));

    v_rand[PRLN_000] = _compute_random_vector (nx,     ny,     nz);
    v_rand[PRLN_100] = _compute_random_vector (nx + 1, ny,     nz);
    v_rand[PRLN_010] = _compute_random_vector (nx,     ny + 1, nz);
    v_rand[PRLN_110] = _compute_random_vector (nx + 1, ny+1,   nz);
    v_rand[PRLN_001] = _compute_random_vector (nx,     ny,     nz + 1);
    v_rand[PRLN_101] = _compute_random_vector (nx + 1, ny,     nz + 1);
    v_rand[PRLN_011] = _compute_random_vector (nx,     ny + 1, nz + 1);
    v_rand[PRLN_111] = _compute_random_vector (nx + 1, ny + 1, nz + 1);
}

//-----------------------------------------------------------

static double _scalar_noise(vector p, double frequency, double amplitude)
{
    vector random_vectors[8];
    double dot_products[8];

    vector lp = v_multiply (frequency, p);

    _compute_random_vertex_vectors (lp, random_vectors);
    _compute_dot_products (lp, random_vectors, dot_products);

    // double noise_value = amplitude*_scalarLinearInterpolate(lp,dot_products);
    double noise_value = amplitude * _scalar_cubic_interpolate(lp, dot_products);

    return noise_value;
}

//-----------------------------------------------------------

static vector _vector_noise(vector p, double frequency, double amplitude)
{
    vector random_vectors[8];
    vector cross_products[8];

    vector lp = v_multiply (frequency, p);

    _compute_random_vertex_vectors (lp, random_vectors);
    _compute_cross_products (lp, random_vectors, cross_products);
    vector noise_vector = _vector_linear_interpolate (lp, cross_products);
    return v_multiply (amplitude, noise_vector);
}

//-----------------------------------------------------------

// double prln_scalar_noise(vector p, double period, double amplitude, int nb_octaves, double lacunarity, double gain)
double prln_scalar_noise (vector p)
{
    double period = 0.25;
    double amplitude = 1.0;
    int nb_octaves = 1.0;
    double lacunarity = 2.0;
    double gain = 0.5;

    double noise_value = 0.0;

    double frequency = 1.0 / period;

    int noct;
    for (noct = 0; noct < nb_octaves; noct++)
    {
        noise_value += _scalar_noise (p, frequency, amplitude);
        frequency *= lacunarity;
        amplitude *= gain;
    }
    return noise_value;
}

//-----------------------------------------------------------

// vector prln_vectornoise(vector p, double period, double amplitude, int nb_octaves, double lacunarity, double gain)
vector prln_vector_noise (vector p)
{
    double period = 2.0;
    double amplitude = 0.35;
    int nb_octaves = 1.0;
    double lacunarity = 2.0;
    double gain = 0.5;

    vector noise_vector = v_new (0, 0, 0);

    double frequency = 1.0 / period;

    int noct;
    for (noct = 0; noct< nb_octaves; noct++)
    {
        vector tmp = v_add (noise_vector, _vector_noise (p, frequency, amplitude));
        noise_vector = tmp;
        frequency *= lacunarity;
        amplitude *= gain;
    }
    return noise_vector;
}
