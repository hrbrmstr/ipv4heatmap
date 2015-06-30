#' @title A package to create curve heatmaps of IPv4 addresses
#' @description This package provides functions for taking a vector of
#' IPv4 addresses and building a Hilbert curve from them.
#' @name ipv4heatmap-package
#' @docType package
#' @useDynLib ipv4heatmap
#' @importFrom Rcpp sourceCpp
#' @import data.table
#' @import ggplot2
#' @import grid
#' @import RColorBrewer
#' @seealso \url{http://xkcd.com/195/},
#'          \url{http://en.wikipedia.org/wiki/Hilbert_curve},
#'          \url{http://maps.measurement-factory.com/}
NULL
