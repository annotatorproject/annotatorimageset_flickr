// Copyright 2017 Annotator Team

#include "FlickrPlugin.h"
#include "Flickr.h"

#include <Poco/ClassLibrary.h>

FlickrPlugin::FlickrPlugin() {}

std::shared_ptr<AnnotatorLib::ImageSet::AbstractImageSet> FlickrPlugin::create(
    std::string path) {
  return std::make_shared<AnnotatorLib::ImageSet::Flickr>(path);
}

ANNOTATORLIB_API POCO_BEGIN_MANIFEST(AnnotatorLib::ImageSet::ImageSetPlugin)
    POCO_EXPORT_CLASS(FlickrPlugin) POCO_END_MANIFEST
