ipv4heatmap
===========

IPv4 Hilbert curve heatmap package for R

Rcpp-backed package for making Hilbert IPv4 space heatmaps in R. The C/C++ code is heavily based on the work of [The Measurement Factory](http://maps.measurement-factory.com/).

(NOTE: you'll need to `brew install boost`, use some other package manager, or manually install the [boost library](http://www.boost.org/))

### News

- Version `0.2.5` adds the ability to pass a numeric vector instead of a character vector to the main function
- Version `0.2` fixes a bug where the resultant plot might not be 4096x4096 and also removes the last of the ggplot2 border artifacts

### Installation

    if (!require("devtools")) install.packages("devtools")
    devtools::install_github("vz-risk/ipv4heatmap")

### Sample Usage

    library(ipv4heatmap)
    library(data.table)
    require(ggplot2)

    # read in a list of IPs (you'll have to find one on your own :-)
    # using fread() and data.table since this particular database has 
    # a ton of them.
    
    dat <- fread("2014-03-01.csv")
    setkey(dat, ipaddr)

    # build the heatmap
    hm <- ipv4heatmap(dat$ipaddr)

    # plot the heatmap (not shown)
    hm$gg

    # read in a list of CIDRs that are in China because, well, CHINA!
    china <- read.table("http://dds.ec/data/chinacidr.txt", header=FALSE)

    # generate the bounding boxes for them
    boxes <- ldply(boundingBoxFromCIDR(china$V1), data.frame)

    # overlay the bounding boxes for China onto the IPv4 addresses we read in and Hilbertized
    hm$gg + geom_rect(data=boxes, aes(xmin=xmin, ymin=ymin, xmax=xmax, ymax=ymax), fill="white", alpha=0.1)
    
![img](https://farm3.staticflickr.com/2895/14600640420_463624bfc3_o.png)
