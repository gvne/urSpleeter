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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "SpleeterComponent.h"
#include "Constants.h"
#include "SpleeterProcessor.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SpleeterComponent::SpleeterComponent() {
  //[Constructor_pre] You can add your own custom stuff here..
  //[/Constructor_pre]

  //[UserPreSize]
  //[/UserPreSize]

  setSize(600, 400);

  //[Constructor] You can add your own custom stuff here..
  addAndMakeVisible(&open_button_);
  open_button_.setButtonText("Open...");
  open_button_.onClick = [this]() {
    FileChooser chooser("Select a file to split...", {}, "*.wav;*.aiff", true);
    if (!chooser.browseForFileToOpen()) {
      return;
    }
    auto file_path = chooser.getResult().getFullPathName();
    setSelectedFilePath(file_path);
  };

  addAndMakeVisible(&selected_file_label_);
  selected_file_path_ = "";

  addAndMakeVisible(&split_two_stems_button_);
  split_two_stems_button_.setButtonText("Split into Two stems !");
  split_two_stems_button_.onClick =
      std::bind(&SpleeterComponent::split, this, spleeter::TwoStems);
  addAndMakeVisible(&split_four_stems_button_);
  split_four_stems_button_.setButtonText("Split into Four stems !");
  split_four_stems_button_.onClick =
      std::bind(&SpleeterComponent::split, this, spleeter::FourStems);
  addAndMakeVisible(&split_five_stems_button_);
  split_five_stems_button_.setButtonText("Split into Five stems !");
  split_five_stems_button_.onClick =
      std::bind(&SpleeterComponent::split, this, spleeter::FiveStems);

  updateComponent();
  //[/Constructor]
}

SpleeterComponent::~SpleeterComponent() {
  //[Destructor_pre]. You can add your own custom destruction code here..
  //[/Destructor_pre]

  //[Destructor]. You can add your own custom destruction code here..
  //[/Destructor]
}

//==============================================================================
void SpleeterComponent::paint(Graphics &g) {
  //[UserPrePaint] Add your own custom painting code here..
  //[/UserPrePaint]

  g.fillAll(Colour(0xff323e44));

  //[UserPaint] Add your own custom painting code here..
  //[/UserPaint]
}

void SpleeterComponent::resized() {
  //[UserPreResize] Add your own custom resize code here..
  auto area = getLocalBounds();
  auto element_width = getGridWidth(area.getWidth());

  // Open button
  Rectangle<int> open_button_area(element_width, 0, element_width * 2,
                                  element_width);
  open_button_area.setY(area.getHeight() / 2 -
                        open_button_area.getHeight() / 2);
  open_button_.setBounds(open_button_area);

  // Selected file label
  auto selected_file_label_area = open_button_area;
  selected_file_label_area.setX(open_button_area.getX() +
                                open_button_area.getWidth() + element_width);
  selected_file_label_area.setWidth(element_width * 5);
  selected_file_label_.setBounds(selected_file_label_area);

  // Split buttons
  auto split_four_stems_button_area = open_button_area;
  split_four_stems_button_area.setX(selected_file_label_area.getX() +
                                    selected_file_label_area.getWidth() +
                                    element_width);
  split_four_stems_button_area.setWidth(element_width * 3);
  split_four_stems_button_.setBounds(split_four_stems_button_area);
  auto split_two_stems_button_area = split_four_stems_button_area;
  split_two_stems_button_area.setY(split_two_stems_button_area.getY() -
                                   2 * element_width);
  split_two_stems_button_.setBounds(split_two_stems_button_area);
  auto split_five_stems_button_area = split_four_stems_button_area;
  split_five_stems_button_area.setY(split_five_stems_button_area.getY() +
                                    2 * element_width);
  split_five_stems_button_.setBounds(split_five_stems_button_area);
  //[/UserPreResize]

  //[UserResized] Add your own custom resize handling here..
  //[/UserResized]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any
// other code here...
void SpleeterComponent::setSelectedFilePath(const String &path) {
  selected_file_path_ = path;
  updateComponent();
}

void SpleeterComponent::updateComponent() {
  split_two_stems_button_.setEnabled(!selected_file_path_.isEmpty());
  split_four_stems_button_.setEnabled(!selected_file_path_.isEmpty());
  split_five_stems_button_.setEnabled(!selected_file_path_.isEmpty());
  if (selected_file_path_.isEmpty()) {
    selected_file_label_.setText("Select an audio file.",
                                 NotificationType::dontSendNotification);
    return;
  }
  selected_file_label_.setText(selected_file_path_,
                               NotificationType::dontSendNotification);
}

void SpleeterComponent::split(spleeter::SeparationType type) const {
  FileChooser chooser("Select an export folder");
  if (!chooser.browseForDirectory()) {
    return;
  }
  runSpleeter(selected_file_path_, type, chooser.getResult().getFullPathName());
}
//[/MiscUserCode]

//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SpleeterComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//[EndFile] You can add extra defines here...
//[/EndFile]
