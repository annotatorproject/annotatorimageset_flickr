// Copyright 2017 Annotator Team

#ifndef ANNOTATOR_ANNOTATORLIB_FLICKR_H
#define ANNOTATOR_ANNOTATORLIB_FLICKR_H

/************************************************************
 ImageFolder class header
 ************************************************************/

#include "AnnotatorLib/ImageSet/AbstractImageSet.h"

#include <string>
#include <vector>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <opencv2/opencv.hpp>

namespace AnnotatorLib {
namespace ImageSet {
/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API Flickr : public AbstractImageSet {
 public:
  Flickr(std::string path);

  /**
   *
   * @return type
   */
  virtual ImageSetType getType() override;

  /**
   *
   * @param frame
   * @return image
   */
  virtual Image getImage(unsigned long position) override;

  virtual std::string getImagePath(unsigned long /* frame */) override;

  virtual bool gotoPosition(unsigned long /* position */) override;

  virtual long getPosition() override;

  /**
   *
   * @return next
   */
  virtual bool hasNext() override;

  /**
   *
   * @return image
   */
  virtual Image next() override;

  /**
   *
   * @return size
   */
  virtual unsigned int size() override;

  virtual unsigned int getFPS() override;

  virtual std::string getPath() override;

  virtual bool equals(std::shared_ptr<AbstractImageSet> other) override;

 protected:
  void initFlickr();
  void search();
  void parseSearchResponse(std::string jsonStr);
  Image urlToImage(std::string url);

  long position = 0;
  std::string path;

  std::vector<std::string> urls;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */
}  // of namespace ImageSet
}  // of namespace AnnotatorLib

/************************************************************
 End of Camera class header
 ************************************************************/

#endif
