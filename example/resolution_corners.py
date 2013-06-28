from __future__ import division
from __future__ import print_function

#!/usr/bin/env python
# resolution_corners.py
#
#   Copyright (C) 2013 Diamond Light Source, Graeme Winter
#
#   This code is distributed under the BSD license, a copy of which is
#   included in the root directory of this package.
#
# Print out the resolution (two-theta) of the corners of the detector


def resolution_corners(sweep):
    """Compute the resolution limit corresponding to the corners of the detector
    surface."""

    import math
    from scitbx import matrix

    detector = sweep.get_detector()
    beam = sweep.get_beam()

    nfast, nslow = map(int, detector.get_image_size())
    dfast, dslow = detector.get_pixel_size()
    F = matrix.col(detector.get_fast_axis())
    S = matrix.col(detector.get_slow_axis())
    origin = matrix.col(detector.get_origin())

    s0 = -1 * matrix.col(beam.get_direction())

    for ds in 0, 1:
        for df in 0, 1:
            corner = origin + nfast * dfast * F * df + nslow * dslow * S * ds
            theta = 0.5 * corner.angle(s0)
            print("%.3f" % (beam.get_wavelength() / (2 * math.sin(theta))))


if __name__ == "__main__":

    import sys
    from dxtbx.imageset import ImageSetFactory

    sweeps = ImageSetFactory.new(sys.argv[1:])
    resolution_corners(sweeps[0])
