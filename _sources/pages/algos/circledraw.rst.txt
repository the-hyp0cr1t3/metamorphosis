Circle draw algorithm
======================

The problem is to determine which pixels need to be colored to rasterize a circle, given its radius and centre.

The main idea is that when a curve passes between two pixels, the pixel that is closer is chosen. This is decided by the relative position of the curve with respect to the midpoint between the two pixels.

By virtue of symmetry, we can iterate through only an eigth of the circle to efficiently rasterize the circle in its entirety.

|pic1|      |pic2|

.. |pic1| image:: ../../images/circledraw1.jpeg
  :alt: Circle symmetry
  :width: 40%

.. |pic2| image:: ../../images/circledraw2.jpeg
  :alt: Circle draw algorithm
  :width: 45%

The `bresenham::figure::add_circle() <../code-reference/figure.html#_CPPv4N9bresenham6figure10add_circleE4uint4uint4uint>`__ method implements the same.