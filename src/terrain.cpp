// Source: notes, https://www.youtube.com/watch?v=qChQrNWU9Xw,
//         https://gamedev.stackexchange.com/questions/78014/how-to-create-a-regular-grid-of-triangles-correctly
#include "TERRAIN.h"

// constructor
TERRAIN::TERRAIN(unsigned int w, unsigned int l): width(w), length(l) {
  // set seed
  seed = rand() % 1000000;

  // set constants
  AMPLITUDE = 15.0f;
  LEVELS = 4.0f;
  ROUGHNESS = 0.3f;
}

// destructor
TERRAIN::~TERRAIN() {
}

// generates the random numbers based on x, z
// returns a number between -1 and 1
float TERRAIN::getNoise(int x, int z) {
  return ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
}

// smooths out areas based on position
// prevents terrain from being too jagged
float TERRAIN::getSmoothNoise(int x, int z) {
  // random numbers offset seed to create larger differences in values
  srand(x * 49632 + z * 325176 + seed);
  // based on x, z as center
  float center = getNoise(x, z) / 10.0f;
  float corners = (getNoise(x - 1, z - 1) + getNoise(x + 1, z - 1)
    + getNoise(x - 1, z + 1) + getNoise(x + 1, z + 1)) / 10.0f;
  // midpoints between corners
  float sides = (getNoise(x - 1, z) + getNoise(x + 1, z) + getNoise(x, z - 1)
    + getNoise(x, z + 1)) / 10.0f;
  return center + corners + sides;
}

// creates curves between points
 float TERRAIN::interpolate(float a, float b, float c) {
   double i = c * M_PI;
   float curve = (float)(1.0f - cos(i)) * 0.5f; // value between 0 and 1
   return a * (1.0f - curve) + b * curve; // linear interpolation formula
}

// looks at nearby coordinates to create heights
float TERRAIN::getInterpolatedNoise(float x, float z) {
  int intX = (int) x;
  int intZ = (int) z;
  float decimalX = x - intX;
  float decimalZ = z - intZ;
  // heights of 4 points nearest to given position x, z
  float v1 = getSmoothNoise(intX, intZ);
  float v2 = getSmoothNoise(intX + 1, intZ);
  float v3 = getSmoothNoise(intX, intZ + 1);
  float v4 = getSmoothNoise(intX + 1, intZ + 1);
  // gives heights at 2 new points between v1, v2 and v3, v4
  float i1 = interpolate(v1, v2, decimalX);
  float i2 = interpolate(v3, v4, decimalX);
  // interpolated height at x, z based off of nearby interpolated height
  return interpolate(i1, i2, decimalZ);
}

// generates the random heights for the terrain based on x and z
float TERRAIN::generateHeight(int x, int z, int offsetX, int offsetZ) {
  x = x + 1000000;
  z = z + 1000000;
  float height = 0;
  float d = (float)pow(2, LEVELS - 1);
  // for each level creates more detail between points of terrain
  for(int i = 0; i < LEVELS; i++) {
     float freq = (float)(pow(2, i) / d);
     float amp = (float)pow(ROUGHNESS, i) * AMPLITUDE;
     // since the random heights are based on position, the offset allows us to shift
     // the height to a new position that's offset-distance away from its original point
     height += getInterpolatedNoise((x + offsetX) * freq, ((z + offsetZ) * freq)) * amp;
  }
  return height;
}

// make the terrain bumpier
void TERRAIN::increasePeaks() {
  if (AMPLITUDE <= 100) {
    AMPLITUDE = AMPLITUDE + 0.5f;
  }
}

// make the terrain less bumpy
void TERRAIN::decreasePeaks() {
  if (AMPLITUDE >= 0) {
    AMPLITUDE = AMPLITUDE - 0.5f;
  }
}

// create the vertices and indices that make up the flat triangle grid
void TERRAIN::createPlane(int offsetX, int offsetZ) {
  // vertices
  vertices.clear();
  for (unsigned int i = 0; i < width; i++) {
    for(unsigned int j = 0; j < length; j++) {
      vertices.push_back((i / 10.0f));
      vertices.push_back(generateHeight(i, j, offsetX, offsetZ) / 10.0f);
      vertices.push_back(-(j / 10.0f));
    }
  }
  // indices
  vertIndices.clear();
  for (unsigned int i = 0; i < length - 1; i++) {
    for(unsigned int j = 0; j < width - 1; j++) {
      vertIndices.push_back(j + (i * length));
      vertIndices.push_back(j + (i * length) + 1);
      vertIndices.push_back(j + (i * length) + width);

      vertIndices.push_back(j + (i * length) + 1);
      vertIndices.push_back(j + (i * length) + width);
      vertIndices.push_back(j + (i * length) + 1 + width);
    }
  }
}
