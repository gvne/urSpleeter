/*
  ==============================================================================

    ResourceFolder_osx.mm
    Created: 26 Jan 2020 5:16:27pm
    Author:  gvne

  ==============================================================================
*/

#include "ResourceFolder.h"
#import <Foundation/Foundation.h>

std::string getResourcesPath() {
  return std::string([[[NSBundle mainBundle] resourcePath] UTF8String]);
}
