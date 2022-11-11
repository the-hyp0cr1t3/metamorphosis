Line draw algorithm
===================

Given two pixel points on the screen, the problem is to determine which pixels need to be colored in between them to rasterize a straight line.

The essence of the algorithm is that if a line passes between two pixels, the pixel that is closer is chosen. This is decided by the relative position of the line with respect to the midpoint between the two pixels.

.. image:: ../../images/linedraw.jpeg
  :alt: Line draw algorithm
  :align: center

The `bresenham::figure::add_line() <../code-reference/figure.html#_CPPv4N9bresenham6figure8add_lineE4uint4uint4uint4uint>`__ method implements the same.