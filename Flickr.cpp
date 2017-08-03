// Copyright 2017 Annotator Team

#define Annotator_AnnotatorLib_Flickr_BODY

/************************************************************
 ImageFolder class body
 ************************************************************/

// include associated header file

#include "Flickr.h"

#include <set>
#include <sstream>

#include <Poco/Net/DNS.h>
#include <Poco/URI.h>
#include <opencv2/opencv.hpp>

#include <Poco/JSON/Handler.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/StreamCopier.h>

// Derived includes directives

namespace AnnotatorLib {
namespace ImageSet {

Flickr::Flickr(std::string path) {
  this->path = path;
  initFlickr();
}

ImageSetType Flickr::getType() { return ImageSetType::UNKNOWN; }

Image Flickr::getImage(unsigned long position) {
  Image img;
  try {
    if (position < urls.size()) img = urlToImage(urls[position]);
  } catch (std::exception &e) {
  }
  return img;
}

std::string Flickr::getImagePath(unsigned long) { return ""; }

bool Flickr::gotoPosition(unsigned long) {
  if (urls.size() < position) return false;
  this->position = position;
  return true;
}

long Flickr::getPosition() { return position; }

bool Flickr::hasNext() {
  if (urls.size() < position) return false;
  this->position = position;
  return true;
}

Image Flickr::next() {
  Image img;
  img = getImage(position);
  position++;
  return img;
}

unsigned int Flickr::size() { return this->urls.size(); }

unsigned int Flickr::getFPS() { return 10; }

std::string Flickr::getPath() { return path; }

bool Flickr::equals(std::shared_ptr<AbstractImageSet> other) {
  if (this == other.get()) return true;
  if (other->getType() != ImageSetType::CAMERA) return false;
  if (this->getPath() != other->getPath()) return false;
  return true;
}

void Flickr::initFlickr() { search(); }

void Flickr::search() {
  Poco::URI uri(path);
  Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
  Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET,
                             uri.getPathAndQuery());
  session.sendRequest(req);
  Poco::Net::HTTPResponse res;
  std::istream &iStr = session.receiveResponse(res);
  std::string jsonStr;
  Poco::StreamCopier::copyToString(iStr, jsonStr);
  parseSearchResponse(jsonStr);
}

void Flickr::parseSearchResponse(std::string jsonStr) {
  Poco::JSON::Parser parser;
  parser.parse(jsonStr);
  Poco::Dynamic::Var result = parser.result();
  Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();
  Poco::JSON::Object::Ptr photos = json->getObject("photos");
  Poco::JSON::Array::Ptr array = photos->getArray("photo");
  for (std::size_t i = 0; i < array->size(); ++i) {
    Poco::JSON::Object::Ptr value = array->getObject(i);
    int farm = value->get("farm").extract<int>();
    std::string server = value->get("server").extract<std::string>();
    std::string id = value->get("id").extract<std::string>();
    std::string secret = value->get("secret").extract<std::string>();
    std::stringstream imageUrl;
    imageUrl << "http://farm" << farm << ".staticflickr.com/" << server << "/"
             << id << "_" << secret << "_n.jpg";
    this->urls.push_back(imageUrl.str());
  }
}

Image Flickr::urlToImage(std::string url) {
  Poco::URI uri(url);
  Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
  Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET,
                             uri.getPathAndQuery());
  session.sendRequest(req);
  Poco::Net::HTTPResponse res;
  std::istream &iStr = session.receiveResponse(res);
  std::string imageStr;
  Poco::StreamCopier::copyToString(iStr, imageStr);
  std::vector<uchar> vec(imageStr.begin(), imageStr.end());
  Image img;
  img = cv::imdecode(vec, cv::IMREAD_ANYCOLOR);
  return img;
}

// static attributes (if any)
}  // of namespace ImageSet
}  // of namespace AnnotatorLib

/************************************************************
 End of ImageFolder class body
 ************************************************************/
