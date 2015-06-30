<!-- README.md is generated from README.Rmd. Please edit that file -->
ipv4heatmap : Generate Hilbert Curve Heatmaps from IPv4 Address Lists

The following functions are implemented:

-   `boundingBoxFromCIDR`: Bounding box from CIDR blocks
-   `ip2long`: Character (dotted-decimal) IPv4 Address Conversion to long integer
-   `ipv4heatmap`: Create an IPv4 Hilbert curve heatmap
-   `ipv4matrix`: IPv4 Hilbert Curve Matrix
-   `long2ip`: Intger IPv4 Address Conversion to Character

### News

-   0.2.0.999 - No longer requires Boost libraries, passes CRAN checks

### Installation

``` r
devtools::install_github("hrbrmstr/ipv4heatmap")
```

### Usage

``` r
library(ipv4heatmap)

# current verison
packageVersion("ipv4heatmap")
#> [1] '0.2.0.9000'

(ip2long(c( "105.212.209.72", "115.126.247.136")))
#> [1] 1775554888 1937700744

(long2ip(c(1775554888, 1937700744)))
#> [1] "105.212.209.72"  "115.126.247.136"

(boundingBoxFromCIDR("30.0.0.0/8"))
#> [[1]]
#> [[1]]$cidr
#> [1] "30.0.0.0/8"
#> 
#> [[1]]$xmin
#> [1] 1024
#> 
#> [[1]]$ymin
#> [1] 512
#> 
#> [[1]]$xmax
#> [1] 1279
#> 
#> [[1]]$ymax
#> [1] 767

# get and plot some IPs from ZeusTracker
loc <- tempfile()
download.file("https://zeustracker.abuse.ch/blocklist.php?download=badips", 
              loc, method="curl")
ips <- grep("^#", readLines(loc), invert=TRUE, value=TRUE)
unlink(loc)

hm <- ipv4heatmap(ips)

hm$gg
```

![](README-usage-1.png)

### Code of Conduct

Please note that this project is released with a [Contributor Code of Conduct](CONDUCT.md). By participating in this project you agree to abide by its terms.
