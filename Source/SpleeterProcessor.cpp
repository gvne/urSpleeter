

/*
  ==============================================================================

    SpleeterProcessor.cpp
    Created: 26 Jan 2020 5:21:53pm
    Author:  gvne

  ==============================================================================
*/

#include "SpleeterProcessor.h"
#include "ResourceFolder.h"

spleeter::Waveform forceStereo(const Eigen::MatrixXf &data) {
  if (data.rows() == 2) {
    return data;
  }
  // make the mean over rows
  auto mean = data.array().rowwise().sum() / data.rows();

  // duplicate it twice to get stereo
  spleeter::Waveform output(2, data.cols());
  output.row(0) = mean;
  output.row(1) = mean;
  return output;
}

spleeter::Waveform read(const String &file, double *sample_rate,
                        std::error_code &err) {
  AudioFormatManager formatManager;
  formatManager.registerBasicFormats();
  auto reader = std::make_unique<AudioFormatReaderSource>(
      formatManager.createReaderFor(file), true);
  auto sample_reader = reader->getAudioFormatReader();
  *sample_rate = sample_reader->sampleRate;
  Eigen::MatrixXf data(sample_reader->numChannels,
                       sample_reader->lengthInSamples);

  // Alloc data
  std::vector<float *> array_data;
  std::vector<std::vector<float>> vec_data;
  for (auto channel_idx = 0; channel_idx < sample_reader->numChannels;
       channel_idx++) {
    std::vector<float> channel_data(sample_reader->lengthInSamples);
    array_data.push_back(channel_data.data());
    vec_data.emplace_back(std::move(channel_data));
  }
  // Read
  if (!sample_reader->read(array_data.data(), sample_reader->numChannels, 0,
                           static_cast<int>(sample_reader->lengthInSamples))) {
    err = std::make_error_code(std::errc::io_error);
    return spleeter::Waveform();
  }

  // Fill in waveform
  for (auto channel_idx = 0; channel_idx < data.rows(); channel_idx++) {
    data.row(channel_idx) = Eigen::Map<Eigen::VectorXf>(
        vec_data[channel_idx].data(), vec_data[channel_idx].size());
  }

  return forceStereo(data);
}

void resample(spleeter::Waveform &source, double original, double desired) {
  if (desired == original) {
    return;
  }

  LagrangeInterpolator interpolator;
  auto speed_ratio = desired / original;

  spleeter::Waveform output(
      2, static_cast<int>(floor(source.cols() * speed_ratio + 1)));

  Eigen::VectorXf input_channel(source.cols());
  Eigen::VectorXf output_channel(output.cols());
  for (auto channel_idx = 0; channel_idx < source.rows(); channel_idx++) {
    interpolator.process(speed_ratio, input_channel.data(),
                         output_channel.data(), output_channel.cols());
    output.row(channel_idx) = output_channel;
  }

  source = output;
}

void write(const String &output_path, const spleeter::Waveform &data) {
  File output_file(output_path);
  ;
  WavAudioFormat format;
  auto writer = std::unique_ptr<AudioFormatWriter>(
      format.createWriterFor(output_file.createOutputStream(), 44100,
                             data.rows(), 16, StringPairArray(), 0));

  AudioSampleBuffer buffer(data.rows(), data.cols());
  for (auto channel_idx = 0; channel_idx < data.rows(); channel_idx++) {
    Eigen::VectorXf row = data.row(channel_idx);
    buffer.copyFrom(channel_idx, 0, row.data(), data.cols());
  }
  writer->writeFromAudioSampleBuffer(buffer, 0, data.cols());
}

void runSpleeter(const String &input_file, spleeter::SeparationType type,
                 const String &output_dir) {
  std::error_code err;
  double sample_rate;
  auto data = read(input_file, &sample_rate, err);
  if (err) {
    // TODO: deal with error
    return;
  }

  spleeter::Initialize(getResourcesPath() + "/models", {type}, err);
  if (err) {
    // TODO: deal with error
    return;
  }

  resample(data, sample_rate, 44100);

  spleeter::Waveform vocals, accompaniment, drums, bass, piano, other;
  switch (type) {
  case spleeter::TwoStems:
    spleeter::Split(data, &vocals, &accompaniment, err);
    write(output_dir + "/vocals.wav", vocals);
    write(output_dir + "/accompaniment.wav", accompaniment);
    break;
  case spleeter::FourStems:
    spleeter::Split(data, &vocals, &drums, &bass, &other, err);
    write(output_dir + "/vocals.wav", vocals);
    write(output_dir + "/drums.wav", drums);
    write(output_dir + "/bass.wav", bass);
    write(output_dir + "/other.wav", other);
    break;
  case spleeter::FiveStems:
    spleeter::Split(data, &vocals, &drums, &bass, &piano, &other, err);
    write(output_dir + "/vocals.wav", vocals);
    write(output_dir + "/drums.wav", drums);
    write(output_dir + "/bass.wav", bass);
    write(output_dir + "/piano.wav", piano);
    write(output_dir + "/other.wav", other);
    break;
  default:
    err = std::make_error_code(std::errc::not_supported);
    break;
  }
}
