/*
  ==============================================================================

    SpleeterProcessor.h
    Created: 26 Jan 2020 5:21:53pm
    Author:  gvne

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "spleeter/spleeter.h"

void runSpleeter(const String &input_file, spleeter::SeparationType type,
                 const String &output_dir);
