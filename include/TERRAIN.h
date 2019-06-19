#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <cstdlib>
#include <iostream>
#include <math.h>

class TERRAIN {
public:
  // constructor
  TERRAIN (unsigned int w, unsigned int l);
  // destructor
  ~TERRAIN ();
  // generates the initial terrain
  // adds on to the existing terrain based on directional conditions
  void createPlane(int offsetX, int offsetZ);
  // generates the random heights for the terrain based on x and z
  float generateHeight(int x, int z, int offsetX, int offsetZ);
  // make the terrain bumpier
  void increasePeaks();
  // make the terrain less bumpy
  void decreasePeaks(); 
  // vertices
  std::vector<float> vertices;
  // indices
  std::vector<unsigned int> vertIndices;
  // initial dimensions of terrain
  unsigned int width;
  unsigned int length;

private:
  // see for random numbers
  int seed;
  // peaks of terrain
  float AMPLITUDE;
  // runs over terrain
  // more runs increases smoothness
  float LEVELS;
  // decreasing smooths out terrain for each level
  float ROUGHNESS;
  // generates the random numbers based on x, z
  float getNoise(int x, int z);
  // smooths out areas based on position
  float getSmoothNoise(int x, int z);
  // creates curves between points
  float interpolate(float a, float b, float c);
  // looks at nearby coordinates to create heights
  float getInterpolatedNoise(float x, float z);
};

#endif
