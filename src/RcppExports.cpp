// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// ip2long
NumericVector ip2long(CharacterVector ip);
RcppExport SEXP ipv4heatmap_ip2long(SEXP ipSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< CharacterVector >::type ip(ipSEXP );
        NumericVector __result = ip2long(ip);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// long2ip
CharacterVector long2ip(NumericVector ip);
RcppExport SEXP ipv4heatmap_long2ip(SEXP ipSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< NumericVector >::type ip(ipSEXP );
        CharacterVector __result = long2ip(ip);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
// ipv4matrix
NumericMatrix ipv4matrix(CharacterVector ip);
RcppExport SEXP ipv4heatmap_ipv4matrix(SEXP ipSEXP) {
BEGIN_RCPP
    SEXP __sexp_result;
    {
        Rcpp::RNGScope __rngScope;
        Rcpp::traits::input_parameter< CharacterVector >::type ip(ipSEXP );
        NumericMatrix __result = ipv4matrix(ip);
        PROTECT(__sexp_result = Rcpp::wrap(__result));
    }
    UNPROTECT(1);
    return __sexp_result;
END_RCPP
}
