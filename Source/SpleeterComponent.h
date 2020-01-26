/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "spleeter/spleeter.h"

#include <future>
#include <stack>
//[/Headers]

//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SpleeterComponent : public Component {
public:
  //==============================================================================
  SpleeterComponent();
  ~SpleeterComponent();

  //==============================================================================
  //[UserMethods]     -- You can add your own custom methods in this section.
  //[/UserMethods]

  void paint(Graphics &g) override;
  void resized() override;

private:
  void setSelectedFilePath(const String &path);
  void updateComponent();
  void split(spleeter::SeparationType type) const;

  //[UserVariables]   -- You can add your own custom variables in this section.
  TextButton open_button_;

  String selected_file_path_;
  Label selected_file_label_;

  TextButton split_two_stems_button_;
  TextButton split_four_stems_button_;
  TextButton split_five_stems_button_;
  
  mutable double progress_;
  ProgressBar progress_bar_;
  
  mutable std::stack<std::future<void>> processes_;
  //[/UserVariables]

  //==============================================================================

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpleeterComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
