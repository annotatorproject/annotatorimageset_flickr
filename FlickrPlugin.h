// Copyright 2017 Annotator Team

#ifndef FLICKRPLUGIN_H
#define FLICKRPLUGIN_H

#include <AnnotatorLib/ImageSet/ImageSetPlugin.h>

class FlickrPlugin : public AnnotatorLib::ImageSet::ImageSetPlugin {
 public:
  FlickrPlugin();

  virtual const std::string name() override { return "flickr"; }
  virtual const std::string description() override {
    return "Flickr Image Set";
  }

  virtual std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet> create(
      std::string path) override;
};

#endif  // FLICKRPLUGIN_H
