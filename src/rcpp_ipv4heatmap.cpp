#include <Rcpp.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <err.h>
#include <assert.h>
#include <math.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace Rcpp;

#include "ipv4-heatmap.h"

char *l2ip(unsigned long val) {
  char conv_ip[] = "               ";
  unsigned short o1, o2, o3, o4;
  o1 = (val & (0xff << 24)) >> 24;
  o2 = (val & (0xff << 16)) >> 16;
  o3 = (val & (0xff << 8)) >> 8;
  o4 = val & 0xff;
  sprintf(conv_ip, "%hu.%hu.%hu.%hu", o1, o2, o3, o4);
  return(strdup(conv_ip));
}

unsigned long ip2l(char *ip) {
  unsigned short o1, o2, o3, o4;
  sscanf(ip, "%hu.%hu.%hu.%hu", &o1, &o2, &o3, &o4 );
  return((unsigned long)( o1 << 24 ) | ( o2 << 16 ) | ( o3 << 8 ) | o4);
}

//' Character (dotted-decimal) IPv4 Address Conversion to long integer
//'
//' Convert IP addresses in character (dotted-decimal) notation to long integers
//'
//' @param ip input character vector of IPv4 addresses (dotted-decimal)
//' @return vector of equivalent long integer IP addresses
//' @export
//' @examples
//' ip2long("24.0.5.11")
//' ip2long(c("24.0.5.11", "211.3.77.96"))
//[[Rcpp::export]]
NumericVector ip2long (CharacterVector ip) {

  int ipCt = ip.size(); // how many elements in vector

  NumericVector ipInt(ipCt); // allocate new numeric vector

  // CONVERT ALL THE THINGS!
  for (int i=0; i<ipCt; i++) {
    ipInt[i] = ip2l(ip[i]);
  }

  return(ipInt);
}


//' Intger IPv4 Address Conversion to Character
//'
//' Converts IP addresses in long integer format to character (dotted-decimal)
//' notation
//'
//' @param ip input numeric (long integer) vector
//' @return vector of equivalent character (dotted-decimal) IP addresses
//' @export
//' @examples
//' long2ip(402654475)
//' long2ip(c(402654475, 3540208992))
//[[Rcpp::export]]
CharacterVector long2ip (NumericVector ip) {

  int ipCt = ip.size();

  CharacterVector ipStr(ipCt); // allocate new character vector

  // CONVERT ALL THE THINGS!
  for (int i=0; i<ipCt; i++) {
    ipStr[i] = l2ip((unsigned long)ip[i]);
  }

  return(ipStr);

}

//' IPv4 Hilbert Curve Matrix
//'
//' Returns a 4096x4096 Hilbert curve matrix for an input vector of IP
//' addresses. Generally not called directly (most of the time you'll want to
//' use \code{ipv4heatmap}), but avilable in the event another method of
//' visualization is necessary/desired.
//'
//' @param ip input numeric (dotted-deciman IPv4s) vector
//' @return 4096x4096 matrix, with non-0 entries being the count of IP addresses in that netblock
// [[Rcpp::export]]
NumericMatrix ipv4matrix_l(NumericVector ip) {

  unsigned int x;
  unsigned int y;

  // init hilbert stuff

  set_order() ;

  // make a matrix to hold our hilbert space & init to 0
  NumericMatrix ipmap(4096, 4096);
  std::fill(ipmap.begin(), ipmap.end(), 0);

  int ipCt = ip.size() ;
  for (int i=0; i<ipCt; i++) {

    if (0 != xy_from_ip(ip[i], &x, &y)) {
      ipmap(x, y) = ipmap(x, y) + 1;
    }

  }

  return(ipmap);

}


//' IPv4 Hilbert Curve Matrix
//'
//' Returns a 4096x4096 Hilbert curve matrix for an input vector of IP addresses. Generally not called directly (most of the time you'll want to use \code{ipv4heatmap}), but avilable in the event another method of visualization is necessary/desired.
//'
//' @param ip input character (dotted-deciman IPv4s) vector
//' @return 4096x4096 matrix, with non-0 entries being the count of IP addresses
//'         in that netblock
//' @export
//[[Rcpp::export]]
NumericMatrix ipv4matrix(CharacterVector ip) {

  unsigned int x;
  unsigned int y;

  // init hilbert stuff

  set_order() ;

  // make a matrix to hold our hilbert space & init to 0
  NumericMatrix ipmap(4096, 4096);
  std::fill(ipmap.begin(), ipmap.end(), 0);

  int ipCt = ip.size() ;
  for (int i=0; i<ipCt; i++) {

    if (0 != xy_from_ip(ip2l(ip[i]), &x, &y)) {
      ipmap(x, y) = ipmap(x, y) + 1;
    }

  }

  return(ipmap);

}

//' Bounding box from CIDR blocks
//'
//' Returns a \code{list} of bounding boxes for a given CIDR within the
//' Hilbert-curve plane
//'
//' @param cidr character vector of dotted-decimal/digit CIDRs
//' @return list of bounding box extents for each CIDR - \code{cidr},
//'         \code{xmin}, \code{ymin}, \code{xmax}, \code{ymax}
//' @export
//' @examples
//' boundingBoxFromCIDR("30.0.0.0/8")
//[[Rcpp::export]]
List boundingBoxFromCIDR(CharacterVector cidr) {

    bbox bbox;

    int cidrCt = cidr.size() ;

    List boxes(cidrCt) ;

    for (int i=0; i<cidrCt; i++) {

       bbox = bbox_from_cidr(cidr[i]);

       boxes[i] = List::create(
                          Rcpp::Named("cidr") = Rcpp::as<std::string>(cidr[i]),
                          Rcpp::Named("xmin") = bbox.xmin,
                          Rcpp::Named("ymin") = bbox.ymin,
                          Rcpp::Named("xmax") = bbox.xmax,
                          Rcpp::Named("ymax") = bbox.ymax
                          );

    }

    return(boxes);
}























