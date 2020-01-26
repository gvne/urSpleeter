/*
  ==============================================================================

    Constants.h
    Created: 26 Jan 2020 10:36:08am
    Author:  gvne

  ==============================================================================
*/

#pragma once

// The number of elements in a component row
const unsigned int kGridElementCount = 20;

inline unsigned int getGridWidth(int component_width) {
  return component_width / kGridElementCount;
}
